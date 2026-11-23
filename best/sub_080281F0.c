extern void sub_080252E8(u8 *q);
void sub_0802533C(u8 *p, u8 idx);
extern void sub_080267B4(u8 *a, u8 kind);
extern u8 gUnknown_02002F50[];
extern u8 gUnknown_020070F0[];
void sub_080281F0(u8 *s)
{
  u8 t;
  switch (s[1])
  {
    case 0:
      s[6] = 0;
      s[1]++;

    case 1:
      t = 6;
    {
      s[t]++;
      if (s[t] <= 0xB4)
      {
        u8 *base = gUnknown_02002F50;
        if (((*((u16 *) (base - -4))) & (t = 1)) == 0)
        {
          return;
        }
      }
      sub_080267B4(gUnknown_020070F0, 8);
      s[0x4698] = 0;
 return; }

    default:
      return;

  }

}

void sub_08028244(u8 *s);
