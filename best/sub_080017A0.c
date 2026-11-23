extern u16 D_0816E280[];

short sub_080017A0(int arg0, signed char *arg1) {
    unsigned int shifted;
    unsigned int temp;
    unsigned int temp2;
    short temp_r7;
    unsigned short val0;
    unsigned short val1;
    unsigned short val2;
    unsigned int sum;
    unsigned int shifted_30;
    
    shifted = (unsigned int)arg0 << 16;
    shifted_30 = shifted >> 30;
    *arg1 = (shifted >> 28) & 3;
    temp = (shifted << 2) >> 18;
    temp2 = temp << 16;
    temp_r7 = temp & 0xFFF;
    
    val0 = D_0816E280[(temp2 >> 26) & 0x1F];
    val1 = D_0816E280[(temp >> 5) & 0x1F];
    val2 = D_0816E280[(temp2 >> 21) & 0x1F];
    
    sum = val0 + val1 + val2;
    if ((sum & 3) != shifted_30) {
        return -temp_r7;
    }
    return temp_r7;
}
