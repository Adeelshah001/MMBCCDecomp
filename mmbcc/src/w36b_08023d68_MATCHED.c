/* Wave 36-B MATCHED: 0x08023d68, 112 B, old_agbcc -O2 -mthumb-interwork,
   pure C (no patch file).
   Extent basis: next function start 0x08023dd8 - 0x08023d68 = 112,
   incl. trailing 00 00 pad (explicit .byte 0,0; gas would emit c0 46).
   Variant count: 3 (v3 = u8 loop counters + explicit trailing pad).
   Key idioms: BOTH loop counters must be u8 (ROM truncates both to
   u8 each iteration: inner j via lsl/lsr after +1 with cmp #14 + bls;
   outer i via lsl/lsr after the r8 save with cmp #23 + bls); u8
   counters also defeat gcc's countdown + pointer strength reduction,
   keeping the count-up index form (r4 = src + j each iteration).
   Inner accumulator: acc = ((u8)acc << 8) | src[j] (lsl #24, lsr #16,
   ldrb, orr); if acc > 35: src[j] = Clamp1(acc,36) and acc =
   (u16)Clamp2(acc,36), else src[j] = 0. Outer: dst[i] = acc (u16 store
   to dst + i*2, offset computed at the loop head before i++).
   Callees: Sub_0804DE70 + Sub_0804DEE8 (both (acc,36)) via .set.
   Harness: ./verify.sh 0x08023d68 112 .text.w36b_08023d68
   w36b_08023d68_MATCHED.c old -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern int Sub_0804DE70(int x, int y);
__asm__(".set Sub_0804DE70, 0x0804de70");
extern int Sub_0804DEE8(int x, int y);
__asm__(".set Sub_0804DEE8, 0x0804dee8");
__attribute__((section(".text.w36b_08023d68")))
void Sub_08023D68(u8 *src, u16 *dst)
{
    u8 i;
    u8 j;
    u16 acc;
    for (i = 0; i < 24; i++) {
        acc = 0;
        for (j = 0; j <= 14; j++) {
            acc = ((u8)acc << 8) | src[j];
            if (acc > 35) {
                src[j] = Sub_0804DE70(acc, 36);
                acc = (u16)Sub_0804DEE8(acc, 36);
            } else {
                src[j] = 0;
            }
        }
        dst[i] = acc;
    }
}
/* Trailing 00 00 pad to the next-function boundary (0x08023dd8), as in ROM. */
__asm__(".section .text.w36b_08023d68\n\t.byte 0, 0\n\t.previous");
