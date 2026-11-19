/* CpuFastSet @ 0x0804DB24 (4 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/bios.c (registry: src/bios.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* MMBCCDecomp — BIOS call veneers (Wave 0).
 * ROM 0x0804DB24-0x0804DB38. Each compiles to `svc #n; bx lr`.
 * Calibrated: this exact idiom is byte-identical to the baserom. */

__attribute__((section(".text.bios")))
void CpuFastSet(void *src, void *dst, unsigned mode)
{
    __asm__ volatile("svc #0x0c");
}
