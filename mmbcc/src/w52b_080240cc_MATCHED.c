/* W52-B FINAL (candidate): 0x080240cc, 224 B EXACT, 0 diffs, OLD agbcc
 * -O2 -mthumb-interwork, linked-at-address. Verified this wave, fresh build.
 * Copy loop: goto entry-check + while, s16 counter ci (ROM: signed bgt +
 * lsl/asr #16); dst loaded after entry check; compiler (old) rotates to
 * ROM-exact in-line entry + body + bounds + mask-check layout, pool at end,
 * no unconditional mid-function jump. Loop-1/loop-2 counters u16 i (bls).
 * Loop-1 is a genuine 4-arg call: Sub_08024B3C(u8,u8,u8,u8) per its MATCHED
 * source (W36); 4th arg (u8)i puts r3=(u8)i at bl exactly as ROM (v6 3-arg
 * call passed a stale r3 and MUST NOT LAND). Loop-2/finals 4-arg as ROM.
 * Sub_08023E34 takes the base variable (adds r0,r7), not the literal.
 * No register pins, no volatile/asm tricks in this file (only .set
 * absolutes for callees, all MATCHED in registry except 23e34 itself).
 * Args: a (r6), idx (r4, u8). */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_0802541C(u32 a, u32 b, u32 c);
__asm__(".set Sub_0802541C, 0x0802541c");
extern u8 Sub_08024500(u8 a);
__asm__(".set Sub_08024500, 0x08024500");
extern void Sub_080260D4(u32 a, u8 b, u8 c);
__asm__(".set Sub_080260D4, 0x080260d4");
extern void Sub_08026184(u32 a, u32 b);
__asm__(".set Sub_08026184, 0x08026184");
extern void Sub_08023E34(u32 a);
__asm__(".set Sub_08023E34, 0x08023e34");
extern void Sub_08024B3C(int a, u8 b, int c, u8 d);

extern void Sub_08024E2C(int a, u8 b, int c, int d);


__attribute__((section(".text.w52b_080240cc")))
void Sub_080240CC(u16 *a, u8 idx)
{
    u32 *base = (u32 *)0x02007090;
    u32 p;
    u8 t;
    u16 i;
    Sub_0802541C(0x02007090, 0x08227210, 0x1B1);
    p = base[5];
    t = Sub_08024500(idx);
    Sub_080260D4(p, t, *(u8 *)(0x08227404 + idx));
    {
        u16 *dst;
        s16 ci;
        ci = 0;
        if ((a[0] & 32768) != 0)
            goto cdone;
        dst = (u16 *)(base[14]);
        while (ci <= 3 && !(a[ci] & 32768)) {
            dst[ci] = a[ci];
            ci++;
        }
    cdone:;
    }
    Sub_08026184(0x020070A8, base[14]);
    Sub_08023E34((u32)base);
    for (i = 0; i <= 29; i++)
        Sub_08024B3C(0, (u8)i, 0, (u8)i);
    for (i = 0; i <= 8; i++)
        Sub_08024E2C(1, (u8)i, 1, (u8)i);
    Sub_08024E2C(1, 10, 1, 10);
    Sub_08024E2C(1, 11, 1, 11);
}
