extern void sub_08023BC4(u32, u32, u32);
extern void sub_08023CE4(u8 *, u8 *);
extern void sub_08023C38(u32, u32, u32);

void sub_08023B64(u16 *p)
{
    u16 *q = p;
    u8 i = 0;
    u16 t;
    do {
        t = q[i];
        if (t <= 9)
            q[i] = t + 1;
        else
            q[i] = t + 0x54;
        i++;
    } while (i <= 23);
}

void sub_08023B2A(int arg2)
{
    u32 r5 = 0x7F;
    u32 r2 = arg2 & 0x7F;
    u8 val0, val1;
    sub_08023BC4(0, 0, r2);
    sub_08023CE4((u8 *)0, (u8 *)0);
    val0 = *(u8 *)0;
    val1 = *(u8 *)4;
    r2 = (val0 + val1) & 0x7F;
    sub_08023C38(0, 0, r2);
    return;
}

void sub_08023CE4(u8 *p0, u8 *p1)
{
    u8 *a = p1;
    u8 *b = p0;
    u8 i = 0;
    u8 *dst, *src;
    do {
        dst = a + i;
        src = b + ((i * 2) & 7);
        *dst ^= *src;
        i++;
    } while (i <= 13);
}

s8 sub_08023D10(u8 *p)
{
    u8 *q = p;
    u8 sum = 0;
    u8 i = 0;
    do {
        sum += q[i];
        i++;
    } while (i <= 13);
    return -sum;
}
