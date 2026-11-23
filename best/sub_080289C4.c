void sub_08029504(u8 *s);
void sub_0800E994(void);
void sub_0800EA14(u8 v);
void sub_0800EA30(u8 v);
void sub_0800520C(void);
void sub_0800EE44(u8 v);
u8 sub_08024384(u16 v);
void sub_0800EA08(u8 a, u8 b);
void sub_0802E9F8(u16 a, u8 *p);
u8 sub_08024618(u8 v);
extern u8 gUnknown_02005168[];
u8 sub_080289C4(u8 *s)
{
  u8 i;
  u8 t;
  u8 v1;
  u8 v2;
  u16 z = 0;
  s[4] = 0;
  s[28] = 0;
  s[6] &= 0xF8;
  s[2] = 0;
  s[3] = 0;
  {
    register u8 w = 0;
    s[24] = w;
  }
  s[5] = 50;
  sub_08029504(s);
  *((u16 *) (s + 18)) = z;
  s[392] = 2;
  s[393] = 2;
  i = 0;
  {
    u32 *a = (u32 *) (s + 336);
    u32 zero = 0;
    u32 *b = (u32 *) (s + 364);
    u8 *c = s + 320;
    u8 *d = s + 328;
    for (; i <= 6; i++)
    {
      u32 *ap = a + i;
      *ap = zero;
      b[i] = zero;
      c[i] = zero;
      d[i] = zero;
    }

  }
  t = 8;
  t = s[6] & t;
  if (t == 0)
  {
    sub_0800E994();
    sub_0800EA14(s[29]);
    sub_0800EA30(s[10]);
    s[2] = 1;
    s[3] = t;
    sub_0800520C();
  }
  if ((s[6] & 16) != 0)
  {
    sub_0800EE44(1);
  }
  v1 = sub_08024384(*((u16 *) (s + 20)));
  v2 = sub_08024384(*((u16 *) (s + 22)));
  sub_0800EA08(v1, v2);
  sub_0802E9F8(*((u16 *) (s + 20)), s + 32);
  sub_0802E9F8(*((u16 *) (s + 22)), s + 176);
  {
    u8 tmp = sub_08024618(s[32]);
    u8 tz = 0;
    s[8] = tmp;
    s[9] = sub_08024618(s[176]);
    s[404] = tz;
    s[408] = tz;
    s[400] = tz;
    s[0] = 2;
    s[1] = tz;
    s[394] = tz;
    s[395] = tz;
    {
      u8 *ep = gUnknown_02005168;
      ep[12] = tz;
      ep += 20;
      ep[12] = tz;
    }
    s[412] = tz;
    s[416] = tz;
  }
  return 1;
}

