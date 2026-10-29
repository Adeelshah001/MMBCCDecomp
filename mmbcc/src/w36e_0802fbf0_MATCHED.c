/* Wave 36-E MATCHED: 0x0802fbf0 (56 B, old_agbcc ONLY, 0 diffs).
 * v8: ppc pinned r2 and REUSED for the 0x18B pointer (no separate p2
 * variable -- that allocated r3); +r barrier on ppc before the reuse
 * keeps the pin and defeats the 0x18B CSE fold (real pool ldr).
 * WARNING: v7 with =r barrier byte-matched but MISCOMPILED (ppc dead,
 * r2 held 394, not pp) -- do NOT use v7. Main agbcc unusable here:
 * it pushes lr for this multi-block leaf (W35-D idiom 1).
 * True extent 0x0802FBF0-0x0802FC28 (46 code + 2 pad + 2 pools).
 * Pools (LE): 0x0000018B @0x2FC20, 0x02005168 @0x2FC24. No callees. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__attribute__((section(".text.w36e_0802fbf0")))
void Sub_0802FBF0(u8 *pp)
{
    register u8 *ppc __asm__("r2") = pp;
    u8 *p1 = ppc + (197 << 1);
    u8 *q;
    u8 v;
    v = *p1;
    if (v <= 99)
        *p1 = v + 5;
    __asm__ volatile("" : "+r"(ppc));
    ppc = ppc + 0x18B;
    v = *ppc;
    if (v <= 99)
        *ppc = v + 5;
    q = (u8 *)0x02005168;
    q[12] = *p1;
    q += 20;
    q[12] = *ppc;
}
