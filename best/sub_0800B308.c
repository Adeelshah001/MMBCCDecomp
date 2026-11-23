extern u8 D_02004E40[];
extern void sub_0800B520(const u16 *, const u16 *, const u16 *);
extern void ResetSelectionDisplayEntries(void);
extern void sub_0800B4C8(void);

u32 sub_0800B308(void)
{
    u8 *base = (u8 *)0x02004e40;
    u32 mask = 15;
    u32 flags = base[4];
    if ((mask & flags) == 0)
        return 1;
    return 0;
}

