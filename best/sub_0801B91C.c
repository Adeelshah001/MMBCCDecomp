struct S_B91C
{
  u8 pad0[9];
  u8 f9;
  u8 pad10[2];
  u32 f12;
  u8 f16;
  u8 pad17[3];
  u32 f20;
  u8 pad24[20];
  u32 f44;
};
extern void sub_0800D9FC(void *s);
extern void sub_08017464(u32 x);
extern u8 (*D_082267F4[])(struct S_B91C *);
extern u32 *D_082243D8[];
void sub_0801B91C(struct S_B91C *s)
{
  u8 ret = D_082267F4[s->f16](s);
  sub_0800D9FC(s);
  if (ret != 0)
  {
    u32 *addr = D_082243D8[s->f9];
    s->f12 = 2;
 do { do { s->f20 = addr[2]; sub_08017464(s->f44); } while (0); s->f44 = 0; } while (0);
  }
}
