typedef short s16;
struct ChipPosition
{
  int x;
  int y;
};
extern u32 D_082243D8[];
extern const s16 D_0804E05C[];
extern void sub_0800D9EC(u8 *o, int idx);
extern int sub_080052A0(void);
extern void sub_0800D9FC(u8 *o);

void sub_0801DE84(u8 *o)
{
  int v12;
  int newX;
  u8 *new_var2;
  int new_var[2];
  s8 tilt;
  int r;
  u32 t3;
  v12 = o[0x12];
  v12--;
  o[0x12] = v12;
  if ((v12 << 24) == 0)
  {
    u32 *tbl = D_082243D8;
    u32 *e;
    newX = o[9];
    e = tbl + newX;
    *((u32 *) (o + 0x0C)) = 2;
    *((u32 *) (o + 0x14)) = *((u32 *) (((u8 *) (*e)) + 8));
  }
  else
  {
    u32 z = ((u32) v12) >> 16;
    if (((u8) (v12 + (z >> 16))) == 4)
    {
      sub_0800D9EC(o, 4);
    }
  }
  if (o[0x0D] == 0)
  {
    o[0x0D]++;
    if (o[0x11] == 0)
    {
      int m;
      r = sub_080052A0();
      m = 3;
      o[0x0E] = (r & m) + 3;
      m &= sub_080052A0();
      m += 2;
      o[0x0F] = m;
    }
    else
    {
      o[0x0E] = 2;
      o[0x0F] = 7;
    }
  }
  *((struct ChipPosition *) (o + 0x50)) = *((struct ChipPosition *) (o + 0x58));
  *((int *) (o + 0x54)) -= *((int *) (o + 0x64));
  {
    int radius;
    t3 = (u32)D_0804E05C;
    new_var[0] = (*(const s16 *)(t3 + ((o[0x13] + 0x40) << 1)) * (radius = *((int *) (o + 0x60)))) >> 8;
    new_var[1] = (*(const s16 *)(t3 + (o[0x13] << 1)) * radius) >> 9;
  }
  tilt = (-new_var[1]) >> 10;
  if (tilt < (-15))
  {
    tilt = -15;
  }
  else
    if (tilt > 15)
  {
    tilt = 15;
  }
  tilt += 16;
  o[0x22] = tilt;
  new_var2 = o + 0x50;
  newX = (*((int *) new_var2)) + new_var[0];
  *((int *) new_var2) = newX;
  *((int *) (o + 0x54)) += new_var[1] >> 1;
  if (o[0x11] == 0)
  {
    newX = o[0x0E];
    *((int *) (o + 0x60)) += newX << 8;
    t3 = o[0x0F];
    *((int *) (o + 0x64)) += t3 << 8;
  }
  else
  {
    r = o[0x0E];
    *((int *) (o + 0x64)) += r << 8;
    if (newX < 0)
    {
      v12 = o[0x13];
      newX = o[0x0F];
      o[0x13] = v12 + newX;
    }
    else
    {
      t3 = o[0x13];
      v12 = o[0x0F];
      o[0x13] = t3 - v12;
    }
  }
  o[0x21] = 7;
  sub_0800D9FC(o);
}
