/* Wave 36 Worker B2 — 0x080114e8, TRUE extent 72 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: code + 2-word pool + trailing pad to 0x08011530. The task-list 120 B is
 * the func_list gap to 0x08011560; the bytes 0x08011530-0x0801155f are a SEPARATE
 * function (at 0x08011530) NOT part of this claim — flag to coordinator as a
 * func_list gap; do NOT extend this file to 120 B.
 * Variant count: 1 (v1 + patch). Callee Sub_08010B30 (void) via .set;
 * indirect calls via _call_via_r1 (harness symdef _call_via_r1=0x0804dcd0).
 * Pool: table 0x08173ec8, struct 0x02005230 (shared word, loaded twice).
 * Key idioms: do-while loop retrying while the (s16) call result < 0; struct+34
 * flag cleared (else call Sub_08010B30); return is (s16)res (sign-extended).
 * Patch: loop-head idx in r1 (not r0); second part reloads struct from the
 * shared pool word and adds 34 (instead of a folded struct+34 pool word);
 * the folded pool word is deleted (net code +4 B, pool -4 B, total unchanged). */
/* v1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
extern void Sub_08010B30(void);
__asm__(".set Sub_08010B30, 0x08010b30");
__attribute__((section(".text.w36b_080114e8")))
s16 Sub_080114E8(void)
{
    u32 *table = (u32 *)0x08173ec8;
    u8 *s = (u8 *)0x02005230;
    u16 res;
    do {
        u8 idx = s[4];
        u32 fn = table[idx];
        res = ((u16 (*)(u8 *))fn)(s);
    } while ((s16)res < 0);
    if (((u8 *)0x02005230)[34] != 0) {
        ((u8 *)0x02005230)[34] = 0;
    } else {
        Sub_08010B30();
    }
    return (s16)res;
}
__asm__(".byte 0, 0");
