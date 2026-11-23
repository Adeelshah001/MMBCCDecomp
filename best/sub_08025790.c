void sub_0802571C(u8 *entry, u8 id, u8 value);
struct DeckEntry
{
  u8 amount;
  u8 id;
  u8 unk02[2];
};
struct DeckState257
{
  u8 unk00;
  u8 defaultId;
  u8 unk02[12];
  u16 base;
  u8 unk10[4];
  struct DeckEntry entries[30];
  u8 unk8C;
  u8 unk8D;
};
extern u8 sub_08025654(struct DeckState257 *, u8);
extern void sub_080255F4(struct DeckState257 *);
extern u32 sub_080266F0(u32);
u8 sub_08025730(struct DeckState257 *deck, u8 id);
void sub_080256E0(struct DeckState257 *deck);
u16 sub_08025790(struct DeckState257 *deck)
{
  u32 id = sub_08025730(deck, 0);
  u32 value;
  if (id == 0)
  {
    id = deck->defaultId;
  }
  value = sub_080266F0(id);
  id = deck->base + value;
  return id;
}

