/* W68-C CLAIM (pure C, 0 diffs): 0x080146C0, 316 B, old_agbcc.
 * Key ordering vs base: m = 15; b = gEntryMgr[0x11AF]; f = 0xF0;
 * gEntryMgr[0x11AF] = (b & m) | f;  -- the compiler splits the b load
 * into address (ldr/ldr/add) + ldrb and places the f mov between them,
 * emitting ROM's window verbatim (mov r0,#15; ldr r1; ldr r2; add;
 * mov r2,#240; ldrb r3; and r0,r3; orr r0,r2; strb r0,[r1]).
 * Semantics: single read of B, single write of (B & 15) | 0xF0; no calls
 * or aliasing between read and write (f is a local int).
 * FLAG (unchanged from base): Check119_Minus3_Le1 is declared u16 here
 * while the landed prototype is unsigned int; only the narrow form emits
 * caller-side lsl#16/cmp/beq in cases 1+3 -- rule on this before landing.
 * This pure-C claim supersedes the W67 asm proposal2 (now moot as backup).
 */
/* Wave 65-D v1: 0x080146C0 (316 B true extent: 312 code + 4 pool).
 * INTERIOR-DISPATCH CHECK: CLEARS as a single function (see RESULTS.md).
 * It is a switch statement, not a multi-function dispatcher: one frame
 * (push {r4,r5,r6,lr}, sub sp,#4), case bodies are inline blocks that
 * share the increment block @0x147BC and the epilogue @0x147EA, and
 * the "bx r2/bx r7" bytes are jump-table WORDS misdecoded as code
 * (table @0x146E0: targets 0x146F8/0x14710/0x1473E/0x14790/0x147A6/
 * 0x147C4; pool @0x146DC = 0x080146E0). The mov pc,r0 at 0x146DA stays
 * in Thumb state (ARMv4T mov-to-PC does not switch state), so the
 * even table entries are correct.
 * Pools re-derived from raw LE bytes: @0x146DC=0x080146E0 (table addr),
 * @0x1470C=0xFFFFC400, @0x14784=0xFFFFEC00, @0x14788=0x02003670,
 * @0x1478C=0x000011AF, @0x147F8=0xFFFFC400 (dup of @0x1470C).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

void Vec2_SetMirrored(u8 *o, s32 x, s32 y);
void ChipSlot_IncUse(u8 *s, u8 idx);
void ChipSlot_Tick(u8 *s);
u16 Check119_Minus3_Le1(u8 *s);
void SetBit16(u8 *s, u8 bit);
void PalModeSet_4DFC(u8 a);
u16 Text_SelectBlobIdx(u16 idx);
void sub_080178A8(u32 a, u32 b, u32 c, u32 d, u8 *e);
u8 TestBit16(u8 *s, u8 bit);
u8 GetField17_U8(u8 *s);
void MaxAssign_17(u8 *s, u8 v);
void DecIfNonZero_18(u8 *s);
void SetBytes_08011F68(u8 *s, u8 v);
extern u8 gEntryMgr[];

__attribute__((section(".text.w68c_080146c0")))
void sub_080146C0(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 8);
        s[14]++;
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        SetBit16(*(u8 **)(s + 44), 3);
        PalModeSet_4DFC(2);
        Text_SelectBlobIdx(149);
        s[18] = 10;
        ChipSlot_IncUse(s, 9);
        s[14]++;
        break;
    case 2: {
        u8 *p = s;
        u8 nib;
        u8 m;
        int f;
        u8 b;
        if (--s[18] != 0)
            break;
        p += 35;
        nib = (u32)(p[0] << 28) >> 28;
        sub_080178A8(130, nib, 0xFFFFEC00, 0, *(u8 **)(s + 44));
        if (TestBit16(*(u8 **)(s + 44), 0) != 0) {
            s[14]++;
            break;
        }
        m = 15;
        b = gEntryMgr[0x11AF];
        f = 0xF0;
        gEntryMgr[0x11AF] = (b & m) | f;
        s[14]++;
        break;
    }
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 10);
        s[14]++;
        break;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
            break;
        MaxAssign_17(*(u8 **)(s + 44), 7);
        s[14]++;
        break;
    case 5:
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u8 **)(s + 44) = 0;
        Vec2_SetMirrored(s, 0xFFFFC400, 0);
        ChipSlot_IncUse(s, 0);
        q[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}

__asm__(
    ".globl PalModeSet_4DFC\n.set PalModeSet_4DFC, 0x08004DFC\n"
    ".globl sub_080178A8\n.set sub_080178A8, 0x080178A8\n"
    ".globl gEntryMgr\n.set gEntryMgr, 0x02003670\n"
);
