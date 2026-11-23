extern u8 D_08105D58[256];
extern u32 D_08105E0C[16];

int sub_0804B970(int a, int b);

int sub_0804C58C(void *arg0, u8 arg1, int arg2) {
    void *ip = arg0;
    int r6 = arg1;
    int r7 = arg2 << 24;
    int r3;
    int r4;
    int r5;
    int r0;
    u8 val1, val2;
    
    if ((unsigned)r6 > 0xB2) {
        r6 = 0xB2;
        r7 = 0xFF000000;
    }
    
    r3 = (int)&D_08105D58[0];
    val1 = D_08105D58[r6];
    
    r4 = (int)&D_08105E0C[0];
    r5 = D_08105E0C[val1 & 0xF];
    r5 = (unsigned)r5 >> (val1 >> 4);
    
    val2 = D_08105D58[r6 + 1];
    r0 = D_08105E0C[val2 & 0xF];
    r0 = (unsigned)r0 >> (val2 >> 4);
    
    r4 = *(int *)((char *)ip + 4);
    r0 = r0 - r5;
    r0 = sub_0804B970(r0, r7);
    r0 = r5 + r0;
    return sub_0804B970(r4, r0);
}
