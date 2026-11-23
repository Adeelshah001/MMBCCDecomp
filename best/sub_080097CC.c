extern void sub_08000758(u8 *src, u8 *dst, u32 size);
extern u32 gUnknown_081720B4[];
extern u32 *gUnknown_081720CC[];
void sub_080097CC(u8 a, u16 b, u16 c, u8 d, short e)
{
  u32 off = c;
  u8 *dst;
  u32 *row;
  u32 ent;
  u32 base;
  off += ((u32) e) << 5;
  off += d;
  off <<= 5;
  dst = (u8 *) (0x06010000 + off);
  base = gUnknown_081720B4[a];
  row = gUnknown_081720CC[a];
  ent = row[b];
  sub_08000758((u8 *) (base + (((u32) ((u16 *) ent)[0]) << 5)), dst, 32);
  sub_08000758((u8 *) (base + (((u32) ((u16 *) ent)[1]) << 5)), (u8 *) (0x06010020 + off), 32);
  sub_08000758((u8 *) (base + (((u32) ((u16 *) ent)[2]) << 5)), (u8 *) (0x06010400 + off), 32);
  sub_08000758((u8 *) ((((u32) ((u16 *) ent)[3]) << 5) + base), (u8 *) (0x06010420 + off), 32);
}

