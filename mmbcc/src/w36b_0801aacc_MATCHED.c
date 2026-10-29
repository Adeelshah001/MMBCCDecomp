/* Wave 36-B MATCHED: 0x0801aacc, 104 B, old_agbcc -O2 -mthumb-interwork.
   Extent basis: next function start 0x0801ab34 (func_list v2) - 0x0801aacc = 104,
   incl. 8 B literal pool (0x082243d8, 0x082266d8). Variant count: 6 (v6).
   Key idioms: pool-const pin + barrier (tbl->r1, tbl2->r0), tmp values pinned
   to r3/r4, index-first integer add for adds r0,r0,r1, unsigned nibble shift.
   Callees: Sub_0800DD08 + Sub_080178A8 via .set (unmatched in registry);
   Sub_0801AB34 is already MATCHED (registry) so extern-only, no .set here.
   Harness: ./verify.sh 0x0801aacc 104 .text.w36b_0801aacc
   w36b_0801aacc_MATCHED.c old Sub_0801AB34=0x0801ab34 -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned int u32;

extern void Sub_0800DD08(int *out, u8 *p);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_080178A8(u8 a, unsigned b, short c, short d, u32 e);
__asm__(".set Sub_080178A8, 0x080178a8");
extern void Sub_0801AB34(u8 *p);
__asm__(".set Sub_0801AB34, 0x0801ab34");

__attribute__((section(".text.w36b_0801aacc")))
void Sub_0801AACC(u8 *p)
{
    struct Pair { int a; int b; } tmp;
    u32 *entry;
    {
        register u32 *tbl __asm__("r1") = (u32 *)0x082243d8;
        __asm__ volatile("" : "+r"(tbl));
        entry = (u32 *)((u32)p[9] * 4 + (u32)tbl);
    }
    *(u32 *)(p + 12) = 1;
    *(u32 *)(p + 20) = *(u32 *)(*(u32 *)entry + 4);
    p[10] &= 0xfd;
    p[10] &= 0xfe;
    Sub_0800DD08((int *)&tmp, p);
    {
        register int a __asm__("r3") = tmp.a;
        register int b __asm__("r4") = tmp.b;
        {
            register u8 *tbl2 __asm__("r0") = (u8 *)0x082266d8;
            __asm__ volatile("" : "+r"(tbl2));
            Sub_080178A8(tbl2[p[16]], ((u32)p[35] << 28) >> 28, (short)a, (short)b, *(u32 *)(p + 44));
        }
    }
    Sub_0801AB34(p);
}
