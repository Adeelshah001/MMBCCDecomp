/* ChipFxTick2_0801E77C @ 0x0801E77C (254 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31a_0801e77c.c (registry: staging/wave31_C/w31c_0801e77c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern u8 gAddrZero[];

void ChipSlot_IncUse(u8 *s, u8 idx);

void NewNode_0801D278(u8 *p, u8 *q, void *sp);

s16 SelBlob_Ret(u16 v);

void Set_08004E24(u8 x);

int Cmp_08004E0C(u8 x);

void Fwd_10BA0(void);

__attribute__((section(".text.w31a_0801e77c")))
void ChipFxTick2_0801E77C(u8 *p) {
    register u32 off __asm__("r0") = p[16] * 12;
    register u8 *tbl __asm__("r2");
    u32 sp0, sp1;
    u8 st;
    { register u32 base __asm__("r1") = (u32)&gAddrZero[0x20051c8];
      tbl = (u8 *)(off + base); }
    { register u32 z0 __asm__("r0") = 0;
      register u32 z1 __asm__("r1") = 0;
      sp0 = z0; sp1 = z1; }
    __asm__ volatile("" :: "m"(sp0), "m"(sp1));
    st = p[14];

    switch (st) {
    case 0:
        ChipSlot_IncUse(p, 8);
        p[14]++;
        p[19] = st;
        *(u16 *)(p + 120) = 60;
        NewNode_0801D278(p, p + 19, &sp0);
        /* fallthrough */
    case 1: {
        register u8 *hp __asm__("r1") = p + 120;
        u16 v = *(u16 *)hp;
        s32 sv;
        __asm__ volatile("movs r3, #0\n\tldrsh %0, [%1, r3]"
                         : "=r"(sv) : "r"(hp) : "r3");
        if (sv != 0) {
            int nv = v - 1;
            *(u16 *)hp = nv;
            if ((nv << 16) == 0)
                SelBlob_Ret(110);
        }
        if ((u8)(p[119] - 3) > 1)
            break;
        p[14]++;
        Set_08004E24(1);
        break;
    }
    case 2:
        if ((s8)Cmp_08004E0C(3) == 0)
            break;
        p[14]++;
        { register u16 *g __asm__("r2") = (u16 *)&gAddrZero[0x20031e0];
          register u32 v __asm__("r0") = 0xEDFF;
          register u32 t __asm__("r1");
          __asm__("ldrh %0, [%1]" : "=r"(t) : "r"(g));
          v &= t;
          { register u32 m __asm__("r1") = 0xDBFF;
            v &= m; }
          *g = (u16)v; }
        Fwd_10BA0();
        break;
    case 3: {
        u8 t = tbl[6];
        if (t != 0) {
            register u32 *tbase __asm__("r1") = (u32 *)&gAddrZero[0x82243d8];
            u8 idx = p[9];
            u32 e = (idx << 2) + (u32)tbase;
            *(u32 *)(p + 12) = 2;
            __asm__ volatile("" : "+r"(e) :: "memory");
            *(u32 *)(p + 20) = *(u32 *)(*(u32 *)e + 8);
        } else {
            p[13] = t;
            p[15] = t;
            p[14] = t;
        }
        tbl[1] = 0;
        break;
    }
    }
}
