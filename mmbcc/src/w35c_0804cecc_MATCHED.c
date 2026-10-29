/* Wave 35-C v4: 0x0804cecc — magic via explicit v variable (adds r0,r1,#1) */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_0804C288(u8 *s, u32 base);
__asm__(".set Worker_0804C288, 0x0804c288");
__attribute__((section(".text.w35c_0804cecc")))
void Sub_0804CECC(u8 *s)
{
    register u8 *sp __asm__("r6") = s;
    u32 v = *(u32 *)(sp + 52);
    int cnt;
    u32 base;
    if (v != 0x68736d53)
        return;
    *(u32 *)(sp + 52) = v + 1;
    *(u32 *)(sp + 4) |= 0x80000000;
    cnt = sp[8];
    base = *(u32 *)(sp + 44);
    for (; cnt > 0; cnt--, base += 80)
        Worker_0804C288(sp, base);
    *(u32 *)(sp + 52) = 0x68736d53;
}
