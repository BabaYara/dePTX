#!/usr/bin/env python3
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

import sys;
from Position import *
from PTXError import *



class PTXSource:

  ## Constructor reads PTX from file
  def __init__(self, filename):
    self.__endOfLine = False
    self.__source = [];
    self.__pos = Position();
    f = open(filename, "r");

    for line in f:
      self.__source += [line]

    f.close()


  ## private methods

  # return length of the current line
  def __lenOfLine(self):
    return len(self.__source[self.__pos.row]);

  # return remainded of the line (supposedly unprocessed)
  def __remainder__(self):
    return self.__source[self.__pos.row][self.__pos.col:];

  # split remainded of the line
  def __split__(self):
    return self.__remainder__().split();

  def split(self):
    return self.__split__();

  ## public methods

  # extract next word in the line
  def nextWordInLine(self):
    if self.isEndOfLine():
      PTXError("PTXSource", self.__pos, "-end-of-line-is-reached-");
    if self.isEOF():
      PTXError("PTXSource", self.__pos, "-end-of-file-reached-");
    self.__endOfLine = False;
    line = self.__split__();
    if len(line) == 0:
      self.__pos.col  = self.__lenOfLine();
      self.__endOfLine = True;
      return '';

    word = line[0]
    remainder = self.__remainder__();
    nspace = remainder.index(word);
    self.__pos.col += len(word) + nspace;
      
    return word

  # find next non empty line
  def nextNonEmptyLine(self):
    if self.isEOF():
      PTXError("PTXSource::nextNonEmptyLine", self.__pos, "-end-of-file-");
    self.__pos.col  = 0;
    self.__pos.row += 1;
    while True:
      line = self.__split__();
      if len(line) > 0:
        self.__endOfLine = False;
        break;
      self.__pos.row += 1;
      if self.isEOF():
        break;

  def nextWord(self):
    word = self.nextWordInLine()
    if self.isEndOfLine():
      self.nextNonEmptyLine();
    return word


  # check if we are at the end of file 
  def isEOF(self):
    return self.__pos.row >= len(self.__source)

  # check for end of line
  def isEndOfLine(self):
    return self.__endOfLine;

  # adjust cursor position
  def adjustCol(self, value):
    self.__pos.col += value;
  def adjustRow(self, value):
    self.__pos.row += value;


  # get/set position
  def setPos(self,pos):
    self.__pos = pos;
  def getPos(self):
    return self.__pos;
  def getRow(self):
    return self.__pos.row;
  def getCol(self):
    return self.__pos.col;

  # from the top..
  def reset(self):
    self.__pos.row = 0;
    self.__pos.col = 0;



# Unit test
if __name__ ==  "__main__":
  if len(sys.argv) < 2:
    print ("Usage: %s source.ptx" % sys.argv[0])
    sys.exit()
  filename = sys.argv[1]

  ptx = PTXSource(filename);

  while  not ptx.isEOF():
    word = ptx.nextWordInLine()
    sys.stdout.write("%s " % word);
    if ptx.isEndOfLine():
      sys.stdout.write("\n");
      ptx.nextNonEmptyLine();

  








