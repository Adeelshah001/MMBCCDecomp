extern short sub_0800EA4C(u8);
extern s8 sub_0800EAB4(void);
extern s8 sub_0800EC7C(u8, u32, short, short, short, short, s8);
extern u32 sub_0800ECD8(u32, u8);
extern s8 sub_0800ECF8(u8, u32, u8, s8);
extern s8 sub_0800ED20(u32, u32, short, s8);
extern void sub_0800EE8C(void);
extern void sub_0804AD24(void);
extern s8 sub_0804AD3C(void);
extern void sub_0804A3FC(void);
extern s8 sub_0804A40C(void);
extern u8 sub_0804A3F0(void);
extern u16 sub_08024554(u8);
extern u8 sub_080242A8(u16, u16);
extern u32 sub_08034F2C(u8 *, u8);
extern short sub_0800303C(u16);
extern u8 sub_08034DB8(u8 *, u8);
extern u8 TryAddChipToInventory(int);
extern u32 sub_080246A8(u16);
extern u8 sub_08024384(u16);
extern u8 sub_080241F8(u16);
extern u16 sub_08024514(u8);
extern void sub_08004E24(u8);
extern int sub_08004E0C(u8);

int sub_080344F0(u8 *state)
{
    int result = 0;
    u8 side = state[4];
    u16 deck;
    int flag;
    int messageIndex;
    const u32 *messages;

    side = (side >> 4) - 1;
    deck = side == 0 ? *(u16 *)(state + 0x14) : *(u16 *)(state + 0x16);

    if (state[3] == 0) {
        int mask = 0x10;
        mask &= state[6];
        if (!mask)
            state[3] = 4;
    }

    switch (state[3]) {
    case 0:
        sub_0800EA4C(0);
        state[6] |= 0x80;
        sub_0804AD24();
        goto advance;
    case 1:
        sub_0800EA4C(0);
        if (sub_0804AD3C() == -1)
            break;
        state[6] &= 0x7F;
        goto advance;
    case 2:
        sub_0804A3FC();
        sub_0800EA4C(0);
        goto advance;
    case 3:
        if (sub_0804A40C() == -1)
            goto update;
        goto advanceAndUpdate;
    case 4: {
        u16 *record;
        u16 *total;
        if (state[6] & 0x10) {
            total = (u16 *)0x020070F0;
            if (sub_0804A3F0() == 0) {
                if (side == 0) {
                    state[3]++;
                    record = (u16 *)((u8 *)total + 0x378);
                    goto win;
                }
                result = 1;
            } else {
                if (side == 1) {
                    state[3]++;
                    record = (u16 *)((u8 *)total + 0x378);
win:
                    if (*record < 999)
                        ++*record;
                    total += 0x18 / 2;
                    if (*total < 9999)
                        ++*total;
                    goto update;
                }
                result = 1;
            }
            record = (u16 *)((u8 *)total + 0x37A);
            if (*record < 999)
                ++*record;
            total += 0x1A / 2;
            if (*total < 9999)
                ++*total;
            goto update;
        }
        if (*(u16 *)(state + 0x14) == 0x1000) {
            if (side == 0)
                goto advanceAndUpdate;
            if (state[0xB] != 4) {
                state[3] = 13;
                goto update;
            }
        }
        result = 1;
        goto update;
    }
    case 5: {
        u8 slot, count;
        short first = sub_08024554(0x73);
        count = 0;
        for (slot = 1; slot <= 11; slot++)
            if (sub_080242A8(deck, slot) == 0x73)
                count++;
        if (count != 0 && sub_0800EC7C(0, 0x0822DF18, 0x73, first, first, first, 0) != 1)
            goto update;
        goto advanceAndPoll;
    }
    case 7: {
        u8 slot;
        if ((s8)sub_0800ECD8(0x0822DEC8, 0) != 1)
            goto update;
        slot = sub_08034F2C(state, side);
        if (slot == 11)
            sub_0800B3F8(0, *(const u32 *)0x0822DEFC, 0);
        else
            sub_0800B448(0, slot, 0);
        goto advanceAndPoll;
    }
    case 9: {
        u16 award;
        u8 slot;
        u32 *money;
        u32 value;
        if (sub_0800EC7C(side, 0x0822DED0, 0xC3, 10, 10, 10, 0) != 1)
            goto update;
        slot = sub_08034F2C(state, side);
        award = ((const u16 *)0x0822E69C)[slot - 1];
        sub_0800B448(0, award, 0);
        money = (u32 *)(0x020070F0 + 0x20);
        value = *money + award;
        if (value > 9999990)
            value = 9999990;
        *money = value;
        sub_0800303C(0x74);
        state[3]++;
    }
        /* fall through */
    case 10:
        if ((u8)sub_0800EA4C(0) == 1)
            break;
        state[0x10] = sub_08034DB8(state, side);
        if (state[0x10] && TryAddChipToInventory(state[0x10]))
            goto advance;
        result = 1;
        break;
    case 11: {
        short first, second, third;
        first = sub_08024554(state[0x10]);
        second = sub_08024554(state[0x10]);
        third = sub_08024554(state[0x10]);
        if (sub_0800EC7C(side, 0x0822DEDC, state[0x10], first, second, third, 0) != 1)
            goto update;
        sub_0800303C(0x75);
        sub_0800B3F8(0, sub_080246A8(state[0x10]), 0);
        goto advanceAndUpdate;
    }
    case 12:
        if ((u8)sub_0800EA4C(0) != 1)
            result = 1;
        break;
    case 13: {
        u8 slot;
        u32 value;
        short first;
        slot = sub_08024384(0x1000) - 50;
        value = ((const u32 *)0x0822E7BC)[slot];
        first = sub_08024514(sub_080241F8(0x1000));
        if (sub_0800ED20(value, 0x0822DF28, first, 0) != 1)
            goto update;
        sub_0800EE8C();
        goto advanceAndUpdate;
    }
    case 14:
        if ((u8)sub_0800EA4C(0) == 1)
            break;
        if (sub_0800EAB4() != 0)
            goto advance;
        state[3] = 19;
        break;
    case 15:
        messageIndex = (u8)(sub_08024384(0x1000) - 50);
        flag = 0;
        if ((state[6] & 0x10) && sub_0804A3F0() == 1)
            flag = 1;
        messages = (const u32 *)0x0822E72C;
        goto showMessage;
    case 17:
        sub_08004E24(0);
        state[3]++;
        /* fall through */
    case 18:
        sub_0800EA4C(0);
        if ((u8)sub_08004E0C(3) == 0)
            break;
        *(u16 *)0x020031E0 &= 0xEDFF;
        *(u16 *)0x020031E0 &= 0xDBFF;
        result = 3;
        break;
    case 19:
        messageIndex = (u8)(sub_08024384(0x1000) - 50);
        flag = 0;
        if ((state[6] & 0x10) && sub_0804A3F0() == 1)
            flag = 1;
        messages = (const u32 *)0x0822E6FC;
showMessage:
        if (sub_0800ECF8(flag, messages[messageIndex], messageIndex, 0) == 1)
            goto advanceAndUpdate;
        goto update;
    case 6:
    case 8:
    case 16:
    case 20:
advanceAndPoll:
        if ((u8)sub_0800EA4C(0) == 1)
            break;
advance:
        state[3]++;
        break;
    case 21:
        sub_08004E24(0);
        state[3]++;
        /* fall through */
    case 22:
        sub_0800EA4C(0);
        if ((u8)sub_08004E0C(3) == 0)
            break;
        *(u16 *)0x020031E0 &= 0xEDFF;
        *(u16 *)0x020031E0 &= 0xDBFF;
        result = 2;
        break;
    }
    return result;

advanceAndUpdate:
    state[3]++;
update:
    sub_0800EA4C(0);
    return result;
}
