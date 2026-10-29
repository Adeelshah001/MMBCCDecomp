/* Wave 16 worker B: 0x0802666C (62 B).
 * If idx != 0 and idx < *(u16*)(s+22): v=Buf_RemoveAt_25290(s+16,idx);
 * Append_0802526C(s+8,v); *(*(s+4)+v*28+25) = 0.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


u8 Buf_RemoveAt_25290(u8 *p, u16 idx);
int Append_0802526C(void *s, u8 v);

void Sub_2666C(u8 *s, u16 idx) __attribute__((section(".text.w16b_0802666c")));
void Sub_2666C(u8 *s, u16 idx)
{
    u8 v;
    if (idx == 0)
        return;
    if (idx >= *(u16 *)(s + 22))
        return;
    v = Buf_RemoveAt_25290(s + 16, idx);
    Append_0802526C(s + 8, v);
    *(*(u8 **)(s + 4) + v * 28 + 25) = 0;
}



__attribute__((section(".text"))) static const u16 w16b_0802666c_pad = 0;