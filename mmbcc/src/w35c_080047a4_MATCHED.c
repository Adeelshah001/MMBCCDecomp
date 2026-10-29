/* Wave 35-C v3: 0x080047a4 — c variable + goto DONE */
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
extern s16 Sub_080047A4(u8 *p);
__attribute__((section(".text.w35c_080047a4")))
s16 Sub_080047A4(u8 *p)
{
    s16 acc = 0;
    u8 **base;
    u8 c = *p;
    if (c > 252)
        goto DONE;
    base = (u8 **)0x02003664;
    do {
        if (c == 249)
            acc = (u16)(acc + Sub_080047A4(*base));
        c = *p;
        if (c <= 239)
            acc++;
        p++;
        c = *p;
    } while (c <= 252);
DONE:
    return acc;
}
