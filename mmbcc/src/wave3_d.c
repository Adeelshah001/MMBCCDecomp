/* MMBCCDecomp — Wave 3 batch 4 (worker D), staged 2026-10-20.
 *
 * 14 of 15 batch-4 leaves MATCHED (byte-identical, proven by linking each
 * section at its ROM address against the real absolute symbols and
 * diffing the full section bytes vs the baserom; SHA-1
 * 72309736f3820470c6f372d6a05ad1f16bc5a946 verified read-only in place).
 * 1 BLOCKED (0x0804DE64, see docs/match_notes_wave3_d.md).
 *
 * Compilers: main agbcc -O2 -mthumb-interwork for ALL matched functions
 * (old_agbcc tried where noted; never needed). All targets are Thumb.
 *
 * Per-function status (all names TENTATIVE — inferred from behavior only):
 *  0x08005208 NullCallback        MATCHED  2 B code (+2 B gas nop pad: ROM has
 *                                          the next function immediately at
 *                                          0x0800520A, strip pad at landing)
 *  0x080257F8 GetU16_10           MATCHED  4 B — *(u16*)(s+0x10)
 *  0x08023E30 GetU32_38           MATCHED  4 B — *(u32*)(s+0x38)
 *  0x08026550 GetU8_19            MATCHED  4 B — s[0x19]
 *  0x08011BC8 EwramGet_02005238   MATCHED 12 B — *(u32*)(0x02005230+8);
 *                                          6 B code + 00 00 gap + 4 B pool
 *  0x08026DB0 EwramSet_020070F7   MATCHED 12 B — *(u8*)(0x020070F0+7) = v
 *  0x08017458 IncU8_12            MATCHED  8 B — s[0x12]++
 *  0x080174E4 GetS16_7C           MATCHED  8 B — ((s16*)(s+0x78))[2];
 *                                          needs the p[2] form: direct
 *                                          (s+0x7C) folds to adds #0x7C
 *  0x0800EA08 EwramSet2_02005138  MATCHED 12 B — *(u8*)0x02005138=a,
 *                                          *(u8*)0x02005139=b
 *  0x0800B6E8 OrU8_1F             MATCHED 12 B — s[0x1F] |= 4 (10 B code +
 *                                          0000 pad); needs `u8 v = 4;`
 *                                          first so the constant lands in r1
 *  0x08004158 SetU32_200          MATCHED 12 B — *(u32*)(s+0x200) = v
 *                                          (10 B code + 0000 pad)
 *  0x0804BE44 Script_NextOp       MATCHED 12 B — ASM-STAGED (not C-compiled):
 *                                          script-interpreter fragment:
 *                                          advance [r1+0x40] script pointer,
 *                                          fetch opcode byte, jump to the
 *                                          ROM-pointer validator at
 *                                          0x0804BE2A. agbcc cannot emit the
 *                                          trailing `b` (no TCO); the
 *                                          C+inline-asm+noreturn probe
 *                                          reproduces the 10 code bytes but
 *                                          gcc appends a 2 B safety `bx lr`.
 *  0x08011CC4 TableU32_0820B6A4   MATCHED 16 B — table[(u16)idx], u32 table
 *                                          at 0x0820B6A4 (12 B code + pool)
 *  0x08011C04 EwramInit_02005260  MATCHED 16 B — p[0]=p[1]=v; p[2]=v+0x10
 *                                          at EWRAM 0x02005260
 *
 * Absolute symbols (.set) are in ONE __asm__ block at the END of this file:
 * GAS 2.42 mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md). Remove each .set when that symbol gets
 * matched for real (duplicate-symbol otherwise).
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u8 gEwram02005230[];
extern u8 gEwram020070F0[];
extern u8 gEwram02005130[];
extern u32 gTbl0820B6A4[];
extern u8 gEwram02005260[];

/* 0x08005208: no-op callback stub (1 bl caller: sub_080050F0). */
__attribute__((section(".text.w3d_noop")))
void NullCallback(void)
{
}

/* 2-byte zero pad: ROM has 0000 at 0x0800520A (next function at
 * 0x0800520C); GAS would otherwise end the section with c046. */
__attribute__((section(".text.w3d_noop")))
static const u8 sPad_NullCallback[2] = { 0, 0 };

/* 0x080257F8 */
__attribute__((section(".text.w3d_getu16_10")))
u16 GetU16_10(u8 *s)
{
    return *(u16 *)(s + 0x10);
}

/* 0x08023E30 */
__attribute__((section(".text.w3d_getu32_38")))
u32 GetU32_38(u8 *s)
{
    return *(u32 *)(s + 0x38);
}

/* 0x08026550 */
__attribute__((section(".text.w3d_getu8_19")))
u8 GetU8_19(u8 *s)
{
    return s[0x19];
}

/* 0x08011BC8: the local `base` keeps the two literal loads split
 * (ldr pool; ldr [r0,#8]); folding base+8 into the pool does NOT match. */
__attribute__((section(".text.w3d_ewramget")))
u32 EwramGet_02005238(void)
{
    u8 *base = gEwram02005230;
    return *(u32 *)(base + 8);
}

/* 0x08026DB0 */
__attribute__((section(".text.w3d_ewramset")))
void EwramSet_020070F7(u8 v)
{
    gEwram020070F0[7] = v;
}

/* 0x08017458 */
__attribute__((section(".text.w3d_incu8_12")))
void IncU8_12(u8 *s)
{
    s[0x12]++;
}

/* 0x080174E4: adds r0,#0x78 / movs r1,#4 / ldrsh [r0,r1] — the p[2] form.
 * Writing *(s16*)(s+0x7C) directly folds to adds #0x7C and does NOT match. */
__attribute__((section(".text.w3d_gets16_7c")))
s16 GetS16_7C(u8 *s)
{
    s16 *p = (s16 *)(s + 0x78);
    return p[2];
}

/* 0x0800EA08 */
__attribute__((section(".text.w3d_ewramset2")))
void EwramSet2_02005138(u8 a, u8 b)
{
    gEwram02005130[8] = a;
    gEwram02005130[9] = b;
}

/* 0x0800B6E8: `u8 v = 4;` first puts the constant in r1 (movs r1,#4 before
 * the ldrb); `s[0x1F] |= 4` / `= 4 | s[0x1F]` allocate r1/r2 swapped. */
__attribute__((section(".text.w3d_oru8_1f")))
void OrU8_1F(u8 *s)
{
    u8 v = 4;
    v |= s[0x1F];
    s[0x1F] = v;
}

/* 2-byte zero pad: ROM has 0000 at 0x0800B6F2; GAS would otherwise end the
 * section with its default nop fill (c046). */
__attribute__((section(".text.w3d_oru8_1f")))
static const u8 sOrU8_1FPd[2] = { 0, 0 };

/* 0x08004158: 0x200 materializes as movs r2,#0x80 / lsls r2,#2. */
__attribute__((section(".text.w3d_setu32_200")))
void SetU32_200(u8 *s, u32 v)
{
    *(u32 *)(s + 0x200) = v;
}

/* 2-byte zero pad: ROM has 0000 at 0x08004162. */
__attribute__((section(".text.w3d_setu32_200")))
static const u8 sSetU32_200Pd[2] = { 0, 0 };

/* 0x0804BE44: ASM-STAGED. Script-interpreter opcode-fetch fragment
 * (bytecode engine at ~0x0804BE10; see docs/match_notes_wave3_d.md):
 *   r2 = [r1+0x40] (script pointer); [r1+0x40] = r2+1;
 *   r3 = *r2 (opcode byte); jump to the ROM-pointer validator 0x0804BE2A
 *   (which zeroes r3 when r2 is outside 0x08105CC8..0x01FFFFFF).
 * C cannot express the trailing `b` (agbcc does no tail-call optimization:
 * `return sub_0804BE2A(...)` emits push{lr}/bl/pop{r1}/bx r1). The probe
 * `__attribute__((noreturn))` + inline-asm `b` reproduces the 10 code bytes
 * exactly, but gcc appends a 2-byte safety `bx lr` after the asm, so the
 * fragment is staged here as file-scope asm (10 B code + 0000 pad). */
__asm__(
".section .text.w3d_script_nextop,\"ax\"\n"
"\t.align 2\n"
"\t.code 16\n"
"\t.thumb_func\n"
"\t.globl Script_NextOp\n"
"\t.type Script_NextOp,%function\n"
"Script_NextOp:\n"
"\tldr r2, [r1, #64]\n"
"\tadd r3, r2, #1\n"
"\tstr r3, [r1, #64]\n"
"\tldrb r3, [r2]\n"
"\tb sub_0804BE2A\n"
"\t.2byte 0x0000\n"
"\t.size Script_NextOp,.-Script_NextOp\n"
);

/* 0x08011CC4: lsls r0,#16 / lsrs r0,#14 zero-extends the u16 arg and scales
 * by 4; u32 table at 0x0820B6A4. */
__attribute__((section(".text.w3d_tblu32")))
u32 TableU32_0820B6A4(u16 i)
{
    return gTbl0820B6A4[i];
}

/* 0x08011C04 */
__attribute__((section(".text.w3d_ewraminit")))
void EwramInit_02005260(u32 v)
{
    u32 *p = (u32 *)gEwram02005260;
    p[0] = v;
    p[1] = v;
    p[2] = v + 0x10;
}

__asm__(
".globl gEwram02005230\n.set gEwram02005230, 0x02005230\n"
".globl gEwram020070F0\n.set gEwram020070F0, 0x020070F0\n"
".globl gEwram02005130\n.set gEwram02005130, 0x02005130\n"
".globl gTbl0820B6A4\n.set gTbl0820B6A4, 0x0820B6A4\n"
".globl gEwram02005260\n.set gEwram02005260, 0x02005260\n"
".globl sub_0804BE2A\n.set sub_0804BE2A, 0x0804BE2A\n"
);
