/* MMBCCDecomp — flag-gated dispatch forwarder (Wave 2).
 * MATCHED 2026-10-20 (worker D, coordinator-verified byte-identical).
 * ROM 0x08006DD8 (88 B, incl. 2-byte zero tail pad).
 * Flags: main agbcc -O2 -mthumb-interwork (no old_agbcc needed).
 *
 * Returns 0 while *(u8*)(0x02004830+0x265) is set, else forwards to
 * sub_08006E6C with u16->s16 / u8->s8 conversions; the last two args
 * travel on the stack. Called 77x, mostly from the table-driven
 * dispatcher sub_080285C4.
 *
 * Absolute callee symbol (.set): remove when sub_08006E6C gets
 * matched for real (duplicate-symbol otherwise). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

/* Absolute callee address. The .globl/.set block MUST come after all
 * code in this file (see bottom): GAS 2.42 binds R_ARM_THM_CALL to a
 * broken synthetic LOCAL *ABS* symbol when the .set precedes the
 * referencing code, but to the correct GLOBAL symbol when it follows.
 * Remove when sub_08006E6C gets matched for real. */

u8 sub_08006E6C(u8 *base, void *p, s16 x, s16 y, s8 z, u8 w);

__attribute__((section(".text.gateddispatch")))
u8 GatedDispatch(void *p, u32 a, u32 b, u32 c, u32 d)
{
    u16 x = (u16)a;
    u16 y = (u16)b;
    u8 z = (u8)c;
    u8 w = (u8)d;
    u8 *base = (u8 *)0x02004830;
    if (*(base + 0x265) != 0)
        return 0;
    return (u8)sub_08006E6C(base, p, (s16)x, (s16)y, (s8)z, w);
}

/* 2-byte zero pad: ROM has 0000 here; GAS would otherwise end the
 * section with its default nop fill (c046). */
__attribute__((section(".text.gateddispatch")))
static const u8 sGatedDispatchPad[2] = { 0, 0 };

/* Absolute callee address — MUST be after all code (see note at top:
 * GAS 2.42 .set-before-code mis-binds THM_CALL relocations). */
__asm__(
    ".globl sub_08006E6C\n.set sub_08006E6C, 0x08006E6C\n"
);
