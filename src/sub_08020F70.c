extern const u32 D_08173760[];
extern const u8 D_08226F34[];
extern const u16 D_0817386C[];
extern const u16 D_081738F2[];
extern u8 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);
extern void sub_08002300(u32 *p, u32 a);
extern void sub_08002904(u32 *p, u32 a, u32 b);
u8 *sub_08020F70(u32 rawKind, u32 bb, u32 cc)
{
  u8 a = rawKind;
  u8 *new_var;
  register u8 *r5;
  if (a != 14)
  {
    r5 = sub_08020ED4(0, 0, 0, 0);
  }
  else
  {
    r5 = sub_08020ED4(0, 1, 0, 0);
  }
  if (r5 != 0)
  {
    r5[16] = 0;
    r5[17] = a;
    *((u32 *) (new_var = r5 + 40)) = bb;
    *((u32 *) (r5 + 44)) = cc;
  }
  {
    const u8 *resources = (const u8 *) D_08173760;
    u8 *r4 = *((u8 **) (resources + 88));
    const u8 *indices = D_08226F34;
    u32 index = r5[17];
    indices = index + indices;
    r4 += ((u32) (*indices)) << 2;
    r4 += *((u32 *) r4);
    {
      const u16 *graphics = D_0817386C;
      const u16 *palette;
      u32 amount = graphics[22];
      index = amount << 5;
      sub_08002300((u32 *) r4, index + 65536);
      r4 += 12;
      palette = D_081738F2;
      amount = palette[22];
      sub_08002904((u32 *) r4, 0, (u8) amount);
    }
  }
  return r5;
}

