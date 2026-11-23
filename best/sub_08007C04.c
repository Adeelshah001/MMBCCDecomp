struct Slot4E18
{
  u8 unk0;
  s8 unk1;
  u16 unk2;
  u8 unk4;
  u8 unk5;
  u8 unk6;
  u8 unk7;
};
struct State3670
{
  u32 unk0;
  u32 unk4;
  u32 unk8;
};
struct Entry32B6C0
{
  u8 data[0x14];
};
extern struct Slot4E18 D_02004E18[];
extern struct State3670 D_02003670;
extern u16 D_08171EF4[];
extern struct Entry32B6C0 D_0832B6C0[];
extern u16 sub_08024670(u16);
extern void sub_08005268(const void *, u32);
extern void sub_08007C8C(u16, int);
int sub_08007C04(int raw0, int raw1)
{
  u32 arg0 = (u16) raw0;
  u32 arg1 = (u16) raw1;
  struct Slot4E18 *slot;
  int mask;
  int t;
  if (arg1 > 3)
  {
    return -1;
  }
  slot = &D_02004E18[arg1];
  t = slot->unk1;
  if ((t != 0) || (slot->unk2 != arg0))
  {
    slot->unk1 = 0;
    slot->unk2 = arg0;
    mask = -3;
    t = slot->unk7;
    mask &= t;
    slot->unk7 = mask;
    if (arg1 == 0)
    {
      u32 dst = (D_02003670.unk8 + (D_08171EF4[0] << 5)) - 0x06000000;
      u16 idx = sub_08024670(arg0);
      t = dst;
      sub_08005268(&D_0832B6C0[idx], t);
      sub_08007C8C(arg0, 0);
    }
  }
  return 0;
}

