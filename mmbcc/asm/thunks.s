	@ MMBCCDecomp — libgcc-style Thumb "call via register" thunks (Wave 0).
	@ agbcc compiles an indirect Thumb call as `bl _call_via_rN`; the
	@ original link resolved these to the thunk span at 0x0804DCCC
	@ (ROM bytes: `bx rN; nop` pairs for r0-r7). Sram_WaitcntInit and
	@ Sram_VerifyWorker call their stack-copied routines via r3, i.e.
	@ through _call_via_r3 @ 0x0804DCD8. All 8 thunks are defined here
	@ so the span is byte-identical; the per-thunk symbols stay
	@ available for the coordinator to assign.
	.section .text.thunks,"ax",%progbits
	.balign 2
	.thumb

	.global _call_via_r0
	.global _call_via_r1
	.global _call_via_r2
	.global _call_via_r3
	.global _call_via_r4
	.global _call_via_r5
	.global _call_via_r6
	.global _call_via_r7

_call_via_r0:
	bx r0
	nop @ mov r8,r8
_call_via_r1:
	bx r1
	nop @ mov r8,r8
_call_via_r2:
	bx r2
	nop @ mov r8,r8
_call_via_r3:
	bx r3
	nop @ mov r8,r8
_call_via_r4:
	bx r4
	nop @ mov r8,r8
_call_via_r5:
	bx r5
	nop @ mov r8,r8
_call_via_r6:
	bx r6
	nop @ mov r8,r8
_call_via_r7:
	bx r7
	nop @ mov r8,r8
