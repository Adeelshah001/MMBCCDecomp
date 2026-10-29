/* MMBCCDecomp — Wave 3 batch 5 staged matches (worker E, coordinator-split).
 * MATCHED 2026-10-20. All functions byte-identical (proven by
 * link-against-stubs + objcopy section diff vs baserom SHA-1
 * 72309736f3820470c6f372d6a05ad1f16bc5a946).
 *
 * This file: main agbcc -O2 -mthumb-interwork (13 functions).
 * Siblings: wave3_e_old.c (old_agbcc: ConstZeroS16_2472C),
 * wave3_e_noiw.c (agbcc WITHOUT -mthumb-interwork: DivZeroStub_4DEDE).
 *
 * All names are TENTATIVE (worker E, inferred from code shape + caller
 * context only). Absolute symbols (.set) are in ONE __asm__ block at the
 * END of this file: GAS 2.42 mis-binds R_ARM_THM_CALL when .set precedes
 * code (see docs/match_notes_wave2.md). EntryMgr_Teardown is already
 * matched for real (src/entrymgr.c) so it is extern-only here, no .set.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

/* Unmatched callees / absolute data (defined via .set at end of file). */
extern u8 gEwram5160[];           /* EWRAM base 0x02005160 */
extern u32 gTbl_0822D69C[];       /* ROM pointer table 0x0822D69C */
/* Already matched for real: */
extern void EntryMgr_Teardown(void);  /* src/entrymgr.c @ 0x08004F18 */

/* 0x08000A18 (2B, tentative): empty stub, returns void. No callers via bl
 * (likely reached via table). */
__attribute__((section(".text.w3e_empty_0a18")))
void EmptyStub_0A18(void)
{
}

/* 2-byte zero pad: ROM has 0000 after the 2 code bytes. */
__attribute__((section(".text.w3e_empty_0a18")))
static const u8 sPad_EmptyStub_0A18[2] = { 0, 0 };

/* 0x08025A08 (4B, tentative): returns byte at p[1]. Callers use it as a
 * small-index/flag byte getter. */
__attribute__((section(".text.w3e_getbyte1_25a08")))
u8 GetByte1_25A08(u8 *p)
{
    return p[1];
}

/* 0x0804005C (4B, tentative): constant 0. */
__attribute__((section(".text.w3e_constzero_4005c")))
u32 ConstZero_4005C(void)
{
    return 0;
}

/* 0x08011C50 (4B + pool, tentative): returns constant 0x4867. Sole caller
 * (sub_08011C80) truncates to u16 and compares `idx >= retval`, so this is
 * some kind of limit/capacity constant. agbcc pool-loads 0x4867. */
__attribute__((section(".text.w3e_getlimit_11c50")))
u16 GetLimit_11C50(void)
{
    return 0x4867;
}

/* 0x080030BC (6B, tentative): stores two halfwords at p+8 / p+10. */
__attribute__((section(".text.w3e_store2h_030bc")))
void StoreTwoHalves_030BC(u16 *p, u16 a, u16 b)
{
    p[4] = a;
    p[5] = b;
}

/* 2-byte zero pad (see EmptyStub_0A18 note). */
__attribute__((section(".text.w3e_store2h_030bc")))
static const u8 sPad_StoreTwoHalves_030BC[2] = { 0, 0 };

/* 0x080361DC (8B, tentative): tail-call wrapper around EntryMgr_Teardown.
 * The push/bl/pop/bx shape (not a direct `b`) is what agbcc -O2
 * -mthumb-interwork emits here. */
__attribute__((section(".text.w3e_teardownwrap_361dc")))
void TeardownWrap_361DC(void)
{
    EntryMgr_Teardown();
}

/* 0x080174CC (8B, tentative): o += 0x78, then halfword stores at +4/+6
 * (i.e. struct offsets 0x7C/0x7E). Sibling getters at 0x174D4/0x174DC/
 * 0x174E4/0x174EC do signed-halfword loads at 0x78/0x7A/0x7C/0x7E, so this
 * looks like an object/sprite attribute block (s16 x/y-ish pair). */
__attribute__((section(".text.w3e_setxy_174cc")))
void SetXY_174CC(u8 *o, u16 x, u16 y)
{
    o += 0x78;
    *(u16 *)(o + 4) = x;
    *(u16 *)(o + 6) = y;
}

/* 0x0801007C (8B + pool, tentative): *(u16 *)(0x02005160 + 0x46) = v.
 * The base must go through a u32 local: agbcc constant-folds
 * `(u8 *)0x02005160 + 0x46` into a single pool word, but the ROM does
 * `ldr r1,[pc,#4]` (pool = 0x02005160) + `adds r1,#0x46`. */
__attribute__((section(".text.w3e_ewramh_1007c")))
void WriteEwramHalf_1007C(u16 v)
{
    u32 base = (u32)gEwram5160;
    *(u16 *)(base + 0x46) = v;
}

/* 0x08004164 (10B, tentative): *(u32 *)(p + 0x204) = v. agbcc materializes
 * 0x204 as `movs r2,#0x81; lsls r2,r2,#2` (no pool). */
__attribute__((section(".text.w3e_setf204_04164")))
void SetField204_04164(u8 *p, u32 v)
{
    *(u32 *)(p + 0x204) = v;
}

/* 2-byte zero pad (see EmptyStub_0A18 note). */
__attribute__((section(".text.w3e_setf204_04164")))
static const u8 sPad_SetField204_04164[2] = { 0, 0 };

/* 0x08003090 (10B + pool, tentative): p[0] = a; p[1] = 0x0816E2CC;
 * p[2] = c (r2/b unused). The pool word points at a ROM struct
 * {0,0,0x08000400,0x20001000,...}. Same caller (sub_08005434) as
 * StoreTwoHalves_030BC and SetField204_04164 — a struct-init family. */
__attribute__((section(".text.w3e_inittri_03090")))
void InitTriple_03090(u32 *p, u32 a, u32 b, u32 c)
{
    p[0] = a;
    p[1] = 0x0816E2CC;
    p[2] = c;
}

/* 0x080267B4 (12B, tentative): inits an 8-byte record: word = 0x13,
 * byte1 = kind, dword+4 = 0. 19 bl-callers pass small constants (e.g. 3)
 * as kind. The explicit `u32 v` temp is load-bearing: it keeps the zero
 * in r2 (`movs r2,#0`) instead of reusing r1. */
__attribute__((section(".text.w3e_initrec8_267b4")))
void InitRec8_267B4(u8 *p, u8 kind)
{
    u32 v = 0x13;
    ((u32 *)p)[0] = v;
    v = 0;
    p[1] = kind;
    ((u32 *)p)[1] = v;
}

/* 0x08024734 (12B + pool, tentative): indexed word load from the ROM
 * pointer table at 0x0822D69C (entries are 0x080Fxxxx code pointers).
 * agbcc schedules the pool load between the two shifts, matching ROM. */
__attribute__((section(".text.w3e_tableget_24734")))
u32 TableGet_24734(u8 i)
{
    return gTbl_0822D69C[i];
}

/* 0x08028874 (12B, tentative): p[0] = (u8)v; p[1] = 0. */
__attribute__((section(".text.w3e_setpair0_28874")))
void SetPairZero_28874(u32 *p, u8 v)
{
    p[0] = v;
    p[1] = 0;
}

__asm__(
    ".globl gEwram5160\n.set gEwram5160, 0x02005160\n"
    ".globl gTbl_0822D69C\n.set gTbl_0822D69C, 0x0822D69C\n"
);
