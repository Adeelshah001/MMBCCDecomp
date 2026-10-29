/* Wave 36 Worker B2 — 0x08023bc4, 116 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: next start 0x08023c38 (func_list v2). No literal pool.
 * Variant count: 5 (v5 + patch). Callee Sub_0804DDA0 via .set.
 * Key idioms: base pinned to r9, shift pinned to r8, sl pinned to sl; u8 counter
 * i initialized AFTER the lsl (arg2<<24) but BEFORE the mask computation, so
 * i lands in r7 and out in r6; two stores (after first shift, and after the
 * ORR when shift != 0). Patch: second part pointer in r0 in place (add r0,r9),
 * shift amount in r1, value in r0 moved to r1 for the ORR; deletes the extra
 * mov r2,r9 (net -2 B, exactly the size gap). */
/* v5: shifted first, then i=0; p2 variable for second part */
typedef unsigned char u8;
typedef unsigned int u32;
extern u32 Sub_0804DDA0(u32 idx, int n);
__asm__(".set Sub_0804DDA0, 0x0804dda0");
__attribute__((section(".text.w36b_08023bc4")))
void Sub_08023BC4(u8 *dst, u8 *base, u32 arg2)
{
    register u8 *b9 __asm__("r9") = base;
    u32 shifted = arg2 << 24;
    u8 i = 0;
    register u32 r8 __asm__("r8") = ((224 << 19) & shifted) >> 24;
    register u32 sl __asm__("sl") = shifted >> 27;
    for (; i <= 13; i++) {
        u8 *out = dst + i;
        u32 idx = i + sl;
        u32 off = Sub_0804DDA0(idx, 14);
        int b = *(b9 + off);
        int res = b << r8;
        *out = res;
        if (r8 != 0) {
            u32 off2 = Sub_0804DDA0(idx + 1, 14);
            u8 *p2 = b9 + off2;
            res |= *p2 >> (8 - (int)r8);
            *out = res;
        }
    }
}
