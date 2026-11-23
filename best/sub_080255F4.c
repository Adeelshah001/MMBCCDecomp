void sub_08025638(u8 *p, u8 idx, u8 val);
u8 sub_08025654(u8 *base, u8 idx);
void sub_080255F4(u8 *s)
{
  u16 i;
  u8 *entries;
  u8 *new_var;
  u32 value;
  u32 mask;
  s[1] = 0;
 do { i = 0; entries = s + 2; } while (0);
  mask = 0xff;
  do
  {
    short index = i;
    u8 *entry = &entries[index];
    u32 flags = *entry;
    flags |= mask;
    *entry = flags;
    i = index + 1;
  }
  while (((short) i) <= 9);
  value = s[12];
  new_var = s + 16;
  value |= mask;
  s[12] = value;
  value = s[13];
  value = mask | value;
  s[13] = value;
  *((u16 *) (s + 14)) = 0;
  *((u16 *) new_var) = 20;
}

extern void sub_08025308(u8 *table);
extern void sub_0802538C(u8 *s);
void InitChipIndexTables(u8 *s, u8 *b);
