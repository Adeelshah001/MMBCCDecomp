extern unsigned short D_02003670;
extern short D_0804E05C[];

void sub_0800C784(int unused, short *out, unsigned short count) {
    unsigned short seed = D_02003670;
    short acc = 0;
    unsigned short i = 0;
    short *table = D_0804E05C;
    short v0;
    short v1;

    if (count == 0)
        return;

    do {
        v0 = table[(unsigned char)(seed >> 1)];
        out[0] = v0 >> 6;
        out[1] = acc;
        out += 2;
        seed = (unsigned short)(seed + 1);
        v1 = table[(unsigned char)(seed) + 0x40];
        acc = (short)(((unsigned int)v1 << 10) >> 16);
        i++;
    } while (i < count);
}
