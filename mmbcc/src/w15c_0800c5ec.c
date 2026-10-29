/* Wave 15-C: FillWrap_0800C5EC @ 0x0800c5ec (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void FillTilemap_C3A0(u16 *base, u16 c);

void FillWrap_0800C5EC(u16 d, u16 *base, u32 c) __attribute__((section(".text.w15c1_0800C5EC")));
void FillWrap_0800C5EC(u16 d, u16 *base, u32 c) { FillTilemap_C3A0(base, (u16)c); }

