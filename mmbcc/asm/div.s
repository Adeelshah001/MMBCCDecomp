	@ MMBCCDecomp — libgcc-style division block (Wave 10, .s transcription).
	@ The four __divsi3/__modsi3/__udivsi3/__umodsi3 helpers at
	@ 0x0804DD08/0x0804DDA0/0x0804DE70/0x0804DEE8 plus the 7 duplicate
	@ bx-thunks at 0x0804DCEC are C-IMPOSSIBLE (proven in
	@ docs/match_notes_wave9_C.md): agbcc/old_agbcc always emit
	@ `push {r4,lr}` (or {r4,r5,lr}) at function start for control-flow
	@ functions using callee-saved regs, and `pop {r4,pc}` epilogues;
	@ the ROM has a mid-prologue `push {r4}` (4th insn) and
	@ `pop {r4}; mov pc,lr` epilogues. So they are hand-transcribed here.
	@ Each function lives in its own section, placed at its exact ROM
	@ address by ldscript.ld. GAS 2.42 pre-UAL Thumb: no `s` suffixes
	@ (`add` not `adds`, `neg` for rsbs #0, `eor`/`ror`/`orr`/`and`/`lsl`/
	@ `lsr`/`sub`/`neg`/`mov`), `nop` == mov r8,r8 (0x46C0).
	.section .text.dupthunks,"ax",%progbits
	.balign 2
	.thumb

	@ 0x0804DCEC: 7 libgcc-style bx-thunks over the HIGH registers
	@ (28 B). CORRECTION to docs/match_notes_wave9_C.md ("bx r0-r6"):
	@ the ROM bytes are 47 40 / 47 48 / 47 50 / 47 58 / 47 60 /
	@ 47 68 / 47 70 = bx r8, bx r9, bx sl, bx fp, bx ip, bx sp, bx lr,
	@ each followed by nop (mov r8,r8). NOT duplicates of the
	@ _call_via_r0..r7 span — a distinct hi-reg twin set.

	.global DupThunks_0804DCEC
	.global DupThunk_r8
	.global DupThunk_r9
	.global DupThunk_r10
	.global DupThunk_r11
	.global DupThunk_r12
	.global DupThunk_r13
	.global DupThunk_r14

DupThunks_0804DCEC:
DupThunk_r8:
	bx r8
	nop @ mov r8,r8
DupThunk_r9:
	bx r9
	nop @ mov r8,r8
DupThunk_r10:
	bx sl
	nop @ mov r8,r8
DupThunk_r11:
	bx fp
	nop @ mov r8,r8
DupThunk_r12:
	bx ip
	nop @ mov r8,r8
DupThunk_r13:
	bx sp
	nop @ mov r8,r8
DupThunk_r14:
	bx lr
	nop @ mov r8,r8

	@ ------------------------------------------------------------------
	@ 0x0804DD08: SDiv_0804DD08 — signed __divsi3 (136 B: DD08..DD90).
	@ beq@DD0A targets DivZeroStub_4DD90 (0x0804DD90, matched, external).
	@ Sign handling: eor r4,r1 / mov ip,r4 up front, negs on each input,
	@ trailing neg of the quotient if the signs differed.
	.section .text.sdiv,"ax",%progbits
	.balign 2
	.thumb

	.global SDiv_0804DD08
SDiv_0804DD08:
	cmp r1, #0
	beq DivZeroStub_4DD90
	push {r4}
	add r4, r0, #0
	eor r4, r1
	mov ip, r4
	mov r3, #1
	mov r2, #0
	cmp r1, #0
	bpl .L_sdiv_r1ok
	neg r1, r1
.L_sdiv_r1ok:
	cmp r0, #0
	bpl .L_sdiv_r0ok
	neg r0, r0
.L_sdiv_r0ok:
	cmp r0, r1
	bcc .L_sdiv_done
	mov r4, #1
	lsl r4, r4, #28
.L_sdiv_align4:
	cmp r1, r4
	bcs .L_sdiv_align1entry
	cmp r1, r0
	bcs .L_sdiv_align1entry
	lsl r1, r1, #4
	lsl r3, r3, #4
	b .L_sdiv_align4
.L_sdiv_align1entry:
	lsl r4, r4, #3
.L_sdiv_align1:
	cmp r1, r4
	bcs .L_sdiv_step
	cmp r1, r0
	bcs .L_sdiv_step
	lsl r1, r1, #1
	lsl r3, r3, #1
	b .L_sdiv_align1
.L_sdiv_step:
	cmp r0, r1
	bcc .L_sdiv_sub1
	sub r0, r0, r1
	orr r2, r3
.L_sdiv_sub1:
	lsr r4, r1, #1
	cmp r0, r4
	bcc .L_sdiv_sub2
	sub r0, r0, r4
	lsr r4, r3, #1
	orr r2, r4
.L_sdiv_sub2:
	lsr r4, r1, #2
	cmp r0, r4
	bcc .L_sdiv_sub3
	sub r0, r0, r4
	lsr r4, r3, #2
	orr r2, r4
.L_sdiv_sub3:
	lsr r4, r1, #3
	cmp r0, r4
	bcc .L_sdiv_looptest
	sub r0, r0, r4
	lsr r4, r3, #3
	orr r2, r4
.L_sdiv_looptest:
	cmp r0, #0
	beq .L_sdiv_done
	lsr r3, r3, #4
	beq .L_sdiv_done
	lsr r1, r1, #4
	b .L_sdiv_step
.L_sdiv_done:
	add r0, r2, #0
	mov r4, ip
	cmp r4, #0
	bpl .L_sdiv_exit
	neg r0, r0
.L_sdiv_exit:
	pop {r4}
	mov pc, lr

	@ ------------------------------------------------------------------
	@ 0x0804DDA0: SMod_0804DDA0 — signed __modsi3 (196 B: DDA0..DE64).
	@ beq@DDA4 targets DivZeroStub (0x0804DE64, matched, external).
	@ Quotient bits are tracked with the ip/ror trick (ror bit position
	@ into r3 and orr into r2); the final adjust adds back selected
	@ divisor shifts. The caller's r0 is stacked (push {r0}) for the
	@ trailing sign fixup.
	.section .text.smod,"ax",%progbits
	.balign 2
	.thumb

	.global SMod_0804DDA0
SMod_0804DDA0:
	mov r3, #1
	cmp r1, #0
	beq DivZeroStub
	bpl .L_smod_r1ok
	neg r1, r1
.L_smod_r1ok:
	push {r4}
	push {r0}
	cmp r0, #0
	bpl .L_smod_r0ok
	neg r0, r0
.L_smod_r0ok:
	cmp r0, r1
	bcc .L_smod_epilogue
	mov r4, #1
	lsl r4, r4, #28
.L_smod_align4:
	cmp r1, r4
	bcs .L_smod_align1entry
	cmp r1, r0
	bcs .L_smod_align1entry
	lsl r1, r1, #4
	lsl r3, r3, #4
	b .L_smod_align4
.L_smod_align1entry:
	lsl r4, r4, #3
.L_smod_align1:
	cmp r1, r4
	bcs .L_smod_step
	cmp r1, r0
	bcs .L_smod_step
	lsl r1, r1, #1
	lsl r3, r3, #1
	b .L_smod_align1
.L_smod_step:
	mov r2, #0
	cmp r0, r1
	bcc .L_smod_sub1
	sub r0, r0, r1
.L_smod_sub1:
	lsr r4, r1, #1
	cmp r0, r4
	bcc .L_smod_sub2
	sub r0, r0, r4
	mov ip, r3
	mov r4, #1
	ror r3, r4
	orr r2, r3
	mov r3, ip
.L_smod_sub2:
	lsr r4, r1, #2
	cmp r0, r4
	bcc .L_smod_sub3
	sub r0, r0, r4
	mov ip, r3
	mov r4, #2
	ror r3, r4
	orr r2, r3
	mov r3, ip
.L_smod_sub3:
	lsr r4, r1, #3
	cmp r0, r4
	bcc .L_smod_looptest
	sub r0, r0, r4
	mov ip, r3
	mov r4, #3
	ror r3, r4
	orr r2, r3
	mov r3, ip
.L_smod_looptest:
	mov ip, r3
	cmp r0, #0
	beq .L_smod_adjust
	lsr r3, r3, #4
	beq .L_smod_adjust
	lsr r1, r1, #4
	b .L_smod_step
.L_smod_adjust:
	mov r4, #14
	lsl r4, r4, #28
	and r2, r4
	beq .L_smod_epilogue
	mov r3, ip
	mov r4, #3
	ror r3, r4
	tst r2, r3
	beq .L_smod_adj2
	lsr r4, r1, #3
	add r0, r0, r4
.L_smod_adj2:
	mov r3, ip
	mov r4, #2
	ror r3, r4
	tst r2, r3
	beq .L_smod_adj1
	lsr r4, r1, #2
	add r0, r0, r4
.L_smod_adj1:
	mov r3, ip
	mov r4, #1
	ror r3, r4
	tst r2, r3
	beq .L_smod_epilogue
	lsr r4, r1, #1
	add r0, r0, r4
.L_smod_epilogue:
	pop {r4}
	cmp r4, #0
	bpl .L_smod_exit
	neg r0, r0
.L_smod_exit:
	pop {r4}
	mov pc, lr

	@ ------------------------------------------------------------------
	@ 0x0804DE70: UDiv_0804DE70 — unsigned __udivsi3 (110 B: DE70..DEDE).
	@ beq@DE72 targets DivZeroStub_4DEDE (0x0804DEDE, ldscript BYTE block,
	@ referenced here via .set). Plain quotient in r2.
	.section .text.udiv,"ax",%progbits
	.balign 2
	.thumb

	.set DivZeroStub_4DEDE, 0x0804DEDE
	.global UDiv_0804DE70
UDiv_0804DE70:
	cmp r1, #0
	beq DivZeroStub_4DEDE
	mov r3, #1
	mov r2, #0
	push {r4}
	cmp r0, r1
	bcc .L_udiv_done
	mov r4, #1
	lsl r4, r4, #28
.L_udiv_align4:
	cmp r1, r4
	bcs .L_udiv_align1entry
	cmp r1, r0
	bcs .L_udiv_align1entry
	lsl r1, r1, #4
	lsl r3, r3, #4
	b .L_udiv_align4
.L_udiv_align1entry:
	lsl r4, r4, #3
.L_udiv_align1:
	cmp r1, r4
	bcs .L_udiv_step
	cmp r1, r0
	bcs .L_udiv_step
	lsl r1, r1, #1
	lsl r3, r3, #1
	b .L_udiv_align1
.L_udiv_step:
	cmp r0, r1
	bcc .L_udiv_sub1
	sub r0, r0, r1
	orr r2, r3
.L_udiv_sub1:
	lsr r4, r1, #1
	cmp r0, r4
	bcc .L_udiv_sub2
	sub r0, r0, r4
	lsr r4, r3, #1
	orr r2, r4
.L_udiv_sub2:
	lsr r4, r1, #2
	cmp r0, r4
	bcc .L_udiv_sub3
	sub r0, r0, r4
	lsr r4, r3, #2
	orr r2, r4
.L_udiv_sub3:
	lsr r4, r1, #3
	cmp r0, r4
	bcc .L_udiv_looptest
	sub r0, r0, r4
	lsr r4, r3, #3
	orr r2, r4
.L_udiv_looptest:
	cmp r0, #0
	beq .L_udiv_done
	lsr r3, r3, #4
	beq .L_udiv_done
	lsr r1, r1, #4
	b .L_udiv_step
.L_udiv_done:
	add r0, r2, #0
	pop {r4}
	mov pc, lr

	@ ------------------------------------------------------------------
	@ 0x0804DEE8: UMod_0804DEE8 — unsigned __umodsi3 (182 B: DEE8..DF9E).
	@ beq@DEEA targets Wrap_0804DF9E (0x0804DF9E, ldscript BYTE block,
	@ referenced here via .set). Early `mov pc,lr` return when the
	@ divisor exceeds the dividend (r0 stays the remainder). Same
	@ ip/ror quotient-tracking and adjust tail as SMod.
	.section .text.umod,"ax",%progbits
	.balign 2
	.thumb

	.set Wrap_0804DF9E, 0x0804DF9E
	.global UMod_0804DEE8
UMod_0804DEE8:
	cmp r1, #0
	beq Wrap_0804DF9E
	mov r3, #1
	cmp r0, r1
	bcs .L_umod_push
	mov pc, lr
.L_umod_push:
	push {r4}
	mov r4, #1
	lsl r4, r4, #28
.L_umod_align4:
	cmp r1, r4
	bcs .L_umod_align1entry
	cmp r1, r0
	bcs .L_umod_align1entry
	lsl r1, r1, #4
	lsl r3, r3, #4
	b .L_umod_align4
.L_umod_align1entry:
	lsl r4, r4, #3
.L_umod_align1:
	cmp r1, r4
	bcs .L_umod_step
	cmp r1, r0
	bcs .L_umod_step
	lsl r1, r1, #1
	lsl r3, r3, #1
	b .L_umod_align1
.L_umod_step:
	mov r2, #0
	cmp r0, r1
	bcc .L_umod_sub1
	sub r0, r0, r1
.L_umod_sub1:
	lsr r4, r1, #1
	cmp r0, r4
	bcc .L_umod_sub2
	sub r0, r0, r4
	mov ip, r3
	mov r4, #1
	ror r3, r4
	orr r2, r3
	mov r3, ip
.L_umod_sub2:
	lsr r4, r1, #2
	cmp r0, r4
	bcc .L_umod_sub3
	sub r0, r0, r4
	mov ip, r3
	mov r4, #2
	ror r3, r4
	orr r2, r3
	mov r3, ip
.L_umod_sub3:
	lsr r4, r1, #3
	cmp r0, r4
	bcc .L_umod_looptest
	sub r0, r0, r4
	mov ip, r3
	mov r4, #3
	ror r3, r4
	orr r2, r3
	mov r3, ip
.L_umod_looptest:
	mov ip, r3
	cmp r0, #0
	beq .L_umod_adjust
	lsr r3, r3, #4
	beq .L_umod_adjust
	lsr r1, r1, #4
	b .L_umod_step
.L_umod_adjust:
	mov r4, #14
	lsl r4, r4, #28
	and r2, r4
	bne .L_umod_adj3
	pop {r4}
	mov pc, lr
.L_umod_adj3:
	mov r3, ip
	mov r4, #3
	ror r3, r4
	tst r2, r3
	beq .L_umod_adj2
	lsr r4, r1, #3
	add r0, r0, r4
.L_umod_adj2:
	mov r3, ip
	mov r4, #2
	ror r3, r4
	tst r2, r3
	beq .L_umod_adj1
	lsr r4, r1, #2
	add r0, r0, r4
.L_umod_adj1:
	mov r3, ip
	mov r4, #1
	ror r3, r4
	tst r2, r3
	beq .L_umod_exit
	lsr r4, r1, #1
	add r0, r0, r4
.L_umod_exit:
	pop {r4}
	mov pc, lr
