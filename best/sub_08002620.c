extern u32 D_02002FB0[];
extern u32 D_040000D4[];

void sub_08002620(u32 arg0, u32 arg1, u32 arg2, u16 arg3) {
    u32 *base;
    u32 temp;
    u32 *dma;
    u32 stack_temp;
    
    base = D_02002FB0;
    base[0xC8/4] = arg0;
    base[0xCC/4] = arg1;
    base[0xC4/4] = arg2;
    temp = arg3 | (arg3 << 16);
    base[0xCC/4 + 1] = temp;
    stack_temp = temp;
    dma = D_040000D4;
    dma[0] = (u32)&stack_temp;
    dma[1] = arg0;
    dma[2] = (arg2 >> 2) | 0x85000000;
    temp = dma[2];
}
