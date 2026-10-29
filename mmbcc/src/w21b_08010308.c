/* Wave 21 Worker B @0x08010308 (90 B). MATCHED with main agbcc + FIXALIGN1.
 * Setup twin of 0x0801029C family: if (*(u8*)0x02005160 != 0) return 0;
 * else Ewram5160_Init_10508(5), then write (z, a, b, 0xff, d, c) to the struct:
 * [66]=z, [48]=(u32)a, [52]=(u32)b, [67]=0xff, [65]=d, [56]=(u16)c; return 1.
 * Mid-function literal pool (pool word at +0x48, 4-aligned by construction).
 *
 * Idioms: sibling-shape transfer from w20d_0801029c.c (pinned p->r4 / z->r5,
 * q1=p+66, q3 pinned ->r0 for `adds r0,r4,#0`); FIXALIGN1 replaces ALL
 * `.align 2, 0` (pool already 4-aligned, no padding needed; assembler warning
 * "section does not have enough alignment" is harmless — ldscript places the
 * section at a 4-aligned address).
 * Evidence: docs/match_notes_wave21_B.md.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Ewram5160_Init_10508(u32 v);

__attribute__((section(".text.w21b_08010308")))
u32 Sub_08010308(u32 a, u32 b, u16 c, u8 d)
{
    register u8 *p __asm__("r4") = (u8 *)0x02005160;
    register u8 z __asm__("r5");
    u8 *q1;
    u8 *q2;
    register u8 *q3 __asm__("r0");
    z = p[0];
    if (z != 0) {
        return 0;
    }
    Ewram5160_Init_10508(5);
    q1 = p + 66;
    *q1 = z;
    *(u32 *)(p + 48) = a;
    *(u32 *)(p + 52) = b;
    q2 = p + 67;
    *q2 = 0xff;
    q3 = p + 65;
    *q3 = d;
    *(u16 *)(p + 56) = c;
    return 1;
}
