struct ChipPosition
{
  int x;
  int y;
};
extern const u32 * const D_082243D8[];
extern void sub_0800D9FC(u8 *o);
void sub_0801DD48(u8 *o)
{
  u8 *q = *((u8 **) (o + 40));
  u32 phase;
  u32 lookup;
  if (o[13] >= 1U)
  {
    goto updateAnimation;
  }
  {
    lookup = q[12];
    if (lookup <= 1)
    {
      int sum;
      *((struct ChipPosition *) (o + 80)) = *((struct ChipPosition *) (q + 80));
      sum = (*((int *) (o + 80))) + (*((int *) (o + 96)));
      *((int *) (o + 80)) = sum;
      *((int *) (o + 84)) += *((int *) (o + 100));
      {
        u8 *t = q;
        int face;
        t += 35;
        face = 15;
        face &= *t;
        if (face == 1)
        {
          *((int *) (o + 80)) = -sum;
        }
      }
    }
    else
    {
      o[13] = ++phase;
    }
  }
  updateAnimation:
  if (((u8) (o[119] - 3)) <= 1)
  {
    u8 *p = *((u8 **) (o + 44));
    (*p)++;
    {
      u32 entryAddress;
      lookup = (u32) D_082243D8;
      q = (u8 *) ((u32) o[9]);
      entryAddress = lookup + (((u32) q) * 4);
      *((u32 *) (o + 12)) = 2;
      *((u32 *) (o + 20)) = (*((const u32 * const *) entryAddress))[2];
    }
  }

  sub_0800D9FC(o);
}

