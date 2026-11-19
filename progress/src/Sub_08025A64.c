/* Sub_08025A64 @ 0x08025A64 (250 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w57a_08025a64_MATCHED.c (registry: src/w57a_08025a64_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern int TblGet11(u8 a);

extern int Gt199_08026700(u8 a);

extern int TblLookup_25730(u8 *s, int b);

extern int sub_08025CA0(u8 *s, int b, u8 idx);

extern int SumStrides_25754(u8 *s);

extern int AddTbl_S14_Idx(u8 *s, u8 tb);

extern void StoreIdx2_25638(u8 *s, int b, u8 idx);

extern void SetU8_Off1(u8 *s, int b);

extern int SearchFF_2567C(u8 *s);

extern int GetRomTableU16(u8 a);

extern int sub_0802583C(u8 *s, int b, s16 c);

extern int GetU16_10(u8 *s);

__attribute__((section(".text.w57a_08025a64")))
int Sub_08025A64(u8 *s, u8 idx)
{
    register u8 idx8 __asm__("r8") = idx;
    register int off __asm__("r7") = idx8 * 4;
    int tb;
    register int tb9 __asm__("r9");
    {
        register int tbh __asm__("r6") = s[off + 20];
        tb = tbh;
        tb9 = tbh;
    }
    if ((TblGet11(tb) & 4) != 0)
        return 8;
    if ((u16)Gt199_08026700(tb) == 1) {
        if ((u8)TblLookup_25730(s, 0) != 0) {
            register u8 *p0 __asm__("r0") = s;
            register int p1 __asm__("r1") = 0;
            register u8 p2 __asm__("r2") = idx8;
            return (u16)sub_08025CA0(p0, p1, p2);
        }
        if ((u16)SumStrides_25754(s) > (u16)AddTbl_S14_Idx(s, tb))
            return 1;
        {
            register u8 *p0 __asm__("r0") = s;
            register int p1 __asm__("r1") = 0;
            register u8 p2 __asm__("r2") = idx8;
            StoreIdx2_25638(p0, p1, p2);
        }
        SetU8_Off1((off + 20) + s, 0);
        return 0;
    } else {
        u8 v = (u8)SearchFF_2567C(s);
        if (v == 0)
            return 6;
        if (v <= 9) {
            if ((u16)sub_0802583C(s, 0, (s16)GetRomTableU16(tb)) == 0) {
                {
                    register u8 *p0 __asm__("r0") = s;
                    register int p1 __asm__("r1") = v;
                    register u8 p2 __asm__("r2") = idx8;
                    StoreIdx2_25638(p0, p1, p2);
                }
                SetU8_Off1((idx8 * 4 + 20) + s, v);
                return 0;
            }
            return 2;
        } else {
            if ((u16)GetU16_10(s) >= (u16)GetRomTableU16(tb9)) {
                {
                    register u8 *p0 __asm__("r0") = s;
                    register int p1 __asm__("r1") = v;
                    register u8 p2 __asm__("r2") = idx8;
                    StoreIdx2_25638(p0, p1, p2);
                }
                SetU8_Off1((idx8 * 4 + 20) + s, v);
                return 0;
            }
            return 3;
        }
    }
}
