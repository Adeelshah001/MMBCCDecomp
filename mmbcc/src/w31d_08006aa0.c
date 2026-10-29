/* Wave 31-D: 0x08006AA0 MATCHED (TilemapFill_08006AA0) around TilemapRectFill_6AD8 (no flag check). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

/* param5 declared s8 here to get the sign-extension; real callee takes u8. */
extern void TilemapRectFill_6AD8(void *ctx, u32 t, s16 x, s16 y, s8 z, u8 w);
__asm__(".set TilemapRectFill_6AD8, 0x08006ad8");

__attribute__((section(".text.w31d_08006aa0")))
void TilemapFill_08006AA0(u32 t, int x, int y, int z, u8 w)
{
    TilemapRectFill_6AD8((void *)0x0200483c, t, (s16)x, (s16)y, (s8)z, w);
}
