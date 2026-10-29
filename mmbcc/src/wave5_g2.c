/* Phase 3 Wave 5 POOL-G2 (4 matched C, coordinator-verified).
 * Evidence: docs/match_notes_wave5_g2.md. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* Task_360C4 @0x080360C4 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 200 bytes in built ROM.
 * Task mode handler: Teardown, switch on p[3] (5 cases):
 * case0 polls sub_0800B148(1,(s16)sub_08024514((u8)sub_080241F8(0x1000)),0);
 * case1 nested (u8) checks via sub_0800B2D8/sub_0800B320(0x0822EB44,0,0,0);
 * case2 falls through to case3; case4 resets p[0x4699]/p[4] and p[3]=1
 * on (u8)sub_0800B2F0. Then Setup, return 0.
 * Idioms: literal-0 for stack-passed 5th arg reproduces ROM's
 * `ldr;ldr;mov r4,#0;str r4,[sp]` scheduling. */
void EntryMgr_Teardown(void);
void EntryMgr_Setup(void);
u32 sub_080241F8(u32 v);
u32 sub_08024514(u32 v);
u32 sub_0800B148(u32 a, u32 b, u32 c);
u32 sub_0800B2D8(void);
u32 sub_0800B320(u32 a, u32 b, u32 c, u32 d);
u32 sub_0800B308(void);
u32 sub_0800B2B4(void);
u32 sub_0800B2F0(void);

__attribute__((section(".text.w5g_360c4")))
u32 Task_360C4(u8 *p)
{
    EntryMgr_Teardown();
    switch (p[3]) {
    case 0: {
        u8 v = (u8)sub_080241F8(0x1000);
        s16 s = (s16)sub_08024514(v);
        if ((u8)sub_0800B148(1, s, 0))
            p[3]++;
        break;
    }
    case 1:
        if ((u8)sub_0800B2D8()) {
            if ((u8)sub_0800B320(0x0822EB44, 0, 0, 0))
                p[3]++;
        }
        break;
    case 2:
        if ((u8)sub_0800B308())
            p[3]++;
    case 3:
        if ((u8)sub_0800B2B4())
            p[3]++;
        break;
    case 4:
        if ((u8)sub_0800B2F0()) {
            p[0x4699] = 0;
            p[4] = 0;
            p[3] = 1;
        }
        break;
    }
    EntryMgr_Setup();
    return 0;
}

/* Task_40798 @0x08040798 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * 7x Gfx_BlitRequest(ptr[i], 0x2f, 1/3/5/7/9/11/13, 8, 0);
 * pointers from ROM 0x082325E4..0x0823261C. */
void Gfx_BlitRequest(u32 a, u32 b, u32 c, u32 d, u32 e);
extern u32 gPtr082325E4[];
extern u32 gPtr082325EC[];
extern u32 gPtr082325F4[];
extern u32 gPtr082325FC[];
extern u32 gPtr08232604[];
extern u32 gPtr08232614[];
extern u32 gPtr0823261C[];

__attribute__((section(".text.w5g_40798")))
void Task_40798(void)
{
    Gfx_BlitRequest(gPtr082325E4[0], 0x2f, 1, 8, 0);
    Gfx_BlitRequest(gPtr082325EC[0], 0x2f, 3, 8, 0);
    Gfx_BlitRequest(gPtr082325F4[0], 0x2f, 5, 8, 0);
    Gfx_BlitRequest(gPtr082325FC[0], 0x2f, 7, 8, 0);
    Gfx_BlitRequest(gPtr08232604[0], 0x2f, 9, 8, 0);
    Gfx_BlitRequest(gPtr08232614[0], 0x2f, 11, 8, 0);
    Gfx_BlitRequest(gPtr0823261C[0], 0x2f, 13, 8, 0);
}

/* Task_45200 @0x08045200 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * Same 7x pattern with arg1=1; pointers from 0x08232C04..0x08232C3C. */
extern u32 gPtr08232C04[];
extern u32 gPtr08232C0C[];
extern u32 gPtr08232C14[];
extern u32 gPtr08232C1C[];
extern u32 gPtr08232C24[];
extern u32 gPtr08232C34[];
extern u32 gPtr08232C3C[];

__attribute__((section(".text.w5g_45200")))
void Task_45200(void)
{
    Gfx_BlitRequest(gPtr08232C04[0], 1, 1, 8, 0);
    Gfx_BlitRequest(gPtr08232C0C[0], 1, 3, 8, 0);
    Gfx_BlitRequest(gPtr08232C14[0], 1, 5, 8, 0);
    Gfx_BlitRequest(gPtr08232C1C[0], 1, 7, 8, 0);
    Gfx_BlitRequest(gPtr08232C24[0], 1, 9, 8, 0);
    Gfx_BlitRequest(gPtr08232C34[0], 1, 11, 8, 0);
    Gfx_BlitRequest(gPtr08232C3C[0], 1, 13, 8, 0);
}

/* Task_4529C @0x0804529C — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * Same 7x pattern with arg1=0x2f; same 0x08232C04 table. */
__attribute__((section(".text.w5g_4529c")))
void Task_4529C(void)
{
    Gfx_BlitRequest(gPtr08232C04[0], 0x2f, 1, 8, 0);
    Gfx_BlitRequest(gPtr08232C0C[0], 0x2f, 3, 8, 0);
    Gfx_BlitRequest(gPtr08232C14[0], 0x2f, 5, 8, 0);
    Gfx_BlitRequest(gPtr08232C1C[0], 0x2f, 7, 8, 0);
    Gfx_BlitRequest(gPtr08232C24[0], 0x2f, 9, 8, 0);
    Gfx_BlitRequest(gPtr08232C34[0], 0x2f, 11, 8, 0);
    Gfx_BlitRequest(gPtr08232C3C[0], 0x2f, 13, 8, 0);
}

__asm__(
    ".globl sub_080241F8\n.set sub_080241F8, 0x080241F8\n"
    ".globl sub_08024514\n.set sub_08024514, 0x08024514\n"
    ".globl sub_0800B2D8\n.set sub_0800B2D8, 0x0800B2D8\n"
    ".globl sub_0800B320\n.set sub_0800B320, 0x0800B320\n"
    ".globl sub_0800B308\n.set sub_0800B308, 0x0800B308\n"
    ".globl sub_0800B2B4\n.set sub_0800B2B4, 0x0800B2B4\n"
    ".globl sub_0800B2F0\n.set sub_0800B2F0, 0x0800B2F0\n"
    ".globl gPtr082325E4\n.set gPtr082325E4, 0x082325E4\n"
    ".globl gPtr082325EC\n.set gPtr082325EC, 0x082325EC\n"
    ".globl gPtr082325F4\n.set gPtr082325F4, 0x082325F4\n"
    ".globl gPtr082325FC\n.set gPtr082325FC, 0x082325FC\n"
    ".globl gPtr08232604\n.set gPtr08232604, 0x08232604\n"
    ".globl gPtr08232614\n.set gPtr08232614, 0x08232614\n"
    ".globl gPtr0823261C\n.set gPtr0823261C, 0x0823261C\n"
    ".globl gPtr08232C04\n.set gPtr08232C04, 0x08232C04\n"
    ".globl gPtr08232C0C\n.set gPtr08232C0C, 0x08232C0C\n"
    ".globl gPtr08232C14\n.set gPtr08232C14, 0x08232C14\n"
    ".globl gPtr08232C1C\n.set gPtr08232C1C, 0x08232C1C\n"
    ".globl gPtr08232C24\n.set gPtr08232C24, 0x08232C24\n"
    ".globl gPtr08232C34\n.set gPtr08232C34, 0x08232C34\n"
    ".globl gPtr08232C3C\n.set gPtr08232C3C, 0x08232C3C\n"
);
