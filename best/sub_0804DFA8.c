void *sub_0804DFA8(void *dst, const void *src, u32 len)
{
  const u8 *s;
  int new_var;
  u8 *d;
  d = (u8 *) dst;
  s = (const u8 *) src;
  if ((len > 15) && (((((u32) s) | ((u32) d)) & 3) == 0))
  {
    u32 *dw = (u32 *) dst;
    register const u32 *sw = (const u32 *) s;
    do
    {
      *(dw++) = *(sw++);
      *(dw++) = *(sw++);
      *(dw++) = *(sw++);
      *(dw++) = *(sw++);
      len -= 16;
    }
    while (len > 15);
    while (len > 3)
    {
      *(dw++) = *(sw++);
      len -= 4;
    }

    d = (u8 *) dw;
    s = (const u8 *) sw;
  }
  {
    u32 n = len - 1;
    new_var = 1;
    if (n != ((u32) (-new_var)))
    {
      do
      {
        *(d++) = *(s++);
      }
      while ((--n) != ((u32) (-new_var)));
    }
  }
  return dst;
}

