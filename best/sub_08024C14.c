extern u16 sub_08025B60(u8 *p, u8 a, u8 b);
u16 sub_08024C14(u8 *s, u8 a, u8 b)
{
  u32 base = *((u32 *) (s + 20));
  long long new_var;
  register u32 off = 216 << 1;
  register u8 *p;
  register u8 v;
  u32 idx;
  p = (u8 *) (base + off);
  v = *p;
  idx = v * 144;
  new_var = base;
  return sub_08025B60((u8 *) (new_var + idx), (long long) a, b);
}

