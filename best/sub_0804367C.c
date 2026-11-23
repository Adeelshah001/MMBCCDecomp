typedef signed short s16;
void sub_08005A9C(u32 x);
u32 sub_0804580C(u8 *s);
u16 sub_08024760(void);
void sub_08045E20(u8 *s);
void sub_08045E40(u8 *s);
u8 sub_08043A9C(u8 *s);
u8 sub_08044828(u8 *s);
void sub_080248AC(u32 x);
extern u8 gUnknown_02004830[];
extern u8 gUnknown_02003670[];
u8 sub_0804367C(u8 *s)
{
  u8 flag = 0;
  switch (s[6])
  {
    case 0:
      sub_08005A9C(3);
      gUnknown_02004830[618] = sub_0804580C(s);
      gUnknown_02004830[619] = 0;
      *((u32 *) (s + 18088)) = 0;
      *((u32 *) (s + 18092)) = 0;
      *((u32 *) (s + 18096)) = 0;
      s[18092] = 5;
      s[18096] = 0;
      s[18098] = 0;
      s[18097] = 1;
      if (sub_08024760() > 7)
    {
      s[18099] = 1;
    }
    else
    {
      s[18099] = 0;
    }
      gUnknown_02003670[4524] = 0;
      sub_08045E20(s);
      s[6]++;

    case 1:
    {
      u8 *q = s + 18094;
      u8 a;
      s8 gv;
      a = *q;
      gv = (s8) gUnknown_02003670[4524];
      if (a == gv)
      {
        if (sub_08043A9C(s) != 0)
        {
          sub_080248AC(0);
          flag = 1;
        }
        if ((*q) != ((u8) gUnknown_02003670[4524]))
        {
          break;
        }
        if (sub_08044828(s) != 0)
        {
          sub_080248AC(0);
          flag = 1;
        }
      }
      else
      {
        s16 diff = (s16) (a - gv);
        u16 step;
        if (diff < 0)
        {
          step = diff >> 1;
        }
        else
        {
          step = (diff >> 1) ? (diff >> 1) : (1);
        }
        gUnknown_02003670[4524] += step;
        {
          u8 nv = gUnknown_02003670[4524];
          if (s[18094] == nv)
          {
            if (((s16) step) < 0)
            {
              if (nv)
              {
                sub_08045E20(s);
              }
              else
              {
                sub_08045E20(s);
              }
            }
            else
            {
              sub_08045E40(s);
            }
          }
        }
      }
      break;
    }

    default:
      break;

  }

  return flag;
}

