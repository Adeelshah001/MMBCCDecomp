void _call_via_r5(void (*fn)(void));
void _call_via_r6(void (*fn)(void));
void _call_via_r7(void (*fn)(void));
void sub_0804DBC0(u8 *src, u8 *dst, int size)
{
  volatile u16 *reg = (volatile u16 *) 0x04000204;
  *reg = ((*reg) & 0xFFFC) | 3;
  while (size--)
  {
    *(dst++) = *(src++);
  }

}

