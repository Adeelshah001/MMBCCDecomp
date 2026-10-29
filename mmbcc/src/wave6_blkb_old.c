/* Wave 6 BLK-B batch (2 verified, coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave6_blkB.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x080230A0: sub_080230A0 (coordinator-verified). */
/* sub_080230A0 @ 0x080230A0 — 2-byte diff test (v2).
 * ROM has `adds r0,r1,#0` before `cmp r0,#3` at 0x080230dc.
 */

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u8 gBase_081705B0[];
extern u8 gTbl_020031E4[];

__attribute__((section(".text.w6b_230a0")))
void sub_080230A0(u8 *s_in)
{
    u8 *s = s_in;
    u32 z = 0;
    u16 h;
    s32 v;

    *(u32 *)(s + 0x6c) = z;

    {
        register u8 vo __asm__("r0");
        vo = 2;
        vo |= s[0xa];
        vo |= 1;
        s[0xa] = vo;
    }

    ChipSlot_Setup(s, 0x3715, 0);
    ChipSlot_IncUse(s, 0);

    *(u32 *)(s + 0x50) = z;
    *(u32 *)(s + 0x54) = z;

    {
        u8 *base = (u8 *)0x081705B0;
        h = *(u16 *)(base + 2);
    }
    {
        s32 w;
        u32 idx = (h >> 4) << 1;
        u8 *tbl;
        __asm__ volatile("" : : : "memory");
        tbl = gTbl_020031E4;
        v = 3 & tbl[idx];
        __asm__ volatile("add %0, %1, #0" : "=l"(w) : "l"(v));
        if (w > 3)
            v = 3;
    }

    {
        u8 *q = s + 0x45;
        u32 mask;
        u32 t;
        v <<= 2;
        mask = 13;
        mask = -mask;
        t = *q;
        t &= mask;
        t |= (u32)v;
        *q = t;
    }

    s[0x22] = 31;
}

/* 0x08037440: Task_37440 (coordinator-verified). */
/* Task_37440 @ 0x08037440 (120 B) v3.
 * No pinning; goto-beq for branch structure.
 */

extern u8 gEwram_02004E40[];
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);
extern u32 sub_0800B368(u32 fn, u32 a, u32 b, u32 c);
extern u32 sub_0800B308(void);

__attribute__((section(".text.w6b_37440")))
u32 Task_37440(u8 *p)
{
    u8 mode;

    EntryMgr_Teardown();
    {
        register u8 *g __asm__("r1") = gEwram_02004E40;
        g[0x14] |= 1;
    }

    mode = p[5];
    if (mode == 0)
        goto case0;
    if (mode == 1)
        goto case1;
    goto epi;

case0: {
        u32 *tbl = (u32 *)0x082300E0;
        u8 idx;
        u32 fn;
        __asm__ volatile("" : : : "memory");
        idx = p[0x469f];
        fn = tbl[idx];
        if (((u8)sub_0800B368(fn, 0, 0, 0)) == 0)
            goto epi;
        {
            u8 m;
            __asm__ volatile(
                "ldrb %0, [%1, #5]\n\t"
                "add %0, #1\n\t"
                "strb %0, [%1, #5]"
                : "=&l"(m) : "l"(p));
        }
        goto epi;
    }

case1:
    if (((u8)sub_0800B308()) != 0) {
        u8 *q = p + 0x4699;
        u8 z = 0;
        *q = mode;
        p[5] = z;
    }

epi:
    EntryMgr_Setup();
    return 0;
}

__asm__(
    ".set gBase_081705B0,0x081705B0\n\t"
    ".set gTbl_020031E4,0x020031E4\n\t"
    ".set gEwram_02004E40,0x02004E40\n\t"
    ".thumb_func\n"
    ".set sub_0800B368,0x0800B368\n\t"
    ".thumb_func\n"
    ".set sub_0800B308,0x0800B308\n\t"
);
