/* Wave 36 Worker B2 — 0x0801bfb4, 124 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: next start 0x0801c030 (func_list v2). Pool: 2090, 0x081705b0,
 * 0x020031e4, 0xffffec00 (-5120 as u32).
 * Variant count: 1 (v1 + patch). Callees Sub_0800D770, Sub_0800D9EC, Sub_0800DD08,
 * Sub_0800DD2C, Sub_0804A378 via .set.
 * Key idioms: idx = (u16 >> 4) * 2 (lsr #4 then lsl #1); x = tab[idx] & 3 with a
 * dead clamp (if x > 3, x = 3) that gcc keeps; s[69] = (s[69] & ~13) | (x << 2);
 * stack buffer (8 B) passed to Sub_0800DD08.
 * Patch: clamp copies x to r0 before comparing (net +2 B); s[69] shift-first
 * with mask via negs -13 (not mov #242; net +2 B). Total +4 B, exactly the gap. */
/* v1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800D770(u8 *s, u32 a, u32 b);
extern void Sub_0800D9EC(u8 *s, u32 x);
extern void Sub_0800DD08(u8 *buf, u8 *s);
extern void Sub_0800DD2C(u8 *s, u32 a, u32 b);
extern void Sub_0804A378(u32 x);
__asm__(".set Sub_0800D770, 0x0800d770");
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
__asm__(".set Sub_0800DD08, 0x0800dd08");
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
__asm__(".set Sub_0804A378, 0x0804a378");
__attribute__((section(".text.w36b_0801bfb4")))
void Sub_0801BFB4(u8 *s)
{
    u8 buf[8];
    u16 v;
    int idx;
    u8 *tab;
    int x;
    Sub_0800D770(s, 2090, 0);
    Sub_0800D9EC(s, 0);
    v = *(u16 *)0x081705b0;
    idx = (v >> 4) * 2;
    tab = (u8 *)0x020031e4;
    x = tab[idx] & 3;
    if (x > 3) x = 3;
    s[69] = (s[69] & ~13) | (x << 2);
    s[34] = 13;
    Sub_0800DD08(buf, s);
    Sub_0800DD2C(s, 0xffffec00, 0);
    Sub_0804A378(159);
}
