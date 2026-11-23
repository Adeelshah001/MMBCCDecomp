struct MPlayInfo4D6 {
    u8 pad00[0x1C];
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u8 pad22[0x12];
    u32 ident;
};

void sub_0804D634(struct MPlayInfo4D6 *info, u16 val)
{
    if (info->ident == 0x68736D53) {
        info->unk1E = val;
        info->unk20 = (val * info->unk1C) >> 8;
    }
}

void sub_0804D130(u8 a)
{
    u8 *p;
    switch (a) {
    case 1:
        p = (u8 *)0x4000063;
        *p = 8;
        p += 2;
        goto tail128;
    case 2:
        p = (u8 *)0x4000069;
        goto tail8;
    case 3:
        *(u8 *)0x4000070 = 0;
        return;
    default:
        p = (u8 *)0x4000079;
    tail8:
        *p = 8;
        p += 4;
    tail128:
        *p = 128;
        break;
    }
}

struct SoundInfo4CD {
    u32 ident;
    vu8 dmaCounter;
};

void sub_0804CD34(void)
{
    struct SoundInfo4CD *info = *(struct SoundInfo4CD **)0x03007FF0;
    u32 id = info->ident;
    if (id != 0x68736D53) {
        volatile u16 *dma = (volatile u16 *)0x040000C6;
        u16 val = 0xB600;
        *dma = val;
        dma += 6;
        *dma = val;
        info->dmaCounter &= 0;
        info->ident = id - 10;
    }
}

void *sub_0804DFA8(void *dst, const void *src, u32 len)
{
    u8 *d = (u8 *)dst;
    const u8 *s = (const u8 *)src;
    if (len > 15 && (((u32)s | (u32)d) & 3) == 0) {
        u32 *dw = (u32 *)dst;
        const u32 *sw = (const u32 *)s;
        do {
            *dw++ = *sw++;
            *dw++ = *sw++;
            *dw++ = *sw++;
            *dw++ = *sw++;
            len -= 16;
        } while (len > 15);
        while (len > 3) {
            *dw++ = *sw++;
            len -= 4;
        }
        d = (u8 *)dw;
        s = (const u8 *)sw;
    }
    while (len--) {
        *d++ = *s++;
    }
    return dst;
}
