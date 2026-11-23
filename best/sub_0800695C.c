typedef short s16;
extern u16 gUnknown_080733A6[];
extern u16 gUnknown_080733B2[];
extern void sub_08006AD8(void *dst, u16 *s, s16 x, s16 y, s8 m, u8 f);
void sub_0800695C(void *dst, u16 *src, u16 a2, u16 a3, s8 a4, u8 a5)
{
  s16 h;
  s16 row;
  s16 j;
  u16 s[4];
  if (a4 != 0)
  {
    h = (u16) a4;
  }
  else
  {
    h = 32;
  }
  s[1] = 0x8000;
  for (row = 0; row < h; row++)
  {
    s[0] = *(src++);
    for (j = 0; j <= 4; j++)
    {
      if (gUnknown_080733A6[j] == s[0])
      {
        s[0] = gUnknown_080733B2[j];
        break;
      }
    }

    {
      s16 c = (s16) a2;
      sub_08006AD8(dst, s, c, (s16) a3, 1, a5);
      a2 = (u16) (c + 1);
    }
  }

  if (a4 != 0)
  {
    sub_08006AD8(dst, src, (s16) a2, (s16) a3, (s8) (a4 - row), a5);
  }
}

