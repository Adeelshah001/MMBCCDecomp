extern const struct ChipAnimData D_081731E0[];
extern const struct ChipAnimTable D_0817344C[];

struct ChipAnimData {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s8 unk3;
    u16 unk4;
    u8 unk6;
    u8 unk7;
};

struct ChipAnimTable {
    const u8 *data;
    u32 limit;
};

struct BattleStruct {
    u8 pad[0x14];
    short animIndex;
    u16 unk16;
    u16 unk18;
    u8 pad2[0x1A];
    u8 unk34;
    u8 unk35;
    u8 unk36;
};

void sub_0800CA10(struct BattleStruct *arg0) {
    const struct ChipAnimData *anim = &D_081731E0[arg0->animIndex];
    s8 v6, v7;
    u16 t16, t18;
    u8 cnt, idx;
    const struct ChipAnimTable *table;
    
    v6 = anim->unk6;
    t16 = arg0->unk16;
    t16 = (t16 - v6) & 0x1FF;
    arg0->unk16 = t16;
    
    v7 = anim->unk7;
    t18 = arg0->unk18;
    t18 = (t18 - v7) & 0x1FF;
    arg0->unk18 = t18;

    if (arg0->unk35 == 0) {
        cnt = ++arg0->unk34;
        idx = anim->unk1;
        table = &D_0817344C[idx];
        if (cnt >= table->limit) {
            arg0->unk34 = 0;
            cnt = 0;
        }
        arg0->unk36 = table->data[cnt];
        arg0->unk35 = anim->unk2;
    } else {
        arg0->unk35--;
    }
}
