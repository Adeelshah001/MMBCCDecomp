extern u32 *D_082243D8[];


extern void sub_0800D9FC(u8 *s);

extern void sub_0800D9EC(u8 *s, u8 idx);

extern void sub_0800D6E0(u8 *s, u32 a, u32 b);

void sub_0801EAC4(u8 *s) {
    u8 *cur = *(u8 **)(s + 40);
    u8 old1;
    u8 old0h;
    sub_0800D9FC(s);
    if (((cur[0] >> 1) & 1) != 0) {
        if ((u8)(s[119] - 3) > 1)
            return;
        if (s[18] != 0) {
            s[18]--;
            if (s[18] != 0)
                return;
        }
        if ((cur[0] & 1) != 0) {
            u32 **base = D_082243D8;
            register u32 sh;
            u32 *slot;
            
            sh = (u32)(s[9] << 2);
            sh += (u32)base;
            slot = (u32 *)sh;
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*slot + 8);
            return;
        }
    } else {
        if (s[18] != 0) {
            s[18]--;
            if (s[18] != 0)
                return;
        }
        if ((cur[0] & 1) != 0) {
            u32 **base = (u32 **)0x082243D8;
            register u32 sh;
            u32 *slot;
            
            sh = (u32)(s[9] << 2);
            sh += (u32)base;
            slot = (u32 *)sh;
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*slot + 8);
            return;
        }
    }
    old1 = cur[1];
    {
        register u32 mm = 15;
        old0h = (u8)(cur[0] >> 4);
        cur += 4;
        *(u8 **)(s + 40) = cur;
        if (old1 == cur[1] && old0h == (u8)((cur[0] >> 4) & mm)) {
            sub_0800D9EC(s, cur[2]);
        } else {
        u16 hv;
        u8 b;
        u8 cl;
        {
            u32 v = 0x200;
            register u32 cp = v;
            
            sub_0800D6E0(s, cur[1] | cp, (u32)(cur[0] >> 4));
        }
        sub_0800D9EC(s, cur[2]);
        hv = *(u16 *)0x081705B0;
        cl = 3;
        b = *(volatile u8 *)(0x020031E4 + ((hv >> 4) << 1));
        cl &= b;
        {
            int cl2 = cl;
            int mk;
            u32 sh;
            u8 *p69;
            
            if (cl2 > 3)
                cl = 3;
            p69 = s + 69;
            sh = (u32)(cl << 2);
            mk = 13;
            
            mk = -mk;
            *p69 = (u8)((*p69 & mk) | sh);
        }
        {
            u8 tv = (u8)(s[17] + 14);
            s[34] = tv;
        }
        }
    }
    s[18] = cur[3];
}
