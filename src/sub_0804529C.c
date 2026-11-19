/* Task_4529C @ 0x0804529C (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_g2.c (registry: src/wave5_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Task_40798 @0x08040798 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * 7x Gfx_BlitRequest(ptr[i], 0x2f, 1/3/5/7/9/11/13, 8, 0);
 * pointers from ROM 0x082325E4..0x0823261C. */
void sub_08006A54(u32 a, u32 b, u32 c, u32 d, u32 e);

/* Task_45200 @0x08045200 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * Same 7x pattern with arg1=1; pointers from 0x08232C04..0x08232C3C. */
extern u32 gUnknown_08232C04[];

extern u32 gUnknown_08232C0C[];

extern u32 gUnknown_08232C14[];

extern u32 gUnknown_08232C1C[];

extern u32 gUnknown_08232C24[];

extern u32 gUnknown_08232C34[];

extern u32 gUnknown_08232C3C[];

/* Task_4529C @0x0804529C — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * Same 7x pattern with arg1=0x2f; same 0x08232C04 table. */
void sub_0804529C(void)
{
    sub_08006A54(gUnknown_08232C04[0], 0x2f, 1, 8, 0);
    sub_08006A54(gUnknown_08232C0C[0], 0x2f, 3, 8, 0);
    sub_08006A54(gUnknown_08232C14[0], 0x2f, 5, 8, 0);
    sub_08006A54(gUnknown_08232C1C[0], 0x2f, 7, 8, 0);
    sub_08006A54(gUnknown_08232C24[0], 0x2f, 9, 8, 0);
    sub_08006A54(gUnknown_08232C34[0], 0x2f, 11, 8, 0);
    sub_08006A54(gUnknown_08232C3C[0], 0x2f, 13, 8, 0);
}
