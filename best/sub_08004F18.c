void sub_08004208(u8 *p);
void sub_08004F70(u8 *base);
void sub_08004F7C(u8 *base);
void sub_08004F18(void)
{
  u8 **new_var2;
  long new_var;
  u8 *base = (u8 *) 0x02003670;
  u8 *p;
  sub_08004208(base + 44);
  sub_08004208(base + 0x264);
  sub_08004208(base + 0x49C);
  p = (u8 *) 0x02005028;
  *p = 0;
  p = base + 0x11AE;
  new_var2 = &p;
  new_var = 0xF8;
  if (((*(*new_var2)) & new_var) != 8)
  {
    sub_08004F70(base);
  }
  else
  {
    sub_08004F7C(base);
  }
}

