typedef signed short s16;
extern u32 *sub_08020ED4(u8 a, u8 b, u8 c, u8 d);
u8 *sub_08021D10(void)
{
  s16 v = *((s16 *) ((*((u8 **) 0x020066f0)) + 10));
  register u8 *n;
  u8 *head;
  register u8 *prev;
  u16 i;
  u32 z;
  u32 t;
  if (v <= 5)
  {
    if (head)
    {
      return 0;
    }
    else
    {
      return 0;
    }
  }
  n = (u8 *) sub_08020ED4(0, 0, 0, 3);
  if (n != 0)
  {
    u8 z2 = 0;
    n[16] = 2;
    n[17] = z2;
    *((u8 **) (n + 40)) = n;
  }
  head = n;
  i = 1;
  z = 0;
  goto loop;
  loop:
  prev = n;

  n = (u8 *) sub_08020ED4(0, 0, 0, 3);
  if (n == 0)
  {
    goto done;
  }
  n[16] = 2;
  n[17] = (u8) i;
  *((u8 **) (n + 40)) = head;
  *((u32 *) (n + 44)) = z;
  *((u8 **) (prev + 44)) = n;
  t = ((u32) i) << 16;
  t += 0x80 << 9;
  i = (u16) (t >> 16);
  if (((s16) (t >> 16)) <= 5)
  {
    goto loop;
  }
  done:
  return head;

}

