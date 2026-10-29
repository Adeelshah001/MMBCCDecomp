/* MMBCCDecomp — Vec2 mirror-aware vector helpers (Wave 2).
 * MATCHED 2026-10-20 (worker B, coordinator-verified byte-identical).
 * ROM 0x0800DD2C (30 B) and 0x0800DD4C (38 B).
 * Flags: old_agbcc -O2 -mthumb-interwork (see Makefile) — main agbcc
 * diverges on register allocation for the (u8 *)o / p += 35 shape.
 *
 * Notes on the match:
 * - Each function tests bit 7 of the flag byte at struct offset +35 and
 *   negates the X component when set (horizontal mirror); the s32
 *   vector lives at +80/+84.
 * - `u8 *p = (u8 *)o; p += 35;` as separate statements reproduces
 *   `adds r3,r4,#0` + `adds r3,#35` (not folded into one add).
 * - `if ((*p & 0x80) != 0)` reproduces the ROM's redundant
 *   `ands; cmp r0,#0; beq`.
 * - The `adds r4,r0,#0` in the ROM is the compiler's own spill of `o`
 *   (r0 clobbered by `movs r0,#128`) — no source-level temp wanted. */

typedef unsigned char u8;
typedef signed int s32;

/* Game object tail: flag byte at +35 (bit 7 = mirror X),
 * s32 vector at +80/+84. */
struct ObjVec {
    u8 _00[35];
    u8 flip;   /* +35: bit 7 = X mirrored */
    u8 _36[44];/* +36..+79 */
    s32 x;     /* +80 */
    s32 y;     /* +84 */
};

__attribute__((section(".text.vec2_setmirrored")))
void Vec2_SetMirrored(struct ObjVec *o, s32 x, s32 y)
{
    u8 *p = (u8 *)o;
    p += 35;

    if ((*p & 0x80) != 0)
        x = -x;
    o->x = x;
    o->y = y;
}

__attribute__((section(".text.vec2_addmirrored")))
void Vec2_AddMirrored(struct ObjVec *o, s32 x, s32 y)
{
    u8 *p = (u8 *)o;
    p += 35;

    if ((*p & 0x80) != 0)
        x = -x;
    o->x += x;
    o->y += y;
}
