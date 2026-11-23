typedef signed short s16;
extern int sub_08024384(int a);
extern int sub_080112FC(int a, int b);
extern int sub_080114B8(void);
extern int sub_080114E8(void);
int sub_08038520(u8 *s)
{
  int r = 0;
  u8 *p = s + 18077;
  s8 v = p[0];
  switch (v)
  {
    case 0:
    {
      int t = sub_08024384(4096) - 50;
      u16 u = sub_080112FC((u8) t, 8);
      if (u == 0)
      {
        r = 18076;
        *(s + r) = 7;
        p[0] = 0;
        break;
      }
      if (((s8) sub_080114B8()) != 0)
      {
        break;
      }
      p[0]++;
    }

    case 1:
      if (((s16) sub_080114E8()) == 1)
    {
      u8 *q = s + 18076;
      int z = 0;
      *q = 7;
      *(s + 18077) = z;
      r = 2;
    }
      break;

    default:
      break;

  }

  return r;
}

