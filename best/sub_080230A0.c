extern u16 D_081705B0[];
extern u8 D_020031E4[];
void sub_0800D6E0(void *, int, int);
void sub_0800D9EC(void *, int);
struct SpriteInit230A0
{
  u8 pad0[0xA];
  u8 flags;
  u8 padB[0x17];
  u8 unk22;
  u8 pad23[0x22];
  u8 unk45;
  u8 pad46[0xA];
  u32 unk50;
  u32 unk54;
  u8 pad58[0x14];
  u32 unk6C;
};
void sub_080230A0(struct SpriteInit230A0 *s)
{
  int palette;
  int mask;
  int index;
  u16 new_var;
  u8 *field;
  s->unk6C = 0;
  {
    int flags = 2;
    flags |= s->flags;
    s->flags = flags | 1;
  }
  sub_0800D6E0(s, 0x3715, 0);
  sub_0800D9EC(s, 0);
  s->unk50 = 0;
  s->unk54 = 0;
  index = (new_var = D_081705B0[1]) >> 4;
  index *= 2;
  field = D_020031E4 - (-index);
  palette = 3;
  palette &= *field;
  index = palette;
  if ((index + 1) > (3 + 1))
  {
    palette = 3;
  }
  field = &s->unk45;
  palette <<= 2;
  mask = ~0xC;
  mask &= *field;
  *field = mask | palette;
  s->unk22 = 0x1F;
}

