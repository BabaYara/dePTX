def inst_mov(inst, suffix, arguments, native_inst, native_args):
  if type(suffix) is list:
    suffix = "_".join(suffix);
  cinst = 'mov_'+suffix+' ('+','.join(arguments)+');';
  return cinst;
