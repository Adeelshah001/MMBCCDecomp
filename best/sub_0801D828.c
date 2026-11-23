extern u16 D_081705B0[];
extern u8 D_020031E4[];
void sub_0800D6E0(void *, int, int);
void sub_0800D9EC(void *, int);
void sub_0800303C(int);
struct SpriteInit1D828
{
  u8 pad0[0xA];
  u8 flags;
  u8 padB[7];
  u8 unk12;
  u8 pad13[0xF];
  u8 unk22;
  u8 pad23[0x22];
  u8 unk45;
  u8 pad46[0xA];
  u32 unk50;
  u32 unk54;
  u8 pad58[0x14];
  u32 unk6C;
};
inline static int LimitMode(int mode)
{
  if (mode > 3)
    mode = 3;
  return mode;
}

inline int inline_fn(int arg0)
{
  return LimitMode(arg0);
}

inline u8 inline_fn2(u8 *arg0)
{
  return *arg0;
}

void sub_0801D828(struct SpriteInit1D828 *s)
{
  int palette;
  int mask;
  int index;
  u8 *bytes;
  u8 *field;
  s->unk6C = 0;
  {
    int flags = 2;
    flags |= s->flags;
    s->flags = flags | 1;
  }
  sub_0800D6E0(s, 0x1401, 0);
  sub_0800D9EC(s, 0);
  index = D_081705B0[0] >> 4;
  index *= 2;
  bytes = D_020031E4 + index;
  palette = 3;
  palette &= inline_fn2(bytes);
  palette = inline_fn(palette);
  field = &s->unk45;
  palette <<= 2;
  mask = ~0xC;
  mask &= *field;
  *field = mask | palette;
  s->unk22 = s->unk12;
  sub_0800303C(0x84);
}

