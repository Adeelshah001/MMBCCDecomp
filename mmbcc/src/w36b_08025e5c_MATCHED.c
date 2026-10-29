/* Wave 36-B MATCHED: 0x08025e5c, 108 B, old_agbcc -O2 -mthumb-interwork + .s patch.
   Extent basis: next function start 0x08025ec8 (func_list v2) - 0x08025e5c = 108,
   no literal pool; includes a trailing 00 00 pad (in this file, after bx r0)
   to the next 4-byte boundary, as in ROM.
   Variant count: 4 (v4 = buf[0], i=0, then dst, then loop; v2 found the dst
   pointer form and the r8 save, v3 added the pad).
   Patch (w36b_08025e5c_patch.py, asserted counts): loop index only -- the
   s+i + [r0, #2] offset form replaced by the ROM s+2+i two-adds form (+2 B,
   exactly filling the code-size gap; the pad supplies the other 2 B).
   Callees: Sub_080258C0 (x3) + Sub_08023A7C via .set (both unmatched in registry).
   Harness: ./verify_patch.sh 0x08025e5c 108 .text.w36b_08025e5c
   w36b_08025e5c_MATCHED.c old w36b_08025e5c_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
extern u8 Sub_080258C0(u8 *s, u8 b);
__asm__(".set Sub_080258C0, 0x080258c0");
extern void Sub_08023A7C(u32 a1, u8 *buf, u32 a2);
__asm__(".set Sub_08023A7C, 0x08023a7c");
__attribute__((section(".text.w36b_08025e5c")))
void Sub_08025E5C(u8 *s, u32 a1, u32 a2)
{
    u8 buf[16];
    s8 i;
    u8 *dst;
    buf[0] = s[0];
    i = 0;
    dst = buf + 1;
    for (; i <= 9; i++) {
        dst[i] = Sub_080258C0(s, *(s + 2 + i));
    }
    buf[11] = Sub_080258C0(s, s[12]);
    buf[12] = Sub_080258C0(s, s[13]);
    buf[13] = 1;
    Sub_08023A7C(a1, buf, a2);
}

/* Trailing 00 00 pad to the next 4-byte boundary, as in ROM (after bx r0). */
__asm__(".byte 0, 0");
