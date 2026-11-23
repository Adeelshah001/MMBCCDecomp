extern void sub_08023BC4(u8 *dst, u8 *base, u32 arg2);
extern void sub_08023CE4(u8 *p0, u8 *p1);
extern void sub_08023C38(u8 *dst, u8 *src, u8 sl);
extern u8 sub_08023D10(u8 *p);
extern void sub_08023D68(u8 *src, u16 *dst);
extern void sub_08023B64(u16 *p);
void sub_08023A7C(u8 *s, u8 *a1, u16 *a2)
{
  register u16 *r9;
  int new_var;
  register int mask;
  u8 *g;
  u8 *q;
  r9 = a2;
  g = (u8 *) 0x02000840;
  mask = 127;
  sub_08023BC4(g, a1, (s[0] + s[4]) & mask);
 do { sub_08023CE4(s, g); q = g; q += 16; new_var = (s[2] + s[6]) & mask; sub_08023C38(q, g, new_var); g[30] = sub_08023D10(q); sub_08023CE4(s, q); sub_08023D68(q, r9); } while (0);
  sub_08023B64(r9);
}
