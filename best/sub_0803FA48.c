int sub_0803FA48(u16 arg0) {
    int r1 = arg0;
    int r2 = 0;
    int val = 0x3A1;
    if (r1 >= val) {
        if (r1 <= val + 1) {
            r2 = 1;
        } else if (r1 == 0x13A0) {
            r2 = 1;
        }
    }
    return r2;
}
