#!/usr/bin/env python3
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

import sys;
from Position import *
from PTXError import *



class PTXSource:

  def __init__(self, filename):
    self.__newline = False
    self.__source = [];
    self.__pos = Position();
    f = open(filename, "r");

    for line in f:
      self.__source += [line]


    f.close()

  def __remainder__(self):
    return self.__source[self.__pos.row][self.__pos.col:];

  def __split__(self):
    return self.__remainder__().split();


  def nextWord(self):
    if self.is_eof():
      PTXError(self.__pos, "-end-of-file-reached-");
    self.__newline = False;
    line = self.__split__();
    if len(line) == 0:
      self.__pos.col  = 0;
      self.__pos.row += 1;
      self.__newline = True;
      return '';

    word = line[0]
    remainder = self.__remainder__();
    nspace = remainder.index(word);
    self.__pos.col += len(word) + nspace;
      
    return word

  def is_eof(self):
    return self.__pos.row >= len(self.__source)

  def is_newline(self):
    return self.__newline


# Unit test
if __name__ ==  "__main__":
  if len(sys.argv) < 2:
    print ("Usage: %s source.ptx" % sys.argv[0])
    sys.exit()
  filename = sys.argv[1]

  ptx = PTXSource(filename);

  while  not ptx.is_eof():
    word = ptx.nextWord()
    sys.stdout.write("%s " % word);
    if ptx.is_newline():
      sys.stdout.write("\n");

  








