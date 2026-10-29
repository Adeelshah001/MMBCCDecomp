/* Wave 36-B MATCHED: 0x0804b5cc, 104 B, old_agbcc -O2 -mthumb-interwork, pure C.
   Extent basis: next function start 0x0804b634 (func_list v2) - 0x0804b5cc = 104,
   incl. 8 B literal pool (0x03002420 WRAM base, 0x082350a0 ROM table).
   Variant count: 4 (v4 = short for-loop + struct-field decrement).
   Key idioms: switch with case-0 fallthrough to case 1; short for-loop
   k=0..3 with (k+1)*32 body offset (produces the r0-int/r4-short dance);
   struct-field --cnt == 0 (no zero-extension copy, unlike a named u16 temp).
   Callee: Sub_0800DDE4 via .set (BLOCKED in registry, unmatched).
   Harness: ./verify.sh 0x0804b5cc 104 .text.w36b_0804b5cc
   w36b_0804b5cc_MATCHED.c old -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct P { u8 pad0; u8 pad1; u8 b2; u8 b3; u8 pad4; u8 pad5; u16 cnt; };

extern void Sub_0800DDE4(u8 *a, u8 *b, u8 *c, int d);
__asm__(".set Sub_0800DDE4, 0x0800dde4");

__attribute__((section(".text.w36b_0804b5cc")))
void Sub_0804B5CC(struct P *p)
{
    u8 state = p->b3;
    switch (state) {
    case 0:
        p->b3 = 1;
        p->cnt = 32;
        /* fallthrough */
    case 1: {
        if ((p->cnt & 3) == 0) {
            short k;
            for (k = 0; k <= 3; k++) {
                u8 *dst = (u8 *)0x03002420 + (k + 1) * 32;
                Sub_0800DDE4(dst, (u8 *)0x082350a0, dst, 1);
            }
        }
        if (--p->cnt == 0) {
            p->b2++;
            p->b3 = 0;
        }
        break;
    }
    default:
        break;
    }
}
