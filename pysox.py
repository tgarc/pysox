from array import array
from _sox import ffi as _ffi, lib as _sox


NULL = _ffi.NULL

__soxversion__ = _ffi.string(_sox.sox_version())

effects = ('allpass',
           'band',
           'bandpass',
           'bandreject',
           'bass',
           'bend',
           'biquad',
           'chorus',
           'channels',
           'compand',
           'contrast',
           'dcshift',
           'delay',
           'dither',
           'downsample',
           'echo',
           'echos',
           'equalizer',
           'fade',
           'fir',
           'firfit',
           'flanger',
           'gain',
           'highpass',
           'hilbert',
           'ladspa',
           'loudness',
           'lowpass',
           'mcompand',
           'mixer',
           'noiseprof',
           'noisered',
           'norm',
           'overdrive',
           'pad',
           'phaser',
           'pitch',
           'rate',
           'remix',
           'repeat',
           'reverb',
           'silence',
           'sinc',
           'spectrogram',
           'speed',
           'splice',
           'stat',
           'stats',
           'stretch',
           'synth',
           'tempo',
           'treble',
           'tremolo',
           'trim',
           'upsample',
           'vad',
           'vol')

_sox_error = ['SOX_SUCCESS',
             'SOX_EOF',
             'SOX_EHDR',
             'SOX_EFMT',
             'SOX_ENOMEM',
             'SOX_EPERM',
             'SOX_ENOTSUP',
             'SOX_EINVAL']

_sox_error = dict( [(k, getattr(_sox, k)) for k in _sox_error] )


init = _sox.sox_init
quit = _sox.sox_quit

class SoXException(Exception):
    def __init__(self, msg, retcode=None):
        if retcode is not None:
            msg = "[Error Code %d] %s" % (retcode, msg)
        super(SoXException, self).__init__(msg)        

class SoXFileException(Exception):
    def __init__(self, file, msg=''):
        errmsg = "[Error Code %d] %s (%s)" % (file.sox_errno, msg, _ffi.string(file.sox_errstr))
        super(SoXException, self).__init__(errmsg)

def set_verbosity(level):
    glob = _sox.sox_get_globals()
    glob.verbosity = level

def find_effect(effect):
    soxeff_h = _sox.sox_find_effect(effect)

    if soxeff_h == _ffi.NULL:
        raise SoXException("Effect '%s' not found" % effect)

    return soxeff_h

def get_effects():
    soxeff_h_funcs = _sox.sox_get_effect_fns()

    i = 0
    sehf = soxeff_h_funcs[0]
    while sehf != _ffi.NULL:
        seh = sehf()

        if seh.name != _ffi.NULL and seh.usage != _ffi.NULL:
            yield _ffi.string(seh.name), _ffi.string(seh.usage)

        i += 1
        sehf = soxeff_h_funcs[i]

@_ffi.def_extern()
def overwrite_permitted(filename):
    return True


class SoXFile:
    def __init__(self, filename, mode='r', rate=0, channels=0, precision=0, length=-1, filetype=None):
        siginf = dict(rate=rate,
                      channels=channels,
                      precision=precision,
                      length=_ffi.cast("sox_uint64_t", length),
                      mult=_ffi.NULL)
        self._siginf = _ffi.new('sox_signalinfo_t *', siginf)

        if 'r' in mode:
            # self._file = _sox.sox_open_read(filename, self._siginf, _ffi.NULL, filetype or _ffi.NULL)
            self._file = _sox.sox_open_read(filename, _ffi.NULL, _ffi.NULL, filetype or _ffi.NULL)
        elif 'w' in mode:
            self._file = _sox.sox_open_write(filename, self._siginf, _ffi.NULL, filetype or _ffi.NULL,
                                             _ffi.NULL, _sox.overwrite_permitted)

        if self._file == _ffi.NULL:
            raise SoXException("Failed to open file '%s'" % filename)

        self.name = filename

    @property
    def rate(self):      return self._file.signal.rate

    @property
    def channels(self):  return self._file.signal.channels

    @property
    def precision(self): return self._file.signal.precision

    @property
    def length(self):    return self._file.signal.length

    @property
    def filetype(self):  return _ffi.string(self._file.filetype)

    @property
    def mode(self):      return self._file.mode

    def tell(self):      return self._file.tell_off

    def seek(self, pos):
        if not self._file.seekable:
            raise SoXException("File seek not supported")
        self._file.seek(pos)

    def close(self):
        retcode = _sox.sox_close(self._file)
        if retcode != 0:
            raise SoXException("Failed to close file '%s'" % self.name, retcode)

    def __repr__(self):
        repr = "SoXFile(mode='{0.mode}', rate={0.rate}, channels={0.channels}, length={0.length}, filetype='{0.filetype}')"
        return repr.format(self)

    def __del__(self):
        self.close()


@_ffi.def_extern()
def _flow_effects_c_callback(all_done, data):
    data = _ffi.from_handle(data)
    return _sox.SOX_SUCCESS


class EffectChain:
    def __init__(self, inpf, outf):
        self._inpf = inpf._file
        self._outf = outf._file
        self._effects = []
        self._cbdata = _ffi.NULL
        self._sec = _sox.sox_create_effects_chain(_ffi.addressof(self._inpf.encoding),
                                                  _ffi.addressof(self._outf.encoding))

        fstr = _ffi.string(self._inpf.filename)
        self.add_effect(b'input', [fstr])

    def add_effect(self, effect, args=None):
        seh = find_effect(effect)
        se = _sox.sox_create_effect(seh)

        if args is None:
            nargs = 0
            argv = _ffi.NULL
        else:
            nargs = len(args)
            argp = [_ffi.new("char[]", a) for a in args]
            argv = _ffi.new("char * const []", argp)

        retcode = _sox.sox_effect_options(se, nargs, argv)

        if retcode != 0:
            raise SoXException("Failed to set parameters for effect '%s'" % effect, retcode)

        retcode = _sox.sox_add_effect(self._sec, se, self._inpf.signal, self._outf.signal)

        if retcode != 0:
            raise SoXException("Failed to add effect '%s'" % effect, retcode)

        self._effects.append(se)

    def flow(self):
        self._cbdata = _ffi.new_handle(self)
        self.add_effect('output', [_ffi.string(self._outf.filename)])
        _sox.sox_flow_effects(self._sec, _sox._flow_effects_c_callback, self._cbdata)

    def __del__(self):
        _sox.sox_delete_effects_chain(self._sec)
