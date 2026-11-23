typedef signed short s16;

struct Unknown0200B810 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 b0:3;
    u8 b3:1;
    u8 b4:1;
    u8 b5:1;
    u8 b6:1;
    u8 b7:1;
    u8 unk7;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC[5];
    u8 unk11;
    u8 unk12[2];
    s16 unk14;
    s16 unk16;
    u8 unk18[5];
    u8 unk1D;
};

extern struct Unknown0200B810 D_0200B810;

void sub_08028880(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5)
{
    struct Unknown0200B810 *s = &D_0200B810;

    s->unk0 = 0;
    s->unk1 = 0;
    s->unk2 = 0;
    s->unk3 = 0;
    s->unk1D = arg2;
    s->unk14 = arg0;
    s->unk16 = arg1;
    s->unk11 = arg5;
    ((u8 *)s)[6] = 0;

    if (arg3 & 1) {
        s->b3 = 1;
    } else {
        s->b3 = 0;
        s->unk7 = 0;
        s->unkA = arg4;
    }

    if ((u8)(arg3 & 2)) {
        s->unkB = 4;
    } else {
        s->unkB = 0;
    }

    if (arg3 & 4) {
        int v = 0x10;
        v |= ((u8 *)s)[6];
        ((u8 *)s)[6] = v & 0x7F;
    } else {
        int v = 0xEF;
        v &= ((u8 *)s)[6];
        ((u8 *)s)[6] = v;
    }

    if (arg3 & 8) {
        int v = 0x20;
        v |= ((u8 *)s)[6];
        ((u8 *)s)[6] = v;
    }
}
