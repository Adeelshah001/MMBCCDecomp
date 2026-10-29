/* Text engine (Wave 1) — Mega Man Battle Chip Challenge decomp.
 *
 * Text_SelectBlob: MATCHED (byte-identical) using old_agbcc.
 *   The original ROM was built with a compiler version matching
 *   tools/agbcc/bin/old_agbcc (pre-patched variant). The current
 *   tools/agbcc/bin/agbcc produces different register allocation
 *   (r3 vs r2 for the table base), so text.c requires old_agbcc.
 *   See docs/match_notes_text.md for details.
 *
 * Text_OpenDialogue: BLOCKED — close but not byte-identical.
 *   Prologue (first 12 insns) matches exactly. Divergence in control
 *   flow and register allocation later. See docs/match_notes_text.md.
 *
 * Blob header layout (from disassembly, feeds Phase 4):
 *   [+0] = window count (u8)
 *   [+2] = flags (u8, compared against cfg[9])
 *   [+3] = flags (u8, bit 7 (0x80) gates sub_0804CBCC call)
 *   [+4] = word (copied to cfg[48])
 *   [+8] = per-window dwords (u32 each, count = window count)
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Absolute symbols for text directory and config table.
 * Defined via .set so the pool contains absolute addresses. */
__asm__(
    ".globl gTextCfgs\n.set gTextCfgs, 0x08106D7C\n"
    ".globl gTextDir\n.set gTextDir, 0x08106DD0\n"
);
extern u32 gTextCfgs[];
extern u8 gTextDir[];

void Text_OpenDialogue(u32 a, u32 b);

/* Text_SelectBlob @0x0804C6B4 — MATCHED with old_agbcc.
 * Indexes the 8-byte text directory, loads blob pointer and config word,
 * calls Text_OpenDialogue. */
__attribute__((section(".text.text_select")))
void Text_SelectBlob(u16 idx)
{
    u32 off = (u32)idx << 16;
    u32 *cfgs = gTextCfgs;
    u8 *dir = gTextDir;
    u32 *entry;
    u16 sub;

    off >>= 13;
    entry = (u32 *)(dir + off);
    sub = *(u16 *)((u8 *)entry + 4);
    Text_OpenDialogue(*(u32 *)((u8 *)cfgs + sub * 12), entry[0]);
}

/* Text_OpenDialogue @0x0804CDE8 — BLOCKED.
 * Dialogue-box state machine. Best attempt below; does not yet match.
 * See docs/match_notes_text.md for the precise diff. */
__attribute__((section(".text.text_open")))
void Text_OpenDialogue(u32 cfgWord, u32 blobPtr)
{
    /* TODO: matching implementation blocked. Stub for now. */
    (void)cfgWord;
    (void)blobPtr;
}
