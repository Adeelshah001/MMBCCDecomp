/* Wave 14 worker C: bulk leaves-up matches (old_agbcc).
 * Coordinator-landed and re-verified byte-identical in built mmbcc.gba.
 * Evidence: docs/match_notes_wave14_C.md, docs/wave14_C_results.tsv.
 *
 * NOTE: .set aliases below are for callees not yet matched.
 * When those are matched, replace the .set with the real symbol.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

__asm__(".set sub_08020ed4, 0x08020ed4");
__asm__(".set sub_08023e30, 0x08023e30");
__asm__(".set sub_080251b8, 0x080251b8");
__asm__(".set sub_08025290, 0x08025290");
__asm__(".set sub_080252e8, 0x080252e8");
__asm__(".set sub_08025730, 0x08025730");
__asm__(".set sub_08025e5c, 0x08025e5c");
__asm__(".set sub_080266f0, 0x080266f0");

/* F_08025790 @ 0x08025790 */
u8 sub_08025730(u8 *p, u8 v); u32 sub_080266f0(u32 v);
__attribute__((section(".text.w14c_08025790")))
u16 F_08025790(u8 *p)
{
    u8 v = sub_08025730(p, 0);
    u32 w = v;
    if (v == 0)
        w = p[1];
    w = sub_080266f0(w);
    return (u16)(*(u16 *)(p + 14) + w);
}

/* DecByte_080254b4 @ 0x080254b4 */
void sub_08025290(u8 *p, u8 i);
__attribute__((section(".text.w14c_080254b4")))
void DecByte_080254b4(u8 *p, u8 i)
{
    u8 *q = *(u8 **)(p + 8) + i;
    u8 *r = (u8 *)(*q + *(u32 *)(p + 4));
    (*r)--;
    if (*r == 0)
        sub_08025290(p + 12, i);
}

/* F_08024f88 @ 0x08024f88 */
u32 sub_08023e30(u8 *p); void sub_08025e5c(u8 *p, u32 v, u32 w);
__attribute__((section(".text.w14c_08024f88")))
void F_08024f88(u32 a)
{
    u32 base;
    u8 *p;
    u8 v;
    u32 t;
    u32 w;
    __asm__ volatile("" : "=r" (base) : "0" (0x020070A4));
    p = *(u8 **)base;
    v = p[0x1B0];
    t = v * 144;
    p += t;
    w = sub_08023e30((u8 *)(base - 0x14));
    sub_08025e5c(p, w, a);
}

/* F_080251d8 @ 0x080251d8 */
u8 sub_08025730(u8 *p, u8 v); u8 sub_080251b8(u8 *p);
__attribute__((section(".text.w14c_080251d8")))
u8 F_080251d8(u8 *p)
{
    u8 v = p[0xD8 << 1];
    u8 w = sub_08025730(p + v * 144, 0);
    if (w == 0)
        w = sub_080251b8(p);
    return w;
}

/* F_0802533c @ 0x0802533c */
void sub_080252e8(u8 *p);
__attribute__((section(".text.w14c_0802533c")))
void F_0802533c(u8 *p, u8 idx)
{
    u8 *q;
    if (idx > 0xf8) return;
    if (idx > 0xc7) {
        q = p + idx;
        if ((*q & 0x7f) > 0x62) return;
        sub_080252e8(q);
    } else {
        q = p + idx;
        if ((*q & 0x7f) > 0x62) return;
        sub_080252e8(q);
    }
}

/* F_08022fe4 @ 0x08022fe4 */
u8 *sub_08020ed4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w14c_08022fe4")))
u8 *F_08022fe4(u8 *p)
{
    u8 *q;
    if (p[7] & 1)
        return 0;
    q = sub_08020ed4(0, 0, 0, 6);
    if (q != 0) {
        q[0x10] = 2;
        q[0x11] = p[0];
        *(u8 **)(q + 0x28) = p;
    }
    p[7] |= 1;
    return q;
}
