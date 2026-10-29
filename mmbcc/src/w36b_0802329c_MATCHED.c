/* Wave 36-B MATCHED: 0x0802329c, 104 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x08023304 (func_list v2) - 0x0802329c = 104,
   no literal pool. Variant count: 3 (v1 C + patch; v2 pin dropped the
   truncation shifts; v3 int-temp pin coalesced into r3).
   Key idioms: u8 flag = q->b7 & 4 with truncating lsl/lsr move (ROM shape),
   ldrsb via register offsets (Thumb has no ldrsb immediate), if/else-if on
   the signed byte with duplicated store blocks.
   Patch (w36b_0802329c_patch.py, asserted counts): push {r4,lr}->push {lr},
   delete add r4,r3,#0, strb r4->strb r3 (x2), delete pop {r4}; net -4 B.
   Callees: Sub_08009EDC + Sub_080099FC via .set (both unmatched in registry).
   Harness: ./verify_patch.sh 0x0802329c 104 .text.w36b_0802329c
   w36b_0802329c_MATCHED.c old w36b_0802329c_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Q { u8 b0; s8 b1; u16 h2; s8 b4; s8 b5; u8 b6; u8 b7; };

extern void Sub_08009EDC(u8 a, u16 b);
__asm__(".set Sub_08009EDC, 0x08009edc");
extern void Sub_080099FC(u8 a, u16 b, u8 c);
__asm__(".set Sub_080099FC, 0x080099fc");

__attribute__((section(".text.w36b_0802329c")))
void Sub_0802329C(u8 *p)
{
    struct Q *q = *(struct Q **)(p + 40);
    u8 flag = q->b7 & 4;
    if (flag == 0) {
        s8 v = q->b1;
        if (v == 0) {
            p[13] = 1;
            p[15] = flag;
            p[14] = flag;
            *(u32 *)(p + 88) = q->h2;
            *(int *)(p + 96) = q->b4;
            *(int *)(p + 100) = q->b5;
            Sub_08009EDC(q->b0, q->h2);
        } else if (v == 1) {
            p[13] = 2;
            p[15] = flag;
            p[14] = flag;
            *(u32 *)(p + 88) = q->h2;
            *(int *)(p + 96) = q->b4;
            *(int *)(p + 100) = q->b5;
            Sub_080099FC(q->b0, q->h2, q->b6);
        }
    }
}
