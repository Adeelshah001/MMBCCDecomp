extern u8 sub_080496E8(u8 a, u8 b);
extern u8 D_082344D6[];
extern u8 D_020070F0[];

u8 sub_08049704(u8 x)
{
    u8 *base = D_020070F0;
    u8 ok = 1;
    u8 i;

    if (x <= 4) {
        for (i = 0; i < D_082344D6[x]; i++) {
            u8 v = sub_080496E8(x, i);
            u32 t = (u32)(base + v * 12);
            t = *(u16 *)(t + 0x32);
            if (t <= 0xFC)
                ok = 0;
        }
    } else {
        u8 v = sub_080496E8(x, 0);
        u32 t = (u32)(base + v * 12);
        t = *(u16 *)(t + 0x32);
        if (t != 0xFF)
            ok = 0;
    }
    return ok;
}
