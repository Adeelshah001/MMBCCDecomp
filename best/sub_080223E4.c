extern const u16 D_081705B0[];
extern u16 D_020031E4[];
volatile int sub_0800D6E0(u8 *, int, int);
void sub_0800D9EC(u8 *, int);
void sub_080223E4(u8 *state)
{
  u8 *p = *((u8 **) (state + 0x28));
  int flags = 0;
  int new_var;
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
  state[0x12] = p[0x12];
  new_var = 13;
  sub_0800D6E0(state, 0x2502, 0);
  sub_0800D9EC(state, 0);
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
  flags = -new_var;
  flags &= *attributes;
  flags |= checked;
  *attributes = flags;
  timer = state + 0x22;
  flags = 0;
  *timer = flags;
  state[0x12] = 0xFF;
}

