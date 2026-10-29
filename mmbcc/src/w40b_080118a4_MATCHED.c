/* W39-A v2: 0x080118a4, 312 B. Like v1 but stack struct replaced by
 * separate locals (flag byte + 3 ints) and short-lived values inlined,
 * to match ROM's push {r4,r5,lr} (s->r5, t->r4) and sp layout
 * (flag at sp+8, ints at sp+12/16/20, outgoing args at sp+0/4).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Inc4_Clear5_7(u8 *s);
extern void Copy3_08011CD4(u16 a, int *o0, int *o1, int *o2);
extern int Sub_08011CC4(u16 a);
extern u8 Sub_08010FDC(u8 t, u8 b19, int c, int o0, int o1, int o2);
extern s8 F_11054(u8 *flag);
extern u8 *TableWalk_080113F4(u16 v);

__attribute__((section(".text.w40b_080118a4")))
int Sub_080118A4(u8 *s)
{
    s8 flag;
    int o0;
    int o1;
    int o2;
    int t;
    int v;
    u8 *q;

    flag = 0xFF;
    if ((*(u8 **)s)[18] != 0)
        goto test2;
    Inc4_Clear5_7(s);
    __asm__ volatile("" ::: "memory");
    goto tail;
test2:
    if (s[36] != 0) {
        Inc4_Clear5_7(s);
        goto tail;
    }
    if (s[5] == 0) {
        o0 = 0;
        o1 = 0;
        o2 = 0;
        if (*(u16 *)(*(u8 **)s + 22) != 0)
            Copy3_08011CD4((u16)(*(u16 *)(*(u8 **)s + 22) - 1), &o0, &o1, &o2);
        *(u16 *)(s + 16) = 1;
        t = (u8)(((*(u8 **)s)[18] & 3) - 1);
        if ((*(u8 **)s)[18] & 4)
            t |= 0x80;
        if ((*(u8 **)s)[18] & 8)
            t |= 0x40;
        t = (u8)t;
        if (Sub_08010FDC(t, (*(u8 **)s)[19], Sub_08011CC4((u16)(*(u16 *)(*(u8 **)s + 20) - 1)), o0, o1, o2) != 0)
            s[5]++;
    }
    if (F_11054(&flag) != 1)
        return 0;
    if (*(u16 *)(*(u8 **)s + 22) == 0)
        goto clear_inc;
    if (flag == 1)
        goto v26;
    if (flag > 1)
        goto gt1;
    if (flag == 0)
        goto v24;
    goto v0;
gt1:
    if (flag == 2)
        goto v28;
    goto v0;
v24:
    v = *(u16 *)(*(u8 **)s + 24);
    goto havev;
v26:
    v = *(u16 *)(*(u8 **)s + 26);
    goto havev;
v28:
    v = *(u16 *)(*(u8 **)s + 28);
    goto havev;
v0:
    v = 0;
havev:
    if ((s16)v <= 0)
        goto clear_inc;
    q = TableWalk_080113F4(v);
    if (q == 0)
        goto clear8;
    *(u8 **)s = q;
    s[4] = 1;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    __asm__ volatile("" ::: "memory");
    goto tail;
clear8:
    s[4] = 8;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    goto tail;
clear_inc:
    s[4]++;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    __asm__ volatile("" ::: "memory");
tail:
    return -1;
}

__asm__(".set Sub_08011CC4, 0x08011cc4");
__asm__(".set Sub_08010FDC, 0x08010fdc");
