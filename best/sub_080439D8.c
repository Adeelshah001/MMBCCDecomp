extern u8 sub_0802478C(u32 idx);
extern u16 sub_08024634(u8 idx);
extern u16 sub_08024F08(void);
extern u16 sub_08024554(u8 idx);
extern u16 sub_08024570(u8 idx);
extern u16 sub_080245E0(u8 idx);
extern u8 sub_08006DD8(void *p, u32 a, u32 b, u32 c, u32 d);
extern void sub_08006A54(u32 a, u32 b, u32 c, u32 d, u32 e);
void sub_080439D8(u8 *p)
{
  u8 b0;
  u8 idx;
  u16 v;
  register u8 *r4;
  register u32 zero;
  u16 t0;
  u16 t1;
  u32 *tbl;
  u32 off;
  u32 *pp;
  u32 p0;
  int a1;
  int a2;
  b0 = p[0x46A9];
  b0 >>= 4;
  idx = (u8) sub_0802478C(b0 + p[0x46AA]);
  v = (u16) sub_08024634(idx);
  if (idx > 199)
  {
    if (zero)
    {
      v = (u16) (v + sub_08024F08());
    }
    else
    {
      v = (u16) (v + sub_08024F08());
    }
  }
  t0 = (u16) sub_08024554(idx);
  r4 = (u8 *) 0x08232D84;
  {
    int a1 = ((s8) r4[16]) + 2;
    int a2 = (s8) r4[17];
    zero = 0;
    sub_08006DD8((void *) t0, a1, a2, 3, zero);
  }
  t1 = (u16) sub_08024570(idx);
  {
    int a1 = ((s8) r4[16]) + 7;
    int a2 = (s8) r4[17];
    sub_08006DD8((void *) t1, a1, a2, 3, zero);
  }
  {
    int a1 = ((s8) r4[16]) + 2;
    int a2 = ((s8) r4[17]) + 2;
    sub_08006DD8((void *) v, a1, a2, 3, zero);
  }
  tbl = (u32 *) 0x08232DF0;
  off = ((u16) sub_080245E0(idx)) >> 12;
  pp = (u32 *) tbl[off];
  p0 = *pp;
  {
    a1 = ((s8) r4[16]) + 6;
    a2 = ((s8) r4[17]) + 2;
    sub_08006A54(p0, a1, a2, 4, zero);
  }
}

