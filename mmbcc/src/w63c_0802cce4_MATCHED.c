/* W59-B C2 (A1 + while(i>2) loop ONLY): 0x0802cce4.
 * Changes vs v1: (1) loop keeps slot=&t2[i] (r6) across calls, entry is
 * reloaded from *slot after each call (ROM never keeps entry in a reg
 * across a call); (2) Obj_AddEntry args 7/8 declared s16 so the (s16)f2
 * loads stay ldrsh (v1's u16 params collapsed them to ldrh); (3) flag
 * param int (ROM passes it unmasked in r3).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_0802D7A0(u8 *s, u8 a, u8 b, int flag, int a5, u16 a6, int a7, s16 a8, int a9, int a10);
__asm__(".set Sub_0802D7A0, 0x0802d7a0");
extern u8 Sub_0802C7B4(int a, u16 *p);
__asm__(".set Sub_0802C7B4, 0x0802c7b4");
extern void Sub_0802FC28(void **ctx, u8 *out);
__asm__(".set Sub_0802FC28, 0x0802fc28");

__attribute__((section(".text.w63c_0802cce4")))
int Sub_0802CCE4(u8 *s, u8 p1, u8 p2, u16 p3, u8 p4)
{
    int flag;
    u8 **t1;
    u8 **t2;
    int mode;
    u8 cnt;
    u8 *bp;
    int bval;
    u8 **slot;
    int f;
    u8 i;

    {
        int ftmp = (p1 == 0);
        flag = ftmp;
    }
    t1 = (u8 **)(p1 == 0 ? s + 336 : s + 364);
    t2 = (u8 **)(p1 == 0 ? s + 364 : s + 336);
    cnt = 0;
    bp = (p1 == 0) ? s + 393 : s + 392;
    bval = *bp;
    {
        int c = s[6] & 1;
        mode = 9;
        if (c == 0)
            mode = 5;
    }
    if (p4 != 0)
        p3 = p3 * p4;
    Sub_0802D7A0(s, p1, p2, flag, 2, p3, *(s16 *)(t1[p2] + 2), *(s16 *)(t1[p2] + 2), 27, mode);
    i = 5;
    while (i > 2) {
        slot = (u8 **)((i * 4) + (int)t2);
        if (*(s16 *)(*slot + 2) != 0) {
            f = *(u16 *)(*slot + 2);
            cnt = cnt + 1;
            Sub_0802C7B4((s16)p3, (u16 *)(*slot + 2));
            Sub_0802D7A0(s, p1, p2, flag, i, p3, ({ __asm__ volatile("lsl %0, %0, #16\n\tasr %0, %0, #16" : "+r"(f)); f; }), *(s16 *)(*slot + 2), 28, mode);
            f = *(s16 *)(*slot + 2);
            if (f == 0) {
                Sub_0802D7A0(s, p1, p2, flag, i, p3, f, f, 24, mode);
                if (i == bval) {
                    Sub_0802D7A0(s, p1, p2, flag, i, f, f, f, 14, mode);
                    Sub_0802D7A0(s, p1, p2, flag, i, f, *(s16 *)(*slot + 2), *(s16 *)(*slot + 2), 78, mode);
                    Sub_0802FC28((void **)(t2 + 6), bp);
                }
            }
            break;
        }
        i = i - 1;
    }
done:
    if (cnt == 0) {
        Sub_0802D7A0(s, p1, p2, flag, 2, cnt, cnt, cnt, 29, mode);
    }
    return 0;
}

/* Trailing pad: code size is 2 mod 4; the next function is 4-aligned. */
__asm__(".balign 4, 0");
