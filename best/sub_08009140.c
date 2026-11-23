extern void sub_08002300(u32 a, u32 b);
extern void sub_080006DC(u16 v, void *dst, u32 n);
extern void sub_08000758(void *src, void *dst, u32 n);
extern void sub_08007BEC(u32 a, u32 b);
void sub_08009140(void)
{
  u8 *base = (u8 *) 0x02003670;
  u8 *p;
  int new_var;
  p = base + 4;
  sub_08002300(0x0830b37c, 150 << 7);
  sub_080006DC(0x1111, (void *) ((*((u32 *) (p + 4))) + (200 << 3)), 32);
  sub_08000758((void *) 0x0806bce0, (void *) ((*((u32 *) (p + 4))) + (204 << 3)), 32);
  sub_080006DC(0x3333, (void *) ((*((u32 *) (p + 4))) + (208 << 3)), 32);
  sub_08002300(0x0830b3e0, 0x46a0);
  sub_08000758((void *) 0x08063fd4, (void *) ((*((u32 *) (p + 4))) + (190 << 5)), 192 << 1);
  sub_08002300(0x0830b78c, 0x5b20);
  sub_08002300(0x0830b3cc, 0x5a40);
  {
    u8 *r = (u8 *) 0x0805c95c;
    sub_08007BEC((u32) r, 11);
    sub_08007BEC(((u32) r) + 32, 12);
    sub_08007BEC(((u32) r) + 64, 13);
    r += 96;
    sub_08007BEC((u32) r, 14);
  }
  sub_08007BEC(0x0806eea0, 10);
  base += 0x11ae;
  new_var = 248;
  if (((*base) & new_var) != 16)
  {
    sub_08007BEC(0x0806b560, 7);
  }
}

