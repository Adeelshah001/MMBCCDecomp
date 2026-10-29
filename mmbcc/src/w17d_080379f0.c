/* Worker D wave17 Part1 C1 re-derivation @0x080379f0 (62B). */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void PalModeSet_4DFC(u8 a);
extern void EntryMgr_Teardown(void);
extern int Cmp_08004E0C(u8 x);
extern void EntryMgr_Setup(void);
__attribute__((section(".text.w17d_080379F0")))
void StateMachine_080379F0(u8 *p)
{
    u8 t = p[2];
    switch (t) {
    case 0:
        PalModeSet_4DFC(1);
        p[2]++;
        /* fallthrough */
    case 1: {
        u32 r;
        EntryMgr_Teardown();
        r = (u32)(s8)Cmp_08004E0C(0);
        if (r == 0) {
            p[1] = 2;
            p[3] = (u8)r;
            p[2] = (u8)r;
        }
        EntryMgr_Setup();
        break;
    }
    default:
        break;
    }
}

