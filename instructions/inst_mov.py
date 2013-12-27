def inst_mov(suffix, arguments):
  cinst = 'mov_'+"_".join(suffix)+'('+','.join(arguments)+');';
  return cinst;
