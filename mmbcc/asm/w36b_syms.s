	@ Wave 36-B data symbols (harness symdefs at verification time).
	@ Defined here, NOT in the C files: an in-file .set would let GAS fold
	@ e.g. Table+143 into a single pool word and change the code shape
	@ (0x0800c41c worker note). Separate-file globals resolve at link time.
	.globl Base
	.set Base, 0x030005c0
	.globl B
	.set B, 0x02004830
	.globl Table
	.set Table, 0x02003670
	.globl Table2
	.set Table2, 0x08173eb8
	.globl Struct2
	.set Struct2, 0x0200b810
	.globl Val
	.set Val, 0x0804ba05
	.globl Arg2
	.set Arg2, 0x03000000
	.globl Cnt
	.set Cnt, 7
