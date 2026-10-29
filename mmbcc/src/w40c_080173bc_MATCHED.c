/* W40-C v3: pinned-barrier scheduling (cf. w20c_080173d4): pin base -> r2
 * plus a barrier on base before the s[9] load forces the pool load first.
 */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w40c_080173bc")))
void Sub_080173BC(u8 *s)
{
    register u32 base __asm__("r2") = 0x082243D8;
    register u32 idx __asm__("r3");
    u32 off;
    u32 *e;
    __asm__ volatile("" : "+r" (base));
    idx = s[9];
    off = idx << 2;
    e = (u32 *)(off + base);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*e + 16);
}
