struct Inner
{
  u8 _pad[0x0D];
  u8 unkD;
  u16 unkE;
};
struct Outer
{
  struct Inner *unk0;
  u8 _pad04[4];
  u32 unk8;
};
extern void sub_080247E8(void);
extern void sub_080112BC(struct Outer *);
u32 sub_080119DC(struct Outer *arg0)
{
  if (arg0->unk0->unkD != 0)
  {
    arg0->unk0->unkD += 0;
    sub_080247E8();
  }
  if (arg0->unk0->unkE != 0)
  {
    arg0->unk8 = arg0->unk0->unkE + arg0->unk8;
  }
  sub_080112BC(arg0);
  return -1;
}

