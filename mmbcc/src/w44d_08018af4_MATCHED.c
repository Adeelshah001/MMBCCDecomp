/* Wave 44 coordinator landing: coordinator-verified 0-diff
 * (standalone rebuild + in-built-ROM check).
 * See staging/w44coord_verify/ for coordinator verification artifacts.
 * .set adjudication (nm wins): kept Vec2_CopyMirrored only (local
 * absolutes, no T global); dropped all other .set lines (T globals exist).
 */
/* W44-D v4 (MATCHED candidate): 0x08018af4, 400 B. Switch state machine, template w38a 0801a484 + w43d lookup idiom.
   Pools (raw LE ROM): 0x223, 0x081705b0, 0x020031e4, 0xffffe700. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Vec2_AddMirrored(u8 *s, int a, int b);
extern void Vec2_CopyMirrored(u8 *out, u8 *s);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void ChipSlot_Setup(u8 *s, int a, int b);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void SetBit16(int v, int bit);
extern u32 *ChipInit_080178A8(int a, int b, int c, int d, int e);
extern u8 GetField17_U8(int v);

__attribute__((section(".text.w44d_08018af4")))
int Sub_08018AF4(u8 *s)
{
    int out[2];
    int mode;
    u8 b;
    int c, t;
    u32 cc, m;
    u8 *p;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored((u8 *)out, s);
    mode = s[13];
    switch (mode) {
    case 0:
        if ((u8)(s[119] - 3) > 1)
            return 0;
        ChipSlot_Setup(s, 0x223, 0);
        ChipSlot_IncUse(s, 1);
        b = ((u8 *)0x020031e4)[(*(u16 *)0x081705b0 >> 4) * 2];
        c = b & 3;
        t = c;
        __asm__ volatile("" : "+r"(t));
        if (t > 3)
            c = 3;
        p = s + 69;
        cc = c << 2;
        __asm__ volatile("movs %0, #13" : "=r"(m));
        m = -m;
        *p = (*p & m) | cc;
        s[34] = 13;
        s[18] = 10;
        __asm__ volatile("" :: "i"(0));
        goto inc;
    case 1:
        s[18]--;
        if (s[18] != 0)
            return 0;
        ChipSlot_IncUse(s, 2);
        s[18] = 10;
        __asm__ volatile("" :: "i"(1));
        goto inc;
    case 2:
        s[18]--;
        if (s[18] != 0)
            return 0;
        ChipSlot_IncUse(s, 3);
        s[18] = 10;
        __asm__ volatile("" :: "i"(2));
        goto inc;
    case 3:
        s[18]--;
        if (s[18] != 0)
            return 0;
        SetBit16(*(u32 *)(s + 44), 3);
        ChipSlot_IncUse(s, 4);
        s[18] = 10;
        __asm__ volatile("" :: "i"(3));
        goto inc;
    case 4:
        s[18]--;
        if (s[18] != 0)
            return 0;
        ChipSlot_IncUse(s, 5);
        s[18] = 2;
        goto inc;
    case 5:
        s[18]--;
        if (s[18] != 0)
            return 0;
        ChipInit_080178A8(66, (int)(((u32)s[35] << 28) >> 28), 240 << 6, -6400, *(u32 *)(s + 44));
        s[10] &= 253;
        s[10] &= 254;
        goto inc;
    case 6:
        goto c6;
    default:
        goto ret0;
    }
inc:
    s[13]++;
    goto ret0;
c6:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
