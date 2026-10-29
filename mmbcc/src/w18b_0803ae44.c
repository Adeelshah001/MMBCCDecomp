/* Wave 18-B: 0x0803AE44 (60 B, 0 callers, 3 bl).
   Task init: zero fields, TblState_0804A2DC(9), Teardown/Setup. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void TblState_0804A2DC(u16 a);
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);

__attribute__((section(".text.w18b_0803ae44")))
void TaskInit_0803AE44(u8 *p)
{
    u32 z = 0;
    u8 *q;

    *(u32 *)(p + 0x4698) = 0;
    q = p + 0x469c;
    *(u32 *)q = 0;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    *q = 0;
    *(u8 *)(p + 0x469d) = 0;
    TblState_0804A2DC(9);
    *(u8 *)(p + 0x46b0) = 0;
    EntryMgr_Teardown();
    EntryMgr_Setup();
}
