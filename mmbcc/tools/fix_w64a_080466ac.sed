s/^	ldrb	r7, \[r0\]$/	ldrb	r1, [r0]/
s/^	add	r0, r7, #7$/	add	r0, r1, #7/
s/^	cmp	r7, r0$/	cmp	r1, r0/
/^	ldr	r5, \.L11+4$/d
s/^	add	r7, r7, #1$/	add	r1, r1, #1/
s/^	lsl	r0, r7, #24$/	lsl	r0, r1, #24/
0,/^	lsr	r4, r0, #24$/s//&\n	mov	r8, r1/
/^\.L6:$/s//&\n	ldr	r5, .L11+4/
s/^	mov	r3, sl$/	mov	r0, sl/
s/^	lsl	r6, r3, #1$/	lsl	r6, r0, #1/
/^	mov	r8, r0$/d
s/^	add	r0, r7, #0$/	mov	r0, r8/
0,/^	bl	CondRectFill_070F0$/s//&\n	mov	r7, #2/
/^\.L7:/,/^\.L9:/s/^\(	bl	CondRectFill_070F0\)$/\1\n	mov	r7, #2/
/^	mov	r3, r8$/d
s/^	str	r3, \[sp\]$/	str	r7, [sp]/
s/^	lsl	r1, r7, #24$/	mov	r1, r8\n	lsl	r0, r1, #24/
s/^	lsr	r1, r1, #24$/	lsr	r1, r0, #24/
0,/^	strh	r0, \[r1\]$/s//	strh	r0, [r1, #40]/
/^	add	r1, r1, #2$/d
s/^	strh	r0, \[r1\]$/	strh	r0, [r1, #42]/
s/^	\.word	33574152$/	.word	33574112/
