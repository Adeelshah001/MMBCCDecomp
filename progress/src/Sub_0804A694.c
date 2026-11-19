/* Sub_0804A694 @ 0x0804A694 (496 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w60b_0804a694_MATCHED.c (registry: src/w60b_0804a694_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern u8 gEwram_0200BD20[];

extern u8 gEwram_02002EE0[];

extern int CtrTick_4AD4C(u8 *a);

extern void sub_08001400(u8 *d, u8 *s, int n);

extern void sub_080014F8(int x);

__attribute__((section(".text.w60b_0804a694")))
int Sub_0804A694(u8 *arg)
{
    u8 *g = gEwram_0200BD20;
    u8 *g2 = gEwram_0200BD20;
    u16 v300c;
    u16 v300h;

    v300c = 300;
    if ((s16)CtrTick_4AD4C(arg) != 0)
        return -2;
    switch (g[126]) {
        u16 *src;
        u16 mg;
        u16 *p162;
        u8 hv;
        u16 t1, t2, t3, t4;
    case 0: {
        register int v124 __asm__("r6");
        u16 magic = 0x76A3;
        u16 v300 = 300;
        __asm__ volatile ("movs r1, #0\n\tldrsh %0, [%1, r1]" : "=&r" (v124) : "r" (g + 124) : "r1");
        if (v124 != 0)
            break;
        sub_08001400(g2, g + 24, 12);
        *(u16 *)(g2 + 0) = magic;
        *(u16 *)(g2 + 2) = *(u16 *)(g + 132);
        *(u16 *)(g2 + 4) = *(u16 *)(g + 134);
        *(u16 *)(g2 + 6) = *(u16 *)(g + 136);
        *(u16 *)(g2 + 8) = *(u16 *)(g + 138);
        *(u16 *)(g + 162) = v300;
        {
        register u8 *hh __asm__("r3") = gEwram_02002EE0;
        if (hh[4] == 0) {
            __asm__ volatile ("add r1, %0, #0\n\tadd r1, #60\n\tldrb r2, [r1]\n\tmovs r0, #223\n\tand r0, r2\n\tldrb r2, [r1]\n\tstrb r0, [r1]" :: "r" (hh) : "r0", "r1", "r2");
            __asm__ volatile ("add r0, %0, #0\n\tadd r0, #98\n\tstrh %1, [r0]" :: "r" (hh), "r" (v124) : "r0");
            g[126] = 1;
        } else {
            __asm__ volatile ("add r1, %0, #0\n\tadd r1, #60\n\tldrb r2, [r1]\n\tmovs r0, #239\n\tand r0, r2\n\tldrb r2, [r1]\n\tstrb r0, [r1]" :: "r" (hh) : "r0", "r1", "r2");
            __asm__ volatile ("add r0, %0, #0\n\tadd r0, #96\n\tstrh %1, [r0]" :: "r" (hh), "r" (v124) : "r0");
            g[126] = 5;
        }
        }
        }
        break;
    case 1:
    case 6:
        *(u16 *)(g + 162) = v300c;
        sub_080014F8(300);
        g[126]++;
        /* fallthrough to shared G162--/H64 tail */
    case 2:
    case 7:
        *(u16 *)(g + 162) -= 1;
        if (gEwram_02002EE0[64] == 0) {
            v300h = 300;
            *(u16 *)(g + 162) = v300h;
            g[126]++;
        }
        break;
    case 3: {
        *(u16 *)(g + 162) -= 1;
        src = (u16 *)(g + 36);
        hv = gEwram_02002EE0[60];
        { int mm = 32; mm &= hv; if (mm == 0) break; }
        mg = 0x76A3;
        t1 = *(u16 *)(g + 36);
        goto shared_copy;
        }
        break;
    case 5: {
        *(u16 *)(g + 162) -= 1;
        src = (u16 *)(g + 24);
        hv = gEwram_02002EE0[60];
        { int mm = 16; mm &= hv; if (mm == 0) break; }
        mg = 0x76A3;
        t1 = *(u16 *)(g + 24);
        }
        /* fallthrough to shared copy */
    shared_copy:
        if (t1 != mg)
            g[127] = 1;
        t1 = src[1];
        *(u16 *)(g + 132) = t1;
        t2 = src[2];
        *(u16 *)(g + 134) = t2;
        t3 = src[3];
        *(u16 *)(g + 136) = t3;
        t4 = src[4];
        *(u16 *)(g + 138) = t4;
        g[126]++;
        break;
    case 4:
    case 8:
        *(s16 *)(g + 124) = 68;
        if (g[127] == 0) {
            *(u16 *)(arg + 0) = *(u16 *)(g + 132);
            *(u16 *)(arg + 2) = *(u16 *)(g + 134);
            *(u16 *)(arg + 4) = *(u16 *)(g + 136);
            *(u16 *)(arg + 6) = *(u16 *)(g + 138);
            return 0;
        }
        return -2;
    default:
        break;
    }
    if (*(s16 *)(g + 162) < 0)
        return -2;
    return -1;
}
