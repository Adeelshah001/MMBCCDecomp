/* MMBCCDecomp — no-interwork functions (coordinator-landed).
 *
 * These functions come from a non-interwork compilation unit (the ROM's
 * SRAM/libgcc-style region at 0x0804DD90-0x0804DE6E): agbcc emits
 * `pop {pc}` epilogues only WITHOUT -mthumb-interwork. Evidence:
 * docs/match_notes_wave3_d.md (DivZeroStub), docs/match_notes_wave3_e.md
 * (DivZeroStub_4DEDE). Makefile rule for this file omits
 * -mthumb-interwork (precedent: text.o/vec2.o/entrymgr.o overrides).
 */

typedef unsigned char u8;
typedef unsigned int u32;

extern void sub_0804DD9C(void);

/* 0x0804DE64: divide-by-zero exit stub (TENTATIVE name, worker D).
 * MATCHED 2026-10-20 (coordinator): agbcc -O2 WITHOUT -mthumb-interwork.
 * ROM 10 B: push {lr}; bl 0x0804DD9C; movs r0,#0; pop {pc}. */
__attribute__((section(".text.w3d_divzero")))
u32 DivZeroStub(void)
{
    sub_0804DD9C();
    return 0;
}

/* 2-byte zero pad: ROM has 0000 after the 10 code bytes. */
__attribute__((section(".text.w3d_divzero")))
static const u8 sPad_DivZeroStub[2] = { 0, 0 };

__asm__(
    /* Temporary: sub_0804DD9C (mov pc,lr stub) is not matched yet.
       Remove this .set when it is (duplicate-symbol otherwise). */
    ".globl sub_0804DD9C\n.set sub_0804DD9C, 0x0804DD9C\n"
);
