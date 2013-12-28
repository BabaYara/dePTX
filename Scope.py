#!/usr/bin/env python3
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

import sys;
from PTXSource import *

class Scope:

  def __init__(self, ptx, inScope = False):
    self.__scope = [];
    if inScope:
      self.__parse__(ptx);
    else:
      ptx.reset();
      self.__findScope__(ptx);

  def __findScope__(self, ptx):
    while not ptx.isEOF():
      word = ptx.nextWord();
      openbrace  = word.find("{");
      if (openbrace >= 0):
        ptx.adjustCol(-(len(word)-openbrace-1));
        self.__scope += [Scope(ptx, inScope = True)];
    

  def __parse__(self, ptx):
    scope_complete = False;
    while not scope_complete:
      word = ptx.nextWord()
      openbrace  = word.find("{");
      closebrace = word.find("}");
      if (openbrace >= 0 and closebrace >= 0):
        PTXError(ptx.getPos(), "Cannot process scope %s" % (word));
      if (openbrace >= 0):
        ptx.adjustCol(-(len(word)-openbrace-1));
#        print ("(%d,%d) openbrace= %d   word= %s" % (ptx.getCol(), ptx.getRow(), openbrace, word))
#        print ("(%d,%d) openbrace= %d   word= %s" % (ptx.getCol(), ptx.getRow(), openbrace, ptx.split()[0]))
        self.__scope += [Scope(ptx, inScope = True)];
      if (closebrace >= 0):
        ptx.adjustCol(-(len(word)-closebrace-1));
        self.__end = ptx.getPos();
        scope_complete = True

  def getNumScope(self):
    return len(self.__scope);

  def getScope(self,i):
    return self.__scope[i];



# Unit test
if __name__ ==  "__main__":
  if len(sys.argv) < 2:
    print ("Usage: %s source.ptx" % sys.argv[0])
    sys.exit()
  filename = sys.argv[1]

  ptx = PTXSource(filename);
  mainScope = Scope(ptx);

  nScope  = mainScope.getNumScope();
  print ("Found %d outer scopes" % nScope)

  for i in range(0,nScope):
    scope = mainScope.getScope(i)
    nSubScope = scope.getNumScope()
    print ("Scope %d has %d sub-scopes" % (i, nSubScope))
    for j in range(0,nSubScope):
      print ("   subscope %d has %d subsub-scopes" % (j, scope.getScope(j).getNumScope()))

  

