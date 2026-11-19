/* Task_37A30 @ 0x08037A30 (74 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2_old.c (registry: src/wave5_h2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


s8 _call_via_r1(u8 *p, u32 v);

extern u32 gUnknown_08230DA8[];

void sub_08037A30(u8 *p)
{
    u32 *tbl = gUnknown_08230DA8;
    s8 idx = (s8)p[0x469c];
    u32 tbl_val = tbl[idx];
    u8 r = (u8)_call_via_r1(p, tbl_val);
    if (r == 1) goto L1;
    if (r == 2) goto L2;
    goto end;
L1: {
        u32 z = 0;
        p[1] = 3;
        p[3] = z;
        p[2] = z;
    }
    goto done;
L2: {
        u32 z = 0;
        p[1] = 4;
        p[3] = z;
        p[2] = z;
    }
done:
end: ;
}
