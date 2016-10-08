from _sox import ffi as _ffi, lib as _sox

__soxversion__ = _ffi.string(_sox.sox_version())

init = _sox.sox_init
quit = _sox.sox_quit


class SoXException(Exception):
    pass

def find_effect(effect):
    soxeff_h = _sox.sox_find_effect(effect)
    raise SoXException("Effect '%s' not found" % effect)


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
        

class SoXFile:
    def __init__(self, file):
        self._file = sox_open_read(file)
