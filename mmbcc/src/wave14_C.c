/* Wave 14 worker C: bulk leaves-up matches (main agbcc).
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

__asm__(".set sub_08000f28, 0x08000f28");
__asm__(".set sub_08001c5c, 0x08001c5c");
__asm__(".set sub_08001c88, 0x08001c88");
__asm__(".set sub_080045ac, 0x080045ac");
__asm__(".set sub_08005274, 0x08005274");
__asm__(".set sub_0800555c, 0x0800555c");
__asm__(".set sub_0800571c, 0x0800571c");
__asm__(".set sub_08007840, 0x08007840");
__asm__(".set sub_08009140, 0x08009140");
__asm__(".set sub_08009238, 0x08009238");
__asm__(".set sub_080092c8, 0x080092c8");
__asm__(".set sub_0800a094, 0x0800a094");
__asm__(".set sub_0800cc94, 0x0800cc94");
__asm__(".set sub_0800cd00, 0x0800cd00");
__asm__(".set sub_0800d480, 0x0800d480");
__asm__(".set sub_0800d680, 0x0800d680");
__asm__(".set sub_0801029c, 0x0801029c");
__asm__(".set sub_08010ba0, 0x08010ba0");
__asm__(".set sub_080111b4, 0x080111b4");
__asm__(".set sub_08011f68, 0x08011f68");
__asm__(".set sub_0802366c, 0x0802366c");
__asm__(".set sub_08024818, 0x08024818");
__asm__(".set sub_08025230, 0x08025230");
__asm__(".set sub_080252d0, 0x080252d0");
__asm__(".set sub_080252f8, 0x080252f8");
__asm__(".set sub_080260a0, 0x080260a0");
__asm__(".set sub_0804044c, 0x0804044c");
__asm__(".set sub_080405d8, 0x080405d8");
__asm__(".set sub_08040698, 0x08040698");
__asm__(".set sub_080406e4, 0x080406e4");
__asm__(".set sub_0804152c, 0x0804152c");
__asm__(".set sub_0804b980, 0x0804b980");
__asm__(".set sub_0804bfd4, 0x0804bfd4");
__asm__(".set sub_0804c610, 0x0804c610");
__asm__(".set sub_0804c7e8, 0x0804c7e8");
__asm__(".set sub_0804db24, 0x0804db24");

/* Fwd_08000f1c @ 0x08000f1c */
void sub_08000f28(void);
__attribute__((section(".text.w14c_08000f1c")))
void Fwd_08000f1c(void)
{
    sub_08000f28();
}

/* Fwd_08002f40 @ 0x08002f40 */
void Fwd_0804c6a8(void);
__attribute__((section(".text.w14c_08002f40")))
void Fwd_08002f40(void)
{
    Fwd_0804c6a8();
}

/* Fwd_08002f4c @ 0x08002f4c */
void sub_0804bfd4(void);
__attribute__((section(".text.w14c_08002f4c")))
void Fwd_08002f4c(void)
{
    sub_0804bfd4();
}

/* Fwd_08005610 @ 0x08005610 */
void sub_0800cc94(void);
__attribute__((section(".text.w14c_08005610")))
void Fwd_08005610(void)
{
    sub_0800cc94();
}

/* Fwd_0800d55c @ 0x0800d55c */
void sub_0800d680(void);
__attribute__((section(".text.w14c_0800d55c")))
void Fwd_0800d55c(void)
{
    sub_0800d680();
}

/* Fwd_08010acc @ 0x08010acc */
void sub_0802366c(void);
__attribute__((section(".text.w14c_08010acc")))
void Fwd_08010acc(void)
{
    sub_0802366c();
}

/* Fwd_08011bd4 @ 0x08011bd4 */
void sub_08010ba0(void);
__attribute__((section(".text.w14c_08011bd4")))
void Fwd_08011bd4(void)
{
    sub_08010ba0();
}

/* Fwd_0804c6a8 @ 0x0804c6a8 */
void sub_0804b980(void);
__attribute__((section(".text.w14c_0804c6a8")))
void Fwd_0804c6a8(void)
{
    sub_0804b980();
}

/* Fwd_08001c4c @ 0x08001c4c */
void sub_08001c5c(void); void sub_08001c88(void);
__attribute__((section(".text.w14c_08001c4c")))
void Fwd_08001c4c(void) { sub_08001c5c(); sub_08001c88(); }

/* Fwd_080050e0 @ 0x080050e0 */
void sub_0800cd00(void); void sub_0800d480(void);
__attribute__((section(".text.w14c_080050e0")))
void Fwd_080050e0(void) { sub_0800cd00(); sub_0800d480(); }

/* StoreRet_0802616c @ 0x0802616c */
void sub_080260a0(u32 v);
__attribute__((section(".text.w14c_0802616c")))
void StoreRet_0802616c(u32 *p, u32 v) { *p = v; sub_080260a0(v); }

/* Fwd_0804c84c @ 0x0804c84c */
void sub_0804c610(u32 a, u16 b);
__attribute__((section(".text.w14c_0804c84c")))
void Fwd_0804c84c(u32 a, u16 b) { sub_0804c610(a, b); }

/* Fwd_08004ee0 @ 0x08004ee0 */
void sub_0800555c(void); void Fwd4_08005704(void); void sub_0800a094(void);
__attribute__((section(".text.w14c_08004ee0")))
void Fwd_08004ee0(void) { sub_0800555c(); Fwd4_08005704(); sub_0800a094(); }

/* Fwd_0801025c @ 0x0801025c */
u32 sub_0801029c(u32 a, u32 b, u32 c, s8 d);
__attribute__((section(".text.w14c_0801025c")))
u32 Fwd_0801025c(u32 a, s8 b) { return sub_0801029c(a, 0, 0, b); }

/* Clr2_08002f24 @ 0x08002f24 */
void sub_0804c7e8(void);
__attribute__((section(".text.w14c_08002f24")))
void Clr2_08002f24(void)
{
    register u8 *p __asm__("r0");
    sub_0804c7e8();
    __asm__ volatile("" : "=r" (p) : "0" (0x02000818));
    *p = 0;
    __asm__ volatile("" : "=r" (p) : "0" (0x02000819));
    *p = 0;
}

/* Guard_0800c4f8 @ 0x0800c4f8 */
void sub_08005274(u32 a, u32 b, u32 c);
__attribute__((section(".text.w14c_0800c4f8")))
void Guard_0800c4f8(u32 x, u32 a) { if (a != 0) sub_08005274(a, 0, 2); }

/* Poke80_08016f74 @ 0x08016f74 */
void sub_08011f68(u8 *p, u32 v);
__attribute__((section(".text.w14c_08016f74")))
void Poke80_08016f74(u8 *p) { u8 *q = p + 0x7c; q[4] = 1; sub_08011f68(p, 5); }

/* IdxByte_08025378 @ 0x08025378 */
u8 sub_080252f8(u8 *p);
__attribute__((section(".text.w14c_08025378")))
u8 IdxByte_08025378(u8 *p, u8 i) { return sub_080252f8(p + i); }

/* Call3_08025464 @ 0x08025464 */
void sub_08025230(u8 *p, u32 v, u32 w);
__attribute__((section(".text.w14c_08025464")))
void Call3_08025464(u8 *p) { sub_08025230(p + 12, *(u32 *)(p + 8), 0xF9); }

/* DerefIdx_08025564 @ 0x08025564 */
u8 IdxByte_08025378(u8 *p, u8 i);
__attribute__((section(".text.w14c_08025564")))
u8 DerefIdx_08025564(u8 **pp, u8 i) { return IdxByte_08025378(*pp, i); }

/* Fwd4_08005704 @ 0x08005704 */
void sub_0800571c(void); void sub_08009140(void); void sub_08009238(void); void sub_080092c8(void);
__attribute__((section(".text.w14c_08005704")))
void Fwd4_08005704(void) { sub_0800571c(); sub_08009140(); sub_08009238(); sub_080092c8(); }

/* InitPtr_08004548 @ 0x08004548 */
void DmaCopy_0800456c(void);
__attribute__((section(".text.w14c_08004548")))
void InitPtr_08004548(u32 a)
{
    register u32 *p __asm__("r1");
    register u32 off __asm__("r0");
    __asm__ volatile("" : "=r" (p) : "0" (0x02003250));
    *p = a;
    __asm__ volatile("" : "=r" (off) : "0" (0x00000414));
    p = (u32 *)((u32)p + off);
    __asm__ volatile("" : "=r" (off) : "0" (0x0816E314));
    *p = off;
    DmaCopy_0800456c();
}

/* Wrap_07818 @ 0x08007818 */
void sub_08007840(u8 *p, s8 a, s8 b, s8 c);
__attribute__((section(".text.w14c_08007818")))
void Wrap_07818(s8 a, s8 b, s8 c)
{
    sub_08007840((u8 *)0x0200483c, a, b, c);
}

/* F5_080429bc @ 0x080429bc */
void sub_08040698(void); void sub_080406e4(void); void sub_0804044c(u32 a);
void sub_080405d8(u32 a); void sub_0804152c(u32 a);
__attribute__((section(".text.w14c_080429bc")))
void F5_080429bc(u32 a)
{
    u32 t = a;
    sub_08040698();
    sub_080406e4();
    sub_0804044c(t);
    sub_080405d8(t);
    sub_0804152c(t);
}

/* Count_08042a38 @ 0x08042a38 */
u8 sub_08024818(u8 i);
__attribute__((section(".text.w14c_08042a38")))
u8 Count_08042a38(void)
{
    u8 c = 0;
    u8 i = 0;
    do {
        if (sub_08024818(i))
            c++;
        i++;
    } while (i <= 0x1d);
    return c;
}

/* DmaCopy_0800456c @ 0x0800456c */
void sub_0804db24(void *dst, void *src, u32 n);
void sub_080045ac(void);
__attribute__((section(".text.w14c_0800456c")))
void DmaCopy_0800456c(void)
{
    u8 *dst;
    register u16 *base __asm__("r2");
    u32 t;
    __asm__ volatile("" : "=r" (dst) : "0" (0x08055B3C));
    __asm__ volatile("" : "=r" (base) : "0" (0x020031E4));
    t = 12;
    t &= *base;
    t <<= 12;
    t += 0x06007800;
    sub_0804db24(dst, (void *)t, 0x80 << 2);
    sub_0804db24((void *)0x0804E31C, (void *)0x03002420, 8);
    sub_080045ac();
}

/* FlagInit_08011070 @ 0x08011070 */
void sub_080111b4(u32 v);
__attribute__((section(".text.w14c_08011070")))
u32 FlagInit_08011070(u8 a, u8 b)
{
    u8 *p;
    u32 r;
    __asm__ volatile("" : "=r" (p) : "0" (0x020051B0));
    if (p[4] == 1) {
        sub_080111b4(3);
        p[0xd] = a;
        p[0xe] = b;
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

/* F_0802663c @ 0x0802663c */
u8 sub_080252d0(u8 *p);
__attribute__((section(".text.w14c_0802663c")))
u8 F_0802663c(u8 *p, u16 v)
{
    u8 w;
    u32 t;
    register u8 *q __asm__("r2");
    if (v >= *(u16 *)(p + 0x16))
        return 1;
    w = sub_080252d0(p + 0x10);
    q = *(u8 **)(p + 4);
    t = w * 7;
    t *= 4;
    t += (u32)q;
    return *(u8 *)(t + 0x18);
}
