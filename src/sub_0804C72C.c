typedef signed int s32;
extern u32 gUnknown_08106D7C[];
extern u8 gUnknown_08106DD0[];
extern void sub_0804CDE8(u32 *p, u32 v);
extern void sub_0804C5F4(u32 *p);
void sub_0804C72C(u16 idx)
{
  u32 *t2 = gUnknown_08106D7C;
  u8 *t1 = gUnknown_08106DD0;
  u8 *e1 = t1 + (idx * 8);
  u16 k = *((u16 *) (e1 + 4));
  u32 *p = (u32 *) t2[k * 3];
  u32 a = *p;
  u32 b = *((u32 *) e1);
  u32 f;
  if (a != b)
  {
    sub_0804CDE8(p, b);
    return;
  }
  f = p[1];
  if (((u16) f) == 0)
  {
    sub_0804CDE8(p, a);
    return;
  }
  k = ((s32) f) >= 0;
  if (k)
  {
    return;
  }
  sub_0804C5F4(p);
}

