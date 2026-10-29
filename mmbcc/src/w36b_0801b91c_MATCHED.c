/* Wave 36-B MATCHED: 0x0801b91c, TRUE extent 80 B (see note), old_agbcc
   -O2 -mthumb-interwork, C + .s patch (w36b_0801b91c_patch.py).
   EXTENT NOTE: the task list gives 112 B (func_list gap 0x0801b91c to
   0x0801b98c), but this function's true extent is 80 B: 70 B code +
   2 B 00 00 pad + 8 B pool (0x082267f4, 0x082243d8), ending at
   0x0801b96c. The remaining 32 B (0x0801b96c-0x0801b98b) are a SEPARATE
   28 B leaf function + 4 B pool (table 0x082243d8) that func_list v2
   does not list; it is NOT part of this claim and NOT a B target.
   Verify over 80 B: ./verify_patch.sh 0x0801b91c 80 ... -> diffs: 0.
   The coordinator should add 0x0801b96c to func_list / assign it
   separately; do NOT extend this file to 112 B.
   Variant count: 2 (v2 = split table assignments; gcc still emitted
   index-first order, so the patch reorders). Key idioms: indirect
   call via _call_via_r1 (extern-only, harness symdef); u8 return kept
   in r4 across the ChipSlot_Tick call; second table deref via an
   address variable (address computed, then f12 = 2 stored, then the
   pointer dereferenced for f20).
   Patch (asserted exactly-1, reorder + rename, no size change): both
   table sequences changed from index-first (ldrb, lsl, ldr, add) to
   base-first (ldr, ldrb r2, lsl, add).
   Callees: Sub_0800D9FC (ChipSlot_Tick) + Sub_08017464 via .set;
   _call_via_r1 via harness symdef _call_via_r1=0x0804dcd0.
   Harness: ./verify_patch.sh 0x0801b91c 80 .text.w36b_0801b91c
   w36b_0801b91c_MATCHED.c old w36b_0801b91c_patch.py
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
__attribute__((section(".text.w36b_0801b91c")))
void Sub_0801B91C(struct S *s)
{
    Func *t1 = (Func *)0x082267f4;
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
