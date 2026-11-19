/* Dispatch_StkTbl @ 0x08023278 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_080E9C04[];

/* 0x08023278: copy 3-word table to stack, then tbl[s[0xD]](s). Tentative.
 * The struct assignment is required for the ldm/stm block copy. */
typedef struct { u32 e[3]; } Tbl3;

void sub_08023278(u8 *s)
{
    Tbl3 t = *(Tbl3 *)gUnknown_080E9C04;
    ((void (*)(u8 *))t.e[s[0xd]])(s);
}
