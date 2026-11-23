struct SoundInfo4CD {
    u32 ident;
    u8 dmaCounter;
};

void sub_0804CD34(void)
{
    struct SoundInfo4CD *info = *(struct SoundInfo4CD **)0x03007FF0;
    u32 id = info->ident;
    if (id != 0x68736D53) {
        volatile u16 *dma = (volatile u16 *)0x040000C6;
        *dma = 0xB600;
        dma += 6;
        *dma = 0xB600;
        *(volatile u8 *)&info->dmaCounter;
        info->dmaCounter = 0;
        info->ident = id - 10;
    }
}
