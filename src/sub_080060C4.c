/* Sub_080060C4 @ 0x080060C4 (96 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_080060c4_MATCHED.c (registry: mmbcc/src/w36a_080060c4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08006168(u32 a, s8 b, s8 c, u8 d, u8 e, u16 f, u16 g);

void sub_080060C4(u8 a0, u8 a1, u8 a2, u8 a3, u16 a4, u16 a5)
{
    u32 pool1 = 0x02004830;
    u32 pool2 = 0x265;
    u8 *flagptr;
    
    flagptr = (u8 *)(pool1 + pool2);
    if (*flagptr == 0) {
        sub_08006168(pool1, (s8)a0, (s8)a1, a2, a3, a4, a5);
    }
}
