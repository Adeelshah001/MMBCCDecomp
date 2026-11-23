void sub_08003130(void *s, void *v);
void sub_08003724(void);
struct SpriteState03154
{
  u32 unk00;
  void *unk04;
  u32 unk08;
  u32 unk0C;
  u32 y : 8;
  u32 affineMode : 2;
  u32 objMode : 2;
  u32 mosaic : 1;
  u32 bpp : 1;
  u32 shape : 2;
  u32 x : 9;
  u32 matrixNum : 5;
  u32 size : 2;
  u16 tileNum : 10;
  u16 priority : 2;
  u16 paletteNum : 4;
  u16 unk16;
  u8 unk18;
  u8 unk19;
  u8 unk1A;
  u8 unk1B;
  u16 unk1C;
  u16 unk1E;
};
void sub_080031B8(struct SpriteState03154 *arg0, u32 arg1, u32 arg2)
{
  int m1;
  int m2;
  int m3;
  int m4;
  int r0;
  int r1;
  int r2;
  sub_08003130(arg0, sub_08003724);
  m1 = ~0x20;
  ((u8 *) arg0)[0x11] = m1 & ((u8 *) arg0)[0x11];
  m2 = 0x0F;
  ((u8 *) arg0)[0x15] = m2 & ((u8 *) arg0)[0x15];
  arg0->unk16 = 0;
  arg0->unk18 = 0;
  arg0->unk19 = 0;
  arg0->mosaic = 1;
  arg0->objMode = 0;
  arg0->priority = 2;
  arg0->unk08 = arg1;
  arg0->unk0C = arg2;
  r0 = ~0x3E;
  m3 = r0;
  r1 = ((u8 *) arg0)[0x13];
  r0 &= r1;
  r1 = 3;
  ;
  ((u8 *) arg0)[0x11] = (((u8 *) arg0)[0x11] = ((u8 *) arg0)[0x11]) | r1;
  r0 &= m3;
  ((u8 *) arg0)[0x13] = r0;
  m4 = ~0x01FF;
  ((u16 *) arg0)[0x09] = m4 & ((u16 *) arg0)[0x09];
  arg0->y = 0;
}

