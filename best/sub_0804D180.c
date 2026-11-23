void sub_0804D180(void *arg0)
{
  u8 *s = arg0;
  u32 new_var[2];
  u32 b_ext;
  u32 a_shifted;
  u32 b_shifted;
  u8 a;
  u8 c;
  u8 d;
  int prod;
  a = s[0x02];
  a_shifted = ((u32) a) << 24;
  new_var[0] = a_shifted >> 24;
  new_var[1] = s[0x03];
  b_shifted = ((u32) new_var[1]) << 24;
  d = b_shifted >> 24;
  b_ext = d;
  if (new_var[0] >= b_ext)
  {
    if ((a_shifted >> 25) >= b_ext)
    {
      s[0x1B] = 0x0F;
      goto label_BA;
    }
  }
  else
    if ((b_shifted >> 25) >= new_var[0])
  {
    s[0x1B] = 0xF0;
    goto label_BA;
  }
  s[0x1B] = 0xFF;
  a = s[0x02];
  new_var[1] = s[0x03];
  new_var[0] = ((u32) (a + new_var[1])) >> 4;
  goto label_CA;
  label_BA:
  a = s[0x02];

  new_var[1] = s[0x03];
  new_var[0] = ((u32) (a + new_var[1])) >> 4;
  s[0x0A] = new_var[0];
  if (new_var[0] > 0x0F)
  {
    new_var[0] = 0x0F;
  }
  label_CA:
  s[0x0A] = new_var[0];

  c = s[0x06];
  d = s[0x0A];
  prod = c;
  prod = prod * d;
  prod += 0x0F;
  prod >>= 4;
  s[0x19] = prod;
  s[0x1B] = s[0x1C] & s[0x1B];
}

