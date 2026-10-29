/* Phase 3 Wave 10 worker H (1 matched C, old_agbcc, worker-verified).
 * ComputeFields @0x0804CFD4 (180 B).
 * Field computer: block 1 (&1) does the (p19*p18)>>5 product chain with
 * s8-weighted sum clamped to [-128,127]; block 2 (&4) does the
 * (s8)p14*p15 accumulation chain; epilogue clears bits 0/2 of p[0].
 * Key idioms:
 * - Opaque `ldrb` inits for pinned regs (pp->r2 via opaque add, v19->r3 /
 *   v18->r1 / rv4->r4 via opaque ldrb) defeat address-order load
 *   scheduling and force Block-1's `ldrb r3,[r2,#19]` before
 *   `ldrb r1,[r2,#18]` plus the `adds r0,r3,#0` copy.
 * - Block-2 header: x pinned r1 via opaque ldrb; separate `t = x & 4`
 *   statement before `b = x` (b pinned r3) gives ROM's program order
 *   `ldrb r1; movs r0,#4; ands r0,r1; adds r3,r1,#0; cmp r0,#0; beq`
 *   (the r1->r3 save is the compiler parking x before the body needs r1).
 * - `adds r1,r1,r0` dest fix: pinned p0->r0 / p1->r1 plus
 *   `__asm__ volatile("add %0, %0, %1" : "+r"(p1) : "r"(p0))` forces the
 *   combiner's dest to r1 (else it emits `adds r0,r0,r1` +
 *   cross-register `lsls r1,r0,#2`).
 * Evidence: docs/match_notes_wave10_H.md. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

__attribute__((section(".text.w10h_0804cfd4")))
void ComputeFields(u32 dummy, u8 *p)
{
    register u8 *pp __asm__("r2");
    register u32 v19 __asm__("r3");
    register u32 v18 __asm__("r1");
    register u32 rv4 __asm__("r4");
    register u32 x __asm__("r1");
    register u32 b __asm__("r3");
    u32 t;
    __asm__ volatile("add %0, %1, #0" : "=r"(pp) : "r"(p));
    if (pp[0] & 1) {
        u32 r3;
        int r1;
        __asm__ volatile("ldrb %0, [%1, #19]" : "=r"(v19) : "r"(pp));
        __asm__ volatile("ldrb %0, [%1, #18]" : "=r"(v18) : "r"(pp));
        {
            register u32 t __asm__("r0");
            __asm__ volatile("add %0, %1, #0" : "=r"(t) : "r"(v19));
            r3 = (u32)(t * v18) >> 5;
        }
        __asm__ volatile("ldrb %0, [%1, #24]" : "=r"(rv4) : "r"(pp));

        if (rv4 == 1) {
            int r0 = (s8)pp[22] + 128;
            r3 = (u32)(r0 * r3) >> 7;
        }
        r1 = ((s8)pp[20] << 1) + (s8)pp[21];
        if (rv4 == 2)
            r1 += (s8)pp[22];
        if (r1 < -128)
            r1 = -128;
        else if (r1 > 127)
            r1 = 127;
        pp[16] = (u8)(((r1 + 128) * r3) >> 8);
        pp[17] = (u8)(((127 - r1) * r3) >> 8);
    }
    __asm__ volatile("ldrb %0, [%1, #0]" : "=r"(x) : "r"(pp));
    t = x & 4;
    b = x;
    if (t) {
        register int p0 __asm__("r0");
        register int p1 __asm__("r1");
        int acc;
        p0 = (s8)pp[14] * pp[15];
        p1 = (s8)pp[12];
        __asm__ volatile("add %0, %0, %1" : "+r"(p1) : "r"(p0));
        p1 <<= 2;
        acc = p1;
        acc += (s8)pp[10] << 8;
        acc += (s8)pp[11] << 8;
        acc += pp[13];
        if (pp[24] == 0)
            acc += (s8)pp[22] << 4;
        pp[8] = (u8)(acc >> 8);
        pp[9] = (u8)acc;
    }
    pp[0] = b & 250;
}
