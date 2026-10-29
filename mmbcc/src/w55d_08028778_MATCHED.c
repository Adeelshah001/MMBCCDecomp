/* W55-D: 0x08028778, 252 B. State machine on s[0] (goto-dispatch).
 * st = s[0] (r6, new state written back at tail); ret = 1 (r9).
 * case 0: st=1; 4e50(1); flag=*(0x02004f80+2);
 *   flag==0 ? 4dfc(1) : 4dfc(flag);
 *   fill(0, 0x03002620, 480); *(0x03002620+516)=32;
 *   *(0x03002620+518)=480; *(0x02000ec0+7)=idx;
 *   *(u16*)0x020031e0 &= 0xedff; &= 0xdbff; 4f18(); 4f80();
 * case 1: 4f18(); cd38(); if ((s8)*(0x02000ec0+8)!=0) goto tail80;
 *   if (*(0x02000ec0)!=idx) goto tail80; st=2;
 *   *(u16*)0x020031e0 &= 0xedff; &= 0xdbff; goto tail80;
 * case 2: 4f18(); ret=0; 4f80();
 * tail: s[0]=st; return ret. Pools (raw LE): flag 0x02004f80;
 * base 0x03002620; off518 0x206; idxptr 0x02000ec0;
 * maskptr 0x020031e0; masks 0xedff, 0xdbff.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_08004E50(int a);
__asm__(".set Sub_08004E50, 0x08004e50");
extern void Sub_08004DFC(int a);
__asm__(".set Sub_08004DFC, 0x08004dfc");
extern void Sub_080006DC(int a, u32 b, int c);
__asm__(".set Sub_080006DC, 0x080006dc");
extern void Sub_08004F18(void);
__asm__(".set Sub_08004F18, 0x08004f18");
extern void Sub_08004F80(void);
__asm__(".set Sub_08004F80, 0x08004f80");
extern void Sub_0800CD38(void);
__asm__(".set Sub_0800CD38, 0x0800cd38");

__attribute__((section(".text.w55d_08028778")))
int Sub_08028778(u8 *s, u8 idx)
{
    int st = s[0];
    int ret = 1;
    if (st == 1)
        goto c1;
    if (st > 1)
        goto gt;
    if (st == 0)
        goto c0;
    goto tail;
gt:
    if (st == 2)
        goto c2;
    goto tail;
c0:
    st = 1;
    Sub_08004E50(1);
    {
        u8 *flagp = (u8 *)0x02004F80;
        if (*(flagp + 2) == 0)
            Sub_08004DFC(1);
        else
            Sub_08004DFC(*(flagp + 2));
    }
    {
        u8 *base = (u8 *)0x03002620;
        Sub_080006DC(0, (u32)base, 480);
        *(u16 *)(base + 516) = 32;
        *(u16 *)(base + 518) = 480;
    }
    {
        u8 *ip0 = (u8 *)0x02000EC0;
        *(ip0 + 7) = idx;
    }
    {
        u16 v = *(u16 *)0x020031E0;
        v &= 0xedff;
        v &= 0xdbff;
        *(u16 *)0x020031E0 = v;
    }
    Sub_08004F18();
    Sub_08004F80();
    goto tail;
c1:
    Sub_08004F18();
    Sub_0800CD38();
    {
        u8 *ip1 = (u8 *)0x02000EC0;
        int b8;
        int k = 8;
        __asm__("ldrsb %0, [%1, %2]" : "=r" (b8) : "r" (ip1), "0" (k));
        if (b8 != 0)
            goto tail80;
        if (*(ip1 + 0) != idx)
            goto tail80;
    }
    st = 2;
    {
        u16 v = *(u16 *)0x020031E0;
        v &= 0xedff;
        v &= 0xdbff;
        *(u16 *)0x020031E0 = v;
    }
tail80:
    Sub_08004F80();
    goto tail;
c2:
    Sub_08004F18();
    ret = 0;
    Sub_08004F80();
    goto tail;
tail:
    s[0] = st;
    return ret;
}

__asm__(".balign 4, 0");
