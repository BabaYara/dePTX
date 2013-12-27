#!/usr/bin/python3
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

import sys
import Instruction

if __name__ == "__main__":
  for line in sys.stdin:
    sys.stderr.write("%s" % line)
#    inst = Instruction(line)
