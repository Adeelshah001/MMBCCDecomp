/* Wave 36-B MATCHED: 0x080098c4, 108 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x08009930 (func_list v2) - 0x080098c4 = 108,
   incl. 12 B literal pool (0x0830b778, 0xffff0000, 0x0000ffff).
   Variant count: 6 (v6 = pinned base r8 + pinned masks r5/r6 + separate-statement
   buf[1] RMW, which defeats the constant fold of ((x&0xffff0000)|1)&0xffff).
   Patch (w36b_080098c4_patch.py, asserted counts): reorder only -- mask loads
   moved into the ROM interleave positions and final ORR/STR destination r4->r0;
   no instructions added/removed, pool position unchanged.
   Callee: Sub_080024BC via .set (unmatched in registry).
   Harness: ./verify_patch.sh 0x080098c4 108 .text.w36b_080098c4
   w36b_080098c4_MATCHED.c old w36b_080098c4_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_080024BC(u32 *base, u32 idx, u32 *buf);
__asm__(".set Sub_080024BC, 0x080024bc");
__attribute__((section(".text.w36b_080098c4")))
void Sub_080098C4(u8 a, u16 b, u8 c, u8 d)
{
    register u32 *base __asm__("r8") = (u32 *)0x0830b778;
    register u32 maskA __asm__("r5") = 0xffff0000;
    register u32 maskB __asm__("r6") = 0x0000ffff;
    volatile u32 buf[2];
    u32 t;
    buf[0] = (a & 0x1F) | ((a >> 5) << 17);
    t = buf[1];
    t &= maskA;
    t |= 1;
    t &= maskB;
    t |= 0x20000;
    buf[1] = t;
    Sub_080024BC(base, ((b + c + (d << 5)) << 5) + 0x10000, (u32 *)buf);
}
