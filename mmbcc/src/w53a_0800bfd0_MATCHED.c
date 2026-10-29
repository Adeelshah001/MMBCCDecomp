/* W53-A e_both7 — derived from d_combo (7 diffs). setup via at r7 + gtmp r7 (both-into-r7 hope). */
/* W53-A d_combo — derived from c_src_i4first (12 diffs). addrtmp + poolv + t2 combined. */
/* W53-A c_src_i4first — derived from v_base_r0pin_src_r3pin (14 diffs). src operands i4-first (commutative adds order test). */
/* W53-A v_base_r0pin_src_r3pin — derived from w53a_0800bfd0_i1_base.c (i1). base r0 + src r3 pins together. */
/* W52-C 0x0800BFD0 (232 B) b2 — fresh rewrite from ROM dis (2026-10-26).
 * TRUE extent 232 B (bx 0xc094, pad 0xc096, pools 0xc098-0xc0b7, next 0xc0b8).
 * Pools raw LE: 02004f40, 020038ac, 08329430, 020031e8, 0832943c, 0832afdc,
 * 00000702, 00002001.
 * ROM register plan: r8 = gp addr then a4; r9 = gp value; sl = bound;
 * ip = base; r5 = count; r6 = arg*4 then inner 0x2001; r4 = dest.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u8 g_02004f40[];
extern u8 tbl_08329430[];
extern u16 g_020031e8;
extern u8 tbl_0832943c[];
extern u8 tbl_0832afdc[];
__asm__(".set g_02004f40, 0x02004f40");
__asm__(".set tbl_08329430, 0x08329430");
__asm__(".set g_020031e8, 0x020031e8");
__asm__(".set tbl_0832943c, 0x0832943c");
__asm__(".set tbl_0832afdc, 0x0832afdc");

extern void Sub_0800244C(u8 *a, int b);
extern void Sub_0800288C(u8 *a, int b);
__asm__(".set Sub_0800244C, 0x0800244c");

__attribute__((section(".text.w53a_0800bfd0")))
void Sub_0800BFD0(int arg)
{
    u16 au = (u16)arg;
    s16 a;
    g_02004f40[4] = (u8)au;
    a = (s16)au;
    if (a != -1) {
        register u32 *gp __asm__("r8");
        int i4;
        int e20;
        u8 *entry;
        register u8 *base __asm__("r0");
        u16 count;
        register u16 bound __asm__("sl");
        short i;
        gp = (u32 *)0x020038ac;
        __asm__ volatile("" : "+r" (gp));
        i4 = a * 4;
        e20 = a * 20;
        { register u32 poolv __asm__("r1"); poolv = (u32)tbl_08329430; entry = (u8 *)(e20 + poolv); }
        *(u8 **)(g_02004f40 + 16) = entry;
        Sub_0800244C(entry, ((g_020031e8 & 12) << 12) + 32);
        { register u8 *t2 __asm__("r3"); t2 = tbl_0832943c; Sub_0800288C((u8 *)(e20 + (u32)t2), 64); }
        base = tbl_0832afdc + *(u32 *)(tbl_0832afdc + i4);
        {
            register u8 *src __asm__("r3");
            src = (u8 *)(i4 + (int)base + 4);
            __asm__ volatile("" : "+r" (src));
            count = *(u16 *)src;
            bound = *(u16 *)(src + 2);
        }
        i = 0;
        if (i < bound) {
            register u32 g __asm__("r9");
            int a4;
            register u8 *ip __asm__("ip");
            { register u32 *at __asm__("r7"); register u32 gtmp __asm__("r7"); at = gp; gtmp = *at; g = gtmp; }
            a4 = i4;
            ip = base;
            do {
                u16 *dst = (u16 *)(g + 0x702);
                short j;
                register u8 *sp __asm__("r3");
                dst += i * 32;
                sp = (u8 *)(a4 + (int)ip + 8);
                sp += i * count * 2;
                j = 0;
                if (j < count) {
                    do {
                        *dst = (u16)(0x2001 + *(u16 *)sp);
                        dst++;
                        sp += 2;
                        j++;
                    } while (j < count);
                }
                i++;
            } while (i < bound);
        }
    }
}
