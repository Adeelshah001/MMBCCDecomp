/* Wave 36-C MATCHED: 0x0801e0d0, 124 B, true extent 0x0801e0d0-0x0801e14c (next fn 0x0801e14c).
   Compiler: old_agbcc. Variants: 6. Key idioms: barrier-after-pool-const forces pool-first load; reversed table add ((idx<<2)+(u32)tbl); dst pin r2 for s+34; s8 clamp t=((s32)(s[84]<<13)>>24)+6 to [0,31], s[34]=31-t.
   Pools LE-verified: 0x020051b0, 0x082243d8, 0x08226a60. Verification: clean-room harness 124/124 B, 0 diffs (old_agbcc).
   Landing note: Sub_0800D9FC .set must be stripped at landing (already defined); Sub_0804DCD0 .set kept (unmatched callee). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;
extern void Sub_0804DCD0(u8 *s, u32 e);
__asm__(".set Sub_0804DCD0, 0x0804dcd0");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__attribute__((section(".text.w36c_0801e0d0")))
void Sub_0801E0D0(u8 *s)
{
    u8 *gp = (u8 *)0x020051b0;
    if ((((int)gp[3] >> s[16]) & 1) == 0) {
        u32 *tbl = (u32 *)0x082243d8;
        u8 idx;
        u32 *e;
        __asm__ volatile("" : "+r"(tbl));
        idx = s[9];
        e = (u32 *)((idx << 2) + (u32)tbl);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*e + 8);
    } else {
        u32 *tbl = (u32 *)0x08226a60;
        u8 idx;
        u32 *e;
        s8 t;
        u8 res;
        register u8 *dst __asm__("r2");
        __asm__ volatile("" : "+r"(tbl));
        idx = s[13];
        e = (u32 *)((idx << 2) + (u32)tbl);
        Sub_0804DCD0(s, *e);
        t = (s8)(((s32)(*(u32 *)(s + 84) << 13) >> 24) + 6);
        if (t > 31) t = 31;
        if (t < 0) t = 0;
        res = 31 - t;
        dst = s + 34;
        *dst = res;
        Sub_0800D9FC(s);
    }
}
