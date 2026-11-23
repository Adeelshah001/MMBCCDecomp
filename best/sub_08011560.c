typedef short s16;
extern void sub_08010AD8(int a, int b, int c);
extern s16 sub_0804A340(void);
extern void sub_0804A328(void);
extern void sub_0804A2DC(u16 a);
extern void sub_08010DDC(int a);
extern void sub_0804A378(u16 a);
inline int inline_fn(u8 arg0)
{
  return arg0 & 7;
}

int sub_08011560(u8 *s)
{
  u8 *r4 = *((u8 **) s);
  u16 x;
  int a1;
  int a2;
  int tailval;
  if (s[5] != 0)
  {
    goto else_block;
  }
  s[5]++;
  if ((*((s16 *) (s + 12))) == (-2))
  {
    x = r4[12];
    if (((s8) r4[12]) > 0)
    {
      a1 = 255;
      a2 = 2;
      goto shared;
    }
    else
    {
      sub_08010AD8(2, -1, 2);
      tailval = 2;
      goto tail;
    }
  }
  x = r4[12];
  if (((s8) r4[12]) <= 0)
  {
    goto else_block;
  }
  a1 = 255;
  a2 = 255;
  goto shared;
  shared:
  {
    u8 t11 = r4[11];
    s8 sb11 = r4[11];
    if (sb11 != 0)
    {
      a1 = (u8) (t11 - 1);
    }
  }

  if (inline_fn(r4[10]) != 0)
  {
    a2 = (u8) ((r4[10] & 7) - 2);
  }
  sub_08010AD8((u8) (x - 1), (s8) a1, (s8) a2);
  tailval = ((s8) r4[12]) - 1;
  tail:
  *((s16 *) (s + 12)) = tailval;

  s[34] = 1;
  return 0;
  else_block:
  if (r4[8] != 0)
  {
    x = (u16) (((u8 *) (*((u32 *) s)))[8] - 1);
    if ((sub_0804A340() << 16) != (x << 16))
    {
      sub_0804A328();
      if (x != 0)
      {
        sub_0804A2DC((u16) (((u8 *) (*((u32 *) s)))[8] - 1));
      }
    }
  }

  if ((r4[10] & 16) != 0)
  {
    sub_08010DDC(16);
  }
  if (r4[9] != 0)
  {
    sub_0804A378((u16) (((u8 *) (*((u32 *) s)))[9] - 1));
  }
  {
    u8 n = s[4] + 1;
    int z = 0;
    s[4] = n;
    s[5] = z;
    s[6] = z;
    s[7] = z;
    return z - 1;
  }
}

