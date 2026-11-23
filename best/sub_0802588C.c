extern long long sub_080266F0(u8 idx);
u16 sub_0802588C(u8 *s)
{
  u16 *new_var;
  new_var = (u16 *) (s + 14);
  return sub_080266F0(s[1]) + (*new_var);
}

