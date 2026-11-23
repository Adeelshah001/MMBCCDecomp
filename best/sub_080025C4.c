extern u32 D_02002FB0[];

int sub_080025C4(int arg0, int arg1, int arg2) {
    u32 *base;
    int save_arg0;
    int save_arg1;
    int save_arg2;
    int count;
    u32 index;
    u32 *entry;
    u32 word;
    u8 byte;
    
    base = D_02002FB0;
    save_arg0 = arg0;
    save_arg1 = arg1;
    save_arg2 = arg2;
    count = base[0];
    if (count <= 0xF) {
        index = count;
        index = (index << 1) + index;
        index = index << 2;
        entry = base + index/4;
        word = entry[1];
        byte = word;
        *(u8*)(entry + 1) = (byte & ~3) | 2;
        word = entry[1];
        entry[1] = (word & 3) | (save_arg2 << 2);
        base[index/4 + 2] = save_arg1;
        base[index/4 + 3] = save_arg0;
        base[0] = count + 1;
        return 0;
    }
    return -1;
}
