extern u16 sub_080266F0(u8 idx);
u16 sub_080258A4(u8 *s, u8 idx)
{
  return (*((u16 *) (s + 14))) + sub_080266F0(idx);
}

