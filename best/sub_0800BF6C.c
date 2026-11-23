struct Unk02004F40 {
    u8 unk00[4];
    s8 unk04;
    u8 unk05;
    u8 unk06[5];
    u8 unk0B;
    u8 unk0C[0x0F];
    u8 unk1B;
};

extern struct Unk02004F40 D_02004F40;

void sub_0800BF6C(u16 arg0, u8 arg1)
{
    struct Unk02004F40 *s = &D_02004F40;
    if (s->unk04 != (short)arg0)
    {
        s->unk05 = arg0;
        if (arg1 == 0x80)
        {
            int v1 = 3;
            v1 &= s->unk0B;
            s->unk0B = v1 | 0x80U;
            {
                int v2 = -7;
                v2 &= s->unk1B;
                s->unk1B = v2;
            }
        }
        else
        {
            if (arg1 > 0x80)
            {
                int v3 = 8;
                v3 |= s->unk1B;
                s->unk1B = v3;
            }
            else
            {
                int v3 = -9;
                v3 &= s->unk1B;
                s->unk1B = v3;
            }
            {
                int v4 = -7;
                v4 &= s->unk1B;
                v4 |= 4;
                s->unk1B = v4;
            }
        }
    }
}
