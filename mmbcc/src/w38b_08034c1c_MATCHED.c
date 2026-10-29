/* W38-B v6: Sub_08034C1C @ 0x08034c1c, 132 B.
   v1 + (a) u32-shift trunc for call result (lsl+lsr, +2B);
   (b) if/else tail (2 pools, ROM branch form); (c) i=3 before tbl
   setup (ROM prologue order); (d) barrier in then-branch to pull
   tblA pool mid-function. Callee 0x08034bd4 BLOCKED (symdef). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
extern int Sub_08034BD4(u8 a, u16 b);
__asm__(".set Sub_08034BD4, 0x08034bd4");
__attribute__((section(".text.w38b_08034c1c")))
void Sub_08034C1C(u8 *s, u8 mode)
{
    u8 *base;
    register u8 *tblA __asm__("r7");
    u8 *tblB;
    u8 i;
    u8 *p;
    if (mode == 0)
        base = s + 336;
    else
        base = s + 364;
    i = 3;
    tblA = (u8 *)0x0200517e;
    tblB = tblA - 20;
    do {
        u32 *ep = (u32 *)(base + i * 4);
        u8 *ptr = (u8 *)*ep;
        u8 v = (u8)(((u32)Sub_08034BD4(ptr[0], *(u16 *)(ptr + 2)) << 24) >> 24);
        u8 *dst;
        if (mode != 0) {
            if (i - 3 == 255)
                goto next;
            dst = (i - 3) + tblA;
            __asm__ volatile("");
        } else {
            if (i - 3 == 255)
                goto next;
            dst = (i - 3) + tblB;
        }
        *dst = v;
next: ;
        i++;
    } while (i <= 5);
    if (mode != 0) {
        __asm__ volatile("" : "+r"(p));
        p = (u8 *)0x0200517c;
    } else
        p = (u8 *)0x02005168;
    p[5] = 4;
    p[6] = 4;
}
