#!/usr/bin/python3
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

import sys;
from Decompile import *

class Instruction:

  def __init__(self,inst_line):
    self.inst = inst_line.split()[0];
    self.args = inst_line.split()[1:];
    inst =          self.inst.replace('.',' ').replace('%',' ').split()
    args = ' '.join(self.args).replace('.','_').replace(',',' ').replace('%','').replace(';','').split();

    self.instName      = inst[0];
    self.instSuffix    = inst[1:];
    self.instArguments = args;

    if self.instName == '@':
      self.instName = 'if';

    self.instName = 'inst_'+self.instName;

    self.args = " ".join(self.args);

    print ("instName     = '%s'" % self.instName);
    print ("instSuffix   = %s" % self.instSuffix);
    print ("instArguments= %s" % self.instArguments);
    print ("nativeInst   = '%s'" % self.inst);
    print ("nativeArgs   = '%s'" % self.args);
    print ("")

  def toC(self):
    cinst = globals()[self.instName](self.instSuffix, self.instArguments, self.inst, self.args);
    return cinst;

  def nativeInst(self):
    return self.inst;

  def nativeArgs(self):
    return self.args;


# Unit test 
if __name__ == "__main__":
  for line in sys.stdin:
    sys.stderr.write("%s" % line)
    inst = Instruction(line).toC()
    print ("%s" % inst)
         

  



  







