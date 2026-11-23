extern u16 sub_08024670(u16);
extern u8 sub_0802468C(u16);
extern void sub_08002904(u32, u8, u8);
extern u16 D_08172140[];
extern u8 D_0832B6CC[];
extern u8 D_081738F2[];
void sub_08009F78(u8 arg0, u16 arg1)
{
  u32 r4 = (u32) arg0;
  u32 r6 = (u32) arg1;
  u32 r0;
  u32 r5;
  char r1;
  u16 r4_half;
  u8 r2;
  r0 = r6;
  r0 = sub_08024670(r0);
  r0 = (u32) ((u16) r0);
  r5 = r0 * 0x14;
  r4_half = D_08172140[r4];
  r4 = (u32) r4_half;
  r5 += (u32) D_0832B6CC;
  r0 = r6;
  r0 = sub_0802468C(r0);
  r0 = (u32) ((u8) r0);
  r1 = r0;
  r2 = D_081738F2[r4 * 2];
  r0 = r5;
  sub_08002904(r0, r1, r2);
}

