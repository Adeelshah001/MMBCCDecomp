/* W39-C: 0x08037700, 148 B, sanctioned asm transcription.
 * C-EXHAUSTION JUSTIFICATION (see notes): W37-C attempt 2 (160 B, ~126
 * diffs) + W38-C pin experiment (180 B, 119 diffs, worse) + W39-C v1
 * (restructure, 148 B, 73 diffs) + v2 (full pins, 156 B, 102 diffs) +
 * v3 (block pins, 164 B, 144 diffs) + v4 (accumulator, 148 B, 73 diffs)
 * + v5 (reordered assignments, 148 B, 60 diffs) + v6 (c pinned r1,
 * 152 B, 106 diffs) + main-agbcc builds of v4/v5 (identical diffs).
 * The wall is structural: ROM's allocator packs the six loop variables
 * into r1-r6 (c=r1, i=r2, val=r3, q=r4, T1=r5, res=r6) with r7 as the
 * *q temp, while both agbcc pack them into r2-r7 (v5: c=r2, i=r3,
 * val=r4, q=r5, T1=r6, res=r7) with r1 as a temp. Pinning any subset
 * shifts the other variables and/or forces extra moves (v6's c pin
 * moved T1 to r2 plus a copy to r7; v3's full pins moved p to r9 and
 * routed the loop sum through r8). No C form found reproduces ROM's
 * allocation; the function is small (148 B) and fully decoded below,
 * so transcription is the right call.
 * Semantics (decoded from ROM): Scramble/SMod loop with a running
 * byte-sum accumulator c. c = T1[0] + p[0x469f]; if c > val exit;
 * loop: i++; if i > 3 exit; c = (u8)(T1[i] + p[0x469f] + c);
 * if c <= val continue; res = i, exit. Tail: v2 = Scramble();
 * t = T2 + res; b = p[0x469f]; ptr = *t + b*4;
 * d = T3[res] + b; return *(u8 *)(*ptr + SMod(v2, d)).
 * val = (u16)Scramble() & 31. Pools (in extent): T1 0x0822fcb4,
 * 0x0000469f, T2 0x0822fe34, T3 0x0822fe50.
 * Callee .set blocks at END (GAS idiom).
 */
	.section .text.w39c_08037700,"ax"
	.align 2
	.code 16
	.syntax unified
	.thumb_func
	.globl Sub_08037700
	.type Sub_08037700,%function
Sub_08037700:
	push	{r4, r5, r6, r7, lr}
	mov	r7, r8
	push	{r7}
	mov	r8, r0
	bl	Scramble_400A8
	lsls	r0, r0, #16
	lsrs	r3, r0, #16
	movs	r0, #31
	ands	r3, r0
	movs	r6, #0
	movs	r2, #0
	ldr	r5, .L_T1
	ldr	r4, .L_469f
	add	r4, r8
	ldr	r0, [r5, #0]
	ldrb	r1, [r4, #0]
	adds	r0, r1, r0
	ldrb	r1, [r0, #0]
	cmp	r1, r3
	bhi	.L_exit
.L_loop:
	adds	r0, r2, #1
	lsls	r0, r0, #24
	lsrs	r2, r0, #24
	cmp	r2, #3
	bhi	.L_exit
	lsls	r0, r2, #2
	adds	r0, r0, r5
	ldr	r0, [r0, #0]
	ldrb	r7, [r4, #0]
	adds	r0, r7, r0
	ldrb	r0, [r0, #0]
	adds	r0, r0, r1
	lsls	r0, r0, #24
	lsrs	r1, r0, #24
	cmp	r1, r3
	bls	.L_loop
	adds	r6, r2, #0
.L_exit:
	bl	Scramble_400A8
	ldr	r2, .L_T2
	lsls	r3, r6, #2
	adds	r2, r3, r2
	ldr	r1, .L_469f
	add	r1, r8
	ldrb	r5, [r1, #0]
	ldr	r1, [r2, #0]
	lsls	r4, r5, #2
	adds	r4, r4, r1
	lsls	r0, r0, #16
	lsrs	r0, r0, #16
	ldr	r1, .L_T3
	adds	r3, r3, r1
	ldr	r1, [r3, #0]
	adds	r1, r1, r5
	ldrb	r1, [r1, #0]
	bl	SMod_0804DDA0
	ldr	r1, [r4, #0]
	adds	r1, r1, r0
	ldrb	r0, [r1, #0]
	pop	{r3}
	mov	r8, r3
	pop	{r4, r5, r6, r7}
	pop	{r1}
	bx	r1
	.align 2
.L_T1:
	.word	0x0822fcb4
.L_469f:
	.word	0x0000469f
.L_T2:
	.word	0x0822fe34
.L_T3:
	.word	0x0822fe50

