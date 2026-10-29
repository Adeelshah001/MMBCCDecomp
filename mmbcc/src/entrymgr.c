/* MMBCCDecomp — Entry manager setup/teardown (Wave 2).
 * MATCHED 2026-10-20 (worker D, coordinator-verified byte-identical).
 * ROM 0x08004F18 (EntryMgr_Teardown, 88 B), 0x08004F70/0x4F7C
 * (vestigial hook slots, 14 B), 0x08004F80 (EntryMgr_Setup, 108 B).
 * Flags: old_agbcc -O2 -mthumb-interwork (see Makefile) — main agbcc
 * mis-schedules ldrb/movs order and mis-allocates the flag pointer.
 *
 * The 3-entry manager lives at 0x02003670 (entries at +44, +0x264,
 * +0x49C); mode flag byte at +0x11AE; generation counter at [base].
 * Teardown releases via the sub_08004208 family; Setup re-inits via
 * the sub_0800419C family and bumps the counter. Always called as a
 * pair from the same callers.
 *
 * Absolute callee symbols (.set): remove each line when that callee
 * gets matched for real (duplicate-symbol otherwise). */

typedef unsigned char u8;
typedef unsigned int u32;

/* Absolute callee addresses. The .globl/.set block MUST come after all
 * code in this file (see bottom): GAS 2.42 binds R_ARM_THM_CALL to a
 * broken synthetic LOCAL *ABS* symbol when the .set precedes the
 * referencing code, but to the correct GLOBAL symbol when it follows.
 * Remove each line when that callee gets matched for real
 * (duplicate-symbol otherwise). */

void sub_08004208(u8 *p);
void sub_080057FC(void);
void sub_0800D568(u32 v);
void sub_0800D59C(u32 v);
void sub_080050E0(u8 *base);
void sub_08004FEC(u8 *base);
void sub_0800419C(u8 *p);

static void EntryMgr_HookA(u8 *base);
static void EntryMgr_HookB(u8 *base);

__attribute__((section(".text.entrymgr_teardown")))
void EntryMgr_Teardown(void)
{
    u8 *base = (u8 *)0x02003670;
    u8 *p;
    sub_08004208(base + 44);
    sub_08004208(base + 0x264);
    sub_08004208(base + 0x49C);
    p = (u8 *)0x02005028;
    *p = 0;
    p = base + 0x11AE;
    if ((*p & 0xF8) != 8)
        EntryMgr_HookA(base);
    else
        EntryMgr_HookB(base);
}

/* Vestigial hook slot @0x08004F70 (worker-D "HelperA"): just forwards
 * to the empty sub_080057FC. */
__attribute__((section(".text.entrymgr_teardown")))
static void EntryMgr_HookA(u8 *base)
{
    (void)base;
    sub_080057FC();
}

/* Vestigial hook slot @0x08004F7C (worker-D "HelperB"): empty. */
__attribute__((section(".text.entrymgr_teardown")))
static void EntryMgr_HookB(u8 *base)
{
    (void)base;
}

/* 2-byte zero pad: ROM has 0000 at 0x4F7E; GAS would otherwise end the
 * section with its default nop fill (c046). */
__attribute__((section(".text.entrymgr_teardown")))
static const u8 sEntryMgrPad[2] = { 0, 0 };

__attribute__((section(".text.entrymgr_setup")))
void EntryMgr_Setup(void)
{
    u8 *base = (u8 *)0x02003670;
    u32 *hp = (u32 *)0x020066F0;
    u8 *p;
    sub_0800D568(*hp);
    sub_0800D59C(*hp);
    p = base + 0x11AE;
    *p |= 2;
    if ((*p & 0xF8) != 8)
        sub_08004FEC(base);
    else
        sub_080050E0(base);
    sub_0800419C(base + 0x49C);
    sub_0800419C(base + 44);
    sub_0800419C(base + 0x264);
    *(u32 *)base += 1;
}

/* Absolute callee addresses — MUST be after all code (see note at top:
 * GAS 2.42 .set-before-code mis-binds THM_CALL relocations). */
__asm__(
    ".globl sub_08004208\n.set sub_08004208, 0x08004208\n"
    ".globl sub_0800D568\n.set sub_0800D568, 0x0800D568\n"
    ".globl sub_0800D59C\n.set sub_0800D59C, 0x0800D59C\n"
    ".globl sub_080050E0\n.set sub_080050E0, 0x080050E0\n"
    ".globl sub_08004FEC\n.set sub_08004FEC, 0x08004FEC\n"
    ".globl sub_0800419C\n.set sub_0800419C, 0x0800419C\n"
);
