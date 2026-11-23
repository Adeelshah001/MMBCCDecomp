extern const u16 D_081705B0[];
extern u16 D_020031E4[];
extern void sub_0800D6E0(u8 *state, int sprite, int enabled);
extern void sub_0800D9EC(u8 *state, int enabled);
void sub_08022E14(u8 *state)
{
  int new_var2;
  u8 priority;
  int flags = 0;
  u8 *timer;
  const u8 *priorityByte;
  int checked;
  int new_var;
  u8 startFlags;
  u8 *attributes;
  *((volatile u32 *) (state + 0x6C)) = flags;
  startFlags = 2;
  startFlags |= state[0xA];
  startFlags |= 1;
  state[0xA] = startFlags;
  new_var = 3;
  new_var2 = 13;
  sub_0800D6E0(state, 0x351D, 0);
  sub_0800D9EC(state, 0);
  priorityByte = (const u8 *) (&D_020031E4[D_081705B0[0] >> 4]);
  priority = new_var;
  priority &= *priorityByte;
  checked = priority;
  if (checked > 3)
  {
    do
    {
      priority = 3;
    }
    while (0);
  }
  attributes = state + 0x45;
  checked = priority << 2;
  flags = -new_var2;
  flags &= *attributes;
  flags |= checked;
  *attributes = flags;
  timer = state + 0x22;
  flags = 0;
  *timer = flags;
  *(u32 *)(state + 0x50) = flags;
  *(u32 *)(state + 0x54) = 0x3000;
}
