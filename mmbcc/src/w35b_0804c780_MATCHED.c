/* Wave 35-B v4: 0x0804c780 split shift sh<<16 ... sh>>13 around pool loads. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_0804CECC(u32 x);
__asm__(".set Worker_0804CECC, 0x0804cecc");

__attribute__((section(".text.w35b_0804c780")))
void Sub_0804C780(int idx)
{
    u32 sh = (u32)idx << 16;
    register u32 *tbl1 __asm__("r2") = (u32 *)0x08106d7c;
    register u32 *tbl2 __asm__("r1") = (u32 *)0x08106dd0;
    u32 t;
    u16 v;
    u32 base;
    u32 v2;
    u32 v3;
    u32 v4;
    __asm__ volatile("" : "+r"(tbl1));
    __asm__ volatile("" : "+r"(tbl2));
    t = (sh >> 13) + (u32)tbl2;
    v = *(u16 *)(t + 4);
    base = (v * 3) * 4;
    base += (u32)tbl1;
    v2 = *(u32 *)base;
    v3 = *(u32 *)v2;
    v4 = *(u32 *)t;
    if (v3 == v4)
        Worker_0804CECC(v2);
}
