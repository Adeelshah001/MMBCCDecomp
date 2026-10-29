	@ MMBCCDecomp — Obj_AddEntry @0x0802D7A0 (340 B, Wave 10, .s transcription).
	@ C-IMPOSSIBLE: 10-param global register allocation (work->r7, a1->r6,
	@ a3->ip, a7->sl, a8->r8, a9->r9, m3->r3, p3->r2, sub sp,#24) not
	@ reproducible by agbcc/old_agbcc (tried -O1/-O2/-Os, pinning, late
	@ mask assignment; see docs/match_notes_wave10_H.md). Hand-transcribed.
	.section .text.objaddentry,"ax",%progbits
	.balign 2
	.thumb

	.global Obj_AddEntry
Obj_AddEntry:
	push	{r4, r5, r6, r7, lr}
	mov	r7, sl
	mov	r6, r9
	mov	r5, r8
	push	{r5, r6, r7}
	sub	sp, #24
	add	r7, r0, #0
	ldr	r0, [sp, #56]
	ldr	r4, [sp, #60]
	ldr	r5, [sp, #64]
	ldr	r6, [sp, #68]
	mov	sl, r6
	ldr	r6, [sp, #72]
	mov	r8, r6
	ldr	r6, [sp, #76]
	mov	r9, r6
	lsl	r1, r1, #24
	lsr	r6, r1, #24
	lsl	r2, r2, #24
	lsr	r2, r2, #24
	str	r2, [sp, #0]
	lsl	r3, r3, #24
	lsr	r3, r3, #24
	mov	ip, r3
	lsl	r0, r0, #24
	lsr	r0, r0, #24
	str	r0, [sp, #4]
	lsl	r4, r4, #16
	lsr	r4, r4, #16
	str	r4, [sp, #8]
	lsl	r5, r5, #16
	lsr	r5, r5, #16
	str	r5, [sp, #12]
	mov	r0, sl
	lsl	r0, r0, #16
	lsr	r0, r0, #16
	mov	sl, r0
	mov	r1, r8
	lsl	r1, r1, #24
	lsr	r1, r1, #24
	mov	r8, r1
	mov	r2, r9
	lsl	r2, r2, #24
	lsr	r2, r2, #24
	mov	r9, r2
	mov	r0, #2
	ldrb	r3, [r7, #6]
	and	r0, r3
	cmp	r0, #0
	beq	.L_0802d810
	add	r0, r1, #0
	sub	r0, #106
	lsl	r0, r0, #24
	lsr	r0, r0, #24
	cmp	r0, #3
	bhi	.L_0802d8de
.L_0802d810:
	ldrb	r5, [r7, #5]
	lsl	r1, r5, #4
	add	r1, r7, r1
	mov	r4, #210
	lsl	r4, r4, #1
	add	r1, r1, r4
	mov	r5, #1
	and	r6, r5
	lsl	r2, r6, #1
	mov	r3, #3
	neg	r3, r3
	add	r0, r3, #0
	ldrb	r6, [r1, #0]
	and	r0, r6
	orr	r0, r2
	strb	r0, [r1, #0]
	ldrb	r0, [r7, #5]
	lsl	r1, r0, #4
	add	r1, r7, r1
	add	r1, r1, r4
	ldr	r2, [sp, #0]
	lsl	r4, r2, #2
	mov	r2, #3
	add	r0, r2, #0
	ldrb	r6, [r1, #0]
	and	r0, r6
	orr	r0, r4
	strb	r0, [r1, #0]
	ldrb	r1, [r7, #5]
	lsl	r0, r1, #4
	add	r0, r7, r0
	mov	r4, #212
	lsl	r4, r4, #1
	add	r0, r0, r4
	mov	r6, ip
	and	r6, r5
	lsl	r1, r6, #1
	ldrb	r5, [r0, #0]
	and	r3, r5
	orr	r3, r1
	strb	r3, [r0, #0]
	ldrb	r6, [r7, #5]
	lsl	r0, r6, #4
	add	r0, r7, r0
	add	r0, r0, r4
	ldr	r3, [sp, #4]
	lsl	r1, r3, #2
	ldrb	r5, [r0, #0]
	and	r2, r5
	orr	r2, r1
	strb	r2, [r0, #0]
	ldrb	r6, [r7, #5]
	lsl	r0, r6, #4
	add	r0, r7, r0
	mov	r1, #214
	lsl	r1, r1, #1
	add	r0, r0, r1
	mov	r2, sp
	ldrh	r2, [r2, #8]
	strh	r2, [r0, #0]
	ldrb	r3, [r7, #5]
	lsl	r0, r3, #4
	add	r0, r7, r0
	mov	r5, #215
	lsl	r5, r5, #1
	add	r0, r0, r5
	mov	r6, sp
	ldrh	r6, [r6, #12]
	strh	r6, [r0, #0]
	ldrb	r1, [r7, #5]
	lsl	r0, r1, #4
	add	r0, r7, r0
	mov	r2, #216
	lsl	r2, r2, #1
	add	r0, r0, r2
	mov	r3, sl
	strh	r3, [r0, #0]
	ldrb	r5, [r7, #5]
	lsl	r0, r5, #4
	add	r0, r7, r0
	mov	r6, #217
	lsl	r6, r6, #1
	add	r0, r0, r6
	mov	r1, r8
	strb	r1, [r0, #0]
	ldrb	r2, [r7, #5]
	lsl	r0, r2, #4
	add	r0, r7, r0
	ldr	r3, [pc, #44]
	add	r0, r0, r3
	mov	r5, r9
	strb	r5, [r0, #0]
	ldrb	r6, [r7, #5]
	lsl	r0, r6, #4
	add	r0, r7, r0
	add	r0, r0, r4
	mov	r1, #1
	ldrb	r2, [r0, #0]
	orr	r1, r2
	strb	r1, [r0, #0]
	ldrb	r0, [r7, #5]
	add	r0, #1
	strb	r0, [r7, #5]
.L_0802d8de:
	add	sp, #24
	pop	{r3, r4, r5}
	mov	r8, r3
	mov	r9, r4
	mov	sl, r5
	pop	{r4, r5, r6, r7}
	pop	{r0}
	bx	r0
	.hword	0x0000	@ padding
	@ pool @ 0x0802d8f0
	.word	0x000001b3
