import sys
from Position import *
def PTXError(pos, error):
  sys.stderr.write( "(%d,%d) : %s " % (pos.row, pos.col, error))

