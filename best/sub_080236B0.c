extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);
u8 *sub_080236B0(short a, u8 *b, u8 *c, u8 *d)
{
  register u8 *cc = c;
  register u8 *dd = d;
  u8 aa = (u8) a;
  u8 nib;
  u32 w35;
  u8 *p;
  w35 = cc[35];
  nib = (w35 << 28) >> 28;
  p = (u8 *) sub_08020ED4(0, 1, nib, 7);
  if (p != 0)
  {
    u8 z = 0;
    u32 dw0;
    u32 dw1;
    p[16] = z;
    p[17] = aa;
    dw0 = *((u32 *) dd);
    dw1 = *((u32 *) (dd + 4));
 do { *((u32 *) (p + 96)) = dw0; *((u32 *) (p + 100)) = dw1; *((u8 **) (p + 40)) = b; *((u8 **) (p + 44)) = cc; } while (0);
  }
  return p;
}
