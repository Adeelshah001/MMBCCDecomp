typedef signed short s16;
typedef signed int s32;
typedef struct 
{
  u8 pad0[10];
  u8 f10;
  u8 pad1[2];
  u8 f13;
  u8 pad2[4];
  u8 f18;
  u8 pad3[16];
  u8 f35;
  u8 pad4[8];
  u32 f44;
  u8 pad5[40];
  u32 f88;
  u32 f92;
  u32 f96;
  u32 f100;
} S;
extern void sub_0800DD4C(u32 a, u32 b, u32 c);
extern void sub_0800DD08(u32 *out, S *s);
extern void sub_080178A8(u32 a, u32 b, s32 c, s32 d, u32 e);
u32 sub_0801B1B8(S *s)
{
  s32 new_var;
  u32 *new_var2;
  u32 out[2];
  u8 st;
  register s32 o0;
  register u32 o1;
  S *new_var3;
  sub_0800DD4C((u32) s, s->f88, s->f92);
  s->f88 += s->f96;
  s->f92 += s->f100;
  sub_0800DD08(out, s);
  o0 = out[0];
  o1 = out[1];
  st = s->f13;
  switch (st)
  {
    ;
    case 0:
      new_var3 = s;
      new_var = o0;
    {
      u32 nib;
      if (new_var <= (220 << 6))
      {
        goto ret0;
      }
      nib = (((u32) new_var3->f35) << 28) >> 28;
      sub_080178A8(120, nib, (s16) new_var, (s16) o1, *(&s->f44));
      s->f18 = 25;
      s->f13++;
      goto ret0;
    }

    case 1:
    {
      u32 nf = s->f18 - 1;
      u32 a = 253;
      s->f18 = nf;
      if ((nf << 24) != 0)
      {
        goto ret0;
      }
      o0 = a;
      o0 = (s->f10 & o0) & 254;
      s->f10 = o0;
      return 1;
    }

    default:
      goto ret0;

  }

  ret0:
  return 0;

}

