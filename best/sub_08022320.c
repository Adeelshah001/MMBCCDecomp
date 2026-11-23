extern const u16 D_081705B0[];
extern const u16 D_082270F4[];
extern u16 D_020031E4[];
void sub_0800D6E0(u8 *, u16, u8);
void sub_0800D9EC(u8 *, u8);
void sub_08022320(u8 *state)
{
  u32 value = *((u32 *) (state + 0x28));
  int flags = 0;
  const u16 *chips;
  u8 startFlags;
  const u8 *priorityByte;
  u8 priority;
  int checked;
  u8 *attributes;
  u8 *timer;
  *((volatile u32 *) (state + 0x6C)) = flags;
  startFlags = 2;
  startFlags |= state[0x0A];
  startFlags |= 1;
  state[0x0A] = startFlags;
  state[0x12] = ((u8 *)value)[0x12];
  chips = D_082270F4;
  value = state[0x11];
  sub_0800D6E0(state, chips[value], 0);
  sub_0800D9EC(state, state[0x12]);
  priorityByte = (const u8 *) (&D_020031E4[D_081705B0[flags = 0] >> 4]);
  priority = 3;
  priority &= *priorityByte;
  checked = priority;
  if (checked > 3)
  {
    priority = 3;
  }
  attributes = state + 0x45;
  checked = priority << 2;
  flags = -13;
  flags &= *attributes;
  flags |= checked;
  *attributes = flags;
  timer = state + 0x22;
  flags = 0;
  *timer = flags;
  state[0x12] = 0xFF;
}
