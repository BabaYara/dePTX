import sys;
def inst_bra(suffix, arguments, native_inst, native_args):
  if (len(suffix) != 0) or (len(arguments) != 1):
    print ("inst_bra: something wrong, suffix is not empty: bra %s %s" % suffix, arguments);
    sys.exit()
  cinst = 'goto '+ arguments[0]+";";
  return cinst;
