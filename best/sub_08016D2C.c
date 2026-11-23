struct BattleObjectInitData {
    u32 unknown;
    u32 value;
};

extern const struct BattleObjectInitData *const D_08223CC0[];
extern const u16 D_081705B0[];
extern u16 D_020031E4[];
extern void sub_08016DAC(u8 *object);

void sub_08016D2C(u8 *object)
{
    u8 *params = object + 0x7C;
    const struct BattleObjectInitData *const *table = D_08223CC0;
    const struct BattleObjectInitData *const *entry = table + object[9];
    int flags;
    int level;
    u8 *attributes;
    int mask;

    *(u32 *)(object + 0x0C) = 1;
    *(u32 *)(object + 0x14) = (*entry)->value;
    if (params[4] == 1)
        object[0x0D] = params[5];

    *(u32 *)(object + 0x6C) = 0;
    flags = 2;
    flags |= object[0x0A];
    flags |= 1;
    object[0x0A] = flags;

    level = 3;
    level &= *(u8 *)&D_020031E4[D_081705B0[0] >> 4];
    if (level > 3)
        level = 3;
    attributes = object + 0x45;
    level *= 4;
    mask = ~0x0C;
    mask &= *attributes;
    *attributes = mask | level;
    object[0x22] = 0x10;
    sub_08016DAC(object);
}
