u32 sub_08004E24(u32 v);
u32 sub_08004E0C(u32 v);
void sub_08004F18(void);
void sub_08004F80(void);
extern u16 gUnknown_020031E0[];
void sub_08035EB0(u8 *p)
{
  switch (p[2])
  {
    case 0:
      sub_08004E24(0);
      p[2]++;

    case 1:
    {
      sub_08004F18();
      if (((u8) sub_08004E0C(3)) != 0)
      {
        u8 z = 0;
        unsigned int v;
        p[1] = 4;
        p[3] = z;
        p[2] = z;
        {
          u16 *g = gUnknown_020031E0;
          v = 0xEDFF;
          v &= g[0];
          v &= 0xDBFF;
          g[0] = v;
        }
      }
      sub_08004F80();
      break;
    }

  }

}

