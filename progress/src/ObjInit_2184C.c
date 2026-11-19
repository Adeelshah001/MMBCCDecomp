/* ObjInit_2184C @ 0x0802184C (164 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_c_old.c (registry: src/wave7_c_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

/* 0x08021594: ObjInit_TypeC (148B, coordinator-verified). */
/* Wave 7 TAG=C. ObjInit_TypeC @ 0x08021594 (148 B). Tentative. v3: corrected
 * addresses (ldrh from 0x081705B0, +0x020031E4); mask as int var; literal
 * base for the 0x11AE access to avoid pool CSE. */

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];

extern u8 gEwram_020031E4[];

__attribute__((section(".text.w7c_0802184c")))
void ObjInit_2184C(u8 *s)
{
    u8 t;
    u32 idx;
    int mask = -13;
    u8 *p;
    u32 sh;
    register int c __asm__("r0");

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    {
        u16 *tbl = (u16 *)0x08227028;
        __asm__ volatile("" : "+r"(tbl));
        ChipSlot_Setup(s, tbl[s[17]], 0);
    }
    {
        u8 *tbl = (u8 *)0x08227020;
        __asm__ volatile("" : "+r"(tbl));
        ChipSlot_IncUse(s, tbl[s[17]]);
    }
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
    if (c > 3)
        idx = 3;
    p = s;
    p += 0x45;
    sh = idx << 2;
    *p = (*p & mask) | sh;
    {
        register u8 z __asm__("r2");
        u8 *p = s;
        s16 *q;
        p += 0x22;
        __asm__("movs %0, #0" : "=r"(z));
        *p = z;
        {
            u8 *tbl = (u8 *)0x08227036;
            q = (s16 *)(tbl + (s[17] << 2));
            *(u32 *)(s + 0x50) = q[0] << 8;
            {
                u8 idx = s[17];
                u32 off = idx << 2;
                tbl += 2;
                q = (s16 *)(tbl + off);
                *(u32 *)(s + 0x54) = q[0] << 8;
            }
        }
        s[0x12] = z;
    }
}
