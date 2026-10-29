typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern void Vec2_AddMirrored(void *o, s32 x, s32 y);
extern void *Vec2_CopyMirrored(void *d, void *s);
extern u32 GetField17_U8(void *s);

__attribute__((section(".text.w36a_0801b880")))
u32 Step_0801b880(u8 *s)
{
    u32 buf[2];
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored(buf, s);
    if (s[13] == 0) {
        u8 v = GetField17_U8(*(void **)(s + 44));
        if (v > 6) {
            s[10] &= 254;
            return 1;
        }
    }
    return 0;
}

__asm__(".set Vec2_AddMirrored, 0x0800dd4c");
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
__asm__(".set GetField17_U8, 0x08017474");
