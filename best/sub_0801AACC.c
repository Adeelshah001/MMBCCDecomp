extern u32 D_082243D8[];
extern u8 D_082266D8[];
extern void sub_0800DD08(int *out, u8 *p);
extern void sub_080178A8(u8 a, unsigned b, short c, short d, u32 e);
extern void sub_0801AB34(u8 *p);
void sub_0801AACC(u8 *p)
{
  register u8 *ptr = p;
  struct 
  {
    int a;
    int b;
  } tmp;
  unsigned long long new_var;
  u32 *entry;
  entry = (u32 *) ((((u32) ptr[9]) * 4) + (new_var = (u32) D_082243D8));
  *((u32 *) (ptr + 12)) = 1;
  *((u32 *) (ptr + 20)) = *((u32 *) ((*entry) + 4));
  ptr[10] &= 0xFD;
  ptr[10] &= 0xFE;
  sub_0800DD08((int *) (&tmp), ptr);
  {
    register int a = tmp.a;
    register int b = tmp.b;
    sub_080178A8(D_082266D8[ptr[16]], (((u32) ptr[35]) << 28) >> 28, (short) a, (short) b, *((u32 *) (ptr + 44)));
  }
  sub_0801AB34(ptr);
}

