extern u8 sub_080258D8(u8 *p, u16 idx);
extern void sub_080259A4(u8 *p, u16 b, u16 c);
u32 sub_080249B8(u8 *p, u8 a, u8 b)
{
  u8 *r4;
  u8 r6;
  u8 r5;
  u32 addr;
  u8 *base;
  u8 idx;
  u8 *ptr;
  r4 = p;
  r6 = a;
  r5 = b;
  if ((r6 > 29) || (r5 > 29))
  {
    return 1;
  }
  addr = *((u32 *) (r4 + 20));
  base = (u8 *) addr;
  idx = base[432];
  ptr = base + (idx * 144);
  if (sub_080258D8(ptr, r6))
  {
    goto upd;
  }
  addr = *((u32 *) (r4 + 20));
  base = (u8 *) addr;
  idx = base[432];
  ptr = base + (idx * 144);
  if (!sub_080258D8(ptr, r5))
  {
    return 0;
  }
  upd:
  addr = *((u32 *) (r4 + 20));

  base = (u8 *) addr;
  idx = base[432];
  ptr = base + (idx * 144);
  sub_080259A4(ptr, a, r5);
  return 0;
}

