/* Wave 36-D MATCHED (C + .s patch w36d_08022290_patch.py, old_agbcc, 0 diffs over 144 B true extent 0x08022290-0x08022320; goto-dispatch fallthrough, table pools upfront + pool order swap, final byte load to r1), 144 B, extent next-func 0x08022320. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 Sub_080225B4(u32 a, u32 b);
__asm__(".set Sub_080225B4, 0x080225b4");
extern void Sub_080224E4(u32 a, u32 b, u32 c, u32 d);
__asm__(".set Sub_080224E4, 0x080224e4");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w36d_08022290")))
void Sub_08022290(u8 *s)
{
    u8 *r6 = *(u8 **)(s + 40);
    if (s[13] != 0) goto end;
    if (s[14] == 0) goto set14;
    if (s[14] == 1) goto dec18;
    goto end;
set14:
    s[14] = 1;
    s[18] = (s[17] << 3) + 60;
dec18:
    s[18]--;
    if ((u8)s[18] > 59) goto end;
    {
        u8 *base1 = (u8 *)0x081738f2;
        u8 *base2 = (u8 *)0x082270b0;
        u16 hv = *(u16 *)(base2 + (s[17] << 1));
        u8 b = *(u8 *)(base1 + ((hv >> 8) << 1));
        u32 res = Sub_080225B4(((u32)s[17] + 3) | hv, 0);
        Sub_080224E4(b, res, 0x082270d4, s[18] >> 2);
    }
    if (s[18] != 0) goto end;
    s[13]++;
    s[14] = 0;
    {
        register u8 bv __asm__("r1") = r6[19];
        r6[19] = (1 << s[17]) | bv;
    }
end:
    Sub_0800D9FC(s);
}
