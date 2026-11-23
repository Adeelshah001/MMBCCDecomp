extern void sub_0800D6E0(u8 *state, int a, int b);
extern void sub_0800D9EC(u8 *state, int a);
void sub_080207EC(u8 *state)
{
  u8 *parent = *((u8 **) (state + 0x28));
  u8 startFlags;
  u8 priority;
  int checked;
  u8 *attributes;
  int mask;
  int velocity;
  u8 new_var;
  *((u32 *) (state + 0x6C)) = 0;
  startFlags = 2;
  startFlags |= state[0x0A];
  startFlags |= 1;
  state[0x0A] = startFlags;
  sub_0800D6E0(state, 0x411A, 0);
  sub_0800D9EC(state, state[0x78]);
  priority = parent[0x45];
  priority <<= 4;
  priority >>= 6;
  checked = priority;
  if (checked > 3)
  {
    priority = 3;
  }
  attributes = state + 0x45;
  checked = priority << 2;
  mask = -13;
  mask &= *attributes;
  mask |= checked;
  *attributes = mask;
  new_var = state[0x11];
  priority = parent[0x22];
  state[0x22] = priority;
  checked = new_var;
  velocity = 2;
  velocity &= checked;
  if (velocity)
  {
    velocity = 0x15400;
    goto setMotion;
  }
  velocity = -0x6400;
  setMotion:
  *((int *) (state + 0x60)) = velocity;

  *((int *) (state + 0x64)) = 0;
}

