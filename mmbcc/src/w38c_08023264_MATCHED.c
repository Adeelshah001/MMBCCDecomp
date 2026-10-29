/* W38-C: 0x08023264, TRUE extent 20 B (next fn 0x08023278).
 * *(u32*)(s+108) = 0; s[10] = (s[10] | 2) & 254 (stepwise).
 */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w38c_08023264")))
void Sub_08023264(u8 *s)
{
    u8 t;
    *(u32 *)(s + 108) = 0;
    t = s[10] | 2;
    s[10] = t & 254;
}
__asm__(".hword 0");
