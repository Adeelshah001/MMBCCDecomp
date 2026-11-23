extern u8 D_02003670[];
extern void sub_08004EE0(void);
extern void sub_08004EF4(void);
extern void sub_080052DC(u8, u8, u8, u8);
extern void sub_080053A0(void);
extern void sub_0800B8D0(void);
void sub_08004E60(u8 mode)
{
  u32 base = (u32) D_02003670;
  u32 offset;
  u32 saved = (((u32) (*((u8 *) (base + 0x11AE)))) << 29) >> 31;
  u32 *new_var;
  u8 *cursor = (u8 *) base;
  u32 i = 0;
  int zero = 0;
  offset += 9;
 do { clearNext: *(cursor++) = zero; i <<= 16; } while (0);
  i += 0x10000;
  new_var = &offset;
  i >>= 16;
  if (i <= (*new_var))
  {
    goto clearNext;
  }
  offset = 0x11AE;
  base += *new_var;
  offset = ((u32) mode) << 3;
  i = 7;
  zero = *((u8 *) base);
  i &= zero;
  i |= *new_var;
  zero = saved << 2;
  offset = -5;
  i &= *new_var;
  i |= zero;
  offset += 2;
  i &= *new_var;
  *((u8 *) base) = i;
  sub_080053A0();
  i = 0xF8;
  base = *((u8 *) base);
  i &= base;
  if (i != 8)
  {
    sub_08004EE0();
  }
  sub_080052DC(0, 0xA0, 0, 0xF0);
  sub_0800B8D0();
  sub_08004EF4();
}
