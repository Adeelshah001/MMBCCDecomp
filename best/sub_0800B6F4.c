extern u8 gUnknown_0817310C[];
inline int inline_fn(int arg0)
{
  return -arg0;
}

void sub_0800B6F4(u8 *p, u8 x)
{
  int m15 = 15;
  int v1 = x & m15;
  int new_var;
  int m16 = 16;
  int new_var2;
  new_var = 18;
  p[new_var] = (new_var2 = p[new_var] & inline_fn(m16)) | v1;
  {
    u8 *tbl = gUnknown_0817310C;
    u8 *e = *((u8 **) (tbl + (x * 12)));
    p[new_var] &= m15;
    p[17] = e[(unsigned long long) 1];
  }
}

