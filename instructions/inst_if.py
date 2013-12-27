import sys;
import Instruction as inst;

def inst_if(suffix, arguments, native_inst, native_args):
  if (len(suffix) != 1):
    print("inst_if: unknown suffix type '%s'" % suffix)
    sys.exit();
  cinst = 'if ('+suffix[0]+') ' + inst.Instruction(native_args).toC();
  return cinst;
