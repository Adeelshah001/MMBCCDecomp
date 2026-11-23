struct BattleLogEntry {
    u8 a0:1;
    u8 a1:1;
    u8 a2:6;
    u8 pad1[3];
    u8 b0:1;
    u8 b1:1;
    u8 b2:6;
    u8 pad2[3];
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u8 unkE;
    u8 unkF;
};

struct BattleState {
    u8 unk00[5];
    u8 logCount;
    u8 unk06[0x19E];
    struct BattleLogEntry entries[50];
};

void sub_08029504(struct BattleState *s)
{
    u8 i;

    for (i = 0; i < s->logCount; i++) {
        s->entries[i].unkE = 0xFF;
        s->entries[i].unkC = 0;
        s->entries[i].unkA = 0;
        s->entries[i].b2 = 0;
        s->entries[i].b1 = 0;
        s->entries[i].b0 = 0;
        s->entries[i].a2 = 0;
        s->entries[i].a1 = 0;
        s->entries[i].a0 = 0;
        s->entries[i].unkF = 10;
    }
    s->logCount = 0;
}
