void sub_0800D728(u8 *sprite, int id, int frame);
void sub_0800D9EC(u8 *arg0, int arg1);

struct SubStruct {
    u8 pad[7];
    u8 unk7;
};

struct MainStruct {
    u8 pad0[0x0A];
    u8 unkA;
    u8 padB[0x07];
    u8 unk12;
    u8 unk13;
    u8 pad14[0x0E];
    u8 unk22;
    u8 pad23[0x05];
    struct SubStruct *unk28;
    u8 pad2C[0x19];
    u8 unk45;
    u8 pad46[0x0A];
    u32 unk50;
    u32 unk54;
    u8 pad58[0x14];
    u32 unk6C;
};

void sub_0801F9EC(u8 *arg0) {
    struct MainStruct *s = (struct MainStruct *)arg0;
    struct SubStruct *r5 = s->unk28;
    u32 r0, r1, r2, r3;
    
    s->unk6C = 0;
    r0 = 2;
    r1 = s->unkA;
    r0 |= r1;
    r1 = 1;
    r0 |= r1;
    s->unkA = r0;
    sub_0800D728(arg0, 0x3D17, 0);
    sub_0800D9EC(arg0, 0);
    
    r0 = *(u16 *)0x081705B0;
    r0 >>= 4;
    r0 *= 2;
    r1 = 0x020031E4;
    r0 += r1;
    r1 = *(u8 *)r0;
    r1 &= 3;
    if ((s8)r1 > 3) r1 = 3;
    
    r2 = (u32)s + 0x45;
    r3 = *(u8 *)r2;
    r0 = -0xD;
    r0 &= r3;
    r1 <<= 2;
    r0 |= r1;
    *(u8 *)r2 = r0;
    
    r0 = (u32)s + 0x22;
    r1 = 0;
    *(u8 *)r0 = r1;
    s->unk50 = r1;
    s->unk54 = r1;
    s->unk12 = 0x40;
    s->unk13 = 0x10;
    r5->unk7 = r1;
}
