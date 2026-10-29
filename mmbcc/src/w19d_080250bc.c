/* 0x080250bc (74 B): search entry table for value x.
 * i scans 1..GetEnt_U16_22()-1; on Fwd_25054(i)==x returns
 * (s8)F_0802663c(base+24, i), else -1.
 * Idioms: GetEnt_U16_22 declared with NO prototype args (its thunk ignores
 * r0), so the loop-condition call emits a bare `bl` with no arg setup.
 * FIXALIGN1 (all `.align 2, 0` -> `.align 1, 0`): the literal pool sits in
 * the initial branch shadow at +0x0c; align-1 keeps the section exactly
 * 74 bytes (kills the 46c0 tail pad). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
extern u16 GetEnt_U16_22(void);
extern u16 Fwd_25054(u16 idx);
extern u8 F_0802663c(u8 *p, u16 v);
__attribute__((section(".text.w19d_080250BC")))
s8 FindEntryIdx_080250BC(u16 x)
{
    u8 *base = (u8 *)0x02007090;
    u16 i = 1;
    while (i < GetEnt_U16_22()) {
        if (Fwd_25054(i) == x)
            return (s8)F_0802663c(base + 24, i);
        i++;
    }
    return -1;
}
