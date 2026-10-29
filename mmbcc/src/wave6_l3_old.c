/* Wave 6 L3 batch (15 verified, coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave6_l3.md. Gfx_Blit3 pool constants
   fixed by coordinator (0xAA46->0x46AA, 0x0823A42B->0x08232BA4). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x080186F4: ObjInit_186F4 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);
void Vec2_AddMirrored(u8 *o, u32 x, u32 y);
u32 Text_SelectBlobIdx(u32 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l3_186f4")))
void ObjInit_186F4(u8 *s)
{
    u32 idx;

    ChipSlot_Setup(s, 0x203, 0);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        u32 zero;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        zero = 0;
        *p = 13;
        *(u32 *)(s + 0x58) = 0x200;
        *(u32 *)(s + 0x60) = zero;
        *(s32 *)(s + 0x5c) = -198;
        *(u32 *)(s + 0x64) = 8;
    }

    Vec2_AddMirrored(s, 0xFFFFD800, 0xFFFFDD00);
    Text_SelectBlobIdx(0x8a);
}



/* 0x0801B3AC: ObjInit_1B3AC (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l3_1b3ac")))
void ObjInit_1B3AC(u8 *s)
{
    u32 idx;
    u32 v58;

    ChipSlot_Setup(s, 0x24F, 0);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 13;
    if (s[17] == 0)
        *(u32 *)(s + 0x58) = 0x300;
    else
        *(u32 *)(s + 0x58) = 0xFFFFFD00;
    *(u32 *)(s + 0x60) = 0;
    *(u32 *)(s + 0x5c) = 0;
    *(u32 *)(s + 0x64) = 0;
    s[18] = 20;
}



/* 0x08022320: ObjInit_22320 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern u16 gTbl_0822F470[];

__attribute__((section(".text.w6l3_22320")))
void ObjInit_22320(u8 *s)
{
    u8 *r2;
    u8 t;
    u32 idx;
    u32 zero;

    r2 = *(u8 **)(s + 0x28);
    __asm__("movs %0,#0" : "=l"(zero));
    *(u32 *)(s + 0x6c) = zero;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    s[18] = r2[18];
    {
        u16 *tbl = gTbl_0822F470;
        ChipSlot_Setup(s, tbl[s[17]], 0);
    }
    ChipSlot_IncUse(s, s[18]);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 0;
    s[18] = 0xff;
}

__asm__(
    
    
    
    
    ".globl gTbl_0822F470\n.set gTbl_0822F470, 0x082270F4\n"
);

/* 0x08020D54: ObjInit_20D54 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l3_20d54")))
void ObjInit_20D54(u8 *s)
{
    u8 *r5 = *(u8 **)(s + 0x28);
    u8 t;
    u32 idx;

    *(u32 *)(s + 0x6c) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x421C, 0);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    *(u32 *)(s + 0x50) = 0x7800;
    *(u32 *)(s + 0x54) = 0x6400;
    {
        u8 t2 = 2;
        t2 |= r5[10];
        r5[10] = t2;
    }
    s[18] = 30;
}



/* 0x080223E4: ObjInit_223E4 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l3_223e4")))
void ObjInit_223E4(u8 *s)
{
    u8 *r2;
    u8 t;
    u32 idx;
    u32 zero;

    r2 = *(u8 **)(s + 0x28);
    __asm__("movs %0,#0" : "=l"(zero));
    *(u32 *)(s + 0x6c) = zero;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    s[18] = r2[18];
    ChipSlot_Setup(s, 0x2502, 0);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 0;
    s[18] = 0xff;
}



/* 0x08022E14: ObjInit_22E14 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l3_22e14")))
void ObjInit_22E14(u8 *s)
{
    u8 t;
    u32 idx;
    u32 zero;

    __asm__("movs %0,#0" : "=l"(zero));
    *(u32 *)(s + 0x6c) = zero;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0x351D, 0);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    {
        u8 *q = s;
        u32 z;
        q += 0x22;
        z = 0;
        *q = z;
        *(u32 *)(s + 0x50) = z;
    }
    *(u32 *)(s + 0x54) = 0x3000;
}



/* 0x0801ABE4: ObjInit_1ABE4 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);
void Vec2_AddMirrored(u8 *o, u32 x, u32 y);
u32 Text_SelectBlobIdx(u32 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern u8 gTbl_08226720[];

__attribute__((section(".text.w6l3_1abe4")))
void ObjInit_1ABE4(u8 *s)
{
    u32 idx;

    ChipSlot_Setup(s, (u16)(0x89 << 2), 0);
    {
        u8 *tbl = gTbl_08226720;
        ChipSlot_IncUse(s, tbl[s[17]]);
    }

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        u32 zero;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        zero = 0;
        *p = 13;
        *(u32 *)(s + 0x58) = 0xA00;
        *(s32 *)(s + 0x60) = -8;
        *(u32 *)(s + 0x5c) = zero;
        *(u32 *)(s + 0x64) = 4;
    }
}

__asm__(
    
    
    
    
    ".globl gTbl_08226720\n.set gTbl_08226720, 0x08226720\n"
);

/* 0x0801D658: ObjInit_1D658 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w6l3_1d658")))
void ObjInit_1D658(u8 *s)
{
    u32 idx;
    u8 v1 = 1;
    register u32 zero __asm__("r1") = 0;
    u8 b1;
    u8 v2;
    u8 b2;

    b1 = s[10];
    v1 |= b1;
    s[10] = v1;
    {
        u8 *p = s;
        p += 0x50;
        *(u32 *)(p + 28) = zero;
    }
    v2 = 2;
    b2 = s[10];
    v2 |= b2;
    s[10] = v2;
    {
        u8 v2 = 2;
        v2 |= s[10];
        s[10] = v2;
    }
    ChipSlot_Setup(s, 0xA02, 0);
    ChipSlot_IncUse(s, s[19]);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    s[0x22] = 0;
}



/* 0x0801D828: ObjInit_1D828 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);
u32 SelBlob_Ret(u32 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern u32 gVal0114[];

__attribute__((section(".text.w6l3_1d828")))
void ObjInit_1D828(u8 *s)
{
    u8 t;
    u32 idx;
    u32 zero;

    __asm__("movs %0,#0" : "=l"(zero));
    *(u32 *)(s + 0x6c) = zero;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, (u32)gVal0114, 0);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        register u32 sh __asm__("r1");
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    {
        u8 b = s[18];
        u8 *p = s;
        p += 0x22;
        *p = b;
    }
    SelBlob_Ret(0x84);
}

__asm__(
    
    
    
    
    ".globl gVal0114\n.set gVal0114, 0x1401\n"
    
);

/* 0x0801F930: ObjInit_1F930 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);
u32 SelBlob_Ret(u32 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern u32 gVal3B16[];

__attribute__((section(".text.w6l3_1f930")))
void ObjInit_1F930(u8 *s)
{
    u8 t;
    u32 idx;
    u32 zero;

    __asm__("movs %0,#0" : "=l"(zero));
    *(u32 *)(s + 0x6c) = zero;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, (u32)gVal3B16, 0);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[1] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        register u32 sh __asm__("r1");
        int mask;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
    }
    {
        u8 b = s[18];
        u8 *p = s;
        p += 0x22;
        *p = b;
    }
    SelBlob_Ret(0x84);
}

__asm__(
    
    
    
    
    ".globl gVal3B16\n.set gVal3B16, 0x3B16\n"
    
);

/* 0x08019090: ObjInit_19090 (coordinator-verified). */
void ChipSlot_Setup(u8 *s, u32 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);
void Vec2_AddMirrored(u8 *o, u32 x, u32 y);
u32 Text_SelectBlobIdx(u32 idx);

extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern u32 gVal022F[];

__attribute__((section(".text.w6l3_19090")))
void ObjInit_19090(u8 *s)
{
    u32 idx;

    ChipSlot_Setup(s, (u32)gVal022F, s[17]);
    ChipSlot_IncUse(s, 0);

    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    {
        u8 *p = s;
        u32 sh;
        int mask;
        u32 zero;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        zero = 0;
        *p = 13;
        *(u32 *)(s + 0x58) = zero;
        *(u32 *)(s + 0x60) = zero;
        *(u32 *)(s + 0x5c) = zero;
        *(u32 *)(s + 0x64) = zero;
    }

    Vec2_AddMirrored(s, 0xFFFFE600, 0xFFFFE700);
    Text_SelectBlobIdx(0x9f);
}

__asm__(
    
    
    
    
    
    
    ".globl gVal022F\n.set gVal022F, 0x22F\n"
);

/* 0x08001DB8: Sram_VerifySlot (coordinator-verified). */
extern u32 gEwram_02002FA0[];
extern u32 gRom_0804E314;
void Sram_WaitcntInit(u8 *dst, u8 *src, u32 len);

__attribute__((section(".text.w6l3_1db8")))
u32 Sram_VerifySlot(u32 a0, u32 key)
{
    u8 sel = (u8)a0;
    u16 tries;
    u32 *p4;
    u16 i;

    if (sel > 1)
        return 0;
    tries = 3;
    p4 = gEwram_02002FA0;
    do {
        i = 0;
        do {
            Sram_WaitcntInit((u8 *)(0x0E000000 + ((sel + (i << 1)) << 13)), (u8 *)p4, 16);
            if (*p4 == gRom_0804E314) {
                register u8 *p __asm__("r1");
                __asm__ volatile ("add %0, %1, #0\n\tsub %0, %0, #32" : "=r" (p) : "r" ((u8 *)p4));
                if (((u8 *)p4)[12] == 0 && ((u8 *)p4)[15] == 1 && *(u32 *)(p + 40) == key)
                    return 1;
            }
            i++;
        } while (i <= 1);
        tries--;
    } while (tries != 0);
    return 0;
}

/* 0x08042EC0: Gfx_Blit3 (coordinator-verified). */
void Gfx_BlitRequest(u32 a, u32 b, u32 c, u32 d, u32 e);
extern u32 *gTbl_08232D5C[];
extern u32 *gTbl_08232D70[];
extern u32 gVal_08232BA4[];
extern s8 gBase_08232D50[];
extern u32 gOff_46AA[];

__attribute__((section(".text.w6l3_42ec0")))
void Gfx_Blit3(u8 *s)
{
    u8 *p = s;
    u32 **tA = (u32 **)gTbl_08232D5C;
    u32 **tB;

    p += (u32)gOff_46AA;
    Gfx_BlitRequest(*tA[*p], gBase_08232D50[4] + 1, gBase_08232D50[5] + 1, 8, 0);
    tB = (u32 **)gTbl_08232D70;
    Gfx_BlitRequest(*tB[*p], gBase_08232D50[4] + 1, gBase_08232D50[5] + 3, 8, 0);
    Gfx_BlitRequest(gVal_08232BA4[0], gBase_08232D50[4] + 1, gBase_08232D50[5] + 5, 8, 0);
}

/* 0x0804CD70: Mem1_AllocInit (coordinator-verified). */
void CallVia_Mem1(u8 *s);
extern u32 gPtr_03007FF0[];
extern u32 gMagic_68736D53[];
extern u32 gVal_0804C021[];

__attribute__((section(".text.w6l3_4cd70")))
void Mem1_AllocInit(u8 *s, u8 *d, u32 cnt_arg)
{
    u8 cnt = (u8)cnt_arg;
    u32 *p;

    if (cnt == 0)
        return;
    if (cnt > 16)
        cnt = 16;
    p = *(u32 **)gPtr_03007FF0;
    if (*p != (u32)gMagic_68736D53)
        return;
    *p += 1;
    CallVia_Mem1(s);
    ((u32 *)s)[11] = (u32)d;
    s[8] = cnt;
    *(u32 *)(s + 4) = 0x80000000;
    if (cnt != 0) {
        do {
            *d = 0;
            cnt--;
            d += 0x50;
        } while (cnt != 0);
    }
    if (p[8] != 0) {
        ((u32 *)s)[14] = p[8];
        ((u32 *)s)[15] = p[9];
        p[8] = 0;
    }
    p[9] = (u32)s;
    p[8] = (u32)gVal_0804C021;
    *p = (u32)gMagic_68736D53;
    ((u32 *)s)[13] = (u32)gMagic_68736D53;
}

/* 0x0803AF98: Task_3AF98 (coordinator-verified). */
void InitRec8_267B4(u8 *a, u32 b);
void EntryMgr_Teardown(void);
void EntryMgr_Setup(void);
extern u8 gOff_469C[];
extern u8 gEwram_020070F0_A[];
extern u8 gOff_4698_A[];
extern u8 gEwram_020070F0_B[];
extern u8 gOff_4698_B[];

__attribute__((section(".text.w6l3_3af98")))
void Task_3AF98(u8 *s)
{
    register u32 off __asm__("r1");
    register u8 *p __asm__("r0");
    u8 v;
    off = (u32)gOff_469C;
    p = s + off;
    v = *p;
    if (v == 8) {
        register u8 *q __asm__("r1");
        register u32 o __asm__("r0");
        InitRec8_267B4(gEwram_020070F0_A, 8);
        o = (u32)gOff_4698_A;
        q = s + o;
        *q = 0;
    } else if (v == 9) {
        register u8 *q __asm__("r1");
        register u32 o __asm__("r0");
        InitRec8_267B4(gEwram_020070F0_B, 8);
        o = (u32)gOff_4698_B;
        q = s + o;
        *q = 6;
    } else {
        u8 z = 0;
        s[1] = 1;
        s[2] = z;
        s[3] = z;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}

__asm__(
    ".set gTbl_0822F470,0x082270F4\n\t"
    ".set gTbl_08226720,0x08226720\n\t"
    ".set gVal0114,0x1401\n\t"
    ".set gVal3B16,0x3B16\n\t"
    ".set gVal022F,0x22F\n\t"
    ".set gEwram_02002FA0,0x02002FA0\n\t"
    ".set gRom_0804E314,0x0804E314\n\t"
    ".set gTbl_08232D5C,0x08232D5C\n\t"
    ".set gTbl_08232D70,0x08232D70\n\t"
    ".set gVal_08232BA4,0x08232BA4\n\t"
    ".set gBase_08232D50,0x08232D50\n\t"
    ".set gOff_46AA,0x46AA\n\t"
    ".set gPtr_03007FF0,0x03007FF0\n\t"
    ".set gMagic_68736D53,0x68736D53\n\t"
    ".set gVal_0804C021,0x0804C021\n\t"
    ".set gOff_469C,0x469C\n\t"
    ".set gEwram_020070F0_A,0x020070F0\n\t"
    ".set gOff_4698_A,0x4698\n\t"
    ".set gEwram_020070F0_B,0x020070F0\n\t"
    ".set gOff_4698_B,0x4698\n\t"
);
