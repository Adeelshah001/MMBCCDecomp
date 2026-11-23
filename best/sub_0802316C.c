extern const u16 D_081705B0[];
extern u16 D_020031E4[];
inline static int LimitMode(int mode)
{
  if (mode > 3)
    mode = 3;
  return mode;
}

void sub_0802316C(u8 *state)
{
  int mode;
  int clear;
  int enabled;
  int active;
  u8 *flags;
  u8 *entry;
  *((u32 *) (state + 0x6C)) = 0;
  enabled = 2;
  enabled |= state[0xA];
  active = 1;
  state[0xA] = enabled | active;
  sub_0800D728(state, 0x3813, 0);
  entry = (u8 *) (&D_020031E4[D_081705B0[1] >> 4]);
  mode = 3;
  mode &= *entry;
  mode = LimitMode(mode);
  flags = state + 0x45;
  entry = flags;
  mode <<= 2;
  clear = 13;
  clear = -clear;
  *entry = (clear & (*entry)) | mode;
  state[0x22] = 0;
}

