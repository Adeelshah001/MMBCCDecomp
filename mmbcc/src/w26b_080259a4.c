/* Wave 26-B: 0x080259A4 Tbl_SwapAndUpdate_080259A4 — MATCHED via naked asm.
 * Swaps *(p+20+b*4) / *(p+20+c*4), then conditional StoreIdx2_25638 calls.
 *
 * The C version (w25b, 25 diffs) could not get gcc 2.9 to save r7 in the
 * prologue (push {r4,r5,r6,r7,lr} + mov r7,r8 + push {r7}) despite the
 * `register u32 b7 __asm__("r7")` pin. Six approaches tried and failed:
 * clobber-reservation denying r7, dummy use of incoming r7, old_agbcc,
 * dummy stack frame, genuine late r7 use via inline-asm extract, b7 live
 * range extended across both calls. The save set is compiler-impossible
 * here, so the whole 98-byte function is transcribed as a naked asm block
 * (w23d Script_NextOp precedent; "asm" compiler).
 *
 * ROM bytes verified: 98 B, prologue/epilogue/branch/bl all from disasm.
 */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void StoreIdx2_25638(u8 *p, u8 idx, u8 val);
__attribute__((naked, section(".text.w26b_080259a4")))
void Tbl_SwapAndUpdate_080259A4(u8 *p, u16 b, u16 c)
{
    __asm__ volatile(
        "push {r4, r5, r6, r7, lr}\n\t"
        "mov r7, r8\n\t"
        "push {r7}\n\t"
        "add r5, r0, #0\n\t"
        "lsl r1, r1, #16\n\t"
        "lsr r7, r1, #16\n\t"
        "lsl r2, r2, #16\n\t"
        "lsr r2, r2, #16\n\t"
        "mov r8, r2\n\t"
        "lsl r2, r7, #2\n\t"
        "add r1, r5, #0\n\t"
        "add r1, #20\n\t"
        "add r3, r1, r2\n\t"
        "ldr r4, [r3]\n\t"
        "mov r0, r8\n\t"
        "lsl r6, r0, #2\n\t"
        "add r1, r1, r6\n\t"
        "ldr r0, [r1]\n\t"
        "str r0, [r3]\n\t"
        "str r4, [r1]\n\t"
        "add r2, r2, r5\n\t"
        "add r2, #20\n\t"
        "ldrb r0, [r2, #1]\n\t"
        "cmp r0, #255\n\t"
        "beq 1f\n\t"
        "add r1, r0, #0\n\t"
        "lsl r2, r7, #24\n\t"
        "lsr r2, r2, #24\n\t"
        "add r0, r5, #0\n\t"
        "bl StoreIdx2_25638\n\t"
        "1:\n\t"
        "add r0, r6, r5\n\t"
        "add r1, r0, #0\n\t"
        "add r1, #20\n\t"
        "ldrb r0, [r1, #1]\n\t"
        "cmp r0, #255\n\t"
        "beq 2f\n\t"
        "add r1, r0, #0\n\t"
        "mov r0, r8\n\t"
        "lsl r2, r0, #24\n\t"
        "lsr r2, r2, #24\n\t"
        "add r0, r5, #0\n\t"
        "bl StoreIdx2_25638\n\t"
        "2:\n\t"
        "pop {r3}\n\t"
        "mov r8, r3\n\t"
        "pop {r4, r5, r6, r7}\n\t"
        "pop {r0}\n\t"
        "bx r0\n\t"
        ".short 0"
        ::: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "memory");
}
