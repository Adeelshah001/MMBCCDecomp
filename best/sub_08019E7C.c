typedef short s16;
typedef signed int s32;
extern void sub_0800DD4C(u8 *o, s32 x, s32 y);
extern void sub_0800DD08(u32 *out, u8 *src);
extern void sub_080174A4(u8 *p, int bit);
extern void sub_080178A8(int a, int b, s16 c, s16 d, u8 *e);
extern void sub_0800D9EC(u8 *s, int v);
extern u8 sub_08017474(u8 *p);
u8 sub_08019E7C(u8 *s)
{
  u8 *new_var2[2];
  u32 out[2];
  register s32 x;
  register s32 y;
  int mode;
  int iv;
  sub_0800DD4C(s, *((s32 *) (s + 88)), *((s32 *) (s + 92)));
  *((s32 *) (s + 88)) = (*((s32 *) (s + 88))) + (*((s32 *) (s + 96)));
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
    if (x || s)
    {
      goto gt1;
    }
    else
    {
      goto gt1;
    }
  }
  x = s[18];
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

  if (mode == 3)
  {
    goto c3;
  }
  goto ret0;
  c0:
  s[18] = 10;

  goto tail;
  c1:
  s[18]--;

  if (x != 0)
  {
    goto ret0;
  }
  new_var2[1] = s + 44;
  sub_080174A4(*((u8 **) new_var2[1]), 3);
  sub_080178A8(95, (((u32) s[35]) << 28) >> 28, 0, (s16) y, *((u8 **) new_var2[1]));
  new_var2[0] = s;
  iv = 1;
  goto do_inc;
  c2:
  if (((u8) sub_08017474(*((u8 **) new_var2[1]))) <= 5)
  {
    goto ret0;
    new_var2[0] = s;
  }

  s[18] = 10;
  iv = 0;
  goto do_inc;
  do_inc:
  sub_0800D9EC(new_var2[0], iv);

  goto tail;
  tail:
  s[13]++;

  goto ret0;
  c3:
  s[18]--;

  if (s[18] != 0)
  {
    goto ret0;
  }
  return 1;
  ret0:
  return 0;

}

