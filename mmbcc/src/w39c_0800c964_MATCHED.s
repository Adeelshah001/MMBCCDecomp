/* W39-C: 0x0800c964, 172 B. Sanctioned asm transcription (see notes for
 * C-exhaustion justification: v1-v10 tried, best C 76 diffs).
 * Transcribed from ROM disassembly; branch/pool offsets resolved by GAS. */
	.section .text.w39c_0800c964,"ax"
    .align 2
    .code 16
    .syntax unified
    .thumb_func
    .globl Sub_0800C964
Sub_0800C964:
    push {r4, r5, r6, lr}
    sub sp, #8
    adds r6, r0, #0
    adds r3, r1, #0
    lsls r1, r2, #16
    lsrs r1, r1, #16
    ldrb r0, [r6, #20]
    lsls r2, r0, #3
    ldr r0, .Lpool_0
    adds r5, r2, r0
    ldrb r2, [r5, #0]
    lsls r0, r2, #2
    ldr r4, .Lpool_1
    adds r2, r0, r4
    ldr r2, [r2, #0]
    adds r2, r2, r4
    adds r0, r0, r2
    movs r2, #32
    str r2, [sp, #0]
    ldrh r4, [r5, #4]
    lsrs r2, r4, #3
    lsls r2, r2, #24
    lsrs r2, r2, #24
    str r2, [sp, #4]
    movs r2, #1
    bl F_0800DF8C
    adds r0, r6, #0
    adds r0, #52
    movs r4, #0
    strb r4, [r0, #0]
    ldrb r0, [r5, #2]
    adds r1, r6, #0
    adds r1, #53
    strb r0, [r1, #0]
    ldr r1, .Lpool_2
    ldrb r2, [r5, #1]
    lsls r0, r2, #3
    adds r0, r0, r1
    ldr r0, [r0, #0]
    ldrb r0, [r0, #0]
    adds r3, r6, #0
    adds r3, #54
    strb r0, [r3, #0]
    ldrb r0, [r5, #0]
    lsls r2, r0, #2
    ldr r1, .Lpool_3
    adds r0, r2, r1
    ldr r0, [r0, #0]
    adds r0, r0, r1
    adds r2, r2, r0
    movs r1, #0
    ldrsb r1, [r3, r1]
    lsls r0, r1, #2
    adds r0, r0, r1
    lsls r0, r0, #2
    adds r2, r2, r0
    ldr r0, .Lpool_4
    str r2, [r0, #12]
    movs r0, #3
    ldrsb r0, [r5, r0]
    cmp r0, #0
    blt .Lskip_g
    lsls r0, r0, #16
    lsrs r0, r0, #16
    bl G_0800C22C
.Lskip_g:
    ldrh r5, [r5, #4]
    cmp r5, #159
    bls .Lend
    strh r4, [r6, #22]
    strh r4, [r6, #24]
.Lend:
    add sp, #8
    pop {r4, r5, r6}
    pop {r0}
    bx r0
    .align 2
.Lpool_0:
    .word 0x081731e0
.Lpool_1:
    .word 0x08741784
.Lpool_2:
    .word 0x0817344c
.Lpool_3:
    .word 0x087493b0
.Lpool_4:
    .word 0x02004f40
    .set F_0800DF8C, 0x0800df8c
    .set G_0800C22C, 0x0800c22c
