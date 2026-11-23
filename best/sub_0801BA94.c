extern void sub_0800DD4C(u8 *s, int a, int b);
extern void sub_0800DD08(u8 *out, u8 *s);
extern void sub_080174A4(u8 *s, u8 bit);
extern u32 *sub_080178A8(int a, int b, int c, int d, int e);
extern u8 sub_08017474(u8 *s);
extern void sub_08017478(u8 *s, u8 v);
extern u8 sub_08017494(u8 *s, u8 bit);
extern void sub_08017464(u8 *s);
extern void sub_0800D9FC(u8 *s);
void sub_0801BA94(u8 *s)
{
  int out[2];
  int mode;
  register int o0;
  int o1;
  u8 *tbl;
  u8 *entry;
  register unsigned int idx;
  u8 *new_var[2];
  mode = s[13];
  if (mode == 1)
  {
    goto c1;
  }
  if (mode > 1)
  {
    goto gt1;
  }
  if (0 == mode)
  {
    goto c0;
  }
  goto tail;
  gt1:
  if (mode == 2)
  {
    goto c2;
  }

  goto tail;
  c0:
  sub_0800DD4C(s, 212 << 2, *((u32 *) (s + 92)));

  *((u32 *) (s + 92)) += *((u32 *) (s + 100));
  if ((*((int *) (s + 84))) <= (-3840))
  {
    goto tail;
  }
  s[10] &= 254;
  s[10] &= 253;
  goto shared;
  c1:
  sub_0800DD08((u8 *) out, s);

  o0 = out[0];
  o1 = out[1];
  if (sub_08017494((u8 *) (*((u32 *) (s + 44))), 1) != 0)
  {
    sub_080178A8(14, (int) ((((u32) s[35]) << 28) >> 28), (short) o0, (short) o1, *((u32 *) (s + 44)));
    goto shared;
  }
  sub_080174A4((u8 *) (*((u32 *) (s + 44))), 3);
  tbl = (u8 *) 0x08226858;
  idx = s[16];
  new_var[1] = (u8 *) (idx + ((int) tbl));
  sub_080178A8(*new_var[1], (int) ((((u32) s[35]) << 28) >> 28), (short) o0, (short) o1, *((u32 *) (s + 44)));
  shared:
  s[13]++;

  goto tail;
  c2:
  if (((u8) sub_08017474((u8 *) (*((u32 *) (s + 44))))) <= 5)
  {
 goto tail; }
  sub_08017478((u8 *) (*((u32 *) (s + 44))), 7);
  sub_08017464((u8 *) (*((u32 *) (s + 44))));
  *((u32 *) (s + 44)) = 0;
  new_var[0] = (u8 *) 0x082243d8;
  entry = (u8 *) ((s[9] * 4) + ((int) new_var[0]));
  *((u32 *) (s + 12)) = mode;
  o1 = *((u32 *) entry);
  *((u32 *) (s + 20)) = *((u32 *) (o1 + 8));
  tail:
  sub_0800D9FC(s);

}
