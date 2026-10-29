/* Wave 36 Worker B2 — 0x0800a0d4, 124 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: next start 0x0800a150 (func_list v2). Pool: struct 0x02004e40,
 * table 0x08173048, base 0x02004830 (via harness symdef B, extern array symbol).
 * Variant count: 4 (v4 + patch). Callee Sub_0800A150 via .set; indirect call via
 * _call_via_r1 (harness symdef).
 * Key idioms: mask variables (int m = -N) force negs for the ~N masks (gcc
 * otherwise uses u8-truncated mov #246/#253/#252); B as an extern array symbol
 * so the +612 index is computed as 153*4 (mov #153, lsl #2, adds) instead of
 * folding base+612 into one pool word.
 * Patch: first table load first with idx in r2 and res in r1; s[19]/s[31] tests
 * and s[31]/s[20] masks reordered to mask-first; +612 index value in r2;
 * s[20] mask byte in r2. All reorder/rename, same length. */
/* v3: mask variables, base variable for +612, pointer variable for table */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Sub_0800A150(u8 *s);
__asm__(".set Sub_0800A150, 0x0800a150");
__attribute__((section(".text.w36b_0800a0d4")))
void Sub_0800A0D4(void)
{
    u8 *s = (u8 *)0x02004e40;
    u32 *table = (u32 *)0x08173048;
    extern u8 B[];
    u8 *b;
    int m9 = -9;
    int m2 = -2;
    int m3 = -3;
    u32 *ptr = table + s[0];
    u8 res = (u8)((u8 (*)(u8 *))*ptr)(s);
    if (s[19] & 2) res |= 128;
    s[4] = res;
    if ((s[31] & 8) == 0 && s[28] != 0) s[28]--;
    b = B;
    if (b[612] != 0) Sub_0800A150(s);
    s[31] &= m9;
    s[20] &= m2;
    s[20] &= m3;
}
