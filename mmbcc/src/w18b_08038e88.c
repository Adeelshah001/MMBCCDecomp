/* Wave 18-B: 0x08038E88 (98 B, 0 callers, 5 bl).
   Task init variant with FlagBit_Set calls. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void FlagBit_Set_11D68(u16 x, u8 y);
extern void TblState_0804A2DC(u16 a);
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);

__attribute__((section(".text.w18b_08038e88")))
void TaskInit_08038E88(u8 *p)
{
    u8 v7 = (u8)(p[20] + 1);
    u32 z = 0;
    u8 *p5;
    u8 *p1;

    if (v7 > 9)
        v7 = 9;
    p5 = p + 0x4698;
    *(u32 *)p5 = 0;
    p1 = p + 0x469c;
    *(u32 *)p1 = 0;
    *(u32 *)(p + 0x46a0) = 0;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    *p1 = 0;
    *(u8 *)(p + 0x469d) = 0;
    FlagBit_Set_11D68(1, 0);
    FlagBit_Set_11D68(2, 0);
    *p5 = 0;
    *(u8 *)(p + 0x469b) = v7;
    TblState_0804A2DC(9);
    EntryMgr_Teardown();
    EntryMgr_Setup();
}
