extern u8 gUnknown_02000ED0[];
u32 sub_0800069C(u32 a)
{
  u32 base = (u32) gUnknown_02000ED0;
  u16 v = *((u16 *) (base + 0x2002));
  u32 vsh = ((u32) v) << 12;
  u16 *cursor = (u16 *) (base + 0x2000);
  u16 w = *cursor;
  u32 t = base + (((u32) w) * 4);
  u32 ret = vsh + t;
  u32 room = 0x400 - w;
  u32 q = (a + 3) >> 2;
  vsh = q;
  if (room >= vsh)
  {
    *cursor = (u16) (w + vsh);
    return ret;
  }
  return 0;
}

