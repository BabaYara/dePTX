#!/usr/bin/python
# PTX decompiler (dePTX)
# Evghenii Gaburov, 2013

class Function:
  functionName = None
  functionArguments = None
  functionReturn = None
  functionBody = None
  functionVisible = None
  functionKernel = None
  functionExtern = None

  def __init__:
    functionArguments = []
    functionBody = []

class Array:
  arrayName = None
  arrayType = None
  arraySize = None
  arrayVals = None
  arrayAlign = None

  def __init__:
    arrayVals = []


class dePTX(object):
  kernels = None
  architecture = None


  def __init__(self):
    self.kernels = []

def loadPTX(name):
  """Load a PTX file"""                                                          
  f = open(name, "r")

  ex = dePTX()
  while True:
    line = f.readline()

    if not line:
      break

    line = line[0:-1]
    if line.strip() == "":
      continue

    closebrace = line.rfind("}")
    openbrace  = line.rfind("{")
    
    



  


  

