/* Wave 73-A v6d: 0x08041E58, fresh. MATCHED (0 diffs, old -O2
 * -mthumb-interwork, standalone linked-at-address).
 * TRUE extent 356 B (tiling): code 348 B through bx at 0x41FB2,
 * + 8 pool at 0x41FB4 (0x000046AC, 0x02004CA0); next function
 * 0x08041FBC. Early pool at 0x41E80 (0x02004E40, 0x000046AD)
 * sits between dispatch and case bodies (2 pad at 0x41E7E).
 * u32 F(u8 *s) returning 0. Prologue: u8 *g pointer variable
 * (g = G_02004E40; g[20] |= 1) -- this form, not a direct
 * G[20] |= 1, gives ROM's register homes (G in r1, constant
 * in r0). Switch on s[0x46AD] (cmp-tree 0/1/2/3); case 0:
 * 24F88(buf), B320(0x08232634,0,0,0) gate (bne+b form from
 * old_agbcc), then 4 windows: for (i = 0, p = b; i <= 7; i++)
 * with address-temp body { u16 *d = p + i; *d = buf[base+i]; }
 * (base 0,6,12,18) -- for-init order (i before p) gives ROM's
 * movs-then-adds init, and the d-temp gives ROM's base-first
 * dest adds; b[6]=b[7]=0; B420(k,b,0) for k=0..3; then
 * s[0x46AD]++. Case 1: B308 gate then shared s[0x46AD]++.
 * Case 2: B2B4 gate then shared++. Case 3: B2F0 gate, then
 * s[0x46AC]=10 and 5F44(0, G_02004CA0[ia], G_02004CA0[ib])
 * with variable indices for the ldrsb form. Locals:
 * buf[24] at sp, b[8] at sp+48 (64 B frame). .set stubs
 * verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

u32 Call_08024F88(u16 *p);
u32 Call_0800B320(u32 a, u32 b, u32 c, u32 d);
u32 Call_0800B420(u32 a, u16 *b, u32 c);
u32 Call_0800B308(void);
u32 Call_0800B2B4(void);
u32 Call_0800B2F0(void);
u32 Call_08005F44(u32 a, s8 b, s8 c);

extern u8 G_02004E40[];
extern s8 G_02004CA0[];

__attribute__((section(".text.w73a_08041e58")))
u32 sub_08041E58(u8 *s)
{
    u16 buf[24];
    u16 b[8];
    u8 i;
    { u8 *g = G_02004E40; g[20] |= 1; }
    switch (s[0x46AD]) {
    case 0:
        Call_08024F88(buf);
        if ((u8)Call_0800B320(0x08232634, 0, 0, 0)) {
            u16 *p;
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[i]; }
            b[6] = 0;
            b[7] = 0;
            Call_0800B420(0, b, 0);
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[6 + i]; }
            b[6] = 0;
            b[7] = 0;
            Call_0800B420(1, b, 0);
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[12 + i]; }
            b[6] = 0;
            b[7] = 0;
            Call_0800B420(2, b, 0);
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[18 + i]; }
            b[6] = 0;
            b[7] = 0;
            Call_0800B420(3, b, 0);
            s[0x46AD]++;
        }
        break;
    case 1:
        if ((u8)Call_0800B308())
            s[0x46AD]++;
        break;
    case 2:
        if ((u8)Call_0800B2B4())
            s[0x46AD]++;
        break;
    case 3:
        if ((u8)Call_0800B2F0()) {
            int ia = 0;
            int ib = 1;
            s[0x46AC] = 10;
            Call_08005F44(0, G_02004CA0[ia], G_02004CA0[ib]);
        }
        break;
    default:
        break;
    }
    return 0;
}

__asm__(
    ".globl Call_08024F88\n.set Call_08024F88, 0x08024F88\n"
    ".globl Call_0800B320\n.set Call_0800B320, 0x0800B320\n"
    ".globl Call_0800B420\n.set Call_0800B420, 0x0800B420\n"
    ".globl Call_0800B308\n.set Call_0800B308, 0x0800B308\n"
    ".globl Call_0800B2B4\n.set Call_0800B2B4, 0x0800B2B4\n"
    ".globl Call_0800B2F0\n.set Call_0800B2F0, 0x0800B2F0\n"
    ".globl Call_08005F44\n.set Call_08005F44, 0x08005F44\n"
    ".globl G_02004E40\n.set G_02004E40, 0x02004E40\n"
    ".globl G_02004CA0\n.set G_02004CA0, 0x02004CA0\n"
);
