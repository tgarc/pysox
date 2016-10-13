#!/usr/bin/env python
import os, sys
import numpy as np
import pysox


def _parser():
    from argparse import Action, ArgumentParser, RawDescriptionHelpFormatter

    class ListEffectsAction(Action):
        def __call__(*args, **kwargs):
            for name in pysox.effects:
                print name
            sys.exit(0)

    class ShowUsageAction(Action):
        def __call__(self, parser, namespace, effect, option_string=None):
            seh = pysox.find_effect(effect)
            usg = seh.usage
            print pysox._ffi.string(seh.name), pysox._ffi.string(usg) if usg != pysox.NULL else ''
            sys.exit(0)
            
    parser = ArgumentParser(formatter_class=RawDescriptionHelpFormatter,
                            description=__doc__)

    parser.add_argument("input")
    parser.add_argument("output")
    parser.add_argument("-l", "--list", nargs=0, action=ListEffectsAction)
    parser.add_argument('-u', "--usage", metavar='effect', action=ShowUsageAction)
    parser.add_argument('-v', "--verbosity", action='count', default=0)

    rawfile = parser.add_argument_group("Input file format specifications used for headerless input files")

    rawfile.add_argument("-t", dest="file_type", 
                        help="Input file type. Typically this is determined from the file extension, but it can be manually overriden here.")

    # rawfile.add_argument("--endian", choices=['file', 'big', 'little'], default='file', type=str.upper, 
    #                     help="Defaults to system endianness (i.e. 'file').")

    # rawfile.add_argument("-e", "--encoding", action='append', type=str.upper,
    #                     help="Sample format encoding.")

    rawfile.add_argument("-b", "--bit-depth", choices=[8,16,24,32], type=int, default=0,
                         help="Sample bit width.")

    rawfile.add_argument("-r", "--rate", type=lambda x: int(float(x[:-1])*1000) if x.endswith('k') else int(x),
                         default=0,
                         help="Sample rate in Hz. Add a 'k' suffix to specify kHz.")

    rawfile.add_argument("-c", "--channels", type=int, default=0, help="Number of channels.")

    return parser

def main(argv=None):
    parser = _parser()

    args = parser.parse_args(argv)

    print "Using SoX v%s" % pysox.__soxversion__

    assert pysox.init() == 0

    pysox.set_verbosity(args.verbosity)

    # import pdb; pdb.set_trace()

    inpfh = pysox.SoXFile(args.input)
    outfh = pysox.SoXFile(args.output, 'w',
                          rate=inpfh.rate,
                          channels=inpfh.channels,
                          precision=inpfh.precision,
                          filetype=inpfh.filetype)

    wav = np.frombuffer(inpfh.read(), dtype='i4')

    # sec = pysox.EffectChain(inpfh, outfh)
    # # sec.add_effect('vol', '3db')
    # sec.flow()

    inpfh.close()
    outfh.close()

    assert pysox.quit() == 0


if __name__ == '__main__':
    sys.exit(main())
    
