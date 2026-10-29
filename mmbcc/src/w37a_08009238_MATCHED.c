/* Wave 37-A v3: 0x08009238, TRUE extent 144 B (0x08009238-0x080092c8).
 * Angle: empty volatile asm barriers ("+r") to defeat gcc constant
 * folding, so base/offset stay separate pool loads + adds like ROM.
 * Fallback variant if v2's explicit pins misbehave.
 */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Sub_08002300(u32 a, u32 b);
extern void Sub_08007BEC(u32 a, u32 b);
extern void Sub_0800288C(u32 a, u32 b);
__asm__(".set Sub_08002300, 0x08002300");
__asm__(".set Sub_08007BEC, 0x08007bec");
__asm__(".set Sub_0800288C, 0x0800288c");
__attribute__((section(".text.w37a_08009238")))
void Sub_08009238(void)
{
    u8 *p = (u8 *)0x02003670;
    u8 *q;
    int m;
    u8 *r;
    __asm__ volatile("" : "+r"(p));
    p += 0x11ae;
    if ((*p & 248) != 16)
        return;
    q = (u8 *)0x02004830;
    __asm__ volatile("" : "+r"(q));
    q += 616;
    m = 15;
    __asm__ volatile("" : "+r"(m));
    *q = (*q & -m) | 2;
    r = (u8 *)0x0830b3a4;
    Sub_08002300((u32)r, 0x67a0);
    Sub_08007BEC(0x0806b2bc, 8);
    Sub_08007BEC(0x0806b560, 7);
    r += 20;
    Sub_08002300((u32)r, 0x7560);
    r = (u8 *)0x0830b64c;
    Sub_08002300((u32)r, 0x81a0);
    Sub_0800288C((u32)r + 12, 96);
}
