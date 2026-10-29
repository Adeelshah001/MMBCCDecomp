/* Wave 41 coordinator landing: coordinator-verified 0-diff (standalone
 * rebuild + independent ROM-extract cmp). See staging/w41coord_verify/COORD_LOG.md.
 */
/* W41-C v4: F_08015ac4 @ 0x08015ac4, 560 B. Rework of W40-D v1:
   - Block layout follows ROM: p6: after case 2, check119: after p6,
     inc: after case 5 (case 5 falls through), tail: after case 6
     (case 6 falls through).
   - check119 tests in if/else-if/else shape (ROM: bne+b-tail, bhi+body).
   - F_0801D070 is 4-arg (0, s, buf, p[8]) with u32 buf[2]={0,0}
     (frame: outgoing sp+0 + buf sp+4/sp+8 = 12).
   - NewNode decl fixed: (u8, s32, u8, u32, u32); -4 via negs, full
     0xffffc400 pool word.
   - Bit-set via per-case variable base tbl (defeats single-const fold).
   - Post-call barriers in case 0 (after IncUse, before goto inc) and
     case 3 (after SetBytes, before goto tail) defeat cross-jump merges.
   NOTE: check119 2nd test direction corrected vs W40 notes: ROM shows
   v>6 -> F body (bhi to body), v<=6 -> tail. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void SetMirrored_0800DD2C(u8 *s, u32 x, u8 y);
extern void IncUse_0800D9EC(u8 *s, u8 idx);
extern s32 GetField17_08017474(u32 p);
extern s32 Check119_08011F50(u8 *s);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void MaxAssign_08017478(u32 p, u8 v);
extern void DecIfNonZero_08017464(u32 p);
extern u8 *NewNode_0801EE14(u8 a, s32 b, u32 c, u32 d, u32 e);
extern void Text_SelectBlobIdx_0804A378(s32 idx);
extern void F_0801D070(s32 a, u8 *s, u32 *out, u16 v);
extern void ChipSlot_Tick_0800D9FC(u8 *s);

__attribute__((section(".text.w41c_08015ac4")))
void F_08015ac4(u8 *s) {
    u8 *p = s + 124;
    u8 mode = s[14];
    if (mode > 6) goto tail;
    switch (mode) {
    case 0:
        SetMirrored_0800DD2C(s, 0xffffc400, 0);
        IncUse_0800D9EC(s, 0);
        __asm__ volatile("" ::: "memory");
        goto inc;
    case 1: {
        u8 v;
        v = (u8)GetField17_08017474(*(u32 *)(s + 44));
        if (v == 0) goto tail;
        v = (u8)GetField17_08017474(*(u32 *)(s + 44));
        if (v > 6) {
            s[14] = 3;
            goto tail;
        }
        {
            u8 *tbl = (u8 *)0x02003670;
            __asm__ volatile("" : "+r" (tbl));
            *(tbl + 0x11af) = (*(tbl + 0x11af) & 15) | 64;
        }
        s[33] = 10;
        IncUse_0800D9EC(s, 3);
        s[14]++;
        goto p6;
    }
    case 2: {
        u8 v;
        v = (u8)GetField17_08017474(*(u32 *)(s + 44));
        if (p[6] >= v) goto check119;
        v = (u8)GetField17_08017474(*(u32 *)(s + 44));
        if (v > 5) goto check119;
        {
            u8 *tbl = (u8 *)0x02003670;
            __asm__ volatile("" : "+r" (tbl));
            *(tbl + 0x11af) = (*(tbl + 0x11af) & 15) | 64;
        }
        s[33] = 10;
        IncUse_0800D9EC(s, 3);
        goto p6;
    }
    p6:
        p[6] = (u8)GetField17_08017474(*(u32 *)(s + 44));
        goto tail;
    check119:
        if ((s16)Check119_08011F50(s) == 0) goto tail;
        else if ((u8)GetField17_08017474(*(u32 *)(s + 44)) > 6) {
            u32 buf[2] = {0, 0};
            F_0801D070(0, s, buf, *(u16 *)(p + 8));
            if (p[7] == 2) {
                IncUse_0800D9EC(s, 7);
                s[14] = 4;
                goto tail;
            } else {
                IncUse_0800D9EC(s, 0);
                goto inc;
            }
        } else goto tail;
    case 3:
        if ((u8)GetField17_08017474(*(u32 *)(s + 44)) <= 6) goto tail;
        MaxAssign_08017478(*(u32 *)(s + 44), 8);
        DecIfNonZero_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        SetMirrored_0800DD2C(s, 0xffffc400, 0);
        IncUse_0800D9EC(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
        __asm__ volatile("" ::: "memory");
        goto tail;
    case 4: {
        u8 *q = s + 33;
        u32 zero = 0;
        *q = 60;
        s[18] = 40;
        NewNode_0801EE14(0, -4, ((u32)s[35] << 28) >> 28, 0xffffc400, zero);
        goto inc;
    }
    case 5:
        s[18]--;
        if (s[18] != 0) goto tail;
        IncUse_0800D9EC(s, 2);
        Text_SelectBlobIdx_0804A378(127);
    inc:
        s[14]++;
        goto tail;
    case 6: {
        u32 zero;
        u8 m;
        u8 v10;
        if ((u8)GetField17_08017474(*(u32 *)(s + 44)) <= 6) goto tail;
        m = 254;
        v10 = s[10] & m;
        zero = 0;
        s[10] = v10;
        MaxAssign_08017478(*(u32 *)(s + 44), 8);
        DecIfNonZero_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = zero;
        SetMirrored_0800DD2C(s, 0xffffc400, 0);
        IncUse_0800D9EC(s, 0);
        p[4] = zero;
        SetBytes_08011F68(s, 0);
    }
    }
tail:
    ChipSlot_Tick_0800D9FC(s);
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".set SetMirrored_0800DD2C, 0x0800dd2c\n"
    ".set IncUse_0800D9EC, 0x0800d9ec\n"
    ".set GetField17_08017474, 0x08017474\n"
    ".set Check119_08011F50, 0x08011f50\n"
    ".set MaxAssign_08017478, 0x08017478\n"
    ".set DecIfNonZero_08017464, 0x08017464\n"
    ".set Text_SelectBlobIdx_0804A378, 0x0804a378\n"
    ".set F_0801D070, 0x0801d070\n"
    ".set ChipSlot_Tick_0800D9FC, 0x0800d9fc\n"
);
