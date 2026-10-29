typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u32 Tbl2_08106D7C[];
extern u8 Tbl1_08106DD0[];
extern void sub_0804cde8(u32 *p, u32 v);
extern void ClearSignBit(u32 *p);

__attribute__((section(".text.w36a_0804c72c")))
void Lookup_0804c72c(u16 idx)
{
    u32 *t2 = Tbl2_08106D7C;
    u8 *t1 = Tbl1_08106DD0;
    u8 *e1 = t1 + idx * 8;
    u16 k = *(u16 *)(e1 + 4);
    u32 *p = (u32 *)t2[k * 3];
    u32 a = *p;
    u32 b = *(u32 *)e1;
    u32 f;
    if (a != b) {
        sub_0804cde8(p, b);
        return;
    }
    f = p[1];
    if ((u16)f == 0) {
        sub_0804cde8(p, a);
        return;
    }
    if ((s32)f >= 0)
        return;
    ClearSignBit(p);
}

__asm__(".set Tbl1_08106DD0, 0x08106dd0");
__asm__(".set Tbl2_08106D7C, 0x08106d7c");
__asm__(".set sub_0804cde8, 0x0804cde8");
__asm__(".set ClearSignBit, 0x0804c5f4");
