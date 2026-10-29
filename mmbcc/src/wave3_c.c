/* MMBCCDecomp — Wave 3 batch 3 (worker C), 2026-10-20.
 * 15/15 MATCHED byte-identical, all with main agbcc
 * (-O2 -mthumb-interwork). Verified by linking each section at its ROM
 * address against 2-byte `bx lr` stubs at the real callee addresses,
 * then byte-diffing the extracted section vs the baserom
 * (SHA-1 72309736f3820470c6f372d6a05ad1f16bc5a946, read in place).
 *
 *  addr        name (TENTATIVE)        code   behavior
 *  0x080057FC  NoopStub                 2 B   empty stub; sole caller EntryMgr_HookA
 *  0x08003130  SetU32_4                 4 B   *(u32*)(s+4) = v
 *  0x08025A0C  GetU8_0                  4 B   return s[0]
 *  0x08017460  GetU8_12                 4 B   return s[0x12]
 *  0x08024724  ToU8                     6 B   return (u8)v
 *  0x0802617C  SetU32Pair               6 B   p[0] = p[1] = v
 *  0x0800EE38  G05130_SetU16_12        12 B   *(u16*)(g_02005130+0x12) = v (pool incl.)
 *  0x080256D4  SetU8_0_FF1              8 B   s[0] = v; s[1] = 0xFF
 *  0x080174EC  GetS16_78_3              8 B   return ((s16*)(s+0x78))[3]
 *  0x08021290  Wrap_ChipSlotTick       10 B   forwarder to sub_0800D9FC (wave-2
 *                                             ChipSlot_Tick candidate, BLOCKED)
 *  0x0804A2CC  G0BD10_Zero2            16 B   g_0200BD10[0] = g_0200BD10[1] = 0 (pool)
 *  0x08017488  IncU8_11                10 B   s[0x11]++; return s[0x11] (reloaded)
 *  0x0800EAB4  G05130_GetS8_0A         16 B   return (s8)g_02005130[0x0A] (pool)
 *  0x08002FC4  Text_SelectBlobU16      14 B   Text_SelectBlob((u16)idx) wrapper
 *  0x0804CA08  G0CE08_IndirectCall     20 B   g_0200CE08(a) via _call_via_r1 (pool)
 *
 * All names tentative (worker C, inferred from behavior). "G0xxxx" names
 * mark functions built around an absolute EWRAM global; the globals
 * g_02005130 / g_0200BD10 / g_0200CE08 are likewise tentative.
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md).
 *
 * Coordinator notes:
 * - NoopStub == sub_080057FC: entrymgr.c already declares it extern with
 *   .set (worker D) — drop that .set on integration (duplicate otherwise).
 * - Text_SelectBlob is extern-only here (defined in src/text.c) — no .set.
 * - _call_via_r1 is referenced implicitly by the backend for the indirect
 *   call; defined in asm/thunks.s — no declaration needed.
 * - gas pads each 2-mod-4 section with c0 46 (mov r8,r8); the ROM has
 *   00 00 in those inter-function gaps, so the trailing pad must NOT be
 *   emitted: strip to the code lengths above and place the next section
 *   at its explicit address (NoopStub 2, ToU8 6, SetU32Pair 6,
 *   Wrap_ChipSlotTick 10, IncU8_11 10, Text_SelectBlobU16 14). */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u8 g_02005130[];
extern u16 g_0200BD10[];
extern void (*g_0200CE08)(u32);
extern void sub_0800D9FC(u8 *s);
extern void Text_SelectBlob(u16 idx);

__attribute__((section(".text.w3c_noopstub")))
void NoopStub(void)
{
}

/* 2-byte zero pad: ROM has 0000 after the 2 code bytes; GAS would
 * otherwise end the section with its default nop fill (c046). */
__attribute__((section(".text.w3c_noopstub")))
static const u8 sPad_NoopStub[2] = { 0, 0 };

__attribute__((section(".text.w3c_setu32_4")))
void SetU32_4(u8 *s, u32 v)
{
    *(u32 *)(s + 4) = v;
}

__attribute__((section(".text.w3c_getu8_0")))
u8 GetU8_0(u8 *s)
{
    return s[0];
}

__attribute__((section(".text.w3c_getu8_12")))
u8 GetU8_12(u8 *s)
{
    return s[0x12];
}

__attribute__((section(".text.w3c_tou8")))
u8 ToU8(u32 v)
{
    return (u8)v;
}

/* 2-byte zero pad (see NoopStub note). */
__attribute__((section(".text.w3c_tou8")))
static const u8 sPad_ToU8[2] = { 0, 0 };

__attribute__((section(".text.w3c_setu32pair")))
void SetU32Pair(u32 *p, u32 v)
{
    p[0] = v;
    p[1] = v;
}

/* 2-byte zero pad (see NoopStub note). */
__attribute__((section(".text.w3c_setu32pair")))
static const u8 sPad_SetU32Pair[2] = { 0, 0 };

__attribute__((section(".text.w3c_g05130_setu16_12")))
void G05130_SetU16_12(u16 v)
{
    u8 *p = g_02005130;

    ((u16 *)p)[9] = v;
}

__attribute__((section(".text.w3c_setu8_0_ff1")))
void SetU8_0_FF1(u8 *s, u8 v)
{
    s[0] = v;
    s[1] = 0xFF;
}

__attribute__((section(".text.w3c_gets16_78_3")))
s16 GetS16_78_3(u8 *s)
{
    s16 *p = (s16 *)(s + 0x78);

    return p[3];
}

__attribute__((section(".text.w3c_wrap_chiptick")))
void Wrap_ChipSlotTick(u8 *s)
{
    sub_0800D9FC(s);
}

/* 2-byte zero pad (see NoopStub note). */
__attribute__((section(".text.w3c_wrap_chiptick")))
static const u8 sPad_Wrap_ChipSlotTick[2] = { 0, 0 };

__attribute__((section(".text.w3c_g0bd10_zero2")))
void G0BD10_Zero2(void)
{
    g_0200BD10[0] = 0;
    g_0200BD10[1] = 0;
}

__attribute__((section(".text.w3c_incu8_11")))
u8 IncU8_11(u8 *s)
{
    s[0x11]++;
    return s[0x11];
}

/* 2-byte zero pad (see NoopStub note). */
__attribute__((section(".text.w3c_incu8_11")))
static const u8 sPad_IncU8_11[2] = { 0, 0 };

__attribute__((section(".text.w3c_g05130_gets8_0a")))
s8 G05130_GetS8_0A(void)
{
    u8 *p = g_02005130;

    return (s8)p[0x0A];
}

__attribute__((section(".text.w3c_text_blobu16")))
void Text_SelectBlobU16(u16 idx)
{
    Text_SelectBlob(idx);
}

/* 2-byte zero pad (see NoopStub note). */
__attribute__((section(".text.w3c_text_blobu16")))
static const u8 sPad_Text_SelectBlobU16[2] = { 0, 0 };

__attribute__((section(".text.w3c_g0ce08_indirectcall")))
void G0CE08_IndirectCall(u32 a)
{
    g_0200CE08(a);
}

__asm__(
    ".globl g_02005130\n.set g_02005130, 0x02005130\n"
    ".globl g_0200BD10\n.set g_0200BD10, 0x0200BD10\n"
    ".globl g_0200CE08\n.set g_0200CE08, 0x0200CE08\n"
    ".globl sub_0800D9FC\n.set sub_0800D9FC, 0x0800D9FC\n"
    ".globl sub_080057FC\n.set sub_080057FC, NoopStub\n"
);
