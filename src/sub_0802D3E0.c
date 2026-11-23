struct BattleChipEntry2D3E0 {
    u16 id;
    signed short power;
};
extern void sub_0802D7A0(void *, u8, u8, u8, u8, u16, signed short, signed short, u8, u8);

int sub_0802D3E0(u8 *battle, u8 side, u8 slot)
{
    const struct BattleChipEntry2D3E0 **chips;
    u8 otherSide = side == 0;

    if (side == 0)
        chips = (const struct BattleChipEntry2D3E0 **)(battle + 0x150);
    else
        chips = (const struct BattleChipEntry2D3E0 **)(battle + 0x16C);
    sub_0802D7A0(battle, side, slot, otherSide, 2, 0, chips[slot]->power, chips[slot]->power, 0x1B, 5);
    return 0;
}

