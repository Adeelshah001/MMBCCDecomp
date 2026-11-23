typedef signed short s16;
extern u8 gUnknown_02003670[];
extern u8 sub_0800B2B4(void);
extern u8 sub_0800B148(u8 a, s16 b, int c);
extern u8 sub_0800B2D8(void);
extern u8 StartSelectionWithEntries(u32 a, int b, int c, int d);
extern u8 sub_0800B308(void);
extern u8 sub_0800B2F0(void);
extern void sub_08010508(int a);
u8 sub_0800FC64(u8 *s)
{
  int new_var;
  switch (s[1])
  {
    case 0:
      if (sub_0800B2B4() == 0)
    {
      break;
    }
      s[1]++;

    case 1:
    {
      register u8 v65;
      if (sub_0800B148(s[69], *((s16 *) (s + 56)), 1) == 0)
      {
        break;
      }
      v65 = s[65];
      {
        unsigned int t = v65;
        int v = v65;
        if (t != 0)
        {
          if (t > 15)
          {
            v = 15;
          }
          {
            u8 *p = gUnknown_02003670;
            int sh;
            p += 0x11af;
            sh = v << 4;
            t = *p;
            *p = (u8) ((t & new_var) | sh);
          }
          new_var = 15;
          s[3] = v65;
        }
        else
        {
          s[3] = 1;
        }
      }
      s[1]++;
      break;
    }

    case 2:
      s[3]--;
      if (((s8) s[3]) > 0)
    {
      break;
    }
      s[1]++;

    case 3:
      if (sub_0800B2D8() == 0)
    {
      break;
    }
      if (StartSelectionWithEntries(*((u32 *) (s + 48)), 0, 0, 0) == 0)
    {
      break;
    }
      s[1]++;
      break;

    case 4:
      if (sub_0800B308() == 0)
    {
      break;
    }
      s[1]++;
      break;

    case 5:
      if (sub_0800B2B4() == 0)
    {
      break;
    }
      s[1]++;
      break;

    case 6:
      if (sub_0800B2F0() == 0)
    {
      break;
    }
      sub_08010508(0);
      break;

    default:
      break;

  }

  return s[0];
}

