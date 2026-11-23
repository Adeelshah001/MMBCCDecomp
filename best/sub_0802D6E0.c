void sub_08004E24(u8 x);
int sub_08004E0C(u8 x);
u32 sub_0802D6E0(u8 *p)
{
  u8 new_var;
  unsigned short new_var2;
  switch (p[1])
  {
    case 0:
      p[1]++;

    case 1:
    {
      u8 t6;
      if (p[2] != 0)
      {
        return 3;
      }
      t6 = p[6];
      new_var = (u8) (t6 & 8);
      if (new_var)
      {
        goto inc;
      }
      {
        u32 c = 0x1000;
        if ((*((u16 *) (p + 20))) == c)
        {
          goto set6;
        }
      }
      {
        u32 m = 16;
        m &= t6;
        if (m == 0)
        {
          goto inc;
        }
      }
      set6:
      p[2] = 6;

      p[3] = 0;
      goto inc;
    }

    case 2:
      new_var = p[2];
      if (new_var != 0)
    {
      return 3;
    }
      inc:
    p[1]++;

      return 3;

    case 3:
      if ((p[6] & 8) == 0)
    {
      sub_08004E24(0);
    }
      p[1]++;

    case 4:
    {
      u16 *q;
      u16 m1;
      u16 t;
      new_var2 = 8;
      p = (u8 *) ((u32) p[6]);
      if (((u32) p) & new_var2)
      {
        goto ret4;
      }
      if (((s8) sub_08004E0C(3)) == 0)
      {
        return 3;
      }
      q = (u16 *) 0x020031E0;
      m1 = 0xEDFF;
      t = m1 & (*q);
      {
        u16 m2 = 0xDBFF;
        t &= m2;
      }
      *q = t;
      ret4:
      return 4;

    }

    default:
      return 3;

  }

}

