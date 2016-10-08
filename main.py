#!/usr/bin/env python
import sys
import pysox


def main():
    print "Using SoX v%s" % pysox.__soxversion__

    assert pysox.init() == 0

    for (name, usage) in pysox.get_effects():
        print "%s: %s" % (name, usage)

    assert pysox.quit() == 0


if __name__ == '__main__':
    sys.exit(main())
    
