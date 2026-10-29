typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void sub_08005268(void *a, void *b);
extern u32 G_020038AC[];
extern u8 T_081731E0[];

__attribute__((section(".text.w36a_0800cb70")))
void Lookup_0800cb70(u8 *s, s8 idx)
{
    u32 p2;
    s8 b;
    s32 b4;
    u8 *t2;
    u32 x;
    u32 y;
    u8 *p;
    if (idx < 0)
        return;
    {
        register u8 *e __asm__("r0");
        {
            register u8 *t1 __asm__("r1") = T_081731E0;
            u32 off = 20;
            e = (*(s16 *)(s + off)) * 8 + t1;
        }
        p2 = G_020038AC[1] + 0xfa000a20;
        b = *e;
        b4 = b * 4;
        t2 = (u8 *)0x087493b0;
        x = *(u32 *)(t2 + b4);
        y = x + (u32)t2;
        p = (u8 *)(b4 + y);
        p += idx * 20;
        sub_08005268(p, (void *)p2);
    }
}

__asm__(".set sub_08005268, 0x08005268");
__asm__(".set G_020038AC, 0x020038ac");
__asm__(".set T_081731E0, 0x081731e0");
