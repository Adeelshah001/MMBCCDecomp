extern void sub_0804E008(u8 *dst, int val, int n);
extern void sub_0802518C(u8 *q, u8 *buf);
extern void sub_08006A54(u8 *buf, int a, int b, int c, int d);
extern int sub_080251D8(u8 *q);
extern void sub_080070F0(u8 v, int a, int b, int c);
extern void sub_08006DD8(u8 v, int a, int b, int c, int d);
inline volatile char inline_fn(u8 *arg0, int arg1)
{
  return arg0[10] & arg1;
}

inline int inline_fn2()
{
  return 22;
}

inline u8 *inline_fn23(u8 *arg0)
{
  return arg0 + 6832;
}

void sub_08048084(u8 *s)
{
  u8 buf[8];
  u8 *q;
  u8 v;
  sub_0804E008(buf, 0, 8);
  if (inline_fn(s, 1))
  {
    q = inline_fn23(s);
    sub_0802518C(q, buf);
    sub_08006A54(buf, 4, 4, 4, 0);
    v = sub_080251D8(q);
    sub_080070F0(v, 10, 4, 0);
    sub_08006DD8(s[5959], 5, 7, 2, 0);
    sub_08006DD8(s[5958], 8, 7, 2, 0);
    sub_08006DD8(s[5957], 11, 7, 2, 0);
  }
  else
  {
    sub_08006DD8(0, 5, 7, 2, 0);
    sub_08006DD8(0, 8, 7, 2, 0);
    sub_08006DD8(0, 11, 7, 2, 0);
  }
  if (s[10] & 2)
  {
    q = s + 12772;
    sub_0802518C(q, buf);
    sub_08006A54(buf, 18, 4, 4, 0);
    v = sub_080251D8(q);
    sub_080070F0(v, 24, 4, 0);
    sub_08006DD8(s[11899], 19, 7, 2, 0);
    sub_08006DD8(s[11898], 22, 7, 2, 0);
    sub_08006DD8(s[11897], 25, 7, 2, 0);
  }
  else
  {
    sub_08006DD8(0, 19, 7, 2, 0);
    sub_08006DD8(0, inline_fn2(), 7, 2, 0);
    sub_08006DD8(0, 25, 7, 2, 0);
  }
}

