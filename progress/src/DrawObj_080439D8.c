/* DrawObj_080439D8 @ 0x080439D8 (196 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w21d_080439d8.c (registry: src/w21d_080439d8.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 F_0802478C(u32 idx);

extern u16 Wrap_GetRomTableU16(u8 idx);

extern u16 GetEnt_U16_14(void);

extern u16 TblGet_f00(u8 idx);

extern u16 TblGet_f04(u8 idx);

extern u16 TblGet_f08(u8 idx);

extern u8 GatedDispatch(void *p, u32 a, u32 b, u32 c, u32 d);

extern void Gfx_BlitRequest(u32 a, u32 b, u32 c, u32 d, u32 e);

__attribute__((section(".text.w21d_080439D8")))
void DrawObj_080439D8(u8 *p)
{
    u8 b0;
    u8 idx;
    u16 v;
    register u8 *r4 __asm__("r4");
    register u32 zero __asm__("r6");
    u16 t0;
    u16 t1;
    u32 *tbl;
    u32 off;
    u32 *pp;
    u32 p0;
    int a1;
    int a2;

    b0 = p[0x46A9];
    b0 >>= 4;
    idx = (u8)F_0802478C(b0 + p[0x46AA]);
    v = (u16)Wrap_GetRomTableU16(idx);
    if (idx > 199) {
        v = (u16)(v + GetEnt_U16_14());
    }
    t0 = (u16)TblGet_f00(idx);
    r4 = (u8 *)0x08232D84;
    {
        int a1 = (s8)r4[16] + 2;
        int a2 = (s8)r4[17];
        zero = 0;
        GatedDispatch((void *)t0, a1, a2, 3, zero);
    }
    t1 = (u16)TblGet_f04(idx);
    {
        int a1 = (s8)r4[16] + 7;
        int a2 = (s8)r4[17];
        GatedDispatch((void *)t1, a1, a2, 3, zero);
    }
    {
        int a1 = (s8)r4[16] + 2;
        int a2 = (s8)r4[17] + 2;
        GatedDispatch((void *)v, a1, a2, 3, zero);
    }
    tbl = (u32 *)0x08232DF0;
    __asm__ volatile("" : "+r" (tbl));
    off = ((u16)TblGet_f08(idx) >> 12);
    pp = (u32 *)tbl[off];
    p0 = *pp;
    {
        a1 = (s8)r4[16] + 6;
        a2 = (s8)r4[17] + 2;
        Gfx_BlitRequest(p0, a1, a2, 4, zero);
    }
}
