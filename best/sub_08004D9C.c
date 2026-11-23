int sub_08004D9C(void) {
    u16 *p = (u16 *)0x020031E0;
    u16 result = 0xEDFF;
    u16 val = *p;
    result &= val;
    val = 0xDBFF;
    result &= val;
    *p = result;
    return 1;
}
