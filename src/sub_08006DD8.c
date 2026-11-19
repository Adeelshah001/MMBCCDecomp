/* GatedDispatch @ 0x08006DD8 (86 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/gateddispatch.c (registry: src/gateddispatch.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

/* Absolute callee address. The .globl/.set block MUST come after all
 * code in this file (see bottom): GAS 2.42 binds R_ARM_THM_CALL to a
 * broken synthetic LOCAL *ABS* symbol when the .set precedes the
 * referencing code, but to the correct GLOBAL symbol when it follows.
 * Remove when sub_08006E6C gets matched for real. */

u8 sub_08006E6C(u8 *base, void *p, s16 x, s16 y, s8 z, u8 w);

u8 sub_08006DD8(void *p, u32 a, u32 b, u32 c, u32 d)
{
    u16 x = (u16)a;
    u16 y = (u16)b;
    u8 z = (u8)c;
    u8 w = (u8)d;
    u8 *base = (u8 *)0x02004830;
    if (*(base + 0x265) != 0)
        return 0;
    return (u8)sub_08006E6C(base, p, (s16)x, (s16)y, (s8)z, w);
}
