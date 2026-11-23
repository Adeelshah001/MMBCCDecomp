void *sub_08021C0C(u32 arg0);
extern void QueueResourceTransfer(void *, u32);
extern void sub_0800288C(void *, u32);
void sub_0802366C(void)
{
  u8 *g = (u8 *) 0x08173760;
  u8 *base = *((u8 **) (g + 0x2C));
  int new_var2;
  u32 off = (*((u32 *) (base + 0x10))) + 0x10;
  u8 *ptr = base + off;
  int new_var;
  new_var2 = 0x16;
  new_var = new_var2;
  QueueResourceTransfer(ptr, ((*((u16 *) (0x0817386C + new_var))) << 5) + 0x10000);
  sub_0800288C(ptr + 0x0C, ((*((u16 *) (0x081738F2 + new_var2))) << 5) + 0x200);
}

extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);
u8 *sub_080236B0(u32 a, u8 *b, u8 *c, u8 *d);
