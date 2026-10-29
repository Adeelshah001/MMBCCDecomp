/* Wave 43 coordinator landing: coordinator-verified 0-diff
 * (standalone rebuild + in-built-ROM check).
 * See staging/w43coord_verify/ for coordinator verification artifacts.
 */
/* Wave 43 Worker C: 0x0801b2d0 v7, extent 220 B.
 * v5 -> v7: inline-asm nibbles + materialization barrier for q (v6 dropped q). named mode local + register pins (x->r5, y->r6, mode->r7,
 * q->r8) reproducing ROM allocation (prologue push {r4-r7,lr} + r8 save);
 * adv-label layout (case0 goto adv; case1 falls through to adv;
 * adv: s[13]++; break; case2 after adv) reproducing ROM block order
 * [case0][case1][adv][case2][ret1][ret0]. Semantics per v1 header.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;
typedef signed short s16;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(s32 *out, u8 *o);
extern void SetBit16_080174A4(u8 *p, s32 bit);
extern s32 Text_SelectBlobIdx_0804A378(s32 idx);
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
    Vec2_CopyMirrored(out, s);
    x = out[0];
    y = out[1];
    mode = s[13];
    switch (mode) {
    case 0: {
        register u8 *q __asm__("r8");
        if (x <= 15359)
            return 0;
        SetBit16_080174A4(*(u8 **)(s + 44), 3);
        Text_SelectBlobIdx_0804A378(149);
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

__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
__asm__(".set SetBit16_080174A4, 0x080174a4");
__asm__(".set Text_SelectBlobIdx_0804A378, 0x0804a378");

/* Coordinator landing note (1b2d0): trailing .balign 4, 0 emits
 * the 2 zero inter-function padding bytes (gas would otherwise
 * pad the 4-aligned section with a 46c0 nop; ROM has 00 00).
 * Same pattern as w43b_08026430 in this wave. */
__asm__(".balign 4, 0");
