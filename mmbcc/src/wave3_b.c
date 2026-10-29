/* MMBCCDecomp — Wave 3 batch 2 (worker, 2026-10-20).
 *
 * 15 leaf functions, all MATCHED byte-identical (worker-verified by
 * objcopy-section byte-diff vs baserom SHA-1
 * 72309736f3820470c6f372d6a05ad1f16bc5a946).
 *
 * Compilers: main agbcc -O2 -mthumb-interwork unless noted.
 *  - TailCallR3 (0x0804C278, 2 B): naked+asm (agbcc lowers any indirect C
 *    call via _call_via_r3; ROM is a direct `bx r3`).
 *  - ArmTrampoline (0x0804B970, 4 B): naked+asm (Thumb->ARM trampoline).
 *  - SetHalf8000 (0x080082CC, 10 B): naked+asm (original compiler's
 *    redundant r2->r1 copy not reproducible in C on this agbcc).
 *  - EwSet8Ret1_20 (0x08010DDC, 12 B): agbcc; the `(u8)(v|1)&1` return
 *    forces back the redundant (u8) truncation the original compiler
 *    emitted before the strb (folds to constant 1).
 *  - All others: plain C, main agbcc, first-try matches.
 *
 * Naming: all names are TENTATIVE (worker-inferred from behavior).
 * EWRAM/ROM struct layouts are minimal (only fields touched by these
 * functions); the 0x02005130/0x02005160/0x020051B0/0x02007090/0x0200BD20
 * regions and the 0x0822740C table need proper naming later.
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md). Remove the ChipSlot_Tick .set when that
 * symbol gets matched for real (duplicate-symbol otherwise); the
 * ewXXX/romXXX data symbols are addresses and stay.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* --- EWRAM / ROM region views (minimal, tentative) --- */
struct Ew02005130 { u8 _00[12]; u16 f12; u16 f14; u16 f16; u16 f18; };
struct Ew02005160 { u8 _00[68]; u8 f68; u8 _69[3]; u8 f72; };
struct Ew020051B0 { u8 _00[20]; u8 f20; };
struct Ew02007090 { u8 _00[18]; u16 f18; };
struct Ew0200BD20 { u8 _00[128]; u16 f128; };
struct Rom0822740C { u8 _00[11]; u8 f11; u8 _0C[4]; }; /* 16-byte entries */

extern struct Ew02005130 ew02005130;
extern struct Ew02005160 ew02005160;
extern struct Ew020051B0 ew020051B0;
extern struct Ew02007090 ew02007090;
extern struct Ew0200BD20 ew0200BD20;
extern struct Rom0822740C rom0822740C[];
extern void ChipSlot_Tick(u8 *s);

/* Tail-call trampoline via r3 (TENTATIVE name).
 * ROM 0x0804C278 (2 B). Callers (text window dispatch: sub_0804C288,
 * sub_0804C2FC, ...) load a function pointer into r3 then `bl` here;
 * `bx r3` jumps to it leaving lr intact so the target returns directly
 * to the caller's caller. */
__attribute__((naked, section(".text.w3b_tailcallr3")))
void TailCallR3(void)
{
    __asm__ volatile("bx r3");
}

/* 2-byte zero pad: ROM has 0000 after the 2 code bytes; GAS would
 * otherwise end the section with its default nop fill (c046). */
__attribute__((section(".text.w3b_tailcallr3")))
static const u8 sPad_TailCallR3[2] = { 0, 0 };

/* Byte setter at struct offset 1 (TENTATIVE name).
 * ROM 0x080256DC (4 B). */
__attribute__((section(".text.w3b_setu8_1")))
void SetU8_Off1(u8 *p, u8 v)
{
    p[1] = v;
}

/* Thumb->ARM trampoline (TENTATIVE name).
 * ROM 0x0804B970 (4 B): adr r2, 0x0804B974; bx r2.
 * Target is ARM code: add r2,r3,r0,lsl r1; add r0,r3,#0; bx lr. */
__attribute__((naked, section(".text.w3b_armtramp")))
void ArmTrampoline(void)
{
    __asm__ volatile("adr r2, 1f\n\tbx r2\n1:");
}

/* Halfword getter at struct offset 14 (TENTATIVE name).
 * ROM 0x080257B8 (4 B). */
__attribute__((section(".text.w3b_getu16_14")))
u16 GetU16_Off14(u8 *p)
{
    return *(u16 *)(p + 14);
}

/* EWRAM u16 getter (TENTATIVE name).
 * ROM 0x08024760 (6 B code): return ew02007090.f18.
 * 14 bl callers in the 0x08042xxx-0x08045xxx range; one compares the
 * result against 7 (u16). */
__attribute__((section(".text.w3b_ewget16_18")))
u16 EwGet16_18(void)
{
    return ew02007090.f18;
}

/* EWRAM u16 setter, offset 14 of 0x02005130 (TENTATIVE name).
 * ROM 0x0800EDF0 (6 B code). */
__attribute__((section(".text.w3b_ewset16_14")))
void EwSet16_14(u16 v)
{
    ew02005130.f14 = v;
}

/* EWRAM u16 setter, offset 16 of 0x02005130 (TENTATIVE name).
 * ROM 0x0800EE2C (6 B code). */
__attribute__((section(".text.w3b_ewset16_16")))
void EwSet16_16(u16 v)
{
    ew02005130.f16 = v;
}

/* Singly-linked list push-front (TENTATIVE name).
 * ROM 0x08004170 (8 B): node->next = *head; *head = node.
 * Callers: sub_080093D0, sub_08009490, sub_0800954C. */
__attribute__((section(".text.w3b_listpush")))
void ListPushFront(void **head, void *node)
{
    void *old = *head;
    *(void **)node = old;
    *head = node;
}

/* EWRAM byte setter, offset 68 of 0x02005160 (TENTATIVE name).
 * ROM 0x0800EE44 (8 B code). */
__attribute__((section(".text.w3b_ewset8_68")))
void EwSet8_68(u8 v)
{
    ew02005160.f68 = v;
}

/* ChipSlot_Tick (0x0800D9FC, BLOCKED wave2) tail wrapper (TENTATIVE).
 * ROM 0x08011F7C (8 B): push {lr}; bl ChipSlot_Tick; pop {r0}; bx r0. */
__attribute__((section(".text.w3b_tickwrap")))
void TickWrapper(u8 *s)
{
    ChipSlot_Tick(s);
}

/* 2-byte zero pad (see TailCallR3 note): 10 B code + 0000. */
__attribute__((section(".text.w3b_tickwrap")))
static const u8 sPad_TickWrapper[2] = { 0, 0 };

/* Halfword setter to constant 0x8000 (TENTATIVE name).
 * ROM 0x080082CC (10 B). Callers at 0x0800A83A/0x0800A84C pass only r0.
 * The original compiler's redundant r2->r1 copy (movs r2,#128;
 * lsls r2,#8; adds r1,r2,#0) is not reproducible in C on this agbcc
 * (always folds to 8 B); direct transcription via naked+asm.
 * NOTE: GAS 2.42 rejects 's'-suffixed Thumb mnemonics (lsls/adds);
 * the unsuffixed forms encode identically (verified byte-for-byte). */
__attribute__((naked, section(".text.w3b_sethalf8000")))
void SetHalf8000(u16 *p)
{
    __asm__ volatile(
        "movs r2, #128\n\t"
        "lsl r2, r2, #8\n\t"
        "add r1, r2, #0\n\t"
        "strh r1, [r0, #0]\n\t"
        "bx lr");
}

/* 2-byte zero pad (see TailCallR3 note): 10 B code + 0000. */
__attribute__((section(".text.w3b_sethalf8000")))
static const u8 sPad_SetHalf8000[2] = { 0, 0 };

/* EWRAM byte setter to 1, offset 72 of 0x02005160 (TENTATIVE name).
 * ROM 0x08010364 (10 B code). Called once from sub_0800EE8C. */
__attribute__((section(".text.w3b_ewset8_72")))
void EwSet8_72(void)
{
    ew02005160.f72 = 1;
}

/* EWRAM u16 setter to 0, offset 128 of 0x0200BD20 (TENTATIVE name).
 * ROM 0x0804A3FC (10 B code). */
__attribute__((section(".text.w3b_ewset16_128")))
void EwSet16_128(void)
{
    ew0200BD20.f128 = 0;
}

/* ROM table byte lookup (TENTATIVE name).
 * ROM 0x08026710 (12 B code): return rom0822740C[(u8)a].f11.
 * 16-byte entries; the struct view is what reproduces the ROM's
 * interleaved scheduling (pool load between the two shifts). Callers
 * truncate the result to u8. 6 bl callers. */
__attribute__((section(".text.w3b_tblget11")))
u8 TblGet11(u8 a)
{
    return rom0822740C[a].f11;
}

/* EWRAM flag setter returning 1 (TENTATIVE name).
 * ROM 0x08010DDC (12 B code): ew020051B0.f20 = (u8)v; return 1.
 * The `(u8)(v|1)&1` return forces back the redundant (u8) truncation
 * the original compiler emitted before the strb (this agbcc drops it
 * as a no-op); the expression still folds the return to constant 1.
 * Sibling reader at 0x08010DEC returns (f20 == 0). */
__attribute__((section(".text.w3b_ewset8ret1_20")))
u8 EwSet8Ret1_20(u8 v)
{
    ew020051B0.f20 = v;
    return (u8)(v | 1) & 1;
}

__asm__(
    ".globl ew02005130\n.set ew02005130, 0x02005130\n"
    ".globl ew02005160\n.set ew02005160, 0x02005160\n"
    ".globl ew020051B0\n.set ew020051B0, 0x020051B0\n"
    ".globl ew02007090\n.set ew02007090, 0x02007090\n"
    ".globl ew0200BD20\n.set ew0200BD20, 0x0200BD20\n"
    ".globl rom0822740C\n.set rom0822740C, 0x0822740C\n"
    /* Wave 35: ChipSlot_Tick (0x0800D9FC) now matched (src/w35a_0800d9fc.c);
       the temporary .set above was removed (duplicate-symbol otherwise). */
);
