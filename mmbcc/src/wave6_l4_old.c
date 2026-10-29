/* Wave 6 L4 batch (29 verified, coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave6_l4.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x08021000: Ent_TblInit_08021000 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_08226F24[];
void Dispatch_08226F2C_10(u8 *s);

__attribute__((section(".text.w6l4_08021000")))
void Ent_TblInit_08021000(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08226F24;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08226F2C_10(s);
}

/* 0x0801ae00: ObjInit_0801AE00 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
u16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w6l4_0801ae00")))
void ObjInit_0801AE00(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x22B, 0);
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
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 13;
    *(u32 *)(s + 88) = 0x600;
    *(u32 *)(s + 96) = 8;
    *(u32 *)(s + 92) = 0x600;
    *(u32 *)(s + 100) = 8;
    Text_SelectBlobIdx(0x96);
}

/* 0x0801dad4: ObjInit_0801DAD4 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801dad4")))
void ObjInit_0801DAD4(u8 *s)
{
    u8 t;
    u32 idx;
    int mask;

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x1400, 0);
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
        p += 0x45;
        idx <<= 2;
        mask = -13;
        *p = (*p & mask) | idx;
    }
    {
        u8 v = s[18];
        u8 *q = s + 0x22;
        *q = v;
    }
}

/* 0x08017e6c: ObjInit_08017E6C (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
u16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w6l4_08017e6c")))
void ObjInit_08017E6C(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x20C, 1);
    ChipSlot_IncUse(s, 1);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
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
        p -= 0x23;
        {
            u32 zero = 0;
            *p = 13;
            *(u32 *)(s + 88) = 0x800;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
    }
    Text_SelectBlobIdx(0xA3);
}

/* 0x0801db9c: ObjInit_0801DB9C (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801db9c")))
void ObjInit_0801DB9C(u8 *s)
{
    u8 t;
    u32 idx;
    int mask;

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x501, 0);
    ChipSlot_IncUse(s, 10);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
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
        u8 *q = s + 0x22;
        u8 z;
        __asm__("movs %0, #0" : "=l"(z));
        *q = z;
    }
}

/* 0x0801bc04: ObjInit_0801BC04 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
u16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w6l4_0801bc04")))
void ObjInit_0801BC04(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x224, 0);
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
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 13;
    Vec2_AddMirrored(s, -15360, 0);
    Text_SelectBlobIdx(0x9F);
}

/* 0x0801acf4: ObjInit_0801ACF4 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801acf4")))
void ObjInit_0801ACF4(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x226, 0);
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
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        {
            u32 zero = 0;
            *p = 13;
            *(u32 *)(s + 88) = 0x700;
            *(u32 *)(s + 96) = -8;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
    }
}

/* 0x08011cd4: Copy3_08011CD4 (coordinator-verified). */
u32 *TableU32_0820B6A4(u16 idx);

__attribute__((section(".text.w6l4_08011cd4")))
void Copy3_08011CD4(u16 a, u32 *o1, u32 *o2, u32 *o3)
{
    u32 *p = TableU32_0820B6A4(a);
    u32 tmp[3];
    s16 i;

    tmp[0] = 0;
    tmp[1] = 0;
    tmp[2] = 0;
    i = 0;
    while (p[i] != 0) {
        tmp[i] = p[i];
        i++;
        if (i > 2)
            break;
    }
    *o1 = tmp[0];
    *o2 = tmp[1];
    *o3 = tmp[2];
}

/* ROM inter-function gap: 00 00 after the 94B function (section would
   otherwise be linker-padded with c0 46). */
__attribute__((section(".text.w6l4_08011cd4")))
static const u16 w6l4_08011cd4_gap = 0;

/* 0x0804ccb8: HwSetup_0804CCB8 (coordinator-verified). */
void CpuSet(void *src, void *dst, u32 len);

__attribute__((section(".text.w6l4_0804ccb8")))
void HwSetup_0804CCB8(void)
{
    u32 *p = *(u32 **)0x03007FF0;
    u32 v = *p;
    u32 bit;
    u32 *r;
    u32 v1;
    u32 v2;

    if (v + 0x978C92AD > 1)
        return;
    *p = v + 10;
    r = (u32 *)0x040000C4;
    v1 = *r;
    bit = 0x2000000;
    if (v1 & bit)
        *r = 0x84400004;
    r = (u32 *)0x040000D0;
    v2 = *r;
    if (v2 & bit)
        *r = 0x84400004;
    *(u16 *)0x040000C6 = 0x400;
    *(u16 *)0x040000D2 = 0x400;
    {
        u32 zero = 0;
        CpuSet(&zero, (u8 *)p + 0x350, 0x05000318);
    }
}

/* 0x0801afe4: ObjInit_0801AFE4 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801afe4")))
void ObjInit_0801AFE4(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x242, 0);
    ChipSlot_IncUse(s, 2);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
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
        p -= 0x23;
        {
            u32 zero = 0;
            *p = 13;
            *(u32 *)(s + 88) = zero;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = 0x200;
            *(u32 *)(s + 100) = 80;
        }
    }
}

/* 0x080217e0: Ent_TblInit_080217E0 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_08227018[];
void Dispatch_0822701C_10(u8 *s);

__attribute__((section(".text.w6l4_080217e0")))
void Ent_TblInit_080217E0(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08227018;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_0822701C_10(s);
}

/* 0x08022920: Ent_TblInit_08022920 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_0822715C[];
void Dispatch_08227168_10(u8 *s);

__attribute__((section(".text.w6l4_08022920")))
void Ent_TblInit_08022920(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_0822715C;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08227168_10(s);
}

/* 0x0801d36c: Ent_TblInit_0801D36C (coordinator-verified). */
extern u32 gTbl_082243D8[];
extern u32 gTbl_08226A04[];
void Dispatch_08226A24_10(u8 *s);

__attribute__((section(".text.w6l4_0801d36c")))
void Ent_TblInit_0801D36C(u8 *s)
{
    u32 *t1 = gTbl_082243D8;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08226A04;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08226A24_10(s);
}

/* 0x08021df8: Ent_TblInit_08021DF8 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_08227088[];
void Dispatch_0822709C_10(u8 *s);

__attribute__((section(".text.w6l4_08021df8")))
void Ent_TblInit_08021DF8(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08227088;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_0822709C_10(s);
}

/* 0x0802054c: Ent_TblInit_0802054C (coordinator-verified). */
extern u32 gTbl_082243D8[];
extern u32 gTbl_08226EC8[];
void Dispatch_08226EDC_10(u8 *s);

__attribute__((section(".text.w6l4_0802054c")))
void Ent_TblInit_0802054C(u8 *s)
{
    u32 *t1 = gTbl_082243D8;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08226EC8;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08226EDC_10(s);
}

/* 0x08023034: Ent_TblInit_08023034 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_082271BC[];
void Dispatch_082271C8_10(u8 *s);

__attribute__((section(".text.w6l4_08023034")))
void Ent_TblInit_08023034(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_082271BC;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_082271C8_10(s);
}

/* 0x08021528: Ent_TblInit_08021528 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_08226FE4[];
void Dispatch_08226FEC_10(u8 *s);

__attribute__((section(".text.w6l4_08021528")))
void Ent_TblInit_08021528(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08226FE4;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08226FEC_10(s);
}

/* 0x0801f1e8: Ent_TblInit_0801F1E8 (coordinator-verified). */
extern u32 gTbl_082243D8[];
extern u32 gTbl_08226DC0[];
void Dispatch_08226DD8_10(u8 *s);

__attribute__((section(".text.w6l4_0801f1e8")))
void Ent_TblInit_0801F1E8(u8 *s)
{
    u32 *t1 = gTbl_082243D8;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08226DC0;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08226DD8_10(s);
}

/* 0x08022644: Ent_TblInit_08022644 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_08227138[];
void Dispatch_08227140_10(u8 *s);

__attribute__((section(".text.w6l4_08022644")))
void Ent_TblInit_08022644(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08227138;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08227140_10(s);
}

/* 0x080236f0: Ent_TblInit_080236F0 (coordinator-verified). */
extern u32 gTbl_08226EF0[];
extern u32 gTbl_082271F0[];
void Dispatch_082271F4_10(u8 *s);

__attribute__((section(".text.w6l4_080236f0")))
void Ent_TblInit_080236F0(u8 *s)
{
    u32 *t1 = gTbl_08226EF0;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_082271F0;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_082271F4_10(s);
}

/* 0x0801b6c4: ObjInit_0801B6C4 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801b6c4")))
void ObjInit_0801B6C4(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x25B, 0);
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
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        {
            u32 zero = 0;
            *p = 13;
            *(u32 *)(s + 88) = zero;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = 80;
        }
    }
}

/* 0x0801aef4: ObjInit_0801AEF4 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801aef4")))
void ObjInit_0801AEF4(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x22D, 0);
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
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        {
            u32 zero = 0;
            *p = 13;
            *(u32 *)(s + 88) = zero;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
    }
}

/* 0x0801b81c: ObjInit_0801B81C (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_0801b81c")))
void ObjInit_0801B81C(u8 *s)
{
    u32 idx;
    int mask;

    ChipSlot_Setup(s, 0x313, 0);
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
        u32 sh;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        {
            u32 zero = 0;
            *p = 13;
            *(u32 *)(s + 88) = zero;
            *(u32 *)(s + 96) = zero;
            *(u32 *)(s + 92) = zero;
            *(u32 *)(s + 100) = zero;
        }
    }
}

/* 0x08016dac: ObjInit_08016DAC (coordinator-verified). */
extern u32 gTbl_08223CF0[];
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l4_08016dac")))
void ObjInit_08016DAC(u8 *s)
{
    u32 *tbl = gTbl_08223CF0;
    u32 idx;
    int mask;

    ((void (*)(u8 *))tbl[s[13]])(s);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
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
    s[0x22] = 16;
}

/* 0x0802503c: Get_0802503C (coordinator-verified). */
u16 Sub80_Field22(u8 *s);
extern u8 gEwram_02007090[];

__attribute__((section(".text.w6l4_0802503c")))
u16 Get_0802503C(void)
{
    u8 *p = gEwram_02007090;
    p += 24;
    return Sub80_Field22(p);
}

/* 0x08007bec: Copy_08007BEC (coordinator-verified). */
void Memcpy16(u8 *src, u8 *dst, u32 size);
extern u8 gEwram_03002420[];

__attribute__((section(".text.w6l4_08007bec")))
void Copy_08007BEC(u8 *src, u16 n)
{
    u32 off = (u16)n << 5;
    Memcpy16(src, gEwram_03002420 + off, 32);
}

/* 0x0800e204: Lists_0800E204 (coordinator-verified). */
void ListIterate_D568(u8 *s);
extern u8 *gMem_02005270;
extern u8 *gMem_020053C0;

__attribute__((section(".text.w6l4_0800e204")))
void Lists_0800E204(void)
{
    ListIterate_D568(gMem_02005270);
    ListIterate_D568(gMem_020053C0);
}

/* 0x08002904: Wrap_08002904 (coordinator-verified). */
void Copy8_28D0(u8 *s, u8 a, u8 b);

__attribute__((section(".text.w6l4_08002904")))
void Wrap_08002904(u8 *s, u8 a, u8 b)
{
    Copy8_28D0(s, a, b + 0x10);
}

/* 0x08028244: Tick_08028244 (coordinator-verified). */
void InitRec8_267B4(u8 *p, u8 kind);
extern u8 gMem_02002F50[];
extern u8 gMem_020070F0[];

__attribute__((section(".text.w6l4_08028244")))
void Tick_08028244(u8 *s)
{
    u8 v = s[1];
    if (v == 0)
        goto zero;
    if (v == 1)
        goto one;
    return;
zero:
    s[6] = 0;
    s[1]++;
one:
    s[6]++;
    if (s[6] > 180)
        goto call;
    {
        struct { u8 pad[4]; u16 flg; } *st = (void *)gMem_02002F50;
        if ((st->flg & 1) == 0)
            goto end;
    }
call:
    InitRec8_267B4(gMem_020070F0, 9);
end:;
}

__asm__(
    ".set gTbl_08226F24,0x08226F24\n\t"
    ".set gTbl_08227018,0x08227018\n\t"
    ".set gTbl_0822715C,0x0822715C\n\t"
    ".set gTbl_08226A04,0x08226A04\n\t"
    ".set gTbl_08227088,0x08227088\n\t"
    ".set gTbl_08226EC8,0x08226EC8\n\t"
    ".set gTbl_082271BC,0x082271BC\n\t"
    ".set gTbl_08226FE4,0x08226FE4\n\t"
    ".set gTbl_08226DC0,0x08226DC0\n\t"
    ".set gTbl_08227138,0x08227138\n\t"
    ".set gTbl_082271F0,0x082271F0\n\t"
    ".set gTbl_08223CF0,0x08223CF0\n\t"
    ".set gEwram_03002420,0x03002420\n\t"
    ".set gMem_02005270,0x02005270\n\t"
    ".set gMem_020053C0,0x020053C0\n\t"
    ".set gMem_02002F50,0x02002F50\n\t"
    ".set gMem_020070F0,0x020070F0\n\t"
);
