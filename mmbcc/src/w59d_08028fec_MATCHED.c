/* W59-D v5 (v4 + mode-4 zero temp):v2 + -16 via named int var m):v1 + switch mode dispatch, mode-4 <=9-then form): 0x08028fec, TRUE extent 512 B (pop/bx @0x291e4; pad @0x291e6;
 * pool @0x291e8; next fn @0x291ec). Task-state fn, returns 3.
 * Entry: Sub_29504(s); s[4] = 0 if any of (s[404]&15)==1, (s[404]&240)==16,
 * (s[408]&15)==1, (s[408]&240)==16, or s[11]==1; else s[4] = Sub_292B0(s)<<4.
 * Mode = s[4]>>4: 1-2 -> s[0]=4 (+s[2]=3/s[3]=0 if (s[6]&8)==0);
 * 4 -> Sub_2D5D4(s), s[28]>9 ? Sub_2EA64 path : s[0]=2,s[1]=0;
 * else (0,3,5+) -> s[11]==1 ? s[11]=2 (+s[2]=8/s[3]=0 if (s[6]&8)==0)
 * : 404/408 bit-test section setting s[320..329] to 10/11.
 */
typedef unsigned char u8;
typedef unsigned int u32;

extern void Sub_08029504(u8 *s);
__asm__(".set Sub_08029504, 0x08029504");
extern u8 Sub_080292B0(u8 *s);
__asm__(".set Sub_080292B0, 0x080292b0");
extern void Sub_0802D5D4(u8 *s);
extern u8 Sub_0802EA64(u8 *s);
__asm__(".set Sub_0802EA64, 0x0802ea64");

__attribute__((section(".text.w59d_08028fec")))
u8 Sub_08028FEC(u8 *s)
{
    int mode;
    Sub_08029504(s);
    if (((s[404] & 15) == 1) || ((s[404] & 240) == 16) ||
        ((s[408] & 15) == 1) || ((s[408] & 240) == 16)) {
        s[4] = 0;
    } else if (s[11] == 1) {
        s[4] = 0;
    } else {
        s[4] = Sub_080292B0(s) << 4;
    }
    mode = s[4] >> 4;
    switch (mode) {
    case 1:
    case 2:
        if ((s[6] & 8) == 0) {
            s[2] = 3;
            s[3] = 0;
        }
        s[0] = 4;
        break;
    case 4:
        Sub_0802D5D4(s);
        if (s[28] <= 9) {
            int z = 0;
            s[0] = 2;
            s[1] = z;
        } else {
            s[4] = Sub_0802EA64(s);
            if ((s[6] & 8) == 0) {
                s[2] = 3;
                s[3] = 0;
            }
            s[0] = mode;
        }
        break;
    default:
        if (s[11] == 1) {
            s[11] = 2;
            if ((s[6] & 8) == 0) {
                s[2] = 8;
                s[3] = 0;
            }
        } else if ((s[404] & 15) == 1) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            {
                int m = -16;
                s[404] = (s[404] & m) | 2;
            }
            if (s[321] == 0)
                s[321] = 11;
            else
                s[320] = 11;
        } else if ((s[404] & 240) == 16) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            s[404] = (s[404] & 15) | 32;
            if (s[321] == 0)
                s[321] = 10;
            else
                s[320] = 10;
        } else if ((s[408] & 15) == 1) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            {
                int m = -16;
                s[408] = (s[408] & m) | 2;
            }
            if (s[329] == 0)
                s[329] = 11;
            else
                s[328] = 11;
        } else if ((s[408] & 240) == 16) {
            if ((s[6] & 8) == 0) {
                s[2] = 5;
                s[3] = 0;
            }
            s[408] = (s[408] & 15) | 32;
            if (s[329] == 0)
                s[329] = 10;
            else
                s[328] = 10;
        }
        break;
    }
    return 3;
}
