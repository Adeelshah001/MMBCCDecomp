/* Fwd4_08005704 @ 0x08005704 (22 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Fwd4_08005704 @ 0x08005704 */
void sub_0800571C(void);

 void Sub_08009140(void);

 void Sub_08009238(void);

 void sub_080092C8(void);

__attribute__((section(".text.w14c_08005704")))
void Fwd4_08005704(void) { sub_0800571C(); Sub_08009140(); Sub_08009238(); sub_080092C8(); }
