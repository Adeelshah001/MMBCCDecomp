/* MMBCCDecomp — Wave 4 batch K, old_agbcc TU (split from wave4_k.c).
 * MATCHED 2026-10-20. 2/2 functions byte-identical with old_agbcc
 * (main agbcc swaps r0/r1 in the mask-clear sequence).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void sub_0804A2DC(u32 v);
u32 sub_08004E24(u32 v);
u32 sub_08004E0C(u32 v);
void EntryMgr_Teardown(void);
void EntryMgr_Setup(void);
extern u16 gEwram_020031E0[];

/* 0x08035EB0: mode dispatch, mask-clear variant. Tentative. OLD_AGBCC. */
__attribute__((section(".text.w4k_t35eb0")))
void Task_35EB0(u8 *p)
{
    switch (p[2]) {
    case 0:
        sub_08004E24(0);
        p[2]++;
    case 1: {
        EntryMgr_Teardown();
        if ((u8)sub_08004E0C(3) != 0) {
            u8 z = 0;
            u16 v;
            p[1] = 4;
            p[3] = z;
            p[2] = z;
            { u16 *g = gEwram_020031E0; v = 0xEDFF; v &= g[0]; v &= 0xDBFF; g[0] = v; }
        }
        EntryMgr_Setup();
        break;
    }
    }
}

/* 0x08036724: mode dispatch, mask-clear variant (twin of Task_35EB0). Tentative. OLD_AGBCC. */
__attribute__((section(".text.w4k_t36724")))
void Task_36724(u8 *p)
{
    switch (p[2]) {
    case 0:
        sub_08004E24(0);
        p[2]++;
    case 1: {
        EntryMgr_Teardown();
        if ((u8)sub_08004E0C(3) != 0) {
            u8 z;
            {
                u16 *g = gEwram_020031E0;
                u16 v = 0xEDFF;
                v &= g[0];
                z = 0;
                v &= 0xDBFF;
                g[0] = v;
            }
            p[1] = 4;
            p[2] = z;
            p[3] = z;
        }
        EntryMgr_Setup();
        break;
    }
    }
}

