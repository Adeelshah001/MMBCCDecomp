/* ListIterate_D568 @ 0x0800D568 (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h1.c (registry: src/wave5_h1.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* ListIterate_D568 @0x0800D568 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 46 bytes in built ROM.
 * Linked-list traversal: InitLinkedNode(s) setup, then iterates nodes
 * (next at +4, fn pointer at +0x14) calling each via _call_via_r1 until
 * back to the s+0x14 sentinel. Idiom: `if (p != s + 0x14)` with the
 * literal (not via an `end` variable) reproduces the r1->r5 move. */
extern void sub_0800440C(u8 *s);

void sub_0800D568(u8 *s)
{
    u8 *p;
    u8 *end;
    sub_0800440C(s);
    p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
    *(u8 **)(s + 0xc) = p;
    if (p != s + 0x14) {
        end = s + 0x14;
        do {
            ((void (*)(u8 *))*(u32 *)(p + 0x14))(p);
            p = *(u8 **)(*(u8 **)(s + 0xc) + 4);
            *(u8 **)(s + 0xc) = p;
        } while (p != end);
    }
}
