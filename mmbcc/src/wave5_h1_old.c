/* Phase 3 Wave 5 POOL-H1 (old_agbcc): TableDispatch_9380 @0x08009380 —
 * MATCHED 2026-10-20, coordinator-verified 0 diffs over 76 bytes in
 * built ROM.
 * Loop over 6 entries (0x34 stride) at EWRAM 0x02004CE0; dispatches via
 * ROM table 0x0817212C indexed by (v>>6)&0xf. old_agbcc required for
 * r0/r1 allocation. Idioms: ((u32)v << 22) >> 28 reproduces the
 * lsls#22/lsrs#28 sequence; dual u16 i / s16 j loop vars for the
 * truncation dance.
 * Evidence: docs/match_notes_wave5_h1.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

extern u32 gTbl_0817212C[];
extern u8 gEwram_02004CE0[];

__attribute__((section(".text.w5h_9380")))
void TableDispatch_9380(void)
{
    u16 i = 0;
    s16 j = i;
    u32 *tbl = gTbl_0817212C;
    while (j <= 5) {
        u8 *p = gEwram_02004CE0 + j * 0x34;
        u8 b = *(p + 0x2c);
        if (b & 1) {
            u16 v = *(u16 *)(p + 0x2c);
            u32 idx = ((u32)v << 22) >> 28;
            ((void (*)(u8 *))tbl[idx])(p);
        }
        i = j + 1;
        j = i;
    }
}

__asm__(
    ".globl gTbl_0817212C\n.set gTbl_0817212C, 0x0817212C\n"
    ".globl gEwram_02004CE0\n.set gEwram_02004CE0, 0x02004CE0\n"
);
