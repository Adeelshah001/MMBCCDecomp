/* Phase 3 Wave 5 POOL-H2 (main agbcc, 9 matched C, coordinator-verified).
 * Task mode handlers and init functions. Evidence:
 * docs/match_notes_wave5_h2.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed char s8;
typedef unsigned int u32;

void EntryMgr_Teardown(void);
void EntryMgr_Setup(void);
void InitRec8_267B4(u8 *a, u32 b);
void CpuFastSet(u32 *dst, u8 *src, u32 size);
void CpuSet(u32 *dst, u8 *src, u32 size);
u32 Text_SelectBlobIdx(u16 idx);
u8 GatedDispatch(u32 p, u32 a, u32 b, u32 c, u32 d);
u8 Gfx_BlitRequest(u32 p, u32 a, u32 b, u32 c, u32 d);
extern u8 gEwram_02004CE0[];
extern u8 gEwram_020070F0[];
extern u32 gRom_0822EF0C[];

__attribute__((section(".text.w5h_35bc8")))
void Task_35BC8(u8 *p)
{
    u8 *pA = p + 0x46aa;
    u8 v = *pA;
    u32 flag = 0;
    u16 *ew;
    if ((s8)v > 12) {
        v -= 13;
        flag = 1;
    }
    p[0x46a9] = 3;
    Text_SelectBlobIdx(0x66);
    ew = (u16 *)gEwram_02004CE0;
    ew[20] = (v << 4) + 0x10;
    ew[21] = flag * 24 + 0x20;
}



__attribute__((section(".text.w5h_35c1c")))
void Task_35C1C(void)
{
    u8 *base = gEwram_020070F0;
    GatedDispatch(base[0x13], 0x2f, 4, 2, 0);
    GatedDispatch(base[0x12], 0x32, 4, 2, 0);
    GatedDispatch(base[0x11], 0x35, 4, 2, 0);
}



__attribute__((section(".text.w5h_35da4")))
void Task_35DA4(u8 *p)
{
    u8 *pA = p + 0x46ab;
    u8 v = *pA;
    u32 flag = 0;
    u16 *ew;
    if ((s8)v > 3) {
        v -= 4;
        flag = 1;
    }
    p[0x46a9] = 3;
    Text_SelectBlobIdx(0x66);
    ew = (u16 *)gEwram_02004CE0;
    ew[20] = (v << 4) + 0xf8;
    ew[21] = flag * 24 + 0x20;
}



__attribute__((section(".text.w5h_37598")))
void Task_37598(u8 *p)
{
    u32 q = *(u32 *)(p + 0x20);
    GatedDispatch(q, 0x14, 1, 7, 2);
    Gfx_BlitRequest(gRom_0822EF0C[0], 0x1b, 1, 1, 2);
}



__attribute__((section(".text.w5h_37ad8")))
void Task_37AD8(u8 *p)
{
    s8 v = (s8)p[0x469c];
    if (v == 4) {
        u32 z = 0;
        p[1] = 2;
        p[3] = z;
        p[2] = z;
    } else if (v == 9) {
        InitRec8_267B4(gEwram_020070F0, 8);
        p[0x4698] = 0;
    } else if (v == 8) {
        InitRec8_267B4(gEwram_020070F0, 8);
        p[0x4698] = 5;
    } else {
        u32 z = 0;
        p[1] = 1;
        p[3] = z;
        p[2] = z;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}



__attribute__((section(".text.w5h_38fe4")))
void Task_38FE4(u8 *p)
{
    s8 v = (s8)p[0x469c];
    if (v == 7) {
        u32 z = 0;
        p[1] = 2;
        p[2] = z;
        p[3] = z;
    } else if (v == 0xb) {
        InitRec8_267B4(gEwram_020070F0, 8);
        p[0x4698] = 0;
    } else if (v == 0xc) {
        InitRec8_267B4(gEwram_020070F0, 8);
        p[0x4698] = 4;
    } else {
        u32 z = 0;
        p[1] = 1;
        p[2] = z;
        p[3] = z;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}



__attribute__((section(".text.w5h_45ebc")))
u32 Task_45EBC(u8 *p)
{
    *(u32 *)(p + 0x46a8) = 0;
    *(u32 *)(p + 0x46ac) = 0;
    *(u32 *)(p + 4) = 1;
    p[0x46ae] = 0;
    p[0x46af] = 1;
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}

__attribute__((section(".text.w5h_4827c")))
u32 Task_4827C(u8 *p)
{
    u32 off = 0x46a8;
    *(u32 *)(p + 0x46a4) = 0;
    *(u32 *)(p + off) = 0;
    p[2] = 1;
    p[3] = 0;
    p[0x46a4] = 0;
    p[0x46a5] = 0;
    p[off - 2] = 0;
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}

__attribute__((section(".text.w5h_496a8")))
void SramInit_496A8(void)
{
    u8 *base = gEwram_020070F0;
    u32 z = 0;
    u8 *p10 = base + 0x10;
    u32 buf[2];
    buf[0] = z;
    CpuFastSet(buf, p10, 0x010000d8);
    buf[1] = z;
    CpuSet(buf + 1, base + (0xdc << 2), 0x05000003);
    *(u32 *)(base + 0x20) = (0xfa << 2);
}

__asm__(
    ".globl gEwram_020070F0\n.set gEwram_020070F0, 0x020070F0\n"
    ".globl gEwram_02004CE0\n.set gEwram_02004CE0, 0x02004CE0\n"
    ".globl gRom_0822EF0C\n.set gRom_0822EF0C, 0x0822EF0C\n"
);
