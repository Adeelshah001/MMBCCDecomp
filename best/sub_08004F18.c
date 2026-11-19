/* EntryMgr_Teardown @ 0x08004F18 (88 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/entrymgr.c (registry: src/entrymgr.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Absolute callee addresses. The .globl/.set block MUST come after all
 * code in this file (see bottom): GAS 2.42 binds R_ARM_THM_CALL to a
 * broken synthetic LOCAL *ABS* symbol when the .set precedes the
 * referencing code, but to the correct GLOBAL symbol when it follows.
 * Remove each line when that callee gets matched for real
 * (duplicate-symbol otherwise). */

void sub_08004208(u8 *p);

static void sub_08004F70(u8 *base);

static void sub_08004F7C(u8 *base);

void sub_08004F18(void)
{
    u8 *base = (u8 *)0x02003670;
    u8 *p;
    sub_08004208(base + 44);
    sub_08004208(base + 0x264);
    sub_08004208(base + 0x49C);
    p = (u8 *)0x02005028;
    *p = 0;
    p = base + 0x11AE;
    if ((*p & 0xF8) != 8)
        sub_08004F70(base);
    else
        sub_08004F7C(base);
}
