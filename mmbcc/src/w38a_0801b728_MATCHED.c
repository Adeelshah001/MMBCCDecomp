/* W38-A: 0x0801b728, 244 B (true extent: bx 0x1b818, next 0x1b81c).
 * 1823c family, int return (like #28/#41).
 * AddMirrored(s,s88,s92); s88+=s96; s92+=s100; CopyMirrored(out,s)
 * (out at sp+0/sp+4, out0 in r2 (dead, pin+barrier), out1 in r3
 * (live, used in c0)).
 * mode = s[13] in r1 (compared directly, reused in c0 for
 * s92/s100 = mode). Modes: 0 -> c0, 1 -> c1, 2 -> c2, 3+ -> ret 0.
 * c0: if out1 > -3840: s92=s100=mode; s18=8 -> shared (s18/s13++).
 *   Else ret 0.
 * c1: s18--; if (s8)s18 != 0 ret 0; else Setup(s,514,0);
 *   IncUse(s,0); clamp v + s69 (same as #7/#39); s34=13;
 *   AddMirrored(s,0,2560); Text_SelectBlobIdx(126); s18=23 ->
 *   shared (s18/s13++). Shared block at 1b7e2: s18=r0, s13++,
 *   ret 0 (c0 r0=8 via b, c1 r0=23 via fall-through).
 * c2: s18--; if (s8)s18 != 0 ret 0; else s10&=254; return 1.
 * Pools: -3840, 514, 0x081705B0, 0x020031E4.
 * Callees: AddMirrored MATCHED, CopyMirrored BLOCKED (.set),
 * Setup/IncUse MATCHED, Text_SelectBlobIdx MATCHED (staged (int),
 * real unknown — flag).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_AddMirrored(u8 *s, int a, int b);
extern void Vec2_CopyMirrored(u8 *out, u8 *s);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void ChipSlot_Setup(u8 *s, int a, u8 b);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern void Text_SelectBlobIdx(int idx);

__attribute__((section(".text.w38a_0801b728")))
int Sub_0801B728(u8 *s)
{
    u32 out[2];
    register int o0 __asm__("r2");
    int o1;
    int mode;
    int e;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Vec2_CopyMirrored((u8 *)out, s);
    o0 = out[0];
    __asm__ volatile("" : "+r"(o0));
    o1 = out[1];
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    return 0;
gt1:
    if (mode == 2)
        goto c2;
    return 0;
c0:
    __asm__ volatile("" : "+r"(o0));
    if (o1 <= -3840)
        return 0;
    *(u32 *)(s + 92) = mode;
    *(u32 *)(s + 100) = mode;
    e = 8;
    goto shared;
c1:
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    ChipSlot_Setup(s, 514, 0);
    ChipSlot_IncUse(s, 0);
    {
        register int v __asm__("r1") = *(u8 *)(0x020031E4 + ((*(u16 *)0x081705B0 >> 4) << 1)) & 3;
        int t;
        int m;
        int sh;
        u8 *q;
        __asm__ volatile("" : "+r"(v));
        t = v;
        __asm__ volatile("" : "+r"(t));
        if (t > 3)
            v = 3;
        q = s + 69;
        sh = v << 2;
        m = 13;
        m = -m;
        *q = (*q & m) | sh;
    }
    s[34] = 13;
    Vec2_AddMirrored(s, 0, 160 << 4);
    Text_SelectBlobIdx(126);
    e = 23;
shared:
    s[18] = e;
    s[13]++;
    return 0;
c2:
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    s[10] &= 254;
    return 1;
}

__asm__(".hword 0");
