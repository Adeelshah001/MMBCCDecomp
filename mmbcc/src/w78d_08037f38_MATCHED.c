/* Wave 74-A v2 (v1 + case0 condition inverted, ret kept in r7 via break-to-tail): 0x08037F38, fresh (registry-checked 2026-10-28, no row).
 * TRUE extent 384 B (tiling): code 380 B through bx at 0x380AA, + 4 pool
 * at 0x380AC? (see below); next function 0x080380B8. State machine on
 * (s8)s[0x469D] (cmp-tree 0/1/2, default -> return 0), returns r7
 * (0 normally, 2 on the two 28880 paths). Case 0 falls through to case 1;
 * case 1 (114B8==0 path) falls through to case 2.
 * Case 0: v=(u8)38C10(s); if v==255: 11D68(20,1); 11DD0(7,(u8)4DE70(
 *   s[0x469E],5)); else: p=TABLE_08230450+s[0x4699];
 *   11DD0(4,(u8)(4DE70(s[0x469E],5)+*p)); 11D68(20,0); 11DD0(5,v);
 *   then s[0x469D]++.
 * Case 1: t=(u8)(24384(4096)-50); w=(u16)112FC(t,7); if w==0:
 *   s[0x469C]=3; s[0x469D]=w; ret=2; s[0x46A0]=w;
 *   28880(4096,*(u16*)(s+0x469A),s[0x469F],8,s[0x46A1],w); return 2.
 *   else if (u8)114B8(w)!=0: return 0; else s[0x469D]++ (fallthrough).
 * Case 2: if (s16)114E8()==1: s[0x469C]=3; s[0x469D]=0; ret=2;
 *   s[0x46A0]=0; 28880(4096,*(u16*)(s+0x469A),s[0x469F],8,s[0x46A1],0);
 *   return 2. Otherwise return ret (0).
 * .set stubs verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

u32 Call_08038C10(u8 *s);
u32 Call_0804DE70(u32 a, u32 b);
void Call_08011DD0(u32 a, u32 b);
void Call_08011D68(u32 a, u32 b);
u32 Call_08024384(u32 a);
u32 Call_080112FC(u32 a, u32 b);
u32 Call_080114B8(u32 a);
u32 Call_080114E8(void);
void Call_08028880(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);

extern u8 TABLE_08230450[];

__attribute__((section(".text.w78d_08037f38")))
int sub_08037F38(u8 *s)
{
    int ret = 0;
    switch ((s8)s[0x469D]) {
    case 0: {
        u8 v = Call_08038C10(s);
        if (v != 255) {
            u8 *p = TABLE_08230450;
            p += s[0x4699];
            Call_08011DD0(4, (u8)(Call_0804DE70(s[0x469E], 5) + *p));
            Call_08011D68(20, 0);
            Call_08011DD0(5, v);
        } else {
            Call_08011D68(20, 1);
            Call_08011DD0(7, (u8)Call_0804DE70(s[0x469E], 5));
        }
        s[0x469D]++;
    }
    case 1: {
        u8 t = (u8)(Call_08024384(4096) - 50);
        u16 w = Call_080112FC(t, 7);
        if (w == 0) {
            s[0x469C] = 3;
            s[0x469D] = w;
            ret = 2;
            s[0x46A0] = w;
            Call_08028880(4096, *(u16 *)(s + 0x469A), s[0x469F], 8,
                          s[0x46A1], w);
            break;
        } else {
            if ((u8)Call_080114B8(w) != 0)
                break;
            s[0x469D]++;
        }
    }
    case 2:
        if ((s16)Call_080114E8() == 1) {
            u16 oC, oD, oA;
            u8 z;
            u8 *pc;
            oC = 0x469C;
            pc = s + oC;
            z = 0;
            pc[0] = 3;
            oD = 0x469D;
            s[oD] = z;
            ret = 2;
            oA = 0x46A0;
            s[oA] = z;
            Call_08028880(4096, *(u16 *)(s + oC - 2), s[oD + 2], 8,
                          s[oA + 1], z);
            break;
        }
        break;
    default:
        break;
    }
    return ret;
}

__asm__(
    ".globl Call_08038C10\n.set Call_08038C10, 0x08038C10\n"
    ".globl Call_0804DE70\n.set Call_0804DE70, 0x0804DE70\n"
    ".globl Call_08011DD0\n.set Call_08011DD0, 0x08011DD0\n"
    ".globl Call_08011D68\n.set Call_08011D68, 0x08011D68\n"
    ".globl Call_08024384\n.set Call_08024384, 0x08024384\n"
    ".globl Call_080112FC\n.set Call_080112FC, 0x080112FC\n"
    ".globl Call_080114B8\n.set Call_080114B8, 0x080114B8\n"
    ".globl Call_080114E8\n.set Call_080114E8, 0x080114E8\n"
    ".globl Call_08028880\n.set Call_08028880, 0x08028880\n"
    ".globl TABLE_08230450\n.set TABLE_08230450, 0x08230450\n"
);
