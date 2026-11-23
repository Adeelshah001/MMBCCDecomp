/* sub_08004398 */
typedef struct Elem {
    struct Elem *next;
    u16 unk4_1;
    u16 unk4_2;
    u8 unk8;
} Elem;

typedef struct List {
    Elem *head;
    short unk4;
    u16 unk6;
    u16 unk8;
    void *unkC;
    void *unk10;
    void *unk14;
    void *unk18;
    u16 unkA;
} List;

void sub_08004398(List *arg0, u8 arg1, Elem *arg2, u16 arg3, u16 arg4) {
    Elem *var_r5 = arg2;
    u16 temp_r6 = arg3;
    u16 temp_r3 = arg4;
    Elem *var_r2 = 0;
    int var_r1;
    short temp_r3_sext;
    
    arg0->head = var_r5;
    arg0->unk4 = (short)(s8)arg1;
    arg0->unk6 = temp_r6;
    arg0->unk8 = temp_r3;
    arg0->unk14 = (void *)((u8 *)arg0 + 0x14);
    arg0->unk18 = (void *)((u8 *)arg0 + 0x14);
    arg0->unk10 = 0;
    arg0->unkA = temp_r3;
    
    var_r1 = (int)temp_r3 << 16;
    if (var_r1 > 0) {
        temp_r3_sext = (short)temp_r6;
        do {
            var_r5->next = var_r2;
            var_r2 = var_r5;
            var_r2->unk8 = arg1;
            var_r5 = (Elem *)((u8 *)var_r2 + temp_r3_sext);
            var_r1 += 0xFFFF0000;
        } while ((short)(var_r1 >> 16) > 0);
        arg0->unk10 = var_r2;
    }
}
