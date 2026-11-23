extern u8 D_02004E40[];
extern const void *D_082300E0[];
void sub_08004F18(void);
void sub_08004F80(void);
u8 sub_0800B368(const void *, u32, u32, u32);
u8 sub_0800B308(void);
int sub_08037440(u8 *s)
{
  u8 new_var;
  sub_08004F18();
  {
    u8 *p = D_02004E40;
    int m = 1;
    new_var = p[0x14];
    m = m | new_var;
    p[0x14] = m;
  }
  switch (s[5])
  {
    case 0:
      if (sub_0800B368(D_082300E0[s[0x469F]], 0, 0, 0))
    {
      s[5]++;
    }
      break;

    case 1:
      new_var = sub_0800B308();
      if (new_var)
    {
      u8 *p = s + 0x4699;
      u8 zero = 0;
      *p = 1;
      s[5] = zero;
    }
      break;

  }

  sub_08004F80();
  return 0;
}

