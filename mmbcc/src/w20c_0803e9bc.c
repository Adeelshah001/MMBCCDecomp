/* Wave20 worker C @0x0803e9bc (88 B). Pool-control + nested-if structure.
 * ROM: if(v!=0){ if(v!=1) goto ret; } else { Sub(); (*p)++; }
 * Pool1 (0x469d) dumps after the 'b ret' (first unconditional jump).
 * CopyHdr_Dispatch takes address of stack slot (sub sp,#4; mov r0,sp).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
extern void Clr36_080475D4(void);
extern s8 CopyHdr_Dispatch(u8 *s);
__attribute__((section(".text.w20c_0803e9bc")))
u32 F_0803E9BC(u8 *s)
{
    u32 r = 0;
    u8 dummy;
    u8 *p = s + 0x469D;
    u8 v = *p;
    if (v != 0) {
        if (v == 1)
            goto body;
        goto ret;
    } else {
        Clr36_080475D4();
        (*p)++;
    }
body:
    {
        s8 q = CopyHdr_Dispatch(&dummy);
        if (q == -1 || q == 1) {
            *(s + 0x469C) = 0;
            *(s + 0x469D) = 10;
            r = 2;
        }
    }
ret:
    return r;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
