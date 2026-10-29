/* W52-D 0x08011560 v6 (v5 + shift-compare + split-n tail) (corrects W38 partial note: the
 * -2 path's b>0 arm does NOT call (2,255,2); (255,2) are the shared
 * block's incoming args for the second call).
 * TRUE extent 252 B (bx 0x0801165a via pop {r1}/bx r1 — returns a value;
 * next fn 0x0801165c, no pad, no pools).
 * s: struct; r4 = *(u8 **)s. Returns 0 (first block) or -1 (else block).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_08010AD8(int a, int b, int c);
extern s16 Sub_0804A340(void);
extern void Sub_0804A328(void);
extern void Sub_0804A2DC(u16 a);
extern void Sub_08010DDC(int a);
extern void Sub_0804A378(u16 a);
__asm__(".set Sub_08010AD8, 0x08010ad8");
__asm__(".set Sub_0804A340, 0x0804a340");
__asm__(".set Sub_0804A328, 0x0804a328");
__asm__(".set Sub_0804A2DC, 0x0804a2dc");
__asm__(".set Sub_08010DDC, 0x08010ddc");
__asm__(".set Sub_0804A378, 0x0804a378");

__attribute__((section(".text.w52d_08011560")))
int Sub_08011560(u8 *s)
{
    u8 *r4 = *(u8 **)s;
    u16 x;
    int a1, a2;
    int tailval;
    if (s[5] != 0)
        goto else_block;
    s[5]++;
    if (*(s16 *)(s + 12) == -2) {
        x = r4[12];
        if ((s8)r4[12] > 0) {
            a1 = 255;
            a2 = 2;
            goto shared;
        } else {
            Sub_08010AD8(2, -1, 2);
            tailval = 2;
            goto tail;
        }
    }
    x = r4[12];
    if ((s8)r4[12] <= 0)
        goto else_block;
    a1 = 255;
    a2 = 255;
    goto shared;
shared:
    {
        u8 t11 = r4[11];
        s8 sb11 = r4[11];
        if (sb11 != 0)
            a1 = (u8)(t11 - 1);
    }
    if ((r4[10] & 7) != 0)
        a2 = (u8)((r4[10] & 7) - 2);
    Sub_08010AD8((u8)(x - 1), (s8)a1, (s8)a2);
    tailval = (s8)r4[12] - 1;
tail:
    *(s16 *)(s + 12) = tailval;
    s[34] = 1;
    return 0;
else_block:
    if (r4[8] != 0) {
        x = (u16)(((u8 *)*(u32 *)s)[8] - 1);
        if ((Sub_0804A340() << 16) != (x << 16)) {
            Sub_0804A328();
            if (x != 0)
                Sub_0804A2DC((u16)(((u8 *)*(u32 *)s)[8] - 1));
        }
    }
    if ((r4[10] & 16) != 0)
        Sub_08010DDC(16);
    if (r4[9] != 0)
        Sub_0804A378((u16)(((u8 *)*(u32 *)s)[9] - 1));
    {
        u8 n = s[4] + 1;
        int z = 0;
        s[4] = n;
        s[5] = z;
        s[6] = z;
        s[7] = z;
        return z - 1;
    }
}
