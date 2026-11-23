extern const u16 D_081705B0[];
extern u16 D_020031E4[];
extern void sub_0800D770(u8 *state, u16 sprite, u8 frame);
extern void sub_0800D9EC(u8 *state, u8 index);
extern void sub_0800DD4C(u8 *state, int x, int y);
extern void sub_0804A378(int soundId);
void sub_0801BEA0(u8 *state)
{
  int priority;
  int flags;
  u8 *attributes;
  u32 offset;
  u32 controls;
  sub_0800D770(state, 0x828, 0);
  sub_0800D9EC(state, 0);
 do { offset = (u32) D_081705B0; offset = *((const u16 *) offset); offset >>= 4; offset <<= 1; controls = (u32) D_020031E4; offset += controls; priority = 3; offset = *((u8 *) offset); priority &= offset; flags = priority; if (flags > 3) { priority = 3; } attributes = state + 0x45; } while (0);
  priority <<= 2;
  flags = -13;
  flags &= *attributes;
  flags |= priority;
  *attributes = flags;
  state[0x22] = 13;
  sub_0800DD4C(state, -0x3C00, 0);
  sub_0804A378(0x9F);
}
