extern u8 _call_via_r3(u8 *a, u16 b, u8 c, u32 fn);
extern u32 gUnknown_082329B0[];
u8 sub_080400D0(u8 *s, u16 b, u8 c)
{
  u32 *tbl = gUnknown_082329B0;
  u32 idx = s[4];
  long long fn = tbl[idx];
  return _call_via_r3(s, b, c, fn);
}

