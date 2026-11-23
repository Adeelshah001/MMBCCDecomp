extern u8 D_02000EC0[];
extern u16 D_020031E0[];
extern const u8 D_08173530[][2];
extern void sub_0800CF10(u8 *p, u8 v, int enable);
extern void sub_080006DC(int value, u32 dest, int count);
void sub_0800CC94(void)
{
  u8 *state = D_02000EC0;
  const u8 *table = (const u8 *) D_08173530;
  u32 entry = *state;
  u32 offset = entry * 2;
  u32 scaled;
  entry = *((const u8 *) (offset + ((u32) table)));
  scaled = entry << 24;
  if (((int) scaled) >= 0)
  {
    u16 *display;
    u16 mask;
    sub_0800CF10(state, scaled >> 24, 1);
 do { display = (u16 *) 0x020031E0; } while (0);
    display[0] |= 0x3800;
  }
  else
  {
    u16 *display = (u16 *) 0x020031E0;
    int mask = 0xC7FF;
    u32 block;
    *display = mask & (*display);
    block = 0x1F00;
    block &= display[5];
    sub_080006DC(0, (block << 3) + 0x06000000, 0x1000);
  }
}
