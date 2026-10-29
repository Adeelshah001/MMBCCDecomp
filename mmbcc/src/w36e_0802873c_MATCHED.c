/* Wave 36-E MATCHED: 0x0802873c (60 B, main agbcc, 0 diffs).
 * v10: tbl pinned r1, idx pinned r2, single inline asm `add r1, r2, r1`
 * (no-s spelling; this GAS rejects 3-operand `adds` in Thumb16 but
 * assembles `add` to the identical halfword 0x1851, disassembled as
 * adds r1, r2, r1). Pure-C v8/v9 still 1 diff (adds r1, r1, r2).
 * Callees via .set: 0x08028778, 0x08028874 (latter MATCHED in build
 * as SetPairZero_28874 -- coordinator strips that .set). */
typedef unsigned char u8;
extern int Worker_08028778(u8 *p, u8 v);
extern void Worker_08028874(u8 *s, u8 v);
__asm__(".set Worker_08028778, 0x08028778");
__asm__(".set Worker_08028874, 0x08028874");
__attribute__((section(".text.w36e_0802873c")))
void Sub_0802873C(u8 *s)
{
    u8 v = s[2];
    if (v == 0)
        goto A;
    if (v == 1)
        goto B;
    return;
A:
    {
        u8 *p = s + 3;
        register u8 *tbl __asm__("r1") = (u8 *)0x0822dde0;
        register u8 idx __asm__("r2") = s[1];
        __asm__ volatile("add %0, %1, %0" : "+r"(tbl) : "r"(idx));
        if ((Worker_08028778(p, *tbl) << 24) != 0)
            return;
    }
    s[2]++;
B:
    Worker_08028874(s, s[1]);
}
