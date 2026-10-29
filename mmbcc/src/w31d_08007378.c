/* Wave 31-D: 0x08007378 MATCHED (CondTilemapRectFill_08007378) — tbl load inside branch, explicit mode-1. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void TilemapRectFill_6AD8(void *ctx, u32 t, s16 x, s16 y, u8 d, u8 e);
__asm__(".set TilemapRectFill_6AD8, 0x08006ad8");

__attribute__((section(".text.w31d_08007378")))
void CondTilemapRectFill_08007378(u8 mode, u16 x, u16 y, u8 z)
{
    u8 *base;
    register u32 t __asm__("r1");
    t = 0;
    base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    if (mode != 0) {
        u32 *tbl = (u32 *)0x08171ee0;
        int m;
        __asm__ volatile("" : "+r"(tbl));
        m = mode - 1;
        t = tbl[m];
    }
    TilemapRectFill_6AD8(base, t, (s16)x, (s16)y, 2, z);
}
