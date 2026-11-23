// sub_0801039C
extern void sub_08010508(u8 v);
extern u8 D_02005160[];

u8 sub_0801039C(u8 *p, u8 b)
{
    u8 bb = b;
    u8 *q = D_02005160;
    
    if (*q != 0)
        return 0;
    sub_08010508(6);
    *(u8 **)(q + 48) = p;
    *(q + 66) = bb;
    return 1;
}

// sub_0801054C
extern void sub_08008030(u32 a, u32 b, u32 c, u32 d, u32 e);
extern void sub_080105A4(u32 a, u32 b);

void sub_0801054C(void *arg0)
{
    u32 var_r2 = 0xE;
    u8 *ptr = (u8 *)0x0200481E;
    
    if ((4 & *ptr) != 0) {
        var_r2 = 0xF;
    }
    
    sub_08008030(0, var_r2, 0, 0, (u32)((u8 *)arg0)[0x3A]);
    
    sub_080105A4(0x02005168, 0);
    sub_080105A4(0x0200517C, 1);
}

// sub_08010AD8
extern u8 D_020051B0[];

void sub_08010AD8(u8 arg0, u8 arg1, u8 arg2)
{
    s8 temp_r2 = (s8)arg2;
    u8 var_r5 = arg2;
    u8 *var_r2 = D_020051B0;
    u16 var_r0 = 0;
    
    if (temp_r2 == -1) {
        s8 val = ((s8 *)D_020051B0)[0x0E];
        if (val != temp_r2) {
            var_r5 = D_020051B0[0x0E];
        }
    }
    
    do {
        var_r2[var_r0] = 0;
        var_r0++;
    } while (var_r0 <= 0x77);
    
    D_020051B0[0x0E] = var_r5;
    D_020051B0[0x0F] = D_020051B0[0x0F] | 1;
    D_020051B0[0x04] = 0;
    D_020051B0[0x02] = arg0;
    *(u16 *)(D_020051B0 + 0x12) = (u16)((s8)arg1);
}

// sub_08010D84
extern void sub_08004E24(u8 v);
extern int sub_08004E0C(u32 v);
extern void sub_080111B4(u32 a);
extern void sub_08011170(u8 a);
extern u16 gUnknown_020031E0;

u8 sub_08010D84(u8 *s)
{
    u8 st = s[0];
    if (st == 0)
        goto state0;
    if (st == 1)
        goto state1;
    goto ret;
state0:
    s[0] = 1;
    sub_08004E24(s[13]);
    goto ret;
state1:
    if ((u8)sub_08004E0C(3) == 0)
        goto ret;
    sub_080111B4(1);
    gUnknown_020031E0 &= 0xedff;
    gUnknown_020031E0 &= 0xdbff;
    sub_08011170(s[2]);
ret:
    return s[4];
}
