#!/usr/bin/python3
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

import sys;
import Decompile as decompile

class Instruction:

  def __init__(self,inst_line):
    inst =          inst_line.split()[0]  .replace('.',' ').replace('%',' ').split()
    args = ' '.join(inst_line.split()[1:]).replace('.','_').replace(',',' ').replace('%','').replace(';','').split();

    self.instName      = inst[0];
    self.instSuffix    = inst[1:];
    self.instArguments = args;

    if self.instName == '@':
      self.instName = 'if';

    self.instName = 'inst_'+self.instName;

#    print ("instName     = '%s'" % self.instName);
#    print ("instSuffix   = %s" % self.instSuffix);
#    print ("instArguments= %s" % self.instArguments);
#    print ("")

  def toC(self):
    cinst = getattr(decompile,self.instName)(self.instSuffix, self.instArguments);
    return cinst;


# Unit test 
if __name__ == "__main__":
  for line in sys.stdin:
    sys.stderr.write("%s" % line)
    inst = Instruction(line).toC()
    print ("%s" % inst)
         

  



  







