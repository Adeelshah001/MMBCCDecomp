/* MMBCCDecomp — Wave 4 batch K staged matches (mode-dispatch handlers).
 * MATCHED 2026-10-20. 5/12 functions byte-identical (main agbcc -O2
 * -mthumb-interwork). 2 old_agbcc functions split to wave4_k_old.c.
 * 5 BLOCKED (see docs/match_notes_wave4_k.md).
 *
 * Functions (all names tentative — inferred from behavior only):
 *  0x08035E0C Task_35E0C   (52 B)  task init: p[1]=2, zero p[2..4], p[0x4699],
 *                               p[0x46B7]; sub_0804A2DC(6); Teardown/Setup
 *  0x08035F0C Task_35F0C   (66 B)  if p[0x46B7]==8: sub_0804A328,
 *                               sub_080267B4(gEwram020070F0,8), p[0x4698]=0;
 *                               else p[1]=1; Teardown/Setup (+2 pad object)
 *  0x080360B0 Task_360B0   (18 B)  return (u8)sub_080400D0(p,0,0) (+2 pad object)
 *  0x08036664 Task_36664   (68 B)  task init: *(u32*)(p+0x4698)=0,
 *                               *(u32*)(p+0x469C)=0, p[1]=1, zero p[2],p[3],
 *                               p[0x4699],p[5],p[0x469E]; sub_0804A2DC(7);
 *                               Teardown/Setup
 *  0x08036780 Task_36780   (96 B)  sub_080267B4(gEwram020070F0,8);
 *                               sub_0804A328(); if p[0x469F]==0/1/2:
 *                               p[0x4698]=1/2/3; Teardown/Setup
 *
 * (Task_35EB0 @0x08035EB0 and Task_36724 @0x08036724 live in
 * wave4_k_old.c — they need old_agbcc.)
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md). Remove each .set when that symbol gets
 * a real definition (duplicate-symbol otherwise).
 *
 * Landing notes:
 * - Task_360B0 (0x080360B0): section carries an explicit 00 00 pad
 *   object (ROM: 18 B code + 0000, next function at 0x080360C4).
 * - Task_35F0C (0x08035F0C): section carries an explicit 00 00 pad
 *   object (ROM: 66 B code + 0000, next function at 0x08035F50).
 * - All other sections are exact size (pools included where present).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void sub_0804A2DC(u32 v);
void sub_0804A328(void);
void sub_080267B4(u8 *a, u32 b);
u32 sub_08004E24(u32 v);
u32 sub_08004E0C(u32 v);
u32 sub_080400D0(u8 *p, u32 b, u32 c);
void EntryMgr_Teardown(void);
void EntryMgr_Setup(void);
extern u8 gEwram020070F0[];
extern u16 gEwram_020031E0[];

/* 0x08035E0C: task init. Tentative. */
__attribute__((section(".text.w4k_t35e0c")))
void Task_35E0C(u8 *p)
{
    u8 z = 0;
    p[1] = 2;
    p[3] = z;
    p[2] = z;
    p[0x4699] = z;
    p[4] = z;
    p[0x46B7] = z;
    sub_0804A2DC(6);
    EntryMgr_Teardown();
    EntryMgr_Setup();
}

/* 0x08035F0C: conditional init. Tentative. */
__attribute__((section(".text.w4k_t35f0c")))
void Task_35F0C(u8 *p)
{
    if (p[0x46B7] == 8) {
        sub_0804A328();
        sub_080267B4(gEwram020070F0, 8);
        p[0x4698] = 0;
    } else {
        p[1] = 1;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}

/* 2-byte zero pad: ROM has 0000 at 0x08035F4E (next function at
 * 0x08035F50); GAS would otherwise end the section with c046. */
__attribute__((section(".text.w4k_t35f0c")))
static const u8 sPad_Task_35F0C[2] = { 0, 0 };

/* 0x080360B0: poll wrapper. Tentative. */
__attribute__((section(".text.w4k_t360b0")))
u8 Task_360B0(u8 *p)
{
    return (u8)sub_080400D0(p, 0, 0);
}

/* 2-byte zero pad: ROM has 0000 at 0x080360C2 (next function at
 * 0x080360C4); GAS would otherwise end the section with c046. */
__attribute__((section(".text.w4k_t360b0")))
static const u8 sPad_Task_360B0[2] = { 0, 0 };

/* 0x08036664: task init, 32-bit stores. Tentative. */
__attribute__((section(".text.w4k_t36664")))
void Task_36664(u8 *p)
{
    *(u32 *)(p + 0x4698) = 0;
    *(u32 *)(p + 0x469C) = 0;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    p[0x4699] = 0;
    p[5] = 0;
    p[0x469E] = 0;
    sub_0804A2DC(7);
    EntryMgr_Teardown();
    EntryMgr_Setup();
}

/* 0x08036780: mode-to-value map. Tentative. */
__attribute__((section(".text.w4k_t36780")))
void Task_36780(u8 *p)
{
    sub_080267B4(gEwram020070F0, 8);
    sub_0804A328();
    if (p[0x469F] == 0) {
        p[0x4698] = 1;
    } else if (p[0x469F] == 1) {
        p[0x4698] = 2;
    } else if (p[0x469F] == 2) {
        p[0x4698] = 3;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
}

__asm__(
    ".globl sub_0804A2DC\n.set sub_0804A2DC, 0x0804A2DC\n"
    ".globl sub_0804A328\n.set sub_0804A328, 0x0804A328\n"
    ".globl sub_080267B4\n.set sub_080267B4, 0x080267B4\n"
    ".globl sub_08004E24\n.set sub_08004E24, 0x08004E24\n"
    ".globl sub_08004E0C\n.set sub_08004E0C, 0x08004E0C\n"
    ".globl sub_080400D0\n.set sub_080400D0, 0x080400D0\n"
    ".globl gEwram_020031E0\n.set gEwram_020031E0, 0x020031E0\n"
);
