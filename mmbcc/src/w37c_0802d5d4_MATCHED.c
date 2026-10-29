/* W37-C MATCHED: 0x0802d5d4, 156 B, old_agbcc, pure C, 0 diffs.
 * Field-init/flag-clear on struct *s. Idioms: temp for first TblGet
 * result so z=0 lands between call and store; offset reuse (392+12).
 * s[8] = TblGet_f0D(s[32]); s[9] = TblGet_f0D(s[176]);
 * Sub_0802D670(s + 336); Sub_0802D670(s + 364);
 * s[392] = 2; s[393] = 2;
 * if ((s[404] & 15) == 4) *(u16*)(s + 166) = 0;
 * if ((s[404] & 240) == 64) *(u16*)(s + 154) = 0;
 * if ((s[408] & 15) == 4) *(u16*)(s + 310) = 0;
 * if ((s[408] & 240) == 64) *(u16*)(s + 298) = 0.
 * Extern callees + addresses: TblGet_f0D 0x08024618 (MATCHED),
 * Sub_0802D670 0x0802d670 (MATCHED).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 TblGet_f0D(u8 v);
extern void Sub_0802D670(u8 *p);

__attribute__((section(".text.w37c_0802d5d4")))
void Sub_0802D5D4(u8 *s)
{
    u16 z;
    u8 t = TblGet_f0D(s[32]);
    z = 0;
    s[8] = t;
    s[9] = TblGet_f0D(s[176]);
    Sub_0802D670(s + 336);
    Sub_0802D670(s + 364);
    s[392] = 2;
    s[393] = 2;
    if ((s[404] & 15) == 4)
        *(u16 *)(s + 166) = z;
    if ((s[404] & 240) == 64)
        *(u16 *)(s + 154) = z;
    if ((s[408] & 15) == 4)
        *(u16 *)(s + 310) = z;
    if ((s[408] & 240) == 64)
        *(u16 *)(s + 298) = z;
}
