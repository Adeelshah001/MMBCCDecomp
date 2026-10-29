	.text

	.global Init
	.arm
Init:
	mov r0, #0x12
	msr cpsr_fc, r0
	ldr sp, [pc, #0x28]
	mov r0, #0x1f
	msr cpsr_fc, r0
	ldr sp, [pc, #0x18]
	ldr r1, [pc, #0xd4]
	add r0, pc, #0x18
	str r0, [r1]
	ldr r1, [pc, #0xcc]
	mov lr, pc
	bx r1
	b Init
	.word 0x03007DA0 @ pool, referenced from 0xd4
	.word 0x03007FA0 @ pool, referenced from 0xc8
IntrWait:
	mov r3, #0x4000000
	add r3, r3, #0x200
	ldr r2, [r3]
	and r1, r2, r2, lsr #16
	ands r0, r1, #0x2000
.Lcrt0_000110:
	bne .Lcrt0_000110
	mov r2, #0
	ands r0, r1, #1
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #2
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #4
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #8
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x10
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x20
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x40
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x80
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x100
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x200
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x400
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x800
	bne .Lcrt0_0001AC
	add r2, r2, #4
	ands r0, r1, #0x1000
.Lcrt0_0001AC:
	strh r0, [r3, #2]
	bx lr
	.word 0x03007FFC @ pool, referenced from 0xd8
	.word 0x0800033D @ pool, referenced from 0xe4
IrqDispatcher:
	mov r3, #0x4000000
	add r3, r3, #0x200
	ldr r2, [r3]
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	mrs r0, spsr
	push {r0, r1, r3, lr}
	and r1, r2, r2, lsr #16
	ands r0, r1, #0x2000
.Lcrt0_0001E0:
	bne .Lcrt0_0001E0
	mov r2, #0x18
	ands r0, r1, #0x40
	bne .Lcrt0_00027C
	mov r2, #0x1c
	ands r0, r1, #0x80
	bne .Lcrt0_00027C
	mov r2, #0
	ands r0, r1, #1
	bne .Lcrt0_00027C
	mov r2, #4
	ands r0, r1, #2
	bne .Lcrt0_00027C
	mov r2, #8
	ands r0, r1, #4
	bne .Lcrt0_00027C
	mov r2, #0xc
	ands r0, r1, #8
	bne .Lcrt0_00027C
	mov r2, #0x10
	ands r0, r1, #0x10
	bne .Lcrt0_00027C
	mov r2, #0x14
	ands r0, r1, #0x20
	bne .Lcrt0_00027C
	mov r2, #0x24
	ands r0, r1, #0x200
	bne .Lcrt0_00027C
	mov r2, #0x28
	ands r0, r1, #0x400
	bne .Lcrt0_00027C
	mov r2, #0x2c
	ands r0, r1, #0x800
	bne .Lcrt0_00027C
	mov r2, #0x20
	ands r0, r1, #0x100
	bne .Lcrt0_00027C
	mov r2, #0x30
	ands r0, r1, #0x1000
.Lcrt0_00027C:
	strh r0, [r3, #2]
	ldr r1, [pc, #0x4c]
	strh r1, [r3]
	mrs r3, apsr
	bic r3, r3, #0xdf
	orr r3, r3, #0x1f
	msr cpsr_fc, r3
	ldr r1, [pc, #0x38]
	add r1, r1, r2
	ldr r0, [r1]
ArmTrampoline:
	stmdb sp!, {lr}
	add lr, pc, #0
	bx r0
	ldm sp!, {lr}
	mrs r3, apsr
	bic r3, r3, #0xdf
	orr r3, r3, #0x92
	msr cpsr_fc, r3
	pop {r0, r1, r3, lr}
	strh r1, [r3]
	msr spsr_fc, r0
	bx lr
	.word 0x000029CF @ padding
	.word 0x03000400 @ padding
	.thumb
crt0_thumb_helpers:
	push {r4, r5, r6, r7, lr}
	mov r4, r8
	mov r5, sb
	mov r6, sl
	mov r7, fp
	push {r4, r5, r6, r7}
	mov r4, sp
	str r4, [r3]
	mov lr, r1
	mov sp, r2
	pop {r4, r5, r6, r7}
	mov fp, r7
	mov sl, r6
	mov sb, r5
	mov r8, r4
	pop {r4, r5, r6, r7}
	bx lr
	.short 0x0000 @ movs r0,r0 NOP idiom (GAS quirk)
	push {r4, r5, r6, r7}
	mov r4, r8
	mov r5, sb
	mov r6, sl
	mov r7, fp
	push {r4, r5, r6, r7}
	mov r3, lr
	str r3, [r0]
	mov r3, sp
	str r3, [r1]
	mov sp, r2
	pop {r4, r5, r6, r7}
	mov fp, r7
	mov sl, r6
	mov sb, r5
	mov r8, r4
	pop {r4, r5, r6, r7}
	pop {r3}
	mov lr, r3
	bx lr
	mov sp, r0
	pop {r4, r5, r6, r7}
	mov fp, r7
	mov sl, r6
	mov sb, r5
	mov r8, r4
	pop {r4, r5, r6, r7}
	pop {r3}
	mov lr, r3
	bx lr
