/* w49d 0x080275F8 (288 B) v4 — mode-2c temp + flipped >30 — flipped mode-2 condition (s++ first) — mode variable (not s[1] reload) — natural C.
 * Decode (fresh ROM dis, 2026-10-26; pools raw LE):
 *   mid pool 0x08027610 = 0x02002F50 (r6 = *(u16 *)0x02002F50).
 *   Offsets: 0x465C (mode 0), 0x4698 (mode 1/2), 0x469C (mode 1b/2).
 *   Pointer 0x020070F0 (InitRec8 arg). Switch on s[1] (compare chain):
 *   case 0 falls through to case 1; case 1's second part falls to case 2.
 *   Mode 0: Sub_23FD0(s+0x465C, s[11]); s[24] |= 1; s[28] &= ~1;
 *   s[12] = 0; s[1]++.
 *   Mode 1: t = (u16)Search_112FC(s[11], 1); if (t == 0) {
 *   FlagBit_Set(30, 1); InitRec8(0x020070F0, 8); s[0x4698] = 0; break; }
 *   if ((u8)TblWalkInit(t) != 0) break; s[1]++; s[0x469C] = 0;
 *   (fallthrough to case 2)
 *   Mode 2: if (((u16)(r6 & 8)) == 0) s[0x469C] = 0;
 *   else s[0x469C]++; if (s[0x469C] <= 30) { if ((s16)Sub_114E8(
 *   s[0x469C]) != 1) break; InitRec8(0x020070F0, 8); s[0x4698] = 0;
 *   FlagBit_Set(30, 1); break; }
 *   FlagBit_Set(30, 1); F_11BD4(); InitRec8(0x020070F0, 8);
 *   s[0x4698] = 0; break; default: break. Returns void.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void Sub_08023FD0(u8 *p, u8 v);
extern u16 Search_080112FC(u8 a, u8 b);
extern void FlagBit_Set_11D68(int a, int b);
extern void InitRec8_267B4(u8 *p, int v);
extern u8 TblWalkInit_080114B8(u16 v);
extern void F_08011BD4(void);
extern s16 Sub_080114E8(u8 v);

__attribute__((section(".text.w49d_080275f8")))
void Func_080275F8(u8 *s) {
    u16 g = *(u16 *)0x02002F50;
    u8 mode = s[1];
    switch (mode) {
    case 0:
        Sub_08023FD0(s + 0x465C, s[11]);
        *(u32 *)(s + 24) |= 1;
        *(u32 *)(s + 28) &= ~1;
        s[12] = mode;
        s[1]++;
        /* fallthrough */
    case 1: {
        u16 t = Search_080112FC(s[11], 1);
        if (t == 0) {
            FlagBit_Set_11D68(30, 1);
            InitRec8_267B4((u8 *)0x020070F0, 8);
            s[0x4698] = 0;
            break;
        }
        if (TblWalkInit_080114B8(t) != 0)
            break;
        s[1]++;
        s[0x469C] = 0;
        /* fallthrough */
    }
    case 2:
        if ((u16)(g & 8) != 0) {
            s[0x469C]++;
        } else {
            s[0x469C] = 0;
        }
        {
            u8 v = s[0x469C];
            if (v > 30) {
                FlagBit_Set_11D68(30, 1);
                F_08011BD4();
                InitRec8_267B4((u8 *)0x020070F0, 8);
                s[0x4698] = 0;
                break;
            }
            if (Sub_080114E8(v) != 1)
                break;
            InitRec8_267B4((u8 *)0x020070F0, 8);
            s[0x4698] = 0;
            FlagBit_Set_11D68(30, 1);
            break;
        }
    default:
        break;
    }
}

__asm__(
    ""
    ""
    ""
    ""
    ".globl F_08011BD4\n.set F_08011BD4, 0x08011bd4\n"
    ""
);
