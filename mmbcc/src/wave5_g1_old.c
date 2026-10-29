/* Phase 3 Wave 5 POOL-G1 (2 matched C, old_agbcc, coordinator-verified).
 * ObjInit_207EC @0x080207EC (132 B) and ObjInit_22EBC @0x08022EBC (140 B).
 * Object initializers using ChipSlot_Setup/IncUse; old_agbcc for mask
 * allocation (& -13 | <<2). Evidence: docs/match_notes_wave5_g1.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);

__attribute__((section(".text.w5g1_207ec")))
void ObjInit_207EC(u8 *s)
{
    u8 *r5 = *(u8 **)(s + 40);
    u8 t;

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x411a, 0);
    ChipSlot_IncUse(s, s[0x78]);
    {
        u32 idx = ((u32)r5[0x45] << 28) >> 30;
        int mask = -13;
        u8 *p = s;
        u32 sh;
        register int c __asm__("r1");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
        p += 0x45;
        sh = idx << 2;
        *p = (*p & mask) | sh;
    }
    {
        u8 *q = r5;
        u8 v;
        u8 *w = s;

        q += 0x22;
        v = *q;
        w += 0x22;
        *w = v;
    }
    if (s[17] & 2)
        *(u32 *)(s + 96) = 0x15400;
    else
        *(u32 *)(s + 96) = 0xFFFF9C00;
    *(u32 *)(s + 100) = 0;
}

extern u16 gRom_08227174[];
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w5g1_22ebc")))
void ObjInit_22EBC(u8 *s)
{
    u8 t;
    u32 idx;
    int mask;

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    {
        u16 *tbl = gRom_08227174;
        ChipSlot_Setup(s, tbl[s[17] * 3], 0);
    }
    ChipSlot_IncUse(s, s[17]);
    idx = *(u8 *)((((gRom_081705B0[1] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 31;
    s[0x41] = (s[0x41] & mask) | 4;
    {
        u8 v = 4;
        s[18] = v;
    }
}

__asm__(

".globl gRom_08227174\n"
        ".set gRom_08227174, 0x08227174\n"
        ".globl gRom_081705B0\n"
        ".set gRom_081705B0, 0x081705B0\n"
        ".globl gEwram_020031E4\n"
        ".set gEwram_020031E4, 0x020031E4\n");
