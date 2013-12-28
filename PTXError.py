import sys
from Position import *
def PTXError(function, pos, error):
  sys.stderr.write( "%s error (%d,%d) : %s \n" % (function, pos.row, pos.col, error))
  sys.exit()

