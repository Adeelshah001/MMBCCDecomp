/* Sub_0804CA30 @ 0x0804CA30 (248 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w42d_0804ca30_MATCHED.c (registry: mmbcc/src/w42d_0804ca30_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void CpuSet(void *src, void *dst, unsigned mode);

extern void Script_InitTable36_0804BE10(u32 a);

extern void Sub_0804CB28(u32 keys);

__attribute__((section(".text.w42d_0804ca30")))
void Sub_0804CA30(u8 *s)
{
    volatile u16 *e;
    register volatile u16 *q __asm__("r1");
    register volatile u32 *d __asm__("r1");
    u32 t;
    *(u32 *)s = 0;
    if (*(u32 *)0x040000C4 & 0x02000000)
        *(u32 *)0x040000C4 = 0x84400004;
    if (*(u32 *)0x040000D0 & 0x02000000)
        *(u32 *)0x040000D0 = 0x84400004;
    e = (u16 *)0x040000C6;
    *e = 1024;
    e += 6;
    *e = 1024;
    q = (u16 *)0x04000084;
    *q = 143;
    q--;
    *q = 0xA90E;
    { u8 bv = *(volatile u8 *)0x04000089; *(volatile u8 *)0x04000089 = (bv & 63) | 64; }
    d = (u32 *)0x040000BC;
    *d = (u32)(s + 848);
    __asm__ volatile("" : "=r"(d) : "0"(d));
    d++;
    *d = 0x040000A0;
    d += 2;
    *d = (u32)(s + 2432);
    __asm__ volatile("" : "=r"(d) : "0"(d));
    d++;
    *d = 0x040000A4;
    *(u8 **)0x03007FF0 = s;
    t = 0;
    CpuSet(&t, s, 0x050003EC);
    s[6] = 8;
    s[7] = 15;
    *(u32 *)(s + 56) = 0x0804C2FD;
    *(u32 *)(s + 40) = 0x0804DB21;
    *(u32 *)(s + 44) = 0x0804DB21;
    *(u32 *)(s + 48) = 0x0804DB21;
    *(u32 *)(s + 60) = 0x0804DB21;
    Script_InitTable36_0804BE10(0x0200CD80);
    *(u32 *)(s + 52) = 0x0200CD80;
    Sub_0804CB28(262144);
    *(u32 *)s = 0x68736D53;
}
