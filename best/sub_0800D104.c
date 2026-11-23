extern u16 D_020031E0;

struct UnkStruct {
    u8 unk[0x0A];
};

void sub_0800D104(struct UnkStruct *arg0) {
    u16 val = 0xEDFF;
    u8 tmp;
    u8 neg3;
    
    val &= D_020031E0;
    val &= 0xDBFF;
    D_020031E0 = val;
    
    neg3 = 3;
    neg3 = -neg3;
    tmp = arg0->unk[0x09];
    tmp &= neg3;
    arg0->unk[0x09] = tmp;
}
