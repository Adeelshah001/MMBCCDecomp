void sub_08002D20(void)
{
  volatile unsigned short v;
  unsigned short *ew;
  int new_var;
  volatile unsigned int *dma;
  int new_var2;
  v = *((volatile unsigned short *) 0x04000000);
  v &= 0xF0E8;
  ew = (unsigned short *) 0x020031E0;
  new_var = 0x04000000;
  new_var2 = 0x0F17;
  *ew &= new_var2;
  v |= *ew;
  *((volatile unsigned short *) new_var) = v;
  dma = (volatile unsigned int *) 0x040000D4;
  dma[0] = ((unsigned int) ew) + 4;
  dma[1] = 0x04000008;
  dma[2] = 0x8400000E;
  dma[2];
}

