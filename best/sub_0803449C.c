extern s8 sub_0800EBF0(void);
extern s8 sub_0800EA4C(s8 v);
u32 sub_0803449C(u8 *s)
{
  u32 ret = 0;
  u8 st = s[3];
  u8 b;
 do { if (st == 0) { goto state0; } if (st == 1) { goto state1; } goto ret; state0: b = 0x80; b |= s[6]; s[6] = b; if (((s8) sub_0800EBF0()) == 1) { s[3]++; } else { sub_0800EA4C(0); goto ret; } } while (0);
  state1:
  if (((u8) sub_0800EA4C(0)) == 1)
  {
    goto ret;
  }

  ret = 0x7F;
  b = ret;
  b &= s[6];
  st = b;
  s[6] = st;
  ret = 7;
  ret:
  return ret;

}
