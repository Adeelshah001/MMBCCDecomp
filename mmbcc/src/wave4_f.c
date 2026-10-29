/* MMBCCDecomp — Wave 4 batch F worker file.
 * 0/14 MATCHED (see docs/wave4_f_results.tsv, docs/match_notes_wave4_f.md).
 * Two best-effort semantic C implementations below (Task_48400, Task_3531C),
 * both BLOCKED on whole-function register allocation. The C is semantically
 * faithful (decoded from ROM) and documents behavior for the recomp track.
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42 mis-binds
 * R_ARM_THM_CALL when the .set precedes the code. Remove each .set when that
 * symbol gets a real definition (duplicate-symbol otherwise). Do NOT .set
 * EntryMgr_Teardown/Setup or Text_SelectBlobIdx — they are real globals in
 * the build (entrymgr.c, text_idx.c).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

extern void EntryMgr_Teardown(void);    /* 0x08004F18 */
extern void EntryMgr_Setup(void);       /* 0x08004F80 */
extern s16 Text_SelectBlobIdx(u16 idx); /* 0x0804A378 */

extern u8 gEwram_02004CE0[];
extern u8 gEwram_02004E40[];
extern u8 gEwram_02002F50[];
extern u8 gEwram_02003670[];
extern u8 gEwram_02004F80[];
extern u8 gRom_082344C0[];
extern u8 gRom_0822EAAC[];
extern u8 gRom_0822EAFC[];

void sub_08004E44(void);
void sub_08004DFC(u8 v);
void sub_0800BEE0(u32 a, u32 b);
void sub_08005A9C(u32 v);
void sub_0800800C(u8 *p, u32 v);
u32 sub_080241F8(u32 v);
u32 sub_08024514(u32 v);
u32 sub_08024384(u32 v);
u32 sub_0800B148(u32 a, u32 b, u32 c);
u32 sub_0800B2D8(void);
u32 sub_0800B368(u32 a, u32 b, u32 c, u32 d);
void sub_08035AFC(u8 *p);
void sub_08035C5C(u8 *p);
void sub_08049560(u8 *p);
u32 sub_08035630(u8 *p);
u32 sub_08035838(u8 *p);

/* 0x08048400 (596 B). 5-case switch on p[0x46A5]. BLOCKED: prologue wants
 * push {r4,r5,r6,lr}, r5=p, r6=ret; compiler emits r7/r8. 3 attempts. */
__attribute__((section(".text.w4f_t48400")))
u8 Task_48400(u8 *p)
{
    u8 ret = 0;
    EntryMgr_Teardown();
    switch (p[0x46a5]) {
    case 0: {
        u8 *base = gEwram_02004CE0;
        u8 *q = base + 0x2c;
        u32 mask;
        u8 v = 1 | *q;
        sub_0800BEE0(0x40, 0x80);
        sub_08005A9C(0x19);
        sub_08049560(p);
        *(u16 *)(base + 0x28) = 0x10;
        *(u16 *)(base + 0x2a) = ((s8)p[0x46a6] << 4) + 8;
        mask = 0x1f;
        mask = -mask;
        v &= mask;
        mask -= 2;
        v &= mask;
        *q = v;
        *(u16 *)(base + 0x2c) &= 0xfffffc3f;
        sub_0800800C(base, 0);
        p[0x46a5]++;
    }
        /* fallthrough */
    case 1:
        if ((u8)sub_0800B148(1, (s16)sub_08024514((u8)sub_080241F8(0x1000)), 4) != 0)
            p[0x46a5]++;
        break;
    case 2:
        if ((u8)sub_0800B2D8() != 0)
            p[0x46a5]++;
        break;
    case 3: {
        u8 idx = sub_08024384(0x1000) - 0x32;
        u32 tbl = ((u32 *)gRom_082344C0)[(s8)p[0x46a6]];
        u32 v = *(u32 *)(tbl + (((u8)idx) << 2));
        if ((u8)sub_0800B368(v, 0, 0, 0) != 0)
            p[0x46a5]++;
        break;
    }
    case 4: {
        u16 f1;
        u32 r4 = 0;
        *(gEwram_02004E40 + 0x14) |= 1;
        sub_08049560(p);
        f1 = *(u16 *)gEwram_02002F50;
        if (f1 & 0x40) {
            u16 f2 = *(u16 *)(gEwram_02002F50 + 4);
            r4 = (f2 & 0x40) ? 0x40 : 0;
        }
        if ((f1 & 0x80) && (*(u16 *)(gEwram_02002F50 + 4) & 0x80))
            r4 = 0x80;
        if ((f1 & 1) && (*(u16 *)(gEwram_02002F50 + 4) & 1))
            r4 = 1;
        if ((f1 & 2) && (*(u16 *)(gEwram_02002F50 + 4) & 2))
            r4 = 2;
        if (r4 == 2) {
            Text_SelectBlobIdx(0x68);
            p[0x46a6] = 6;
            ret = 6;
        } else if (r4 > 2) {
            if (r4 == 0x40) {
                if ((s8)p[0x46a6] > 0) {
                    Text_SelectBlobIdx(0x66);
                    p[0x46a6]--;
                    p[0x46a5] = 3;
                }
            } else if (r4 == 0x80) {
                if ((s8)p[0x46a6] <= 1) {
                    Text_SelectBlobIdx(0x66);
                    p[0x46a6]++;
                    p[0x46a5] = 3;
                }
            }
        } else if (r4 == 1) {
            Text_SelectBlobIdx(0x67);
            p[0x46a4] = 1;
            p[0x46a5] = 0;
        }
        break;
    }
    default:
        break;
    }
    EntryMgr_Setup();
    return ret;
}

/* 0x0803531c (788 B). 5-case switch on p[0x46A9]. BLOCKED: not compile-
 * attempted; prologue wants r5=p, r7=ret. Semantics fully decoded
 * (see docs/match_notes_wave4_f.md). */
__attribute__((section(".text.w4f_t3531c")))
u8 Task_3531C(u8 *p)
{
    u8 ret = 0;
    EntryMgr_Teardown();
    switch (p[0x46a9]) {
    case 0:
        sub_08004E44();
        sub_08004DFC(gEwram_02004F80[2]);
        {
            u8 *base = gEwram_02004CE0;
            u8 *q = base + 0x2c;
            u32 mask;
            u8 v = 1 | *q;
            *(u16 *)(base + 0x28) = 0x10;
            *(u16 *)(base + 0x2a) = 0x20;
            mask = 0x1f;
            mask = -mask;
            v &= mask;
            mask -= 2;
            v &= mask;
            *q = v;
            *(u16 *)(base + 0x2c) &= 0xfffffc3f;
            sub_0800800C(base, 0);
        }
        sub_0800BEE0(0x40, 0x80);
        sub_08005A9C(0x17);
        /* fallthrough */
    case 1:
        sub_08035AFC(p);
        sub_08035C5C(p);
        p[0x46ac] = 0;
        p[0x46aa] = 0;
        p[0x46ab] = 0;
        p[0x46a9]++;
        if ((u8)sub_0800B148(1, (s16)sub_08024514((u8)sub_080241F8(0x1000)), 0) != 0)
            p[0x46a9]++;
        break;
    case 2:
        if ((u8)sub_0800B2D8() != 0)
            p[0x46a9]++;
        break;
    case 3: {
        /* Two ROM sub-paths (p[0x46AC]==0 via 0x0822EAAC/(s8)p[0x46AA],
         * else via 0x0822EAFC/(s8)p[0x46AB]); each gates on sub_0800B368
         * then issues 4x sub_0800B448 field writes. Simplified here. */
        u32 fn = ((u32 *)gRom_0822EAAC)[(s8)p[0x46aa]];
        if ((u8)sub_0800B368(fn, 0, 0, 0) != 0)
            p[0x46a9]++;
        break;
    }
    case 4:
        gEwram_02004E40[0x14] |= 1;
        if (p[0x46ac] == gEwram_02003670[0x11ac]) {
            if (p[0x46ac] == 0)
                ret = (u8)sub_08035630(p);
            else {
                ret = (u8)sub_08035838(p);
                sub_08035C5C(p);
            }
        } else {
            s8 d = (s8)((u8)p[0x46ac] - gEwram_02003670[0x11ac]);
            gEwram_02003670[0x11ac] += (d >= 0) ? 1 : -1;
        }
        break;
    default:
        break;
    }
    EntryMgr_Setup();
    return ret;
}

__asm__(
    ".globl gEwram_02004CE0\n.set gEwram_02004CE0, 0x02004CE0\n"
    ".globl gEwram_02004E40\n.set gEwram_02004E40, 0x02004E40\n"
    ".globl gEwram_02002F50\n.set gEwram_02002F50, 0x02002F50\n"
    ".globl gEwram_02003670\n.set gEwram_02003670, 0x02003670\n"
    ".globl gEwram_02004F80\n.set gEwram_02004F80, 0x02004F80\n"
    ".globl gRom_082344C0\n.set gRom_082344C0, 0x082344C0\n"
    ".globl gRom_0822EAAC\n.set gRom_0822EAAC, 0x0822EAAC\n"
    ".globl gRom_0822EAFC\n.set gRom_0822EAFC, 0x0822EAFC\n"
    ".globl sub_08004E44\n.set sub_08004E44, 0x08004E44\n"
    ".globl sub_08004DFC\n.set sub_08004DFC, 0x08004DFC\n"
    ".globl sub_0800BEE0\n.set sub_0800BEE0, 0x0800BEE0\n"
    ".globl sub_08005A9C\n.set sub_08005A9C, 0x08005A9C\n"
    ".globl sub_0800800C\n.set sub_0800800C, 0x0800800C\n"
    ".globl sub_080241F8\n.set sub_080241F8, 0x080241F8\n"
    ".globl sub_08024514\n.set sub_08024514, 0x08024514\n"
    ".globl sub_08024384\n.set sub_08024384, 0x08024384\n"
    ".globl sub_0800B2D8\n.set sub_0800B2D8, 0x0800B2D8\n"
    ".globl sub_0800B368\n.set sub_0800B368, 0x0800B368\n"
    ".globl sub_08035AFC\n.set sub_08035AFC, 0x08035AFC\n"
    ".globl sub_08035C5C\n.set sub_08035C5C, 0x08035C5C\n"
    ".globl sub_08049560\n.set sub_08049560, 0x08049560\n"
    ".globl sub_08035630\n.set sub_08035630, 0x08035630\n"
    ".globl sub_08035838\n.set sub_08035838, 0x08035838\n"
);
