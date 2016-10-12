#!/usr/bin/env python
import os
import ctypes.util
from cffi import FFI as _FFI

_ffi = _FFI()


with open(os.path.join(os.path.dirname(__file__), 'sox.h')) as soxh:
    _ffi.set_source('_sox', '''\
#include <sox.h>
''',
                    libraries=["sox"])
    _ffi.cdef(soxh.read())

if __name__ == '__main__':
    _ffi.compile(verbose=True)
