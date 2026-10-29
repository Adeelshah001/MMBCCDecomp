/* Wave 7 batch D (3 matched, coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave7_d.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x08017f8c: ObjInit_TypeA (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern void Vec2_AddMirrored(u8 *s, int x, int y);

__attribute__((section(".text.w7d_08017f8c")))
void ObjInit_TypeA(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x21C, 0);
    ChipSlot_IncUse(s, 0);
    if (s[16] == 2) {
        idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
        {
            register int c __asm__("r0");
            __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
            if (c > 3)
                idx = 3;
        }
        {
            u8 *p = s;
            u32 zero;
            p += 0x45;
            idx <<= 2;
            mask = -13;
            *p = (*p & mask) | idx;
            p -= 0x23;
            zero = 0;
            *p = 17;
            *(u32 *)(s + 88) = 0x600;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
        Vec2_AddMirrored(s, 0x3300, -0x1F00);
    } else {
        idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
        {
            register int c __asm__("r0");
            __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
            if (c > 3)
                idx = 3;
        }
        {
            u8 *p = s;
            u32 zero;
            p += 0x45;
            idx <<= 2;
            mask = -13;
            *p = (*p & mask) | idx;
            p -= 0x23;
            zero = 0;
            *p = 12;
            *(u32 *)(s + 88) = 0x706;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
        Vec2_AddMirrored(s, 0x2C00, -0x1500);
    }
}



/* 0x0801dcc0: ObjInit_TypeB (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w7d_0801dcc0")))
void ObjInit_TypeB(u8 *s)
{
    u32 idx;
    int mask;

    *(u32 *)(s + 0x6C) = 0;
    {
        u32 v;
        v = 2;
        v |= s[0xA];
        v |= 1;
        s[0xA] = v;
    }
    ChipSlot_Setup(s, 0x501, 0);
    ChipSlot_IncUse(s, 11);
    {
        u8 *p = s;
        register int m41 __asm__("r0");
        p += 0x41;
        m41 = -13;
        *p = (*p & m41) | 4;
    }
    idx = *(u8 *)((((gRom_081705B0[1] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        p += 0x45;
        idx <<= 2;
        mask = -13;
        *p = (*p & mask) | idx;
    }
    {
        u8 v12 = s[0x12];
        s[0x22] = v12;
    }
    {
        u8 *q = *(u8 **)(s + 0x28);
        q += 0x21;
        *q = 8;
    }
}



/* 0x080205b8: ObjInit_205B8 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w7d_080205b8")))
void ObjInit_205B8(u8 *s)
{
    u32 idx;
    int mask;

    *(u32 *)(s + 0x6C) = 0;
    {
        u32 v;
        register u32 c1 __asm__("r1");
        v = 2;
        v |= s[0xA];
        __asm__("movs %0,#1" : "=r"(c1));
        v |= c1;
        s[0xA] = v;
    }
    ChipSlot_Setup(s, 0x401B, 0);
    ChipSlot_IncUse(s, 0);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        register u32 sh __asm__("r0");
        register int m __asm__("r1");
        p += 0x45;
        sh = idx << 2;
        m = -13;
        *p = (*p & m) | sh;
    }
    if (s[0x11] & 2) {
        s[0x48] = 1;
        s[0xA] |= 16;
    }
    s[0x12] = 16;
    if (s[0x11] & 1) {
        *(u32 *)(s + 0x50) = 0x7800;
        *(u32 *)(s + 0x54) = 0x8C00;
    } else {
        *(u32 *)(s + 0x50) = 0x7800;
        *(u32 *)(s + 0x54) = 0x2000;
    }
}

__attribute__((section(".text.w7d_080205b8")))
static const u16 pad_080205b8 = 0;


