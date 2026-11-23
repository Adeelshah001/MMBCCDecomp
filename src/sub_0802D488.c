extern u8 sub_0802D574(void);
int sub_0802D488(u8 a, u8 b)
{
  register u32 aa = (((u32) a) << 24) >> 24;
  register u32 bb = (((u32) b) << 24) >> 24;
  register int r = 0;
  if (aa == 5)
  {
    if ((bb == 3) || (bb == 1))
    {
      r = 3;
    }
  }
  else
    if (aa == (bb = sub_0802D574()))
  {
    r = 6;
  }
  return r;
}

