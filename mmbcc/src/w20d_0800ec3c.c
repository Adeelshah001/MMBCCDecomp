/* Wave 20-D @0x0800EC3C (64 B). MATCHED with main agbcc.
 * Twin of 0x0800EB30: calls Setup_0801009C(a-f); if (s8)result==1,
 * calls SetByte20_Clear21to23_02005130(11) and returns 1; else returns result.
 */
typedef unsigned char u8;
typedef signed char s8;

extern u8 Setup_0801009C(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f);
extern void SetByte20_Clear21to23_02005130(u8 v);

__attribute__((section(".text.w20d_0800EC3C")))
s8 F_0800EC3C(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f)
{
    s8 r = (s8)Setup_0801009C(a, b, c, d, e, f);
    if (r == 1) {
        SetByte20_Clear21to23_02005130(11);
        return 1;
    }
    return r;
}
