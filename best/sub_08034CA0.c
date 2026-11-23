void sub_08034CA0(const u8 *state)
{
  u8 control;
  u8 present = 0xFC & state[0x18];
  if (present != 0)
  {
    u8 index = (state[0x18] >> 2) - 3;
    present = 2 & control;
    if (present == 0)
    {
      if (index != 0xFF)
      {
        u8 *flags = (u8 *) 0x02005168;
        flags[7] = 1 << (7 & index);
        return;
      }
      {
        u8 *flags = (u8 *) 0x02005168;
        flags[7] = present;
      }
      return;
    }
    if (index != 0xFF)
    {
      u8 *flags = (u8 *) 0x0200517C;
      flags[7] = 1 << (index & 7);
      return;
    }
    {
      u8 *flags = (u8 *) 0x0200517C;
      flags[7] = 0;
    }
    return;
  }
  {
    u8 *flags = (u8 *) 0x02005168;
    flags[7] = present;
    flags[0x1B] = present;
  }
}

