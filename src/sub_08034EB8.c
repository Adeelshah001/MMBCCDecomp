extern u8 sub_080245C4(u8 b);
extern u32 sub_080400A8(void);
extern u32 __modsi3(u32 a, u32 b);
u8 sub_08034EB8(u8 *base, u8 arg1)
{
  register u8 *b8;
  u8 buf[12];
  u8 target;
  u8 count;
  u8 new_var;
  u8 res;
  u8 i;
  ;
  target = arg1;
  count = 0;
  res = count;
  for (i = 1; i <= 11; i++)
  {
    u8 *elem;
    if ((((u8) sub_080245C4(*((i * 12) + base))) == target) && ((*((i * 12) + base)) != 0))
    {
      buf[count] = *((i * 12) + base);
      count++;
    }
  }

  new_var = count;
  if (count != 0)
  {
    u16 rnd = sub_080400A8();
    u32 idx = __modsi3(rnd, new_var);
    res = buf[idx];
  }
  return res;
}

