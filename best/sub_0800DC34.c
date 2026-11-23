typedef signed short s16;
typedef signed int s32;
extern void sub_08000758(u16 *src, s16 *dst, s32 n);
extern void sub_080006DC(u16 col, s16 *dst, s32 n);
void sub_0800DC34(u16 *source, u32 color, s16 *dest, u32 factor)
{
  u16 *src = source;
  s16 *dst = dest;
  u32 shifted = color << 16;
  u32 col = shifted >> 16;
  u8 f = factor;
  u16 c;
  u16 tr;
  u16 tg;
  u16 tb;
  s32 i;
  u32 mask;
  u16 v;
  u8 vr;
  u8 vg;
  u8 vb;
  u8 d;
  if (f == 0)
  {
    sub_08000758(src, dst, 0x20);
    return;
  }
  if (f > 0x0E)
  {
    sub_080006DC(col, dst, 0x20);
    return;
  }
  tr = (u16) col;
  tr &= 0x1F;
  c = shifted >> 21;
  tg = c;
  tg &= 0x1F;
  c >>= 5;
  tb = c & 0x1F;
  mask = 0x1F;
  i = 0x0F;
  do
  {
    v = *src;
    vr = v & mask;
    v >>= 5;
    vg = v & mask;
    v >>= 5;
    vb = v & mask;
    d = (u8) (((((s32) tr) - ((s32) vr)) * f) >> 4);
    vr = vr + d;
    d = (u8) (((((s32) tg) - ((s32) vg)) * f) >> 4);
    vg = vg + d;
    d = (u8) (((((s32) tb) - ((s32) vb)) * f) >> 4);
    vb = vb + d;
    v = ((unsigned int) (vr | (vg << 5))) | (vb << 10);
    src++;
    *dst = v;
    dst++;
    i--;
  }
  while (i >= 0);
}

