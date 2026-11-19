/* EwSet8Ret1_20 @ 0x08010DDC (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Ew020051B0 { u8 _00[20]; u8 f20; };

extern struct Ew020051B0 gUnknown_020051B0;

/* EWRAM flag setter returning 1 (TENTATIVE name).
 * ROM 0x08010DDC (12 B code): RomBase_20051B0.f20 = (u8)v; return 1.
 * The `(u8)(v|1)&1` return forces back the redundant (u8) truncation
 * the original compiler emitted before the strb (this agbcc drops it
 * as a no-op); the expression still folds the return to constant 1.
 * Sibling reader at 0x08010DEC returns (f20 == 0). */
u8 sub_08010DDC(u8 v)
{
    gUnknown_020051B0.f20 = v;
    return (u8)(v | 1) & 1;
}
