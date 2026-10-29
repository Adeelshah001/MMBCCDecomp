/* Wave 16-D: ObjSlotInit_05FC0 @ 0x08005fc0 (84 B: 80 code+pad + 4 pool).
 * Coordinator-landed, 0-diff verified vs ROM. Compiler: main agbcc.
 * Behavior: p = (u8 *)(0x2004CA0 + ((u8)a << 5)) (32-byte table entry);
 * p[30] = 0; p[31] = (p[31] | 1) & -7 | 4 | 1; then for s16 i in 0..11:
 * ((u16 *)(p + 4))[i] = 0, p[31] |= 1.
 * Idioms: (u8)a<<5 combiner-folded to lsls#24/lsrs#19; `p += pool` keeps p
 * in r0 (adds r0,r0,r1); mask-first int temps (v|1 / v&-7 via movs+negs /
 * v|4 / v|1 kept unfolded); scoped `int one` forces movs r3,#1 before ldrb;
 * s16 loop counter (lsls#16/asrs#16, ble); pinned loop invariants
 * (register vars: q4->r3, zero->r5, uno->r4); i=0 hoisted before q copy;
 * divided-syntax asm ("add %0,%1,%0") forces adds r1,r3,r1 operand order. */
typedef unsigned char u8; typedef unsigned short u16; typedef short s16;
void ObjSlotInit_05FC0(u8 a) __attribute__((section(".text.w16d_08005fc0")));
void ObjSlotInit_05FC0(u8 a)
{
    u8 *p = (u8 *)((u8)a << 5);
    int v;
    s16 i;
    u8 *q;
    p += 0x2004CA0;
    p[30] = 0;
    {
        int one = 1;
        v = p[31];
        v |= one;
        v &= -7;
        v |= 4;
        v |= one;
        p[31] = v;
    }
    i = 0;
    q = p;
    {
        register u8 *q4 __asm__("r3") = q + 4;
        register u16 zero __asm__("r5") = 0;
        register int uno __asm__("r4") = 1;
        for (; i <= 11; i++) {
            int off = (s16)i * 2;
            __asm__ volatile("add %0, %1, %0" : "+r" (off) : "r" (q4));
            *(u16 *)off = zero;
            q[31] |= uno;
        }
    }
}
