#!/usr/bin/env python3
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

import sys
from __future__ import print_function

class Types:
  typeDict = None

  def __init__:
    typeDict = {
        'pred' : 'bool_t',
        's8'   : 'int8_t',
        'u8'   : 'uint8_t',
        'b8'   : 'uint8_t',
        's16'  : 'int16_t',
        'u16'  : 'uint16_t',
        'b16'  : 'uint16_t',
        's32'  : 'int32_t',
        'u32'  : 'uint32_t',
        'b32'  : 'uint32_t',
        's64'  : 'int64_t',
        'u64'  : 'uint64_t',
        'b64'  : 'uint64_t',
        'f32'  : 'float',
        'f64'  : 'double'
        }

    def map(self,ptxType):
      if 'ptxType' in typeDict:
        return typeDict[ptxType];
      else:
        print("ptxType= '%s' is unknown' % ptxType, file=sys.stderr)
        sys.exit()









