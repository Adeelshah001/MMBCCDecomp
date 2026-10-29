/* Wave 36-D MATCHED (C + .s patch w36d_0802daf8_patch.py, old_agbcc, 0 diffs over 140 B true extent 0x0802daf8-0x0802db84; goto-dispatch, signed sb, shared check70, dispatch subs/blt + lsrs-deletion patch, trailing 00 00 pad), 140 B, extent next-func 0x0802db84. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u8 Sub_0803FD68(u16 a);
__asm__(".set Sub_0803FD68, 0x0803fd68");
extern u8 Sub_0803F920(u16 a);
__asm__(".set Sub_0803F920, 0x0803f920");
extern u8 Sub_0803FACC(u16 a);
__asm__(".set Sub_0803FACC, 0x0803facc");

__attribute__((section(".text.w36d_0802daf8")))
u32 Sub_0802DAF8(u16 a, u16 b)
{
    u32 r6 = 0;
    u8 r1 = Sub_0803FD68(a);
    s32 sb = b;
    u8 res;
    if (b == 962)
        goto callacc;
    if (sb > 962)
        goto gt;
    if (sb < 960)
        goto end;
    res = Sub_0803F920(a);
    goto check70;
gt:
    if (b == 9152)
        goto check56;
    if (sb > 9152)
        goto gt2;
    if (b == 5056)
        goto check50;
    goto end;
gt2:
    if (b == 17344)
        goto set7check4;
    goto end;
check50:
    if (r1 == 1)
        goto set6;
    goto check5a;
check56:
    if (r1 == 2)
        goto set6;
    goto check5a;
check5a:
    if (r1 == 5)
        goto set6;
    goto set7;
set7:
    r6 = 7;
    goto end;
set7check4:
    r6 = 7;
    if (r1 != 4)
        goto end;
    goto set6;
callacc:
    res = Sub_0803FACC(a);
check70:
    r6 = 7;
    if (res == 0)
        goto end;
    goto set6;
set6:
    r6 = 6;
    goto end;
end:
    return r6;
}

/* Explicit 00 00 pad after bx (ROM has 2 pad bytes at the extent end). */
__asm__(".short 0");
