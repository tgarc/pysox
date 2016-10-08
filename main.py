#!/usr/bin/env python
import sys
import pysox

def main():
    assert pysox.init() == 0
    
    assert pysox.quit() == 0

if __name__ == '__main__':
    sys.exit(main())
    
