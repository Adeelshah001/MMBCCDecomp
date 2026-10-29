/* Wave 36-D MATCHED (C + .s patch w36d_080227dc_patch.py, old_agbcc, 0 diffs over 140 B true extent 0x080227dc-0x08022868; patch: case1 288 copy + address recompute, case2 pool-first reorder, case1 f18/t/d register fix), 140 B, extent next-func 0x0802278c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern void Sub_0800D9FC(void *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w36d_080227dc")))
void Sub_080227DC(u8 *s)
{
    register s32 st __asm__("r2") = s[13];
    if (st == 1)
        goto case1;
    if (st > 1)
        goto gt;
    if (st == 0)
        goto case0;
    goto end;
gt:
    if (st == 2)
        goto case2;
    goto end;
case0: {
        u8 *p;
        register u32 v0 __asm__("r1");
        s[13] = 1;
        p = s + 76;
        v0 = 256;
        *(u16 *)p = v0;
        p += 2;
        *(u16 *)p = v0;
        s[18] = 32;
    }
    /* fall through */
case1: {
        u32 t;
        register u32 c __asm__("r1") = 288;
        register u8 f18b __asm__("r4") = s[18];
        register u32 v0 __asm__("r0") = c;
        register u32 v __asm__("r2") = v0 - f18b;
        u8 *p = s + 76;
        *(u16 *)p = v;
        *(u16 *)(s + 78) = v0 - s[18];
        t = ((u32)s[18] << 24);
        if (t == 0) {
            s[13]++;
        } else {
            u32 d;
            t >>= 25;
            t <<= 16;
            d = 1;
            if (t != 0)
                d = t >> 16;
            s[18] -= d;
        }
        goto end;
    }
case2: {
        register u32 base __asm__("r1") = 0x08226ef0;
        register u8 f9b __asm__("r4") = s[9];
        u32 *addr = (u32 *)base + f9b;
        u32 *e;
        *(u32 *)(s + 12) = st;
        e = *(u32 **)addr;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)e + 8);
        goto end;
    }
end:
    Sub_0800D9FC(s);
}
