extern void sub_08005130(u8 *base);
extern void sub_08005208(u8 *base);
void sub_080050F0(void)
{
  register u8 *base = (u8 *) 0x02003670;
  register u8 *p = base + 0x11ae;
  register int b = *p;
  u8 *new_var;
  new_var = p;
  if ((b & 2) == 0)
  {
    return;
  }
  {
    register int nb;
    nb = ~2;
    nb &= b;
    if ((nb & 248) != 8)
    {
      *new_var = nb;
      sub_08005130(base);
    }
    else
    {
 do { sub_08005208(base); } while (0);
    }
  }
}
