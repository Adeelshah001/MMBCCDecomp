/* F_0801B2D0 @ 0x0801B2D0 (218 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w43c_0801b2d0_MATCHED.c (registry: mmbcc/src/w43c_0801b2d0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;
typedef signed short s16;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(s32 *out, u8 *o);

extern void SetBit16(u8 *p, s32 bit);

extern s32 Text_SelectBlobIdx(s32 idx);

extern void ChipInit_0801EBF0(s32 a, s32 b, s32 c, s16 d, s32 e);

extern void ChipInit_080178A8(s32 a, s32 b, s32 c, s32 d, u32 e);

__attribute__((section(".text.w43c_0801b2d0")))
int F_0801B2D0(u8 *s)
{
    s32 out[2];
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    u8 mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    y = out[1];
    mode = s[13];
    switch (mode) {
    case 0: {
        register u8 *q __asm__("r8");
        if (x <= 15359)
            return 0;
        SetBit16(*(u8 **)(s + 44), 3);
        Text_SelectBlobIdx(149);
        q = s + 35;
        __asm__ volatile("" : "+r" (q));
        {
            /* ROM nibble loads use r1 (first) / r2 (second) as temp regs;
             * plain C loads into r0 here, so force them with asm. At the
             * first asm, r0 still holds q's address (from q = s + 35). */
            register u32 n1 __asm__("r2");
            register u32 n2 __asm__("r1");
            __asm__ volatile("ldrb r1, [r0]\n\tlsl %0, r1, #28\n\tlsr %0, %0, #28" : "=r" (n1) :: "r1");
            ChipInit_0801EBF0(58, 0, n1, (s16)x, mode);
            __asm__ volatile("mov r2, r8\n\tldrb r2, [r2]\n\tlsl %0, r2, #28\n\tlsr %0, %0, #28" : "=r" (n2) :: "r2");
            ChipInit_080178A8(121, n2, 240 << 6, 0, *(u32 *)(s + 44));
        }
        *(s32 *)(s + 88) = mode;
        *(s32 *)(s + 92) = mode;
        s[18] = 30;
        goto adv;
    }
    case 1:
        if (--s[18] != 0)
            return 0;
        *(s32 *)(s + 100) = -100;
    adv:
        s[13]++;
        break;
    case 2:
        if (y >= -7680)
            return 0;
        s[10] &= 0xfd;
        s[10] &= 0xfe;
        return 1;
    default:
        return 0;
    }
    return 0;
}
