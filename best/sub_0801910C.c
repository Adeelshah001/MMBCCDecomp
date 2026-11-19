/* Step_0801910C @ 0x0801910C (314 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w65d_0801910c_MATCHED.c (registry: staging/w65d_fresh/w65d_0801910c_RECOMMENDED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void *sub_0804DFA8(void *dst, const void *src, u32 len);

extern void sub_0800DD4C(void *o, s32 x, s32 y);

extern void *sub_0800DD08(void *d, void *s);

extern void sub_080174A4(u8 *s, u8 bit);

extern void sub_0800D9EC(u8 *s, u8 idx);

extern u32 sub_080178A8(u32 a, u32 b, u32 c, u32 d, u8 *e);

extern u8 sub_08017474(u8 *s);

u32 sub_0801910C(u8 *s)
{
    u8 buf[12];
    u64 t;
    u8 *p;
    u8 *q;
    u8 v;
    u8 b0;

    sub_0804DFA8(buf, (const void *)0x080E9BFC, 3);
    sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08(buf + 4, s);
    t = *(u64 *)(buf + 4);
    sub_080174A4(*(u8 **)(s + 44), 3);
    switch (s[13]) {
    case 0:
        p = s; p += 119;
        if ((u8)(p[0] - 3) > 1)
            break;
        sub_0800D9EC(s, 1);
        *(u32 *)(s + 88) = 512;
        *(u32 *)(s + 96) = 0;
        *(u32 *)(s + 92) = -128;
        *(u32 *)(s + 100) = 8;
        s[13]++;
        break;
    case 1:
        if (*(s32 *)(s + 100) > 0) {
            if (*(s32 *)(s + 92) > 127)
                *(s32 *)(s + 100) = -8;
        } else if (*(s32 *)(s + 92) <= -128) {
            *(s32 *)(s + 100) = 8;
        }
        if ((s32)t <= 12800)
            break;
        b0 = buf[s[17]];
        q = s; q += 35;
        sub_080178A8(b0, (u32)(q[0] << 28) >> 28, 15360, 0xFFFFE200, *(u8 **)(s + 44));
        *(u32 *)(s + 88) = 0;
        *(u32 *)(s + 96) = 0;
        *(u32 *)(s + 92) = 0;
        *(u32 *)(s + 100) = 0;
        sub_0800D9EC(s, 2);
        s[13]++;
        break;
    case 2:
        p = s; p += 119;
        if ((u8)(p[0] - 3) > 1)
            break;
        s[13]++;
        break;
    case 3:
        v = s[10];
        v &= 253;
        v &= 254;
        s[10] = v;
        s[13]++;
        break;
    case 4:
        if (sub_08017474(*(u8 **)(s + 44)) <= 5)
            break;
        return 1;
    }
    /* Keep t (both halves; high half otherwise dead) live; emits no code. */
    
    return 0;
}
