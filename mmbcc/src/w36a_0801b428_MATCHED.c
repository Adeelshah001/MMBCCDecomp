typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed char s8;

extern void Vec2_AddMirrored(void *o, s32 x, s32 y);
extern void *Vec2_CopyMirrored(void *d, void *s);

__attribute__((section(".text.w36a_0801b428")))
u32 Step_0801b428(u8 *s)
{
    u32 buf[2];
    u8 v;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored(buf, s);
    if (s[13] != 0)
        return 0;
    if ((s8)--s[18] != 0)
        return 0;
    v = s[10];
    v &= 253;
    v &= 254;
    s[10] = v;
    return 1;
}
__asm__(".short 0x0000");

__asm__(".set Vec2_AddMirrored, 0x0800dd4c");
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
