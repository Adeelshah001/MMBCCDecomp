/* Wave 15-C: CopyBytes_0800EAC4 @ 0x0800eac4 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_02005130[];
extern u8 g_02005168[];
void SetByte20_Clear21to23_0800E1F0(u8 x);

void CopyBytes_0800EAC4(u8 a, u8 b) __attribute__((section(".text.w15c1_0800EAC4")));
void CopyBytes_0800EAC4(u8 a, u8 b)
{
    g_02005130[6] = a;
    g_02005130[4] = a;
    g_02005130[7] = b;
    g_02005130[5] = b;
    g_02005168[10] = g_02005130[8];
    g_02005168[30] = g_02005130[9];
    SetByte20_Clear21to23_0800E1F0(1);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl SetByte20_Clear21to23_0800E1F0\n"
    ".set SetByte20_Clear21to23_0800E1F0, 0x0800E1F0\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl g_02005168\n"
    ".set g_02005168, 0x02005168\n"
);
