/* W48-D v2 (v1 + pinned-r0 prologue + case0 own-test form):
 * 0x08041fbc, TRUE extent 276 B (bx 0x20c0, pads/pools to 0x20d0,
 * next function 0x080420d0). Decode from fresh ROM disassembly;
 * pools re-derived from raw LE bytes:
 *  41fe0 = 0x02004e40 (EWRAM base, prologue), 41fe4 = 0x000046ad
 *  (mode offset), 41fe8 = 0x08041fec (jump-table base),
 *  table 41fec..41fff = 42000/42030/42060/42074/42090,
 *  202c = 0x000046ad, 205c = 0x08232b1c (mode-1 table),
 *  2070 = 0x000046ad, 208c = 0x000046ad,
 *  20c4 = 0x000046ac, 20c8 = 0x000046ad, 20cc = 0x02004ca0.
 *  Prologue: EWRAM[20] |= 1; mode = s[0x46ad]; mode > 4 -> ret.
 *  case 0: r = B148(1, (s16)Sub200((u8)Tbl241F8(4096)), 1); -> tail.
 *  case 1: if (B2D8()==0) -> ret;
 *          r = B320(table[(u8)(Tbl24384(4096)-50)], 0,0,0);
 *          if (r==0) -> ret; s[0x46ad]++; -> ret.
 *  case 2: if (B308()==0) -> ret; s[0x46ad]++; -> ret.
 *  case 3: r = B2B4(); -> tail.
 *  tail: if ((r<<24)!=0) s[0x46ad]++; -> ret.
 *  case 4: if (B2F0()==0) -> ret; s[0x46ac]=10; s[0x46ad]=0;
 *          Sub_08005F44(0, (s8)byte[0x02004ca0], (s8)byte[0x02004ca1]);
 *          -> ret.  ret: return 0.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern u8 TblGetByte_241F8(u16 a);
extern u16 Sub200_08024514(u8 v);
extern u8 Sub_0800B148(u8 a, s16 b, u8 c);
extern u8 Tst_0800B2D8(void);
extern u8 TblGetByte_24384(u16 a);
extern u8 Sub_0800B320(u32 a, u32 b, u32 c, u32 d);
extern u8 Check_B308(void);
extern u8 CheckAndSet_B2B4(void);
extern u8 Tst_0800B2F0(void);
extern void Sub_08005F44(u32 a, s8 b, s8 c);
extern u8 gEwram_02004E40[];

__attribute__((section(".text.w49c_08041fbc")))
int Sub_08041FBC(u8 *s)
{
    register u8 r __asm__("r0");
    {
        register u8 *gp __asm__("r0") = gEwram_02004E40;
        gp[20] |= 1;
    }
    switch (s[0x46ad]) {
    case 0:
        r = Sub_0800B148(1, (s16)Sub200_08024514((u8)TblGetByte_241F8(4096)), 1);
        if (r != 0) {
            u8 *pp = s + 0x46ad;
            __asm__ volatile("" :: "i"(0));
            (*pp)++;
        }
        goto ret;
    case 1:
        if (Tst_0800B2D8() == 0)
            goto ret;
        r = Sub_0800B320(((u32 *)0x08232b1c)[(u8)(TblGetByte_24384(4096) - 50)], 0, 0, 0);
        if (r == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 2:
        if (Check_B308() == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 3:
        r = CheckAndSet_B2B4();
        goto tail;
    tail:
        if ((r << 24) != 0)
            s[0x46ad]++;
        goto ret;
    case 4:
        if (Tst_0800B2F0() == 0)
            goto ret;
        {
            u8 *pp = s + 0x46ac;
            int z = 0;
            *pp = 10;
            s[0x46ad] = z;
        }
        {
            s8 *bp = (s8 *)0x02004ca0;
            Sub_08005F44(0, bp[0], bp[1]);
        }
        goto ret;
    default:
        goto ret;
    }
ret:
    return 0;
}

__asm__(
    ""
    ""
    ".set Sub_0800B148, 0x0800b148\n"
    ""
    ".set TblGetByte_24384, 0x08024384\n"
    ""
    ""
    ""
    ""
    ".set Sub_08005F44, 0x08005f44\n"
    ".globl gEwram_02004E40\n.set gEwram_02004E40, 0x02004e40\n"
);
