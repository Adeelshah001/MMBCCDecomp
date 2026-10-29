/* MMBCCDecomp — text blob index forwarder (Wave 2).
 * MATCHED 2026-10-20 (worker C, coordinator-verified byte-identical).
 * ROM 0x0804A378 (18 B code + 2 B zero pad).
 * Flags: main agbcc -O2 -mthumb-interwork.
 *
 * Tiny forwarder: zero-extends its u16 arg, calls sub_0800303C (the
 * Text_SelectBlob caller that returns the blob index), sign-extends
 * the result to s16. Callers ignore the return — invoked for the
 * blob-select side effect. The `pop {r1}; bx r1` epilogue is ordinary
 * agbcc output for this shape (cf. Sram_Read).
 *
 * Absolute callee symbol (.set) is at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md). Remove when sub_0800303C gets matched
 * for real (duplicate-symbol otherwise). */

typedef unsigned short u16;
typedef signed short s16;
typedef unsigned char u8;

s16 sub_0800303C(u16 idx);

__attribute__((section(".text.text_selidx")))
s16 Text_SelectBlobIdx(u16 idx)
{
    return sub_0800303C(idx);
}

/* 2-byte zero pad: ROM has 0000 at 0x4A38A; GAS would otherwise end the
 * section with its default nop fill (c046). */
__attribute__((section(".text.text_selidx")))
static const u8 sTextSelIdxPad[2] = { 0, 0 };

__asm__(
    ".globl sub_0800303C\n.set sub_0800303C, 0x0800303C\n"
);
