inline int inline_fn(u32 arg0)
{
  return arg0 & 0x1F;
}

void sub_0800DD74(u16 *src, u16 *dst)
{
  s8 i;
  u32 c;
  u32 r;
  u32 g;
  u32 b;
  u32 r2;
  u32 g2;
  u16 gray;
  for (i = 0; i < 16; i++)
  {
    c = *(src++);
    r = inline_fn(c);
    c >>= 5;
    g = inline_fn(c);
    c >>= 5;
    b = inline_fn(c);
    r2 = (r * 18432) >> 16;
    g2 = (g * 38912) >> 16;
    r = (b * 6144) >> 16;
    r2 += g2;
    r += r2;
    gray = r;
    gray = (gray > 0x1F) ? (0x1F) : (gray);
    *(dst++) = (gray | (gray << 5)) | (gray << 10);
  }

}

