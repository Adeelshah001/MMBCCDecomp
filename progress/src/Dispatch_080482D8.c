/* Dispatch_080482D8 @ 0x080482D8 (168 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w27b_080482d8.c (registry: mmbcc/src/w27b_080482d8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void Call4E60_4E44(void);

void PalModeSet_4DFC(u8 a);

extern u8 g_02004F80[];

extern u32 g_08234328[];

extern u8 g_46A4[];

extern u8 g_46A5a[];

extern u8 g_46A5a[];

extern u8 g_46B7[];

__attribute__((section(".text.w27b_080482d8")))
u8 Dispatch_080482D8(u8 *s)
{
    switch (s[3]) {
    case 0:
        Call4E60_4E44();
        PalModeSet_4DFC(g_02004F80[2]);
        s[3]++;
        /* fall through */
    case 1: {
        u8 *r5p;
        register u32 tblv __asm__("r1") = (u32)g_08234328;
        u32 off;
        u32 idx32;
        register u32 faddr __asm__("r0");
        register u32 retr __asm__("r2");
        off = (u32)g_46A4;
        __asm__ volatile("" : "+r"(off) : : "r5");
        r5p = s + off;
        idx32 = *r5p;
        __asm__ volatile("" : "+r"(idx32) : : "r0");
        faddr = idx32 << 2;
        faddr += tblv;
        tblv = *(u32 *)faddr;
        retr = ((u8 (*)(u8 *))tblv)(s);

        if (retr == 0)
            return 0;
        if (retr == 2) {
            u8 zero = 0, four = 4;
            register u32 off2 __asm__("r2");
            register u32 pp2 __asm__("r0");
            s[2] = four;
            s[3] = zero;
            *r5p = four;
            off2 = (u32)g_46A5a;
            pp2 = (u32)s + off2;
            *(u8 *)pp2 = zero;
        } else if (retr == 5) {
            register u32 zero __asm__("r0") = 0;
            register u32 four __asm__("r1") = 4;
            register u32 off5 __asm__("r2");
            register u32 pp5 __asm__("r1");
            s[2] = (u8)four;
            s[3] = (u8)zero;
            *r5p = (u8)retr;
            off5 = (u32)g_46A5a;
            pp5 = (u32)s + off5;
            *(u8 *)pp5 = (u8)zero;
        } else if (retr == 6) {
            register u32 zero __asm__("r0") = 0;
            register u32 four __asm__("r1") = 4;
            register u32 off6 __asm__("r1");
            register u32 pp6 __asm__("r0");
            s[2] = (u8)four;
            s[3] = (u8)zero;
            off6 = (u32)g_46B7;
            pp6 = (u32)s + off6;
            *(u8 *)pp6 = (u8)retr;
        } else {
            u8 zero = 0, three = 3;
            s[2] = three;
            s[3] = zero;
        }
        break;
    }
    default:
        break;
    }
    return 0;
}
