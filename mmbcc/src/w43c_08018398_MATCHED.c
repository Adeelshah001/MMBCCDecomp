/* Wave 43 coordinator landing: coordinator-verified 0-diff
 * (standalone rebuild + in-built-ROM check).
 * See staging/w43coord_verify/ for coordinator verification artifacts.
 */
/* Wave 43 Worker C: 0x08018398 v3, extent 220 B.
 * v2 -> v3: register pins x->r2, y->r3, max->r5 (ROM allocation;
 * max function-scope pinned, assigned in case0).
 * v1 fixes: case-local max (ROM computes 240<<6 in case0, not prologue);
 * adv-label layout (cases 0-2 goto adv; case3 falls through to adv;
 * adv: s[13]++; break; case4 after adv) to reproduce ROM block order
 * [case0][case1][case2][case3][adv][case4][ret1][ret0];
 * unsigned nibble shift ((u32)s[35]<<28)>>28 (w36b idiom);
 * GetField17 returns u8 (ROM zero-extends after the call);
 * volatile y load forces ROM's ldr r3,[sp,#8].
 * Jump table + pools re-derived from raw words (see v1 header).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern void Vec2_CopyMirrored(s32 *out, u8 *o);
extern void ChipInit_080178A8(s32 a, s32 b, s32 c, s32 d, u32 e);
extern u8 GetField17_08017474(u8 *p);

__attribute__((section(".text.w43c_08018398")))
int F_08018398(u8 *s)
{
    s32 out[2];
    register s32 x __asm__("r2");
    register s32 y __asm__("r3");
    register s32 max __asm__("r5");
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    Vec2_CopyMirrored(out, s);
    x = out[0];
    y = *(volatile s32 *)&out[1];
    (void)y;
    switch (s[13]) {
    case 0: {
        max = 240 << 6;
        if (x <= max)
            return 0;
        ChipInit_080178A8(92, ((u32)s[35] << 28) >> 28, max, -5120, *(u32 *)(s + 44));
        *(s32 *)(s + 96) = -1536;
        goto adv;
    }
    case 1:
        if (*(s32 *)(s + 88) > 0)
            return 0;
        *(s32 *)(s + 96) = 0;
        s[18] = 12;
        goto adv;
    case 2:
        if (--s[18] != 0)
            return 0;
        *(s32 *)(s + 88) = -1536;
        goto adv;
    case 3:
        if (x >= -11520)
            return 0;
        *(s32 *)(s + 88) = 0;
    adv:
        s[13]++;
        break;
    case 4:
        if (GetField17_08017474(*(u8 **)(s + 44)) > 5)
            return 1;
        return 0;
    default:
        return 0;
    }
    return 0;
}

__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
__asm__(".set GetField17_08017474, 0x08017474");
