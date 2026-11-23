struct Q
{
  u8 b0;
  s8 b1;
  u16 h2;
  s8 b4;
  s8 b5;
  u8 b6;
  u8 b7;
};
extern void sub_08009EDC(u8 a, u16 b);
extern void sub_080099FC(u8 a, u16 b, u8 c);
void sub_0802329C(u8 *p)
{
  u8 *new_var;
  struct Q *q = *((struct Q **) (p + 40));
  u8 flag = 4;
  flag &= q->b7;
  if (flag == 0)
  {
    int v = q->b1;
    if (v == (96 * 0))
    {
      p[13] = 1;
      p[15] = flag;
      p[14] = flag;
      *((u32 *) (p + 88)) = q->h2;
      *((int *) (p + 96)) = q->b4;
      *((int *) (p + 100)) = q->b5;
      sub_08009EDC(q->b0, q->h2);
    }
    else
      if (v == 1)
    {
      p[13] = 2;
      p[15] = flag;
      p[14] = flag;
      *((u32 *) (p + 88)) = q->h2;
      flag = 100;
      new_var = p + flag;
      *((int *) (p + 96)) = q->b4;
      *((int *) new_var) = q->b5;
      sub_080099FC(q->b0, q->h2, q->b6);
    }
  }
}

