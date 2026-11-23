typedef short s16;
extern u16 sub_08024670(u16 v);
extern void sub_08000758(void *dst, void *src, u32 n);
extern void sub_080006DC(u16 v, void *dst, u32 n);
extern void sub_08009F78(u8 a, u16 b);
void sub_08009EDC(u8 a, u16 b)
{
  int new_var;
  u16 idx;
  u8 *p;
  u8 *new_var3[2];
  u16 *p1;
  u16 t1;
  u16 t2;
  u8 *vr;
  u8 *dst;
  s16 i;
  u8 *new_var2;
  idx = sub_08024670(b);
  new_var = idx * 20;
  new_var2 = ((u8 *) 0x0832b6c0) + new_var;
  p = new_var2;
  new_var3[0] = (u8 *) 0x08172140;
  p1 = (u16 *) ((a * 2) + ((u32) new_var3[0]));
  new_var3[1] = (u8 *) 0x0817386c;
  t1 = *p1;
  t2 = *((u16 *) ((t1 * 2) + ((u32) new_var3[1])));
  vr = ((u8 *) 0x06010000) + (t2 * 32);
  dst = p + (*((u32 *) p));
  i = 0;
  do
  {
    sub_08000758(dst, vr, 256);
    dst += 256;
    vr += 1024;
    i++;
  }
  while (i <= 6);
  sub_080006DC(0, vr, 256);
  sub_08009F78(a, b);
}

