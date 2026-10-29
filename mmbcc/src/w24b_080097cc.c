/* Wave 24-B: 0x080097cc (148 B) MATCHED.
   Copies 4 tiles (32 B each) from ROM tables to VRAM.
   Tables accessed via extern arrays (idiom: extern array forces the
   address pool-load BEFORE the index shift; a casted absolute address
   fuses to shift-before-load).
   Build: main agbcc, then apply w24b_080097cc_patch.sh to the .s
   (ldrh temp-reg allocation r1/r2/r1/r5 + copy4 tail). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Memcpy16(u8 *src, u8 *dst, u32 size);
extern u32 gTileBaseTbl[];
extern u32 *gTileIdxTbl[];

__attribute__((section(".text.w24b_080097cc")))
void Load4Tiles(u8 a, u16 b, u16 c, u8 d, u8 e)
{
    u32 off = c;
    u8 *dst;
    u32 *row;
    u32 ent;
    u32 base;

    off += (u32)e << 5;
    off += d;
    off <<= 5;
    dst = (u8 *)(0x06010000 + off);
    base = gTileBaseTbl[a];
    row = gTileIdxTbl[a];
    ent = row[b];
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[0] << 5)), dst, 32);
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[1] << 5)), (u8 *)(0x06010020 + off), 32);
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[2] << 5)), (u8 *)(0x06010400 + off), 32);
    Memcpy16((u8 *)(base + ((u32)((u16 *)ent)[3] << 5)), (u8 *)(0x06010420 + off), 32);
}

/* TU-local absolute symbols for the ROM tables (novel in build).
   .globl+.set must FOLLOW the referencing code (GAS 2.42 ordering rule). */
__asm__(
    ".globl gTileBaseTbl\n"
    ".set gTileBaseTbl, 0x081720B4\n"
    ".globl gTileIdxTbl\n"
    ".set gTileIdxTbl, 0x081720CC\n"
);
