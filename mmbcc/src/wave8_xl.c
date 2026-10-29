/* Wave 8 batch XL: ARM sound-driver mixer fragment.
 * Evidence: docs/match_notes_wave8_XL.md, docs/wave8_XL_results.tsv.
 */
/* Audio mixer ARM fragment (TENTATIVE name).
 * ROM 0x0804BCDC (168 B): ARM code entered via ARM `beq` from 0x0804BBB8
 * (sound-driver region). Software sample-mix inner loop: ldrsb sample
 * fetch, mul volume scaling, bic masking, str writeback; the `ble`
 * exits to 0x0804BC74 (earlier ARM code); function ends with
 * `add r0,pc,#1; bx r0` back to Thumb at 0x0804BD84.
 * Matched via naked+asm (Thumb compiler cannot emit ARM from C);
 * precedent: ArmTrampoline (src/wave3_b.c). */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

__attribute__((naked, section(".text.w8xl_0804bcdc")))
void Audio_MixFragment(void)
{
    __asm__ volatile(
        ".arm\n\t"
        "stmdb sp!, {r4, r12}\n\t"
        "ldr r14, [r4, #28]\n\t"
        "ldr r1, [r4, #32]\n\t"
        "mul r4, r12, r1\n\t"
        "ldrsb r0, [r3]\n\t"
        "ldrsb r1, [r3, #1]!\n\t"
        "sub r1, r1, r0\n\t"
        ".Lmix_c:\n\t"
        "ldr r6, [r5]\n\t"
        "ldr r7, [r5, #1584]\n\t"
        ".Lmix_b:\n\t"
        "mul r9, r14, r1\n\t"
        "add r9, r0, r9, asr #23\n\t"
        "mul r12, r10, r9\n\t"
        "bic r12, r12, #0xff0000\n\t"
        "add r6, r12, r6, ror #8\n\t"
        "mul r12, r11, r9\n\t"
        "bic r12, r12, #0xff0000\n\t"
        "add r7, r12, r7, ror #8\n\t"
        "add r14, r14, r4\n\t"
        "movs r9, r14, lsr #23\n\t"
        "beq .Lmix_d\n\t"
        "bic r14, r14, #0x3f800000\n\t"
        "subs r2, r2, r9\n\t"
        "ble .Lmix_ext\n\t"
        "subs r9, r9, #1\n\t"
        "addeq r0, r0, r1\n\t"
        ".inst 0x11b300d9\n\t" /* ldrsbne r0,[r3,r9]! (GAS rejects this form) */
        "ldrsb r1, [r3, #1]!\n\t"
        "sub r1, r1, r0\n\t"
        ".Lmix_d:\n\t"
        "adds r5, r5, #0x40000000\n\t"
        "bcc .Lmix_b\n\t"
        "str r7, [r5, #1584]\n\t"
        "str r6, [r5], #4\n\t"
        "subs r8, r8, #4\n\t"
        "bgt .Lmix_c\n\t"
        "sub r3, r3, #1\n\t"
        "ldmia sp!, {r4, r12}\n\t"
        "str r14, [r4, #28]\n\t"
        "str r2, [r4, #24]\n\t"
        "str r3, [r4, #40]\n\t"
        "ldr r8, [sp]\n\t"
        "add r0, pc, #1\n\t"
        "bx r0"
    );
}

__asm__(
    ".set .Lmix_ext, 0x0804bc74"
);
