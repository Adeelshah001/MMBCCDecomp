/* MMBCCDecomp — guarded blit-request forwarder (Wave 2).
 * MATCHED 2026-10-20 (worker C, coordinator-verified byte-identical).
 * ROM 0x08006A54 (68 B code + 8 B pool).
 * Flags: main agbcc -O2 -mthumb-interwork (first-try match, incl.
 * register allocation and pool order).
 *
 * If *(u8*)(0x02004830+0x265) is nonzero, return; else forward to
 * sub_08006AD8(ctx, a, (s16)b, (s16)c, (s8)d, (u8)e). The s16/s16 pair
 * suggests X/Y. Name is tentative (worker C, inferred from the shared
 * callee with the tilemap blit path).
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md). gReqCtx is pool-loaded (order-safe
 * either way). Remove each .set when that symbol gets matched for
 * real (duplicate-symbol otherwise). */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u8 gReqCtx[];

void sub_08006AD8(u32 ctx, u32 a, s16 b, s16 c, s8 d, u8 e);

__attribute__((section(".text.gfx_blitreq")))
void Gfx_BlitRequest(u32 a, u16 b, u16 c, u8 d, u8 e)
{
    u8 *ctx = gReqCtx;

    if (*(ctx + 0x265) != 0)
        return;
    sub_08006AD8((u32)ctx, a, b, c, d, e);
}

__asm__(
    ".globl gReqCtx\n.set gReqCtx, 0x02004830\n"
    ".globl sub_08006AD8\n.set sub_08006AD8, 0x08006AD8\n"
);
