extern void sub_08008030(u32 a, u32 b, u32 c, u32 d, u32 e);
extern void sub_080105A4(u32 a, u32 b);

void sub_0801054C(void *arg0)
{
    u32 saved_arg0 = (u32)arg0;
    u32 val = 0xE;
    u8 *ptr = (u8 *)(0x02003670 + 0x11AE);
    u32 base = 0x02005168;
    
    if ((4 & *ptr) != 0) {
        val = 0xF;
    }
    
    sub_08008030(0, val, 0, 0, (u32)((u8 *)saved_arg0)[0x3A]);
    
    sub_080105A4(base, 0);
    sub_080105A4(base + 0x14, 1);
}
