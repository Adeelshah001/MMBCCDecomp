typedef short s16;
typedef signed int s32;
extern void sub_0800DD4C(u8 *o, s32 x, s32 y);
extern void sub_0800DD08(u32 *out, u8 *src);
extern void sub_080178A8(int a, int b, s16 c, s16 d, u8 *e);
extern u8 sub_08017494(u8 *p, int bit);
extern u8 sub_08017474(u8 *p);
u8 sub_080197BC(u8 *s)
{
  u32 out[2];
  unsigned short new_var;
  u8 **new_var3;
  u8 t;
  register s32 x;
  register s32 y;
  s32 new_var2;
  int mode;
  sub_0800DD4C(s, *((s32 *) (s + 88)), *((s32 *) (s + 92)));
  *((s32 *) (s + 88)) += *((s32 *) (s + 96));
  *((s32 *) (s + 92)) += *((s32 *) (s + 100));
  sub_0800DD08(out, s);
  x = out[0];
  y = out[1];
  mode = s[13];
  if (mode == 1)
  {
    goto c1;
  }
  if (mode > 1)
  {
    goto gt1;
  }
  if (mode == 0)
  {
    goto c0;
  }
  goto ret0;
  gt1:
  if (mode == 2)
  {
    goto c2;
  }

  goto ret0;
  c0:
  if (x <= 12800)
  {
    goto ret0;
  }

  sub_080178A8(82, (((u32) s[35]) << 28) >> 28, 15360, (s16) y, *((u8 **) (s + 44)));
  new_var3 = (u8 **) (s + 44);
  if (sub_08017494(*new_var3, 0) != 0)
  {
    s[13] = 1;
    goto ret0;
  }
  new_var = 253;
  new_var2 = x;
  t = s[10] & new_var;
  t = t & 254;
  s[10] = t;
  goto c1tail;
  c1:
  if (new_var2 <= 30720)
  {
    goto ret0;
  }

  c1tail:
  s[13] = 2;

  goto ret0;
  c2:
  if (((u8) sub_08017474(*new_var3)) > 5)
  {
    return 1;
  }

  ret0:
  return 0;

}

