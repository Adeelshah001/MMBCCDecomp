extern u8 gUnknown_08173530[];
extern u32 sub_0802260C(u8 idx);
extern u8 sub_08022634(u32 node);
extern void sub_0800520C(int x);
int sub_0800D1E0(u8 *p0, u8 *p1, u8 *p2, u8 *p3)
{
  u8 v2 = *p2;
  u8 v3 = *p3;
  u8 v1 = *p1;
  int ret = 1;
  u8 v16 = p0[6];
  int new_var;
  switch (v1)
  {
    case 0:
      v1 = 1;

    case 1:
    {
      u8 *base = gUnknown_08173530;
      int off = v16 * 2;
      u32 node;
      int five = 5;
      base++;
      node = sub_0802260C(*(base + off));
      *((u32 *) (p0 + 12)) = node;
      if (node == (new_var = 0))
      {
        break;
      }
      v1 = (u8) (v1 + 1);
      p0[9] &= -five;
    }

    case 2:
      if (sub_08022634(*((u32 *) (p0 + 12))) == new_var)
    {
      break;
    }
      sub_0800520C(1);
      ret = new_var;
      break;

  }

  *p2 = v2;
  *p3 = v3;
  *p1 = v1;
  return ret;
}

