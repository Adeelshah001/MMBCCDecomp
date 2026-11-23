extern u16 D_0816E240[];

u16 sub_08001754(u32 arg0, u32 arg1) {
    u32 combined = (u32)(u16)arg0 | ((u32)(arg1 & 3) << 12);
    u16 a = D_0816E240[(combined >> 5) & 0x1F];
    u16 b = D_0816E240[combined & 0x1F];
    u16 c = D_0816E240[combined >> 10];
    u16 sum = (u16)(a + b + c);
    return (u16)(((sum & 3) << 14) | combined);
}

void sub_0800063C(void) {
    u32 stack_var;
    volatile u32 *reg;
    volatile u16 *vram;

    reg = (volatile u32 *)0x040000D4;
    vram = (volatile u16 *)0x02000ED0;
    *(volatile u16 *)0x04000204 = 0x45B7;
    stack_var = 0;
    reg[0] = stack_var;
    reg[1] = 0x03000000;
    reg[2] = 0x85001F80;
    reg[2];
    reg[0] = stack_var;
    reg[1] = 0x02000000;
    reg[2] = 0x85010000;
    reg[2];
    vram[0x1001] = 0;
    vram[0x1000] = 0;
}
