/* W60-B v37 (v24 + int-mm H-test + t1-as-chk + t1 != mg compare): 0x0804A694, TRUE extent 496 B.
 * MAIN agbcc 0 DIFFS (verified standalone linked-at-address, file as-is); old_agbcc 12 diffs
 * (H-test only: H pointer r1 vs ROM r0 + movs-before-ldrb order, 6 B per case in case3/case5).
 * Jump-table switch on G[126], cases 0-8, shared bodies 1=6, 2=7, 4=8.
 * G = 0x0200BD20, H = 0x02002EE0 (absolute addresses here so the standalone verifier's pool
 * words match ROM; coordinator maps to proper extern symbols on landing). Magic constant 0x76A3.
 * Case3/5 H-test: int mm accumulator (mm &= hv) puts the AND result in r0 under main, matching
 * ROM's load-before-mask shape; the loaded value rides switch-scope temp t1 (which already
 * allocates to r1 in the shared copy), so case loads are mg->r0 (pool ldr) and chk->r1 (ldrh),
 * exactly as in ROM; shared compare is (t1 != mg) so cmp reads cmp r1, r0 as in ROM.
 * Case 0: if (G[124] != 0) goto epilogue; memcpy(G, G+24, 12); G[0..8] (u16)
 *   = 0x76A3, G[132], G[134], G[136], G[138]; G[162] = 300; if (H[4] == 0)
 *   { H[60] &= 223; H[98] = G[124]; G[126] = 1; } else { H[60] &= 239;
 *   H[96] = G[124]; G[126] = 5; } goto epilogue.
 * Case 1/6: G[162] = 300; Sub_080014F8(300); g[126]++; G[162]--;
 *   if (H[64] == 0) { G[162] = 300; g[126]++; } goto epilogue.
 * Case 2/7: G[162]--; if (H[64] == 0) { G[162] = 300; g[126]++; } epilogue.
 * Case 3: G[162]--; src = G+36; if ((H[60] & 32) == 0) epilogue; else shared
 *   with t1 = G[36] (chk) and mg = 0x76A3.
 * Case 5: G[162]--; src = G+24; if ((H[60] & 16) == 0) epilogue; else shared
 *   with t1 = G[24] (chk) and mg = 0x76A3.
 * Shared (3/5): if (t1 != mg) g[127] = 1; G[132] = src[1]; G[134] =
 *   src[2]; G[136] = src[3]; G[138] = src[4]; g[126]++; epilogue.
 * Case 4/8: G[124] = 68; if (g[127] != 0) return -2; arg[0..3] (u16) =
 *   G[132..138]; return 0.
 * Epilogue: return (*(s16 *)(G+162) < 0) ? -2 : -1.
 * Do NOT land v10 (mg clobbered, semantically broken) or v18 (hh call-clobbered,
 * semantically broken) -- both deleted in W59, do not recreate.
*/
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

extern u8 G[];
extern u8 H[];
extern int Sub_0804AD4C(u8 *a);
extern void Sub_08001400(u8 *d, u8 *s, int n);
extern void Sub_080014F8(int x);

/* Standalone-verification absolutes (coordinator removes on landing, when
 * real symbols exist): G = 0x0200BD20, H = 0x02002EE0, callees absolute. */
__asm__(".set G, 0x0200BD20");
__asm__(".set H, 0x02002EE0");
__asm__(".set Sub_0804AD4C, 0x0804AD4C");
__asm__(".set Sub_08001400, 0x08001400");
__asm__(".set Sub_080014F8, 0x080014F8");

__attribute__((section(".text.w60b_0804a694")))
int Sub_0804A694(u8 *arg)
{
    u8 *g = G;
    u8 *g2 = G;
    u16 v300c;
    u16 v300h;

    v300c = 300;
    if ((s16)Sub_0804AD4C(arg) != 0)
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
        Sub_08001400(g2, g + 24, 12);
        *(u16 *)(g2 + 0) = magic;
        *(u16 *)(g2 + 2) = *(u16 *)(g + 132);
        *(u16 *)(g2 + 4) = *(u16 *)(g + 134);
        *(u16 *)(g2 + 6) = *(u16 *)(g + 136);
        *(u16 *)(g2 + 8) = *(u16 *)(g + 138);
        *(u16 *)(g + 162) = v300;
        {
        register u8 *hh __asm__("r3") = H;
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
        Sub_080014F8(300);
        g[126]++;
        /* fallthrough to shared G162--/H64 tail */
    case 2:
    case 7:
        *(u16 *)(g + 162) -= 1;
        if (H[64] == 0) {
            v300h = 300;
            *(u16 *)(g + 162) = v300h;
            g[126]++;
        }
        break;
    case 3: {
        *(u16 *)(g + 162) -= 1;
        src = (u16 *)(g + 36);
        hv = H[60];
        { int mm = 32; mm &= hv; if (mm == 0) break; }
        mg = 0x76A3;
        t1 = *(u16 *)(g + 36);
        goto shared_copy;
        }
        break;
    case 5: {
        *(u16 *)(g + 162) -= 1;
        src = (u16 *)(g + 24);
        hv = H[60];
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
