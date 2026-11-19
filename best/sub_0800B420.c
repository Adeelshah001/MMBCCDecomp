/* Sub_0800B420 @ 0x0800B420 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_0800b420_MATCHED.c (registry: mmbcc/src/w35b_0800b420_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08008460(u32 b, u8 *p, int n, u8 c);

void sub_0800B420(u8 a, u32 b, u8 c)
{
    u8 aa = a;
    u32 bb = b;
    u8 cc = c;
    u32 t = (u32)aa << 24;
    u8 ccT = (u8)(((u32)cc << 24) >> 24);
    u8 *base = (u8 *)0x02004e40;
    
    t >>= 20;
    t += 36;
    t += (u32)base;
    sub_08008460(bb, (u8 *)t, 8, ccT);
}
