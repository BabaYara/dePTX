def inst_gen(inst, suffix, arguments, native_inst, native_args):
  if type(suffix) is list:
    suffix = "_".join(suffix);
  cinst = inst+"_"+suffix+' ('+','.join(arguments)+');';
  return cinst;
