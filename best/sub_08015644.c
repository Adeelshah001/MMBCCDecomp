typedef signed short s16;
extern void sub_0800D9EC(u8 *s, u8 n);
extern void sub_0800D9FC(u8 *s);
extern void sub_0800DD2C(u8 *o, int x, int y);
extern short sub_08011F50(u8 *s);
extern void sub_08011F68(u8 *s, int a);
extern u8 sub_08017474(u32 a);
extern void sub_08017464(u32 a);
extern void sub_0801AA70(int a, int b, int c, int d, int e, u32 f);
extern u8 gUnknown_08223E60[][2];
extern s16 gUnknown_08223ED8[][2];
void sub_08015644(u8 *s)
{
  u8 *t = s + 124;
  int new_var;
  switch (s[14])
  {
    case 0:
      sub_0800D9EC(s, 2);
      s[14]++;
      break;

    case 1:
    {
      int b0;
      int b1;
      int nib;
      s16(*tp)[2];
      s16 *e;
      if (sub_08011F50(s) == 0)
      {
        break;
      }
      b0 = gUnknown_08223E60[s[17]][0];
      b1 = gUnknown_08223E60[s[17]][1];
      nib = (int) ((((u32) s[35]) << 28) >> 28);
      tp = gUnknown_08223ED8;
      e = tp[t[0]];
      sub_0801AA70(b0, b1, nib, e[0], e[1], *((u32 *) (s + 44)));
      new_var = 0xfe;
      s[10] &= new_var;
      s[14]++;
      break;
    }

    case 2:
      if (sub_08017474(*((u32 *) (s + 44))) <= 6)
    {
      break;
    }
      s[10] |= 1;
      sub_0800D9EC(s, 1);
      s[14]++;
      break;

    case 3:
      if (sub_08011F50(s) == 0)
    {
      break;
    }
      sub_08017464(*((u32 *) (s + 44)));
      *((u32 *) (s + 44)) = 0;
      sub_0800DD2C(s, -15360, 0);
      sub_0800D9EC(s, 0);
      t[4] = 0;
      sub_08011F68(s, 0);
      break;

    default:
      break;

  }

  sub_0800D9FC(s);
}

