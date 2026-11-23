extern void sub_08006578(int x, int y, u8 width, u8 height, u16 a, u16 b);
extern u32 D_02003670;
extern u16 D_08171EF4[];
extern const u8 sub_08172020[];
void sub_08007D64(u16 arg0, u8 arg1, unsigned char arg2)
{
  u32 idx = (D_02003670 >> 1) & 3;
  int new_var;
  if (arg0 == 0)
  {
    u16 base = D_08171EF4[0];
    s8 i;
    for (i = 0; i < 7; i++)
    {
      s8 y = arg2;
      const u8 *tbl = sub_08172020 + 0xE6;
      new_var = 8;
      sub_08006578((s8) arg1, (s8) (y + i), 8, 1, base + tbl[i + (idx * new_var)], D_08171EF4[1]);
    }

  }
}

