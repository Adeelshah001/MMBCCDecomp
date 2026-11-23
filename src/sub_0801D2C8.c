extern u32 *CreateBattleObject(u8 a, u8 b, u8 c, u8 d);
u32 *sub_0801D2C8(u8 a, u32 b, u32 c, u32 *d)
{
  register u32 type;
  u32 *n;
  type = 6;
  if (a == 0)
  {
 do { type = 5; } while (0);
  }
  n = CreateBattleObject(0, 1, 0, 12);
  if (n != 0)
  {
    u8 *q = (u8 *) n;
    u32 z = 0;
    u32 v0;
    u32 v1;
    q[16] = type;
    q[17] = z;
    v0 = d[0];
    v1 = d[1];
    *((u32 *) (q + 96)) = v0;
    *((u32 *) (q + 100)) = v1;
    *((u32 *) (q + 40)) = c;
    *((u32 *) (q + 44)) = b;
  }
  return n;
}
