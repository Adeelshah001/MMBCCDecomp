/* Wave 36 Worker B2 — 0x0803ff0c, 116 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: next start 0x0803ff80 (func_list v2). No literal pool.
 * Variant count: 5 (v5 + patch). Callees Sub_0803FC8C, Sub_0803F998, Sub_0803FA1C via .set.
 * Key idioms: a in r4, a2 pinned to r8, b pinned to r5, b2 as a normal variable
 * with an empty-asm barrier (so gcc keeps it distinct from b, landing in r7),
 * c pinned to r9, res pinned to r6. The r7 pin alone miscompiles the third
 * branch (gcc compares sp to 5); the barrier form is required.
 * Patch: prologue reorder (a2 copy first); return as a move, not a u8
 * truncation (net -2 B, exactly the size gap). */
/* v5: b2 normal with barrier, others pinned */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 Sub_0803FC8C(u16 a);
extern u8 Sub_0803F998(u16 a);
extern u8 Sub_0803FA1C(u16 a);
__asm__(".set Sub_0803FC8C, 0x0803fc8c");
__asm__(".set Sub_0803F998, 0x0803f998");
__asm__(".set Sub_0803FA1C, 0x0803fa1c");
__attribute__((section(".text.w36b_0803ff0c")))
u8 Sub_0803FF0C(u16 a0, u8 b0, u8 c0)
{
    u16 a = a0;
    register u16 a2 __asm__("r8") = a;
    register u8 b __asm__("r5") = b0;
    u8 b2 = b;
    register u8 c __asm__("r9") = c0;
    register u8 res __asm__("r6") = 0;
    __asm__ volatile("" : "=r"(b2) : "0"(b2));
    if ((u8)Sub_0803FC8C(a) != 0) {
        res = 1;
        if (b == 5) res = 2;
    } else if (a == 12288) {
        res = 1;
        if (b == 3) res = 2;
    } else if ((u8)Sub_0803F998(a) != 0) {
        res = 1;
        if (b2 != 5) {
            res = 2;
        } else if ((u8)Sub_0803FA1C(a2) == 0 && c == 1) {
            res = 2;
        }
    }
    return res;
}
