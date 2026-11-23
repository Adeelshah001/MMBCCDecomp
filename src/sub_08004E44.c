/* sub_08004E44 */
void sub_08004E60(u32);

void sub_08004E44(void) {
    sub_08004E60(0);
}

/* sub_08004E24 */
void sub_08004E24(u8 x) {
    u8 *p = (u8 *)0x02004F80;
    p[0] = (x << 7) | 64;
    p[2] = (x == 0) ? 1 : 2;
}

/* sub_08004E0C */
int sub_08004E0C(u8 x) {
    u8 *p = (u8 *)0x02004F80;
    return (p[1] == x) ? 1 : 0;
}

/* sub_08004D9C */
int sub_08004D9C(void) {
    u16 *p = (u16 *)0x020031E0;
    u16 v = *p & 0xEDFF;
    v &= 0xDBFF;
    *p = v;
    return 1;
}
