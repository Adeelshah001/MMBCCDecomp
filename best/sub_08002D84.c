/* Sub_08002D84 @ 0x08002D84 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08002d84_MATCHED.c (registry: mmbcc/src/w35c_08002d84_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct A { u16 f0; u16 f2; u8 pad4[4]; u8 f8; u8 f9; u8 f10; u8 pad11; u16 f12; u16 f14; u16 f16; u16 f18; u8 pad20[4]; u16 f24; u8 pad26[2]; u32 f28; u8 pad32[11]; u8 f43; };

extern void sub_08002DCC(u32 v);

void sub_08002D84(void)
{
    register u32 A = 0x03002830;
    u32 *C;
    u32 tmp;
    
    *(u32 *)(A + 1028) = (128 << 5);
    *(u32 *)(A + (128 << 3)) = A;
    tmp = (128 << 2);
    C = (u32 *)0x040000d4;
    C[0] = (u32)&tmp;
    C[1] = A;
    C[2] = 0x85000100;
    sub_08002DCC(*(volatile u32 *)&C[2]);
}
