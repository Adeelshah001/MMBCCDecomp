/* Wave 36-E MATCHED: 0x08027d48 leaf (4 B, main agbcc, 0 diffs).
 * Trivial getter: return p[2]. Verified 0 diffs over the 4 B extent
 * 0x08027d48-0x08027d4c (ldrb r0, [r0, #2]; bx lr). See
 * w36e_08027d48_evidence.md for the predecessor/successor checks.
 * No callees, no pools, no padding. */
typedef unsigned char u8;
__attribute__((section(".text.w36e_08027d48")))
u8 Sub_08027D48(u8 *p)
{
    return p[2];
}
