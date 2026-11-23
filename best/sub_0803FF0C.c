int sub_0803FC8C(u16);
int sub_0803F998(u16);
int sub_0803FA1C(u16);

int sub_0803FF0C(u16 arg0, u8 arg1, u8 arg2) {
    int ret = 0;
    
    if (sub_0803FC8C(arg0) != 0) {
        ret = 1;
        if (arg1 == 5) ret = 2;
    } else if (arg0 == 0x3000) {
        ret = 1;
        if (arg1 == 3) ret = 2;
    } else if (sub_0803F998(arg0) != 0) {
        ret = 1;
        if (arg1 != 5) ret = 2;
        else if (sub_0803FA1C(arg0) == 0 && arg2 == 1) ret = 2;
    }
    
    return ret;
}
