/* Wave 194 LANDING (2026-11-02 user ruling, sanctioned exception):
 * 0x08012B80 v10 alias, LANDED 0-diff (424/424 B, old_agbcc -O2, SHA 3453b252).
 * Sanctioned trick: .set alias block (Call_0800D9EC_c1 aliasing 0x0800D9EC);
 * compiler-steering only, invents no logic. Sanctioned FOR THIS FUNCTION ONLY
 * per the 2026-11-02 ruling; invented-logic tricks remain banned.
 * Section tag renamed w176f_ -> w194f_ at landing; no .set stub dropped
 * (audit: no stub symbol has a real definition in mmbcc/src/).
 */
/* Wave 176 Worker F restage of w176f_08012B80_v10_alias_oldO2.c (verbatim except section tag). */
/* Wave 169 Worker F restage of w168f_08012B80_v10_alias_oldO2.c (verbatim except section tag). */
/* Wave 168 Worker F restage of w167f_08012B80_v10_alias_oldO2.c (verbatim except section tag). */
/* Wave 167 Worker F restage of w166f_08012B80_v10_alias_oldO2.c (verbatim except section tag). */
/* Wave 166-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w165f_/w165f_08012B80_v10_alias_oldO2.c except section tag renamed to w166f_08012B80_v10_alias_oldO2; see RESULTS.md. */
/* Wave 165-F restage (STAGED ONLY, NOT LANDED): verbatim restage of w121a_/w121a_08012b80_v10_alias_oldO2.c except section tag renamed to w166f_08012B80_v10_alias_oldO2; see RESULTS.md. */
/* Wave 121-A re-verify: copy of Wave 120-A w121a_08012b80_v10_alias_oldO2.c, section renamed to .text.w121a_... only (plus this header line). */
/* Wave 93-A v10 (v9 + case-1 D9EC alias): 0x08012B80, 0 over / 0 full,
 * built 424 B = true extent 424 B, old_agbcc -O2 -mthumb-interwork
 * (standalone linked-at-address diff, verified Wave 93 from this staged
 * path; main agbcc gives 4 diffs elsewhere on this base, so the claim
 * compiler is old_agbcc). Change vs v9 (one change): case 1 calls
 * Call_0800D9EC_c1(s, 1) -- a second .set alias to the SAME address
 * 0x0800D9EC (see stub block at end) -- instead of the s[14] re-read.
 * Mechanism: ROM's case-1 and case-5 D9EC setups are RTL-identical
 * (adds r0,s; movs r1,#1; bl; b shared tail), so gcc -O2 cross-jumps
 * case-1's tail into case-5's when both call the same symbol (bare
 * literal-1 poison, 296/308, still true for the non-alias form and NOT
 * retried). With distinct callee symbols the RTL call insns differ, so
 * no merge happens, and both bl instructions still encode to the same
 * target address, giving byte-identical output. No pin, no inline asm,
 * no barrier, no flag change; the call is a plain C call to the same
 * function. LANDING NOTE for coordinator: in the real build the alias
 * must survive as a symbol alias for the matched D9EC function
 * (e.g. an ldscript alias), otherwise the two calls collapse to one
 * symbol and the merge returns; if the alias is ruled not-landable,
 * fall back to v9 (4/4, s[14] re-read). */
/* Wave 89-A v9 (clean, no pin/asm/barrier). 0x08012B80, 4/4 diffs,
 * built 424 B = true extent 424 B, old_agbcc -O2 -mthumb-interwork
 * (standalone linked-at-address diff, verified Wave 89; main result on
 * this base recorded in notes). Breakthrough vs v7 (94/98): case 7 moved
 * OUT of the switch into a post-switch label (case 7: goto c7; default:
 * goto epi; } s[14]++; goto epi; c7: ...; goto epi; epi: D9FC(s);).
 * This reproduces ROM layout exactly: shared increment at built 0x08012CDC
 * BEFORE case-7 code at 0x08012CE4, case-7 code BEFORE epilogue at
 * 0x08012D16, epilogue + trailing pool at 0x08012D24. Remaining diffs
 * ONLY: +122,+123,+124,+125 - case-1 D9EC argument block (built re-reads
 * s[14], ROM uses literal 1). POISON: do NOT "fix" this by writing
 * D9EC(s, 1) - it cross-jumps case-1's D9EC tail into case-5's and gives
 * 296/308, 412 B (tested on this base). The re-read is semantically exact:
 * s[14] is provably 1 in case 1 and DD2C (MATCHED Vec2_SetMirrored) writes
 * only s+80/s+84, so s[14] is unchanged across the DD2C call.
 * Prior header (Wave 86-A v7) below.
 */
/* Wave 86-A v7 (v6 + shift-mask spelling for s[35]&15 in cases 3 and 5):
 * v6 note: DD2C is MATCHED Vec2_SetMirrored (src/vec2.c): it reads s+35 and
 * writes ONLY s+80/s+84, so s[14] is provably unchanged across the DD2C call
 * and D9EC(s, s[14]) passes exactly 1 — semantically exact, clean C:
 * Wave 85-A v1: 0x08012B80, registry-fresh (func_stats 420 B). TRUE extent 420 B:
 * next function 0x08012D24. Decode from ROM disassembly (jump-table base
 * 0x08012BA0 at 0x08012B9C; cases BC0/BE0/C04/C24/C60/C76/CBC/CE4):
 * void F(u8 *s). Switch on s[14] (8 cases; default -> epilogue).
 * Shared tail (CDC): s[14]++; epilogue: Call_0800D9FC(s); return.
 * case 0: DD2C(s, -15360, 0); D9EC(s, 2); A378(152); -> tail.
 * case 1: if (F50(s) == 0) -> epilogue; DD2C(s, 1024, 0); D9EC(s, 1); -> tail.
 * case 2: if (F50(s) == 0) -> epilogue; A4_174A4(*(s+44), 3); D9EC(s, 9); -> tail.
 * case 3: if (F50(s) == 0) -> epilogue; AB94(30, s[35]&15, 15360, -7168, *(s+44));
 *   D9EC(s, 10); A78_17478(*(s+44), 1); -> tail.
 * case 4: if (F50(s) == 0) -> epilogue; D9EC(s, 2); -> tail.
 * case 5: if (F50(s) == 0) -> epilogue; B98C(10, 0, s[35]&15, -15360, -25600,
 *   *(s+44)); DD2C(s, -15360, 0); D9EC(s, 1); -> tail.
 * case 6: if (F50(s) == 0) -> epilogue; A78_17478(*(s+44), 8); D9EC(s, 0);
 *   s[18] = 30; -> tail.
 * case 7: if ((s8)--s[18] != 0) -> epilogue; A64_17464(*(s+44)); *(s+44) = 0;
 *   DD2C(s, -15360, 0); D9EC(s, 0); s[128] = 0; F68_1F68(s, 0); -> epilogue.
 * .set stubs verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

s16 Call_08011F50(u8 *s);
void Call_0800DD2C(u8 *s, s32 x, s32 y);
void Call_0800D9EC(u8 *s, u32 a);
void Call_0800D9EC_c1(u8 *s, u32 a);
void Call_0804A378(u32 a);
void Call_080174A4(u32 a, u32 b);
void Call_0801AB94(u32 a, u32 b, s32 c, s32 d, u32 e);
void Call_08017478(u32 a, u32 b);
void Call_0801B98C(u32 a, u32 b, u32 c, s32 d, s32 e, u32 f);
void Call_08017464(u32 a);
void Call_08011F68(u8 *s, u32 a);
void Call_0800D9FC(u8 *s);

__attribute__((section(".text.w194f_08012b80_v10_alias_oldO2")))
void sub_08012B80(u8 *s)
{
    u8 *p124 = s + 124;
    switch (s[14]) {
    case 0:
        Call_0800DD2C(s, -15360, 0);
        Call_0800D9EC(s, 2);
        Call_0804A378(152);
        break;
    case 1:
        if (Call_08011F50(s) == 0)
            goto epi;
        Call_0800DD2C(s, 1024, 0);
        Call_0800D9EC_c1(s, 1);
        break;
    case 2:
        if (Call_08011F50(s) == 0)
            goto epi;
        Call_080174A4(*(u32 *)(s + 44), 3);
        Call_0800D9EC(s, 9);
        break;
    case 3:
        if (Call_08011F50(s) == 0)
            goto epi;
        Call_0801AB94(30, ((u32)s[35] << 28) >> 28, 15360, -7168, *(u32 *)(s + 44));
        Call_0800D9EC(s, 10);
        Call_08017478(*(u32 *)(s + 44), 1);
        break;
    case 4:
        if (Call_08011F50(s) == 0)
            goto epi;
        Call_0800D9EC(s, 2);
        break;
    case 5:
        if (Call_08011F50(s) == 0)
            goto epi;
        Call_0801B98C(10, 0, ((u32)s[35] << 28) >> 28, -15360, -25600, *(u32 *)(s + 44));
        Call_0800DD2C(s, -15360, 0);
        Call_0800D9EC(s, 1);
        break;
    case 6:
        if (Call_08011F50(s) == 0)
            goto epi;
        Call_08017478(*(u32 *)(s + 44), 8);
        Call_0800D9EC(s, 0);
        s[18] = 30;
        break;
    case 7:
        goto c7;
    default:
        goto epi;
    }
    s[14]++;
    goto epi;
c7:
        if ((s8)--s[18] != 0)
            goto epi;
        Call_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Call_0800DD2C(s, -15360, 0);
        Call_0800D9EC(s, 0);
        p124[4] = 0;
        Call_08011F68(s, 0);
        goto epi;
epi:
    Call_0800D9FC(s);
}

__asm__(
    ".globl Call_08011F50\n.set Call_08011F50, 0x08011F50\n"
    ".globl Call_0800DD2C\n.set Call_0800DD2C, 0x0800DD2C\n"
    ".globl Call_0800D9EC\n.set Call_0800D9EC, 0x0800D9EC\n"
    ".globl Call_0800D9EC_c1\n.set Call_0800D9EC_c1, 0x0800D9EC\n"
    ".globl Call_0804A378\n.set Call_0804A378, 0x0804A378\n"
    ".globl Call_080174A4\n.set Call_080174A4, 0x080174A4\n"
    ".globl Call_0801AB94\n.set Call_0801AB94, 0x0801AB94\n"
    ".globl Call_08017478\n.set Call_08017478, 0x08017478\n"
    ".globl Call_0801B98C\n.set Call_0801B98C, 0x0801B98C\n"
    ".globl Call_08017464\n.set Call_08017464, 0x08017464\n"
    ".globl Call_08011F68\n.set Call_08011F68, 0x08011F68\n"
    ".globl Call_0800D9FC\n.set Call_0800D9FC, 0x0800D9FC\n"
);
