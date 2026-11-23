extern void sub_0800D6E0(u8 *, u16, u8);
extern void sub_0800D9EC(u8 *, u8);
extern u32 sub_080052A0(void);
extern const u16 D_081705B0[];
extern u8 D_020031E4[][2];
void sub_0801DDC4(u8 *state)
{
  u8 *motion;
  u32 address;
  int mode;
  int compare;
  int oldFlags;
  int zero;
  {
    int mask = 1;
    zero = 0;
    mask |= ((vu8 *) state)[0x0A];
    ((vu8 *) state)[0x0A] = mask;
  }
  motion = state + 0x50;
  *((int *) (motion + 0x1C)) = zero;
  {
    int mask = 2;
    oldFlags = ((vu8 *) state)[0x0A];
    mask |= oldFlags;
    ((vu8 *) state)[0x0A] = mask;
  }
  sub_0800D6E0(state, 0x501, 0);
  sub_0800D9EC(state, 0);
  if (!state[0x11])
  {
    {
      int value = sub_080052A0();
      int mask = 7;
      mask &= value;
      mask += 0x10;
      state[0x12] = mask;
    }
    state[0x13] = sub_080052A0();
    {
      int value = sub_080052A0();
      int mask = 15;
      mask &= value;
      mask += 8;
      mask <<= 8;
      *((int *) (state + 0x60)) = mask;
    }
    {
      int value = sub_080052A0();
      mode = 3;
      mode &= value;
      mode = -mode;
      mode = ((u32) mode) << 8;
      *((int *) (state + 0x64)) = mode;
    }
    goto setMode;
  }
  {
    int value = sub_080052A0();
    int mask = 15;
    value &= mask;
    state[0x12] = value + 0x18;
    value = sub_080052A0();
    mask &= value;
    oldFlags = mask << 4;
    state[0x13] = oldFlags;
    *((int *) (state + 0x60)) = 0x1400;
    *((int *) (state + 0x64)) = zero;
  }
  setMode:
  address = D_081705B0[0];

  address >>= 4;
  address <<= 1;
  address += (u32) D_020031E4;
  mode = 3;
  mode &= *((u8 *) address);
  compare = mode;
  if (compare > 3)
  {
    mode = 3;
  }
  compare = (u32) (state + 0x45);
  mode <<= 2;
  {
    int mask = -13;
    oldFlags = *((u8 *) compare);
    mask &= oldFlags;
    mask |= mode;
    *((u8 *) compare) = mask;
  }
}

