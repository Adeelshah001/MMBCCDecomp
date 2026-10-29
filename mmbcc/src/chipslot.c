/* MMBCCDecomp — battle-chip slot helpers (Wave 2).
 * MATCHED 2026-10-20 (worker A, coordinator-verified byte-identical).
 * ROM 0x0800D9EC (ChipSlot_IncUse, 16 B), 0x0800D6E0
 * (ChipSlot_Setup, 34 B + 2 B zero pad).
 * Flags: main agbcc -O2 -mthumb-interwork (both first-try).
 *
 * Thin wrappers around the table-slot bookkeeping routines:
 * IncUse bumps a slot's use count via sub_08004258(s+0x70, idx)
 * (216 callers — the most-called utility in the ROM); Setup
 * initializes a slot via sub_0800D800(s, 0, b, c, 0) with the 5th
 * arg on the stack (95 callers).
 *
 * Absolute callee symbols (.set) are at the END of this file:
 * GAS 2.42 mis-binds R_ARM_THM_CALL when the .set precedes the code
 * (see docs/match_notes_wave2.md). Remove each line when that callee
 * gets matched for real (duplicate-symbol otherwise). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void sub_08004258(u8 *p, u8 idx);
void sub_0800D800(u8 *s, u8 a, u16 b, u8 c, u8 d);

__attribute__((section(".text.chipslot_incuse")))
void ChipSlot_IncUse(u8 *s, u8 idx)
{
    sub_08004258(s + 0x70, idx);
}

__attribute__((section(".text.chipslot_setup")))
void ChipSlot_Setup(u8 *s, u16 b, u8 c)
{
    sub_0800D800(s, 0, b, c, 0);
}

/* 2-byte zero pad: ROM has 0000 at 0xD702; GAS would otherwise end the
 * 34-byte section with its default nop fill (c046). */
__attribute__((section(".text.chipslot_setup")))
static const u8 sChipSlotPad[2] = { 0, 0 };

__asm__(
    ".globl sub_08004258\n.set sub_08004258, 0x08004258\n"
    ".globl sub_0800D800\n.set sub_0800D800, 0x0800D800\n"
);
