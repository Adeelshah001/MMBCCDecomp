/* Wave 43 coordinator landing: coordinator-verified 0-diff
 * (standalone rebuild + in-built-ROM check).
 * See staging/w43coord_verify/ for coordinator verification artifacts.
 */
/* v6 = v4 compares (sa + lim, all signed encodings correct) + v5 pins
 * (a2 s32 r5, cat r1) + v5 tail label order (ROM layout) + cat declared
 * before lim (ROM: lsrs cat before ldr lim). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u8 Sub_0803F920(u16 a);
__asm__(".set Sub_0803F920, 0x0803f920");
extern u8 Sub_0803FACC(u16 a);
__asm__(".set Sub_0803FACC, 0x0803facc");

__attribute__((section(".text.w43a_0803ff80")))
u32 Sub_0803FF80(u16 a, u16 b)
{
    register s32 a2 __asm__("r5") = a;
    s32 sa = a;
    u32 res = 0;
    register int cat __asm__("r1") = b >> 12;
    s32 lim = 961;
    u8 h;
    if (sa > lim)
        goto big;
    lim -= 1;
    if (sa >= lim)
        goto helper1early;
    if (sa == 930)
        goto invcat;
    if (sa > 930)
        goto mid;
    if (sa == 96)
        goto chip96;
    goto end;
mid:
    if (sa == 931)
        goto cat0;
    if (sa == 932)
        goto helper1mid;
    goto end;
big:
    if (sa == 5056)
        goto cat1;
    if (sa > 5056)
        goto huge;
    if (sa == 962)
        goto helper2;
    if (sa == 5024)
        goto cat1;
    goto end;
huge:
    if (a2 == 9152)
        goto cat2;
    if (a2 == 17344)
        goto cat4;
    goto end;
invcat:
    res = 1;
    if (cat == 0)
        res = 2;
    goto end;
cat0:
    res = 1;
    if (cat != 0)
        res = 2;
    goto end;
helper1mid:
    h = Sub_0803F920(b);
    res = 1;
    if (h == 0)
        res = 2;
    goto end;
helper1early:
    h = Sub_0803F920(b);
    res = 1;
    if (h != 0)
        res = 2;
    goto end;
helper2:
    h = Sub_0803FACC(b);
    res = 1;
    if (h != 0)
        res = 2;
    goto end;
cat1:
    res = 1;
    if (cat == 1)
        res = 2;
    goto end;
cat2:
    res = 1;
    if (cat == 2)
        res = 2;
    goto end;
cat4:
    res = 1;
    if (cat == 4)
        res = 2;
    goto end;
chip96:
    if (b == 208 || b == 217)
        res = 2;
    else
        res = 1;
    goto end;
end:
    return res;
}
