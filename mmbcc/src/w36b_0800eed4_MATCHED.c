/* Wave 36-B MATCHED: 0x0800eed4, 108 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x0800ef40 (func_list v2) - 0x0800eed4 = 108,
   incl. 24 B literal pool in two clusters (0x02005160, 0x02002f50, 0x02004e40;
   0x02004e40, 0x08173e8c, 0x02005160) plus a 4 B trailing fragment at 0x0800ef3c
   (ldrb r0, [r0]; bx lr) that sits between the pool and the next func_list
   entry -- included verbatim in this file (Sub_0800EF3C, NOT a separate claim)
   so the full-extent comparison passes; the coordinator may split it at landing.
   Variant count: 6 (v2 base = nested tests with cross-jumped shared OR +
   function-pointer table call; v3/v4/v5 allocation variants did not beat it).
   Patch (w36b_0800eed4_patch.py, asserted counts): unfold q+20 pool constant
   to the q base with a [r1, #20] offset form (same effective address), and
   reorder the table load ahead of the index load. No instructions added/removed.
   Indirect call goes through _call_via_r1 (already MATCHED in the build, at
   0x0804dcd0): extern-only via the harness symdef, NO .set in this file.
   Callees: Sub_0801054C + Sub_08010750 via .set (both unmatched in registry).
   Harness: ./verify_patch.sh 0x0800eed4 108 .text.w36b_0800eed4
   w36b_0800eed4_MATCHED.c old w36b_0800eed4_patch.py _call_via_r1=0x0804dcd0
   -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef u8 (*fn_t)(u8 *p);
extern void Sub_0801054C(u8 *p);
__asm__(".set Sub_0801054C, 0x0801054c");
extern void Sub_08010750(u8 *p);
__asm__(".set Sub_08010750, 0x08010750");
__attribute__((section(".text.w36b_0800eed4")))
void Sub_0800EED4(void)
{
    u8 *p = (u8 *)0x02005160;
    fn_t fn;
    u8 ret;
    if (p[68] == 0) {
        if ((*(u16 *)0x02002f50 & 1) != 0) {
            ((u8 *)0x02004e40)[20] |= 1;
        }
    } else {
        ((u8 *)0x02004e40)[20] |= 2;
    }
    fn = ((fn_t *)0x08173e8c)[p[0]];
    ret = fn(p);
    {
        u8 *q = (u8 *)0x02005160;
        q[0] = ret;
        Sub_0801054C(q);
        Sub_08010750(q);
    }
}

/* Trailing fragment at 0x0800ef3c (NOT a separate claim): the 4 bytes after
   this function's pool and before the next func_list entry (0x0800ef40)
   decode as ldrb r0, [r0]; bx lr. Included so the full-extent comparison
   (0x0800eed4..0x0800ef40) passes; the coordinator may split it at landing. */
__attribute__((section(".text.w36b_0800eed4")))
u8 Sub_0800EF3C(u8 *p) { return *p; }
