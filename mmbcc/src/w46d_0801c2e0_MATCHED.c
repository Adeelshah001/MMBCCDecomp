/* W46-D v1: 0x0801c2e0, 284 B (bx 0x1c3f8, pad 0x1c3fa, next 0x1c3fc).
 * 1823c-family goto-dispatch, mode in r4. Pools (raw LE ROM):
 * c0 byte-op base 0x02003670 at 0x0801c360, offset 0x11af at
 * 0x0801c364; ChipInit stack arg -25600 (0xffff9c00) at 0x0801c3ec.
 * Callees: all MATCHED except Vec2_CopyMirrored (BLOCKED, keep .set;
 * coordinator drops the MATCHED .sets at landing, as usual). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Vec2_AddMirrored(u8 *s, int a, int b);
extern void Vec2_CopyMirrored(u8 *out, u8 *s);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void Vec2_SetMirrored(u8 *s, int a, int b);
extern int Text_SelectBlobIdx(int idx);
extern void SetBit16(int v, int bit);
extern u32 *ChipInit_0801B98C(int a, int b, int c, int d, int e, int f);
extern u8 GetField17_U8(int v);
extern void MaxAssign_17(int v, int val);

__attribute__((section(".text.w46d_0801c2e0")))
int Sub_0801C2E0(u8 *s)
{
    int out[2];
    int out2[2];
    int mode;
    register int o0 __asm__("r6");
    int o1;
    int m;
    int h;
    int off;
    u8 *q;
    u8 *q35;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored((u8 *)out, s);
    o0 = out[0];
    o1 = out[1];
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto ret0;
gt1:
    if (mode == 2)
        goto c2;
    goto ret0;
c0:
    if (o1 <= 0)
        goto ret0;
    Vec2_CopyMirrored((u8 *)out2, s);
    Vec2_SetMirrored(s, o0, o1);
    *(u32 *)(s + 92) = mode;
    *(u32 *)(s + 100) = mode;
    {
        register u8 *base __asm__("r1");
        base = (u8 *)0x02003670;
        off = 0x11af;
        __asm__ volatile("" : "+r"(off));
        q = base + off;
        h = 128;
        m = 15;
        *q = (*q & m) | h;
    }
    Text_SelectBlobIdx(135);
    s[18] = m;
    s[13]++;
    goto ret0;
c1:
    s[18]--;
    if (s[18] != 0)
        goto c2;
    q35 = s + 35;
    ChipInit_0801B98C(4, 0, (int)(((u32)*q35 << 28) >> 28), 160 << 5, -25600, *(u32 *)(s + 44));
    ChipInit_0801B98C(4, 1, (int)(((u32)*q35 << 28) >> 28), 240 << 6, -25600, *(u32 *)(s + 44));
    ChipInit_0801B98C(4, 0, (int)(((u32)*q35 << 28) >> 28), 200 << 7, -25600, *(u32 *)(s + 44));
    SetBit16(*(u32 *)(s + 44), 3);
    s[13]++;
c2:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 5)
        goto ret0;
    MaxAssign_17(*(u32 *)(s + 44), 7);
    return 1;
ret0:
    return 0;
}

__asm__(".balign 4, 0");
