void sub_08025290(u8 *p, u8 i);
void sub_080254B4(u8 *p, u8 i);
extern void sub_0802533C(u8 *p, u8 idx);
extern void sub_080253BC(u8 *s);
void sub_0802541C(u8 *s, u8 *p, u16 n);
extern void sub_0802526C(u8 *, u8);
extern u8 sub_08025324(u8 *, u8);
void sub_080254E0(u8 *s, u8 i)
{
  u8 *count = (*((u8 **) (s + 4))) + i;
  u8 limit = sub_08025324(*((u8 **) s), i);
  if (limit != (*count))
  {
    u8 *entry = (*((u8 **) (s + 4))) + i;
    int value = (*entry) + 1;
    if (i)
    {
      *entry = value;
    }
    else
    {
      *entry = value;
    }
    if ((*((u8 **) (s + 4)))[i] == 1)
    {
      sub_0802526C(s + 12, i);
    }
  }
}

