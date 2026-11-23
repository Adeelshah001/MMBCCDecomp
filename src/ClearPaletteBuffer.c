typedef volatile u32 vu32;

struct PaletteState {
    u16 colors[0x200];
    u8 unk400;
    u8 unk401;
    u8 unk402;
    u8 unk403;
    u16 unk404;
    u16 unk406;
};

extern struct PaletteState D_03002420;
extern vu32 D_040000D4[];

void ClearPaletteBuffer(void)
{
    volatile u32 fill = 0;
    vu32 *dma = D_040000D4;

    dma[0] = (u32)&fill;
    dma[1] = (u32)&D_03002420;
    dma[2] = 0x85000100;
    dma[2];

    dma[0] = (u32)&D_03002420;
    dma[1] = 0x05000000;
    dma[2] = 0x84000100;
    dma[2];

    D_03002420.unk402 = 0x20;
    D_03002420.unk401 = 0x20;
    D_03002420.unk400 = 0x20;
    D_03002420.unk404 = 0;
    D_03002420.unk406 = 0x400;
}
