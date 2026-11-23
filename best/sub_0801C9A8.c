extern void sub_0800DD4C(u8 *s, int a, int b);
extern void sub_0800DD08(u8 *out, u8 *s);
extern void sub_0800D9EC(u8 *s, int idx);
extern void sub_080174A4(int v, int bit);
extern u32 *sub_080178A8(int a, int b, int c, int d, int e);
extern u32 *sub_0801B98C(int a, int b, int c, int d, int e, int f);
extern u8 sub_08017474(int v);
extern void sub_08017478(int v, int val);
int sub_0801C9A8(u8 *s)
{
  int out[2];
  int mode;
  int new_var[2];
  sub_0800DD4C(s, *((u32 *) (s + 88)), *((u32 *) (s + 92)));
  *((u32 *) (s + 88)) += *((u32 *) (s + 96));
  *((u32 *) (s + 92)) += *((u32 *) (s + 100));
  sub_0800DD08((u8 *) out, s);
  if (s[19] != 0)
  {
    new_var[0] = --s[19];
    if (new_var[0] != 0)
    {
      goto dispatch;
    }
    new_var[1] = (s[19] = 7);
    {
      register short *tbl;
      int nib;
      int idx;
      short tv;
      nib = (int) ((((u32) s[35]) << 28) >> 28);
      tbl = (short *) 0x0822696c;
      idx = new_var[1] & s[14];
      tv = tbl[idx];
      sub_0801B98C(7, 1, nib, tv, new_var[0], *((u32 *) (s + 44)));
    }
    s[14] = (s[14] + 1) & new_var[1];
  }
  dispatch:
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

  if (mode == 3)
  {
    goto c3;
  }
  goto ret0;
  c0:
  s[18]--;

  if (s[18] != 0)
  {
    goto ret0;
  }
  sub_080174A4(*((u32 *) (s + 44)), 3);
  sub_0800D9EC(s, 1);
  s[18] = 6;
  s[19] = 1;
  goto inc;
  c1:
  s[18]--;

  if (s[18] != 0)
  {
    goto ret0;
  }
  sub_080178A8(122, (int) ((((u32) s[35]) << 28) >> 28), 240 << 6, 0, *((u32 *) (s + 44)));
  inc:
  s[13]++;

  goto ret0;
  c2:
  if (((u8) sub_08017474(*((u32 *) (s + 44)))) <= 5)
  {
    goto c3;
  }

  {
    int z = 0;
    int f = 15;
    s[18] = f;
    s[19] = z;
  }
  s[13]++;
  c3:
  s[18]--;

  if (s[18] != 0)
  {
    goto ret0;
  }
  sub_08017478(*((u32 *) (s + 44)), 7);
  return 1;
  ret0:
  return 0;

}

