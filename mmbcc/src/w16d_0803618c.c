/* Wave 16-D: ResetStateBlock_3618c @ 0x0803618c (80 B: 68 code + 12 pool).
 * Coordinator-landed, 0-diff verified vs ROM (bl immediates are
 * R_ARM_THM_CALL relocs, resolved at link). Compiler: main agbcc.
 * Behavior: zeroes 8 bytes at 0x200BCE8, sets byte0 = param, then runs an
 * init call sequence (Call4E60_4E44 / PalModeSet_4DFC(*(u8*)(0x2004F80+2)) /
 * SyncObjFlagBits_BEE0(0x40,0x80) / *(u16*)0x2004830 = 0 / sub_08021780).
 * Idioms: r5 base pin (local register var); opaque register copy
 * (u8 *p = r5 -> adds r1,r5,#0); u16 loop counter (lsl/lsr #16, bls);
 * late-assigned u16 zero pinned to r4 (mov r4,#0 after loop); tied-opaque
 * asm defeating pool folding for 0x2004F80 (keeps ldrb r0,[r0,#2] with
 * unfolded pool word). */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
void Call4E60_4E44(void);
void PalModeSet_4DFC(u8);
void SyncObjFlagBits_BEE0(u32, u32);
void ResetStateBlock_3618C(u8 a) __attribute__((section(".text.w16d_0803618c")));
void ResetStateBlock_3618C(u8 a)
{
    register u8 *r5 __asm__("r5") = (u8 *)0x200BCE8;
    register u8 *q __asm__("r0");
    u8 *p = r5;
    u16 i;
    u16 zero;
    for (i = 0; i <= 7; i++)
        *p++ = 0;
    zero = 0;
    r5[0] = a;
    Call4E60_4E44();
    __asm__ volatile("" : "=r" (q) : "0" ((u8 *)0x2004F80));
    PalModeSet_4DFC(q[2]);
    SyncObjFlagBits_BEE0(0x40, 0x80);
    *(u16 *)0x2004830 = zero;
    sub_08021780();
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl PalModeSet_4DFC\n"
    ".set PalModeSet_4DFC, 0x08004DFC\n"
    ".thumb_func\n"
    ".globl sub_08021780\n"
    ".set sub_08021780, 0x08021780\n"
);
