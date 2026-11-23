extern void sub_0800D6E0(u8 *, int, int);
extern void sub_0800D9EC(u8 *, int);
extern void sub_0804A378(int);
extern const u16 D_081705B0[];
extern u16 D_020031E4[];
inline static int LimitMode(int mode)
{
  if (mode > 3)
    mode = 3;
  return mode;
}

void sub_0801AE00(u8 *state)
{
  int mode;
  int clear;
  u8 *flags;
  u8 *entry;
  sub_0800D6E0(state, 0x22B, 0);
  sub_0800D9EC(state, 0);
  entry = (u8 *) (&D_020031E4[D_081705B0[0] >> 4]);
  mode = 3;
  mode &= *entry;
 do { mode = LimitMode(mode); flags = state + 0x45; mode <<= 2; clear = 13; } while (0);
  clear = -clear;
  *flags = (clear & (*flags)) | mode;
  state[0x22] = 0xD;
  *((u32 *) (state + 0x58)) = 0x600;
  *((u32 *) (state + 0x60)) = 8;
  *((u32 *) (state + 0x5C)) = 0x600;
  *((u32 *) (state + 0x64)) = 8;
  sub_0804A378(0x96);
}
