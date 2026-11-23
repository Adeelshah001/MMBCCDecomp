typedef struct { u32 words[4]; } MenuControl;
typedef u32 (*DispatchCallback)(u8 *);
extern DispatchCallback const D_08234D4C[];
extern u32 sub_0804DCD0(u8 *, DispatchCallback);
extern s8 sub_08028778(u8 *, int);
extern void sub_08002FD4(u16);
extern u8 D_0200BD20[];

s8 sub_0804AF90(u8 *entry)
{
    u32 base = (u32)D_08234D4C;
    u8 id = *(volatile u8 *)entry;
    DispatchCallback fn = *(DispatchCallback *)(base + (id << 2));
    return (s8)sub_0804DCD0(entry, fn);
}

int sub_0804B350(u8 *entry)
{
    s8 result = sub_08028778(entry + 1, 0);
    if (result == 0) {
        int group = entry[4];
        if (group <= 5) {
            *(u32 *)entry = result;
            entry[0] = 1;
        } else {
            *(u32 *)entry = result;
            entry[0] = 2;
        }
    }
    return 0;
}

void CopyControlStateAndResetFlags(const MenuControl *control)
{
    u8 *base = D_0200BD20;
    u8 *flag = base + 127;
    *flag-- = 0;
    *flag = 0;
    *(MenuControl *)(base + 140) = *control;
}

u32 sub_0804B954(u8 *entry)
{
    if (!entry[1]) {
        entry[1] = 1;
        sub_08002FD4(17);
    }
    return 1;
}
