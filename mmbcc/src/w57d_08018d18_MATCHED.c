/* W57-D v5 (v4a + nib inlined into ChipInit args): 0x08018d18, TRUE extent 260 B (bx @0x18e1a, next fn @0x18e1c).
 * v2 (old_agbcc -O2 -mthumb-interwork): 248 B / 184 diffs (shift-dominated).
 * Fixes vs v2: (1) shared block physically AFTER case 3 in source so mode 3
 * falls through into it (ROM: mode3 0x18dca -> shared 0x18dce, no branch;
 * v2 branched from mode3 to a trailing shared block); (2) dead load of
 * out[1] into pinned r3 forced via empty asm use (ROM loads r2 AND r3
 * after CopyMirrored, r3 never read afterwards); (3) r5 thr pin, r2 a pin kept.
 * mode0: thr=-5120 -> shared; mode1: thr=5120 -> shared; mode2: thr=15360,
 * cmp, ChipInit(70,nib,thr,-2560,s44), TestBit(s44,0)? s[13]=3 :
 * (s[10]&=~2, s[10]&=~1, s[13]=5) -> 0; mode3: thr=25600 -> shared (fallthrough);
 * shared: a<=thr -> 0 else ChipInit(69,nib,thr,-2560,s44), s[13]++ -> 0;
 * mode4: a>30720 -> 1 else fallthrough; mode5: GetField(s44)>5 -> 1 else 0;
 * default -> 0. Jump table base 0x08018d58 (raw LE words verified).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_0800DD4C(u8 *s, int a, int b);
__asm__(".set Sub_0800DD4C, 0x0800dd4c");
extern void Sub_0800DD08(u8 *d, u8 *s);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_080178A8(int a, int b, int c, int d, u32 e);
__asm__(".set Sub_080178A8, 0x080178a8");
extern u8 Sub_08017494(u32 v, int bit);
__asm__(".set Sub_08017494, 0x08017494");
extern u8 Sub_08017474(u32 v);
__asm__(".set Sub_08017474, 0x08017474");

__attribute__((section(".text.w57d_08018d18")))
int Sub_08018D18(u8 *s)
{
    int out[2];
    register int a __asm__("r2");
    register int b __asm__("r3");
    register int thr __asm__("r5");
    Sub_0800DD4C(s, *(int *)(s + 88), *(int *)(s + 92));
    *(int *)(s + 88) += *(int *)(s + 96);
    *(int *)(s + 92) += *(int *)(s + 100);
    Sub_0800DD08((u8 *)out, s);
    a = out[0];
    b = out[1];
    __asm__ volatile("" : : "r"(b));
    switch (s[13]) {
    case 0:
        thr = -5120;
        goto shared;
    case 1:
        thr = 5120;
        goto shared;
    case 2:
        thr = 15360;
        if (a <= thr)
            return 0;
        Sub_080178A8(70, ((unsigned)s[35] << 28) >> 28, thr, -2560, *(u32 *)(s + 44));
        if ((u8)Sub_08017494(*(u32 *)(s + 44), 0) != 0) {
            s[13] = 3;
            return 0;
        } else {
            s[10] &= ~2;
            s[10] &= ~1;
            s[13] = 5;
            return 0;
        }
    case 3:
        thr = 25600;
    shared:
        if (a <= thr)
            return 0;
        Sub_080178A8(69, ((unsigned)s[35] << 28) >> 28, thr, -2560, *(u32 *)(s + 44));
        s[13]++;
        return 0;
    case 4:
        if (a > 30720)
            return 1;
        /* fall through */
    case 5:
        if ((u8)Sub_08017474(*(u32 *)(s + 44)) > 5)
            return 1;
        return 0;
    default:
        return 0;
    }
}
