typedef signed short s16;
void sub_08011DD0(int a, u8 b);
u8 sub_080496E8(u8 a, u8 b);
void sub_0804990C(void);
u8 sub_08024384(int a);
u16 sub_080112FC(u8 a, int b);
u8 sub_080114B8(u16 a);
s16 sub_080114E8(int a);
void sub_08011BD4(void);
int sub_080396B4(u8 *s)
{
  u16 keys = *((u16 *) 0x02002F50);
  s8 st = (s8) s[0x469D];
  u16 r;
  switch (st)
  {
    case 0:
      st = s[0x469B];
    {
      u8 diff = (u8) ((st - s[0x4698]) - 1);
      u8 idx;
      u8 *p;
      sub_08011DD0(1, diff);
      sub_08011DD0(2, s[0x469A]);
      sub_08011DD0(3, 0);
      diff = (u8) ((st - s[0x4698]) - 1);
      idx = sub_080496E8(diff, s[0x469A]);
      p = (s + (idx * 12)) + 48;
      if ((*p) <= 98)
      {
        (*p)++;
      }
      s[0x469E] = 0;
      if (s[21] == 1)
      {
        sub_0804990C();
        *((u32 *) (s + 24)) |= 4;
        *((u32 *) (s + 28)) &= ~4;
      }
      s[0x469D]++;
    }

    case 1:
    {
      r = sub_080112FC((u8) (sub_08024384(0x1000) - 50), 4);
      if (r == 0)
      {
        s[0x469D] += 2;
        break;
      }
      if (sub_080114B8(r) != 0)
      {
        break;
      }
      s[0x469D]++;
      s[0x469F] = 0;
    }

    case 2:
    {
      u8 f;
      if ((keys & 8) != 0)
      {
        s[0x469F]++;
      }
      else
      {
        s[0x469F] = 0;
      }
      f = s[0x469F];
      if (f > 30)
      {
        sub_08011BD4();
        s[0x469D]++;
      }
      else
        if (sub_080114E8(f) == 1)
      {
        s[0x469D]++;
      }
      break;
    }

    case 3:
    {
      r = sub_080112FC((u8) (sub_08024384(0x1000) - 50), 3);
      if (r == 0)
      {
        s[0x469C] = 4;
        s[0x469D] = 0;
        break;
      }
      if (sub_080114B8(r) != 0)
      {
        break;
      }
      s[0x469D]++;
      s[0x469F] = 0;
    }

    case 4:
    {
      u8 f;
      if ((keys & 8) != 0)
      {
        s[0x469F]++;
      }
      else
      {
        s[0x469F] = 0;
      }
      f = s[0x469F];
      if (f > 30)
      {
        sub_08011BD4();
      }
      else
        if (sub_080114E8(f) != 1)
      {
        break;
      }
    }
    {
      u8 *p = s + 0x469C;
      u8 z = 0;
      *p = 5;
      s[0x469D] = z;
    }
      break;

    default:
      break;

  }

  return 0;
}

