extern u8 D_020051B0[];

void sub_08010AD8(u8 arg0, u8 arg1, u8 arg2)
{
    u8 var_r5 = arg2;
    u16 var_r0 = 0;
    u8 *var_r2;
    
    if ((s8)arg2 == -1) {
        s8 val = ((s8 *)D_020051B0)[0x0E];
        if (val != (s8)arg2) {
            var_r5 = D_020051B0[0x0E];
        }
    }
    
    var_r2 = D_020051B0;
    
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
