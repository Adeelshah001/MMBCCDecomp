/* W46-D v2: 0x0801bb94, 32 B leaf. v1 (statement order) did s[12]=4
 * before the table computation and loaded the pool late (11 diffs).
 * ROM interleaves like 0x0801ba94's c2: table computation (pool
 * FIRST), then s[12]=4, then the two derefs. Structure mirrors
 * w46d_0801ba94_v10's c2: pinned+barrier table base (r2 here),
 * integer-plus entry computation (result in the index register r1),
 * s[12] store between address computation and deref. */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w46d_0801bb94")))
void Sub_0801BB94(u8 *s)
{
    u8 *entry;
    register u8 *tbase __asm__("r2");
    s[10] &= 254;
    tbase = (u8 *)0x082243d8;
    __asm__ volatile("" : "+r"(tbase));
    entry = (u8 *)(s[9] * 4 + (int)tbase);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)entry + 16);
}
