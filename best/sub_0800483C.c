/* sub_0800483C */
extern u8 gUnknown_02003250[];

typedef struct Data_02003250 {
    u32 unk0;
    u32 count;
    u32 arr0[48];
    u8 arr1[48];
    u8 arr2[48];
    u16 arr3[48];
} Data_02003250;

void sub_0800483C(u32 arg0, s8 arg1, s8 arg2, u16 arg3) {
    Data_02003250 *data = (Data_02003250 *)gUnknown_02003250;
    u32 r4 = arg0;
    s8 r5 = arg1;
    s8 r6 = arg2;
    u16 r3 = arg3;
    u32 count;
    
    count = data->count;
    if ((int)count > 0x2F)
        return;
    data->arr0[count] = r4;
    data->arr1[count] = r5;
    data->arr2[count] = r6;
    data->arr3[count] = r3;
    data->count = count + 1;
}
