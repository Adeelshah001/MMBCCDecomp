void sub_08004E24(u8 x);
void sub_08004F18(void);
int sub_08004E0C(u8 x);
void sub_08004F80(void);
void sub_08004DFC(u8 a);
extern u8 gUnknown_02004F80[];
extern u16 gUnknown_020031E0[];
u8 sub_08042C04(u8 *s)
{
  int new_var;
  switch (s[5])
  {
    case 0:
      sub_08004E24(0);
      s[5]++;

    case 1:
 do { sub_08004F18(); new_var = sub_08004E0C(3) << 24; if (new_var != 0) { u16 v = gUnknown_020031E0[0]; v = (u16) (v & 0xEDFFu); v = (u16) (v & 0xDBFFu); gUnknown_020031E0[0] = v; s[5]++; } } while (0);
      sub_08004F80();
      break;

    case 2:
      sub_08004DFC(gUnknown_02004F80[2]);
      s[5]++;

    case 3:
    {
      int r;
      sub_08004F18();
      r = (sub_08004E0C(0) << 24) >> 24;
      if (r == 0)
      {
        if (s[7] == 1)
        {
          s[7] = s[4];
          s[4] = 3;
        }
        else
        {
          s[7] = s[4];
          s[4] = 1;
        }
        s[5] = (u8) r;
        s[6] = (u8) r;
      }
      sub_08004F80();
      break;
    }

    default:
      break;

  }

  return 0;
}
