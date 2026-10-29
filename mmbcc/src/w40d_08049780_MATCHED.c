/* Wave 40 Worker D: 0x08049780, 396 B. v2: cases in ROM layout order
   (even case-index first, then odd), cases 1/5 store v24 before the
   final v28 mask so the final [ands; str] can share. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0804990C(void);
extern u16 GetEnt_U16_14(void);
extern void F_08024F30(u16 a);
extern u16 GetEnt_U16_10(void);
extern void F_08024F70(u16 a);

__attribute__((section(".text.w40d_08049780")))
void F_08049780(u8 arg)
{
    u8 idx = arg;
    u8 *g = (u8 *)0x020070f0;
    u32 v24, v28;
    if (g[20] >= idx)
        return;
    g[20]++;
    Sub_0804990C();
    switch (idx - 1) {
    case 0:
        F_08024F30((u16)(GetEnt_U16_14() + 20));
        *(u32 *)(g + 24) |= 8;
        *(u32 *)(g + 28) &= ~8;
        return;
    case 2:
        F_08024F30((u16)(GetEnt_U16_14() + 20));
        *(u32 *)(g + 24) |= 64;
        *(u32 *)(g + 28) &= ~64;
        return;
    case 4:
        F_08024F30((u16)(GetEnt_U16_14() + 20));
        *(u32 *)(g + 24) |= 256;
        *(u32 *)(g + 28) &= ~256;
        return;
    case 6:
        *(u32 *)(g + 24) |= 2048;
        *(u32 *)(g + 28) &= ~2048;
        F_08024F30((u16)(GetEnt_U16_14() + 40));
        return;
    case 8:
        *(u32 *)(g + 24) |= 8192;
        *(u32 *)(g + 28) &= ~8192;
        F_08024F30((u16)(GetEnt_U16_14() + 60));
        return;
    case 1:
        v24 = *(u32 *)(g + 24);
        v24 |= 16;
        v28 = *(u32 *)(g + 28);
        v28 &= ~16;
        v24 |= 32;
        *(u32 *)(g + 24) = v24;
        v28 &= ~48;
        *(u32 *)(g + 28) = v28;
        F_08024F70((u16)(GetEnt_U16_10() + 10));
        return;
    case 3:
        *(u32 *)(g + 24) |= 128;
        *(u32 *)(g + 28) &= ~128;
        F_08024F70((u16)(GetEnt_U16_10() + 10));
        return;
    case 5:
        v24 = *(u32 *)(g + 24);
        v24 |= 512;
        v28 = *(u32 *)(g + 28);
        v28 &= ~512;
        v24 |= 1024;
        *(u32 *)(g + 24) = v24;
        v28 &= ~1536;
        *(u32 *)(g + 28) = v28;
        F_08024F70((u16)(GetEnt_U16_10() + 10));
        return;
    case 7:
        *(u32 *)(g + 24) |= 4096;
        *(u32 *)(g + 28) &= ~4096;
        F_08024F70((u16)(GetEnt_U16_10() + 30));
        return;
    default:
        return;
    }
}

