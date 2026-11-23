extern void sub_0800D6E0(u8 *, u16, u8);
extern void sub_0800D9EC(u8 *, u8);
extern const u16 D_081705B0[];
extern u8 D_020031E4[][2];
void sub_0801B3AC(u8 *state)
{
  int mode;
  u8 *flags;
  int clear;
  u32 temp;
  int velocity;
  sub_0800D6E0(state, 0x24F, 0);
  sub_0800D9EC(state, 0);
  temp = D_081705B0[0];
  temp >>= 4;
  temp <<= 1;
  temp += (u32) D_020031E4;
  mode = 3;
  mode &= *((u8 *) temp);
 do { velocity = mode; if (velocity > 3) { mode = 3; } flags = state + 0x45; mode <<= 2; clear = -13; clear &= *flags; *flags = clear | mode; state[0x22] = 13; velocity = state[0x11]; if (!velocity) { velocity = 0x300; goto setMotion; } velocity = -0x300; setMotion: *((int *) (state + 0x58)) = velocity; } while (0);
  *((int *) (state + 0x60)) = 0;
  *((int *) (state + 0x5C)) = 0;
  *((int *) (state + 0x64)) = 0;
  state[0x12] = 0x14;
}
