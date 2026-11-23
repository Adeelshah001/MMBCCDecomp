void *sub_0804E008(void *dst, int c, u32 n)
{
    u8 *s = (u8 *)dst;
    if (n >= 4 && ((u32)s & 3) == 0) {
        u32 *aligned = (u32 *)dst;
        u32 buffer;
        c &= 0xFF;
        buffer = (c << 8) | c;
        buffer |= (buffer << 16);
        while (n >= 16) {
            *aligned++ = buffer;
            *aligned++ = buffer;
            *aligned++ = buffer;
            *aligned++ = buffer;
            n -= 16;
        }
        while (n >= 4) {
            *aligned++ = buffer;
            n -= 4;
        }
        s = (u8 *)aligned;
    }
    while (n--) {
        *s++ = c;
    }
    return dst;
}

void sub_0804C288(u8 a, u8 *p)
{
    u8 *pp = p;
    u32 *node;
    if ((*pp & 0x80) == 0)
        return;
    node = *(u32 **)(pp + 32);
    if (node == 0)
        goto done;
    do {
        u32 z = 0;
        if (*(u8 *)node != 0) {
            if ((((u8 *)node)[1] & 7) != 0) {
                typedef void (*Func)(void);
                register u8 *tmp;
                tmp = *(u8 **)0x03007FF0;
                tmp = *(u8 **)(tmp + 44);
                ((Func)tmp)();
            }
            *(u8 *)node = z;
        }
        *(u32 *)((u8 *)node + 44) = z;
        node = *(u32 **)((u8 *)node + 52);
    } while (node != 0);
done:
    *(u32 **)(pp + 32) = node;
}

struct StructBD20 {
    u8 pad00[0x7C];
    short unk7C;
};

struct Struct2EE0 {
    u8 flags;
    u8 pad01;
    u16 bit0:1;
    u16 bit1:1;
    u16 rest:14;
};

extern struct StructBD20 D_0200BD20;
extern struct Struct2EE0 D_02002EE0;

void sub_0804A450(void)
{
    struct StructBD20 *a = &D_0200BD20;
    struct Struct2EE0 *b = &D_02002EE0;

    if (b->flags & 1) {
        if (a->unk7C != 0) {
            a->unk7C--;
            if (a->unk7C == 8) {
                b->bit1 = 0;
            }
        }
    }
}

extern u8 D_020070F0[];

u8 sub_080499AC(u8 idx)
{
    u8 *pool = D_020070F0;
    u8 r = 0;
    u8 *base = pool + idx * 12;
    int v = *(u16 *)(base + 0x152);
    if (v == 254) goto yes2;
    if (v > 254) goto big;
    if (v == 253) goto yes1;
    goto no;
big:
    if (v != 255) goto no;
    r = 3;
    goto no;
yes2:
    r = 2;
    goto no;
yes1:
    r = 1;
no:
    return r;
}
