/* Wave 26-C: 0x08042c04 — switch on s[5], entry manager states */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

void Set_08004E24(u8 x);
void EntryMgr_Teardown(void);
int Cmp_08004E0C(u8 x);
void EntryMgr_Setup(void);
void PalModeSet_4DFC(u8 a);

extern u8 g_02004F80[];
extern u16 g_020031E0[];

__attribute__((section(".text.w26c_08042c04")))
u8 F_08042C04(u8 *s)
{
    switch (s[5]) {
    case 0:
        Set_08004E24(0);
        s[5]++;
        /* fall through */
    case 1:
        EntryMgr_Teardown();
        if ((Cmp_08004E0C(3) << 24) != 0) {
            u16 v = g_020031E0[0];
            v = (u16)(v & 0xEDFFu);
            v = (u16)(v & 0xDBFFu);
            g_020031E0[0] = v;
            s[5]++;
        }
        EntryMgr_Setup();
        break;
    case 2:
        PalModeSet_4DFC(g_02004F80[2]);
        s[5]++;
        /* fall through */
    case 3: {
        int r;
        EntryMgr_Teardown();
        r = (Cmp_08004E0C(0) << 24) >> 24;
        if (r == 0) {
            if (s[7] == 1) {
                s[7] = s[4];
                s[4] = 3;
            } else {
                s[7] = s[4];
                s[4] = 1;
            }
            s[5] = (u8)r;
            s[6] = (u8)r;
        }
        EntryMgr_Setup();
        break;
    }
    default:
        break;
    }
    return 0;
}

__asm__(
    ".thumb_func\n"
    ".globl PalModeSet_4DFC\n"
    ".set PalModeSet_4DFC, 0x08004dfc\n"
    ".thumb_func\n"
    ".globl g_02004F80\n"
    ".set g_02004F80, 0x02004f80\n"
    ".thumb_func\n"
    ".globl g_020031E0\n"
    ".set g_020031E0, 0x020031e0\n"
);
