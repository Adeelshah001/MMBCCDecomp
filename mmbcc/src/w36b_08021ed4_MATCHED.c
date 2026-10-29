/* Wave 36-B MATCHED: 0x08021ed4, 104 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x08021f3c (func_list v2) - 0x08021ed4 = 104,
   incl. 4 B literal pool (0x082270bc, LE bytes bc 70 22 08).
   Variant count: 9 (v9 = v3 switch-form with corrected pool value).
   Key idioms: switch dispatch (compare chain, cases out of line), table pointer
   declared inside case 1 (caller-saved r1, not callee-saved r4), fresh p[18]
   reads so the entry address recomputes per field.
   Patch (w36b_08021ed4_patch.py, exactly-1 assertion): case-1 second field
   access rewritten from offset-register form (mov r1,#2; ldrsh [r0,r1]) to
   ROM base-fold form (adds r1,#2; adds r0,r0,r1; movs r1,#0; ldrsh [r0,r1]);
   net +2 B, code 98 -> 100 B, pool stays at offset 100.
   Callee: ChipSlot_Tick (0x0800d9fc) already MATCHED -> extern-only, no .set.
   Harness: ./verify_patch.sh 0x08021ed4 104 .text.w36b_08021ed4
   w36b_08021ed4_MATCHED.c old w36b_08021ed4_patch.py ChipSlot_Tick=0x0800d9fc
   -> diffs: 0. */
typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;

extern void ChipSlot_Tick(u8 *p);

__attribute__((section(".text.w36b_08021ed4")))
void Sub_08021ED4(u8 *p)
{
    u8 *q = *(u8 **)(p + 40);
    u8 first = q[0];
    u8 state = p[13];
    switch (state) {
    case 0:
        if (first == 255) {
            p[10] &= 0xfe;
        } else {
            p[10] |= 1;
            p[13]++;
            p[18] = first;
        }
        break;
    case 1: {
        struct Pair { s16 a; s16 b; } *t;
        p[13] = 0;
        t = (struct Pair *)0x082270bc;
        *(u32 *)(p + 80) = (u32)(t[p[18]].a << 8);
        *(u32 *)(p + 84) = (u32)(t[p[18]].b << 8);
        break;
    }
    default:
        break;
    }
    ChipSlot_Tick(p);
}
