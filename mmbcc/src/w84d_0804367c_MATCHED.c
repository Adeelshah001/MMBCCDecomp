/* Wave 71-A v6: 0x0804367c, fresh. TRUE extent 344 B
 * (342 code through bx @0x437D0 + 2 pad @0x437D2; next fn @0x437D4).
 * u8 F(u8 *s): flag=0 (r6); switch on s[6]; case 0 falls through
 * into case 1 after s[6]++; default -> tail (return flag).
 * Case 0: setup stores (see below), Call_08024760() > 7 gate for
 * s[18099], G[4524]=0, Call_08045E20(s), s[6]++.
 * Case 1: q = s+18094; gv = (s8)G[4524]; if (*q != gv) diff path:
 *   s16 diff = *q - gv; step = diff>>1 (floor); if diff>=0 and
 *   step==0 step=1; G[4524] += step (u8 wrap);
 *   if (*q == G[4524]) { (s16)step<0 ? Call_08045E20(s)
 *                                    : Call_08045E40(s); }
 *   else (equal path): if Call_08043A9C(s) { Call_080248AC(0);
 *   flag=1; } if (*q != (u8)G[4524]) tail; if Call_08044828(s) {
 *   Call_080248AC(0); flag=1; } tail.
 * Pool constants from raw LE bytes: G_A 0x02004830 (+618/+619),
 * G_B 0x02003670 (+4524), s-offsets 18088/18092/18096/18098/18097/
 * 18099/18094. .set stubs are verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

void Call_08005A9C(u32 x);
u32 Call_0804580C(u8 *s);
u16 Call_08024760(void);
void Call_08045E20(u8 *s);
void Call_08045E40(u8 *s);
u8 Call_08043A9C(u8 *s);
u8 Call_08044828(u8 *s);
void Call_080248AC(u32 x);

extern u8 G_02004830[];
extern u8 G_02003670[];

__attribute__((section(".text.w84d_0804367c")))
u8 sub_0804367c(u8 *s)
{
    u8 flag = 0;
    switch (s[6]) {
    case 0:
        Call_08005A9C(3);
        G_02004830[618] = Call_0804580C(s);
        G_02004830[619] = 0;
        *(u32 *)(s + 18088) = 0;
        *(u32 *)(s + 18092) = 0;
        *(u32 *)(s + 18096) = 0;
        s[18092] = 5;
        s[18096] = 0;
        s[18098] = 0;
        s[18097] = 1;
        if (Call_08024760() > 7)
            s[18099] = 1;
        else
            s[18099] = 0;
        G_02003670[4524] = 0;
        Call_08045E20(s);
        s[6]++;
    case 1: {
        u8 *q = s + 18094;
        u8 a;
        s8 gv;
        a = *q;
        gv = (s8)G_02003670[4524];
        if (a == gv) {
            if (Call_08043A9C(s) != 0) {
                Call_080248AC(0);
                flag = 1;
            }
            if (*q != (u8)G_02003670[4524])
                break;
            if (Call_08044828(s) != 0) {
                Call_080248AC(0);
                flag = 1;
            }
        } else {
            s16 diff = (s16)(a - gv);
            u16 step;
            if (diff < 0)
                step = diff >> 1;
            else
                step = (diff >> 1) ? (diff >> 1) : 1;
            G_02003670[4524] += step;
            { u8 nv = G_02003670[4524];
            if (s[18094] == nv) {
                if ((s16)step < 0)
                    Call_08045E20(s);
                else
                    Call_08045E40(s);
            }
            }
        }
        break;
    }
    default:
        break;
    }
    return flag;
}

/* 2-byte zero pad: ROM has 00 00 at +342/+343; GAS would otherwise end the
 * 342-byte code with its default nop fill (c0 46). Pure-C pad object,
 * same-section, per the landed chipslot.c / text_idx.c / 2FDA0 precedent. */
__attribute__((section(".text.w84d_0804367c")))
static const u8 s4367CPad[2] = { 0, 0 };

__asm__(
    ".globl Call_08005A9C\n.set Call_08005A9C, 0x08005A9C\n"
    ".globl Call_0804580C\n.set Call_0804580C, 0x0804580C\n"
    ".globl Call_08024760\n.set Call_08024760, 0x08024760\n"
    ".globl Call_08045E20\n.set Call_08045E20, 0x08045E20\n"
    ".globl Call_08045E40\n.set Call_08045E40, 0x08045E40\n"
    ".globl Call_08043A9C\n.set Call_08043A9C, 0x08043A9C\n"
    ".globl Call_08044828\n.set Call_08044828, 0x08044828\n"
    ".globl Call_080248AC\n.set Call_080248AC, 0x080248AC\n"
    ".globl G_02004830\n.set G_02004830, 0x02004830\n"
    ".globl G_02003670\n.set G_02003670, 0x02003670\n"
);
