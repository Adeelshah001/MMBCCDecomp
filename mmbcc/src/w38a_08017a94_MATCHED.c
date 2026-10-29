/* W38-A: 0x08017a94, 216 B. Init-task (18474 family).
 * e = 0x082263a8 + (s[16]<<4); s[12]=1;
 * s[20] = *(u32*)(*(u32*)(0x082243d8 + (s[9]<<2)) + 4);
 * s[108]=0; s[10] = 2|s[10]|1; Setup(s, 768|e[1], e[0]);
 * IncUse(s, e[2]); v = *(u8*)(0x020031e4 +
 * ((*(u16*)0x081705b0>>4)<<1)) & 3, clamped to 3 (dead clamp,
 * kept via barrier); s[69] = (s[69] & -13) | (v<<2); s[34]=14;
 * if (e[12] & 1): CopyMirrored(out, s); SetMirrored(s, e[8],
 * e[10]) [s16 via ldrsh asm]; else AddMirrored(s, e[8], e[10]);
 * if (e[5]) Text_SelectBlobIdx(e[5]); tail Sub_08017B6C(s).
 * Callees: Setup 0x0800d6e0, IncUse 0x0800d9ec, CopyMirrored
 * 0x0800dd08 (BLOCKED, .set), SetMirrored 0x0800dd2c,
 * AddMirrored 0x0800dd4c, Text_SelectBlobIdx 0x0804a378
 * (all MATCHED except CopyMirrored), Sub_08017B6C 0x08017b6c
 * (unlisted gap callee, .set).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, int b, u8 c);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void Vec2_CopyMirrored(u32 *out, u8 *src);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern int Text_SelectBlobIdx(int idx);
extern void Sub_08017B6C(u8 *s);
__asm__(".set Sub_08017B6C, 0x08017b6c");

__attribute__((section(".text.w38a_08017a94")))
void Sub_08017A94(u8 *s)
{
    u32 out[2];
    u8 *e;
    u32 *p;
    u8 *q;
    int v, w, sh, m;
    {
        register int sh1 __asm__("r1");
        register u8 *b __asm__("r0");
        sh1 = s[16] << 4;
        b = (u8 *)0x082263a8;
        __asm__ volatile("" : "+r"(b));
        e = (u8 *)(sh1 + (u32)b);
    }
    {
        register u32 *base __asm__("r1");
        register int s9 __asm__("r2");
        base = (u32 *)0x082243d8;
        __asm__ volatile("" : "+r"(base));
        s9 = s[9];
        p = (u32 *)((s9 << 2) + (u32)base);
    }
    {
        register int one __asm__("r1");
        register int t10 __asm__("r3");
        register int res __asm__("r0");
        one = 1;
        *(u32 *)(s + 12) = one;
        *(u32 *)(s + 20) = *(u32 *)(*p + 4);
        *(u32 *)(s + 108) = 0;
        t10 = s[10];
        res = 2 | t10;
        res |= one;
        s[10] = res;
    }
    {
        /* ROM arg: movs r1,#192; lsls r1,#2; adds r0,r1,#0;
         * ldrb r1,[e,#1]; orrs r1,r0 (C reorders to e[1]-first
         * with no adds under both agbcc versions, so pin the
         * computation with asm; arg itself stays a C call arg). */
        register int arg __asm__("r1");
        __asm__ volatile("mov %0, #192\n\tlsl %0, %0, #2\n\tadd r0, %0, #0\n\tldrb %0, [%1, #1]\n\torr %0, %0, r0" : "=r"(arg) : "r"(e) : "r0", "cc");
        ChipSlot_Setup(s, arg, e[0]);
    }
    ChipSlot_IncUse(s, e[2]);
    v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
    w = v;
    __asm__ volatile("" : "+r"(w));
    if (w > 3)
        v = 3;
    q = s + 69;
    sh = v << 2;
    __asm__ volatile("movs %0, #13" : "=r"(m));
    m = -m;
    *q = (*q & m) | sh;
    s[34] = 14;
    if (*(u16 *)(e + 12) & 1) {
        register s32 x __asm__("r1");
        register s32 y __asm__("r2");
        Vec2_CopyMirrored(out, s);
        __asm__ volatile("movs r2, #8\n\tldrsh %0, [%1, r2]" : "=r"(x) : "r"(e) : "r2");
        __asm__ volatile("movs r3, #10\n\tldrsh %0, [%1, r3]" : "=r"(y) : "r"(e) : "r3");
        Vec2_SetMirrored(s, x, y);
    } else {
        register s32 x __asm__("r1");
        register s32 y __asm__("r2");
        __asm__ volatile("movs r0, #8\n\tldrsh %0, [%1, r0]" : "=r"(x) : "r"(e) : "r0");
        __asm__ volatile("movs r3, #10\n\tldrsh %0, [%1, r3]" : "=r"(y) : "r"(e) : "r3");
        Vec2_AddMirrored(s, x, y);
    }
    if (e[5] != 0)
        Text_SelectBlobIdx(e[5]);
    Sub_08017B6C(s);
}

/* Trailing 0000 pad to 4-byte boundary (next fn at 0x08017b6c). */
__asm__(".hword 0");
