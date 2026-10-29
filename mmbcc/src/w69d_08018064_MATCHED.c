/* 0x08018064, first C form from fresh ROM decode. TRUE extent 328 B
 * (326 code through bx @0x181a8 + 2 pad to next fn @0x181ac).
 * Calls: Sub_0800DD4C(s, s[88], s[92]); s[88]+=s[96]; s[92]+=s[100];
 * Sub_0800DD08(&v, s) fills Pair v (sp+4/sp+8); px=v.x, py=v.y (py dead load).
 * s[16]==2: switch s[13]: 0: px<=11520 -> ret 0 else Draw(62, nibble(s[35]), 15360, -7680, s[44]);
 * 1: px<=30720 -> ret 0 else s[88]=-1536, s[96]=0, bit-toggle, s[13]++;
 * 2: px>11519 -> ret 0 else Draw(63, nibble, 15360, -7680, s[44]);
 * 3: px>=-11008 -> ret 0 else ret 1. s[16]!=2: switch s[13]:
 * 0: px<=34560 -> ret 0 else toggle, s[88]=-1786, s[96]=0, s[13]++;
 * 1: px>=-12800 -> ret 0 else ret 1. Success paths s[13]++ then ret 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct { s32 x, y; } Pair;

void Sub_0800DD4C(u8 *s, u32 a, u32 b);
void Sub_0800DD08(u32 *out, u8 *s);
void Sub_080178A8(int a, u32 b, int c, s32 d, u32 e);

__attribute__((section(".text.w69d_08018064")))
u8 sub_08018064(u8 *s)
{
    volatile Pair v;
    s32 px;
    register s32 py __asm__("r2");

    Sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Sub_0800DD08((u32 *)&v, s);
    px = v.x;
    py = v.y;
    if (s[16] == 2) {
        switch (s[13]) {
        case 0:
            if (px <= 11520)
                goto ret0;
            Sub_080178A8(62, ((u32)s[35] << 28) >> 28, 15360, -7680, *(u32 *)(s + 44));
            break;
        case 1:
            if (px <= 30720)
                goto ret0;
            *(u32 *)(s + 88) = -1536;
            *(u32 *)(s + 96) = 0;
            { u8 tb = ((s[10] >> 4) ^ 1) & 1;
            u8 nv;
            s[72] = tb;
            if (tb != 0)
                nv = s[10] | 16;
            else
                nv = s[10] & 239;
            s[10] = nv; }
            break;
        case 2:
            if (px > 11519)
                goto ret0;
            Sub_080178A8(63, ((u32)s[35] << 28) >> 28, 15360, -7680, *(u32 *)(s + 44));
            break;
        case 3:
            if (px >= -11008)
                goto ret0;
            return 1;
        default:
            goto ret0;
        }
        s[13]++;
        goto ret0;
    } else {
        switch (s[13]) {
        case 0:
            if (px <= 34560)
                goto ret0;
            { u8 tb = ((s[10] >> 4) ^ 1) & 1;
            u8 nv;
            s[72] = tb;
            if (tb != 0)
                nv = s[10] | 16;
            else
                nv = s[10] & 239;
            s[10] = nv; }
            *(u32 *)(s + 88) = -1786;
            *(u32 *)(s + 96) = 0;
            break;
        case 1:
            if (px >= -12800)
                goto ret0;
            return 1;
        default:
            goto ret0;
        }
        s[13]++;
        goto ret0;
    }
ret0:
    return 0;
}

__asm__(".balign 4, 0");

__asm__(
    ".globl Sub_0800DD4C\n.set Sub_0800DD4C, 0x0800dd4c\n"
    ".globl Sub_0800DD08\n.set Sub_0800DD08, 0x0800dd08\n"
    ".globl Sub_080178A8\n.set Sub_080178A8, 0x080178a8\n"
);
