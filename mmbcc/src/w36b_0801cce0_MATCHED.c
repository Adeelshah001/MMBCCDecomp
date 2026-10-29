/* Wave 36-B MATCHED: 0x0801cce0, TRUE extent 80 B (see note), old_agbcc
   -O2 -mthumb-interwork, C + .s patch (w36b_0801cce0_patch.py).
   Structural twin of 0x0801b91c (same code shape, different table1).
   EXTENT NOTE: as with 0x0801b91c, the task list's 112 B is the
   func_list gap (0x0801cce0 to 0x0801cd50); this function's true
   extent is 80 B (70 B code + 2 B pad + 8 B pool: 0x082269ac,
   0x082243d8), ending at 0x0801cd30, where the same separate 32 B
   leaf function begins (not a B target, flagged for the coordinator).
   Patch: identical to w36b_0801b91c_patch.py (both table sequences
   base-first, index in r2).
   Callees: Sub_0800D9FC (ChipSlot_Tick) + Sub_08017464 via .set;
   _call_via_r1 via harness symdef _call_via_r1=0x0804dcd0.
   Harness: ./verify_patch.sh 0x0801cce0 80 .text.w36b_0801cce0
   w36b_0801cce0_MATCHED.c old w36b_0801cce0_patch.py
   _call_via_r1=0x0804dcd0 -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned int u32;
struct S { u8 pad0[9]; u8 f9; u8 pad10[2]; u32 f12; u8 f16; u8 pad17[3]; u32 f20; u8 pad24[20]; u32 f44; };
typedef u8 (*Func)(struct S *s);
extern u8 _call_via_r1(struct S *s);
extern void Sub_0800D9FC(struct S *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
extern void Sub_08017464(u32 x);
__asm__(".set Sub_08017464, 0x08017464");
__attribute__((section(".text.w36b_0801cce0")))
void Sub_0801CCE0(struct S *s)
{
    Func *t1 = (Func *)0x082269ac;
    u8 ret = t1[s->f16](s);
    Sub_0800D9FC(s);
    if (ret != 0) {
        u32 *t2 = (u32 *)0x082243d8;
        u32 *addr = t2 + s->f9;
        s->f12 = 2;
        s->f20 = ((u32 *)*(u32 **)addr)[2];
        Sub_08017464(s->f44);
        s->f44 = 0;
    }
}
