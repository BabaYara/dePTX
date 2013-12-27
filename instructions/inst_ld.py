import sys;
import Instruction as i;

# def inst_ld_param:
# def inst_ld_global:

def inst_ld(inst, suffix, arguments, native_inst, native_args):
#  if (len(suffix) != 1):
#    print("inst_if: unknown suffix type '%s'" % suffix)
#    sys.exit();
#  cinst = 'if ('+suffix[0]+') ' + i.Instruction(native_args).toC();
#  return cinst;
  if type(suffix) is list:
    suffix = "_".join(suffix);
  args = ",".join(arguments).replace("[","(").replace("]",")");
  cinst = inst+"_"+suffix+' ('+args+');';
  return cinst;
