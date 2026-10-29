/* Wave 17 worker C: table/state functions. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef signed char s8; typedef signed short s16;

extern int TblValidate_300C(u16 a);
extern void Text_SelectBlobU16(u16 a);
extern void F_08002FD4(u16 a);
extern void FlagBit_Set_11D68(u16 x, u8 y);
extern u32 FlagBit_Get_11D34(u16 x);
extern u16 TableLookup_U16(u8 a0, u8 a1);
extern u8 *TableLookup_11C80(u16 idx);
extern u8 TblByte_11DB0(u16 idx);
extern u8 TblLookup_25730(u8 *tbl, u8 idx);
extern u32 SumStrides_25754(u8 *tbl);
extern u32 AddTbl_S14(u8 *s);
extern u8 TblGet_25654(u8 *base, u8 idx);
extern void SetU8_Off1(u8 *p, u8 v);
extern void StoreIdx2_25638(u8 *p, u8 idx, u8 val);

/* 0x0804a2dc (70 B): TblValidate + Text_Select/F_08002FD4 dispatch. */
__attribute__((section(".text.w17c_0804a2dc")))
void TblState_0804A2DC(u16 a)
{
    u16 *p = (u16 *)0x0200BD10;
    if (p[1] != 0) {
        int v = TblValidate_300C(a);
        if (v != 0)
            goto Lend;
        if (p[1] != 0) {
            if (TblValidate_300C(p[0]) != 0) {
                F_08002FD4(p[0]);
                p[1] = v;
            }
        }
    }
    Text_SelectBlobU16(a);
    {
        u16 *q = (u16 *)0x0200BD10;
        q[1] = 1;
        q[0] = a;
    }
Lend:;
}

/* 0x080112fc (248 B): flag-init + table walk. */
__attribute__((section(".text.w17c_080112fc")))
u16 Search_080112FC(u8 a, u8 b)
{
    u16 i = 3;
    u16 cur;
    u8 *p;
    do {
        if (a + 3 == i)
            FlagBit_Set_11D68(i, 1);
        else
            FlagBit_Set_11D68(i, 0);
        i++;
    } while (i <= 8);
    cur = TableLookup_U16(a, b);
    if (cur == 0)
        return 0;
    goto loop;
adv:
    if (*(s16 *)(p + 4) == 0)
        return 0;
    cur = *(u16 *)(p + 4);
loop:
    p = TableLookup_11C80(cur);
    {
        s8 v0 = (s8)p[0];
        if (v0 > 0) {
            if ((u8)FlagBit_Get_11D34((u16)v0) == 0)
                goto adv;
        } else if (v0 < 0) {
            if ((u8)FlagBit_Get_11D34((u16)(-(s8)p[0])) == 1)
                goto adv;
        }
    }
    {
        s8 v1 = (s8)p[1];
        if (v1 > 0) {
            if ((u8)FlagBit_Get_11D34((u16)v1) == 0)
                goto adv;
        } else if (v1 < 0) {
            if ((u8)FlagBit_Get_11D34((u16)(-(s8)p[1])) == 1)
                goto adv;
        }
    }
    {
        s8 v2 = (s8)p[2];
        if (v2 > 0) {
            if (TblByte_11DB0((u16)v2) < p[3])
                goto adv;
        } else if (v2 < 0) {
            if (TblByte_11DB0((u16)(-(s8)p[2])) >= p[3])
                goto adv;
        }
    }
    return cur;
}

/* 0x080113f4 (194 B): same walk, returns u8*. */
__attribute__((section(".text.w17c_080113f4")))
u8 *TableWalk_080113F4(u16 cur)
{
    u8 *p;
    if (cur == 0)
        return 0;
    goto loop;
adv:
    if (*(s16 *)(p + 4) == 0)
        return 0;
    cur = *(u16 *)(p + 4);
loop:
    p = TableLookup_11C80(cur);
    {
        s8 v0 = (s8)p[0];
        if (v0 > 0) {
            if ((u8)FlagBit_Get_11D34((u16)v0) == 0)
                goto adv;
        } else if (v0 < 0) {
            if ((u8)FlagBit_Get_11D34((u16)(-(s8)p[0])) == 1)
                goto adv;
        }
    }
    {
        s8 v1 = (s8)p[1];
        if (v1 > 0) {
            if ((u8)FlagBit_Get_11D34((u16)v1) == 0)
                goto adv;
        } else if (v1 < 0) {
            if ((u8)FlagBit_Get_11D34((u16)(-(s8)p[1])) == 1)
                goto adv;
        }
    }
    {
        s8 v2 = (s8)p[2];
        if (v2 > 0) {
            if (TblByte_11DB0((u16)v2) < p[3])
                goto adv;
        } else if (v2 < 0) {
            if (TblByte_11DB0((u16)(-(s8)p[2])) >= p[3])
                goto adv;
        }
    }
    return p;
}

/* 0x08025a10 (84 B): TblLookup + SumStrides/AddTbl compare + SetU8/StoreIdx. */
__attribute__((section(".text.w17c_08025a10")))
u32 F_08025A10(u8 *s, u8 idx)
{
    TblLookup_25730(s, idx);
    if (idx == 0) {
        u32 sum = SumStrides_25754(s);
        u32 add = AddTbl_S14(s);
        if ((sum << 16) > (add << 16))
            return 1;
    }
    {
        u8 t = TblGet_25654(s, idx);
        SetU8_Off1(s + (((u32)(u8)t << 2) + 20), 255);
        StoreIdx2_25638(s, idx, 255);
    }
    return 0;
}
