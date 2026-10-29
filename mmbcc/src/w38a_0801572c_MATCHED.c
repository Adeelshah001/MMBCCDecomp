/* W38-A: 0x0801572c, 236 B. Goto-dispatch SetMirrored family (twin of #32).
 * p = s+124. mode = s[14] (compared directly):
 * c0: SetMirrored(s,-15360,0); IncUse(s,11); -> inc2 (s14++).
 * c1: if Check119(s): IncUse(s,12); -> inc2. Else tail.
 * c2: if Check119(s): a0 = t1[s17*2], a1 = t1[s17*2+1] (t1=0x08223E62,
 *   byte pairs, base+1 form); nib=(s35<<28)>>28 (unsigned lsr);
 *   tb = 0x08223ED8 + s124*4 (pool-first); h0 = ldrsh tb[o0=0],
 *   h1 = ldrsh tb[o1=2] (variable offsets); Sub_0801CD50(a0,a1,nib,h0,
 *   h1,s44_value); -> inc2 (s14++ only, NO IncUse, fall-through).
 * c3: if GetField(s44_value)>6: Dec(s44); s44=0; SetMirrored(s,-15360,0);
 *   IncUse(s,0); p[4]=0; SetBytes(s,0). tail.
 * inc2: s[14]++; tail. tail: Tick(s).
 * Shared s14++ block at 0x157be (after c2, before c3).
 * Callees: SetMirrored MATCHED, IncUse MATCHED, Check119 MATCHED (u16),
 * Sub_0801CD50 0x0801cd50 (unlisted, .set, (int*6) — 6th arg s44 VALUE
 * per #27/#28/#32), GetField MATCHED (staged (int)->u8 per #28),
 * Dec MATCHED, SetBytes MATCHED, Tick MATCHED.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Vec2_SetMirrored(u8 *s, int a, int b);
extern void ChipSlot_IncUse(u8 *s, int idx);
extern u16 Check119_Minus3_Le1(u8 *s);
extern void Sub_0801CD50(int a, int b, int c, int d, int e, int f);
__asm__(".set Sub_0801CD50, 0x0801cd50");
extern u8 GetField17_U8(int v);
extern void DecIfNonZero_18(int v);
extern void SetBytes_08011F68(u8 *s, u8 v);
extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w38a_0801572c")))
void Sub_0801572C(u8 *s)
{
    u8 *p = s + 124;
    int mode = s[14];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto tail;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto tail;
c0:
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 11);
    goto inc2;
c1:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    ChipSlot_IncUse(s, 12);
    goto inc2;
c2:
    if (Check119_Minus3_Le1(s) == 0)
        goto tail;
    {
        u8 *t1 = (u8 *)0x08223E62;
        u8 *b1;
        int a0, a1;
        int nib;
        register u8 *base2 __asm__("r3");
        u8 *tb;
        int o0 = 0;
        int o1 = 2;
        int h0, h1;
        a0 = t1[s[17] * 2];
        b1 = t1 + 1;
        a1 = b1[s[17] * 2];
        nib = (int)(((u32)s[35] << 28) >> 28);
        base2 = (u8 *)0x08223ED8;
        __asm__ volatile("" : "+r"(base2));
        {
            int off = p[0] * 4;
            __asm__ volatile("add %0, %1, %2" : "=r"(tb) : "r"(off), "r"(base2));
        }
        __asm__ volatile("" : "+r"(tb));
        h0 = *(s16 *)(tb + o0);
        h1 = *(s16 *)(tb + o1);
        Sub_0801CD50(a0, a1, nib, h0, h1, *(u32 *)(s + 44));
    }
inc2:
    s[14]++;
    goto tail;
c3:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) <= 6)
        goto tail;
    DecIfNonZero_18(*(u32 *)(s + 44));
    *(u32 *)(s + 44) = 0;
    Vec2_SetMirrored(s, -15360, 0);
    ChipSlot_IncUse(s, 0);
    p[4] = 0;
    SetBytes_08011F68(s, 0);
tail:
    ChipSlot_Tick(s);
}
