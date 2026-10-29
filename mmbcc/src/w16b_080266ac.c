/* Wave 16 worker B: 0x080266AC (66 B).
 * Loop i = *(u16*)(s+22)-1 down to 1: v=Buf_RemoveAt_25290(s+16,i);
 * Append_0802526C(s+8,v); *(*(s+4)+v*28+25) = 0.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


u8 Buf_RemoveAt_25290(u8 *p, u16 idx);
int Append_0802526C(void *s, u8 v);

void Sub_266AC(u8 *s) __attribute__((section(".text.w16b_080266ac")));
void Sub_266AC(u8 *s)
{
    u16 i = *(u16 *)(s + 22) - 1;
    while (i != 0) {
        u8 v = Buf_RemoveAt_25290(s + 16, i);
        Append_0802526C(s + 8, v);
        *(*(u8 **)(s + 4) + v * 28 + 25) = 0;
        i--;
    }
}



__attribute__((section(".text"))) static const u16 w16b_080266ac_pad = 0;