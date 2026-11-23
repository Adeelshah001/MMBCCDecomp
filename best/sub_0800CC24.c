extern vu8 D_02000EC0[];
extern u8 D_02003670[];
extern u16 D_020031EA[];
extern u16 D_02003220[];
void sub_0800CC24(void)
{
  vu8 *state = D_02000EC0;
  vu8 *cursor = state;
  u32 i = 0;
  unsigned short new_var;
  u8 *scene = D_02003670;
  u16 *display = D_020031EA;
  u16 *window = D_02003220;
  int clearValue = 0;
  int zero;
  u8 *flags;
  unsigned short mask;
  int control;
  clear:
  *(cursor++) = clearValue;

  i <<= 16;
  control = 0x10000;
  i += control;
  i >>= 16;
  if (i <= 15)
  {
    goto clear;
  }
  zero = 0;
  state[7] = zero;
  state[6] = zero;
  state[0] = zero;
  mask = 0x11AE;
  flags = (u8 *) (mask + ((u32) scene));
  if (1)
  {
    mask = 7;
    mask &= *flags;
    *flags = mask;
    display[0] = 0x4204;
    display[7] = zero;
    display[8] = zero;
    mask = 0x3F3F;
    ;
  }
  new_var = 0;
  window[new_var] = mask;
  i = 0x060A;
  window[1] = i;
}

