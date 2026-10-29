/* Wave 36-B MATCHED: 0x08007cf4, 112 B, old_agbcc -O2 -mthumb-interwork,
   C + .s patch (w36b_08007cf4_patch.py).
   Extent basis: next function start 0x08007d64 - 0x08007cf4 = 112,
   incl. 8 B literal pool (0x02004e18, 0x08171ef4) + trailing 00 00 pad
   to the next-function boundary (gas would emit c0 46).
   Variant count: 7 (v7 = m pinned to r1, callee returns int, OR as
   1 | f7, explicit trailing pad). Key idioms: m = -5 variable forces
   the negs form for the f7 &= (mov #5 + negs, not mov #251 + and);
   struct fields for the two u16 stack args keep base + offset form
   (no pool folding); the 6-arg call's stack args land at [sp,#0]/[sp,#4].
   Patch (all asserted exactly-1): entry temp swap (idx*8 in r2, table
   in r1); f7 &= result in r1 + strb r1; &1 test result in r1 + cmp r1;
   delete the extra ORR-0 pair (-4 B, exactly the size gap); |= block
   load order constant-first then f7.
   Callees: Sub_08006578 (6 args: s8, s8, 8, 7, u16, u16) + Sub_08022FE4
   via .set.
   Harness: ./verify_patch.sh 0x08007cf4 112 .text.w36b_08007cf4
   w36b_08007cf4_MATCHED.c old w36b_08007cf4_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Ent { u8 pad[4]; u8 f4; u8 f5; u8 pad6; u8 f7; };
struct Arr { u16 f0; u16 f2; };
extern void Sub_08006578(s8 a, s8 b, int c, int d, u32 e, u32 f);
__asm__(".set Sub_08006578, 0x08006578");
extern int Sub_08022FE4(struct Ent *e);
__asm__(".set Sub_08022FE4, 0x08022fe4");
__attribute__((section(".text.w36b_08007cf4")))
void Sub_08007CF4(u16 idx, u8 a, u8 b)
{
    struct Ent *e = ((struct Ent *)0x02004e18) + idx;
    e->f4 = a;
    e->f5 = b;
    {
        register int m __asm__("r1") = -5;
        e->f7 = m & e->f7;
    }
    if (idx == 0) {
        Sub_08006578(a, b, 8, 7, ((struct Arr *)0x08171ef4)->f0, ((struct Arr *)0x08171ef4)->f2);
    } else {
        if ((e->f7 & 1) == 0) {
            if (Sub_08022FE4(e) != 0) {
                e->f7 = 1 | e->f7;
            }
        }
    }
}
/* Trailing 00 00 pad to the next-function boundary (0x08007d64), as in ROM.
   GAS would otherwise emit c0 46 here. */
__asm__(".section .text.w36b_08007cf4\n\t.byte 0, 0\n\t.previous");
