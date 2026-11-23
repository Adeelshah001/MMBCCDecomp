extern void sub_0800DD4C(u8 *s, int a, int b);
extern void sub_0800DD08(u8 *out, u8 *s);
extern void sub_0800D6E0(u8 *s, int a, u8 b);
extern void sub_0800D9EC(u8 *s, int idx);
extern void sub_0804A378(int idx);
inline int inline_fn(int arg0, int arg1)
{
  return arg0 | arg1;
}

int sub_0801B728(u8 *s)
{
  u32 out[2];
  register int o0;
  int o1;
  int mode;
  int new_var;
  int e;
  sub_0800DD4C(s, *((u32 *) (s + 88)), *((u32 *) (s + 92)));
  *((u32 *) (s + 88)) += *((u32 *) (s + 96));
  *((u32 *) (s + 92)) += *((u32 *) (s + 100));
  sub_0800DD08((u8 *) out, s);
  o0 = out[0];
  o1 = out[1];
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
  return 0;
  gt1:
  if (mode == 2)
  {
    goto c2;
  }

  return 0;
  c0:
  if ((-3840) >= o1)
  {
    return 0;
  }

  *((u32 *) (s + 92)) = mode;
  *((u32 *) (s + 100)) = mode;
  e = 8;
  goto shared;
  c1:
  s[18]--;

  if (((s8) s[18]) != 0)
  {
    return 0;
  }
  sub_0800D6E0(s, 514, 0);
  sub_0800D9EC(s, 0);
  {
    register int v = (*((u8 *) (0x020031E4 + (((*((u16 *) 0x081705B0)) >> 4) << 1)))) & 3;
    int t;
    int m;
    int sh;
    u8 *q;
    t = v;
    if ((t - 1) > (3 - 1))
    {
      v = 3;
    }
    q = s + 69;
    sh = v << 2;
    m = 13;
    m = -m;
    *q = inline_fn((*q) & m, sh);
  }
  s[34] = 13;
  o0 = s[18];
  sub_0800DD4C(s, 0, 160 << 4);
  sub_0804A378(126);
  e = 23;
  shared:
  s[18] = e;

  s[13]++;
  return 0;
  c2:
  s[18]--;

  if (((s8) o0) != 0)
  {
    return 0;
  }
  new_var = 254;
  s[10] &= new_var;
  return 1;
}

