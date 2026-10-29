/* Wave 72-A v7: 0x080493EC, fresh. TRUE extent 372 B: code 364 B
 * through bx at 0x49556, plus pool words at 0x49558 (0x46A4) and
 * 0x4955C (0x46A5) referenced by case 4; next function 0x08049560.
 * Returns 0 on all paths; Teardown (0x08004F18) first, Setup
 * (0x08004F80) + return 0 shared tail. Case 0 falls through into
 * case 1 (shared bl 0x0804A3FC + shared s[18085]++); cases 1/2/3
 * increments are written naturally and left for old_agbcc to
 * cross-jump into the shared 0x49524 block. Case-0 ands block:
 * temp t = 1 | byte, strh stores between OR and ANDs, t &= ~30
 * then ~32 (ROM materializes -31 via movs+negs and derives -33
 * via subs #2). Offset variable off (18086 -> 18087 via off++)
 * reproduces ROM's r5 reuse. .set stubs are verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

void Call_08004F18(void);
void Call_0800BEE0(u32 a, u32 b);
void Call_08005A9C(u32 a);
void Call_08049560(u8 *s);
void Call_0800800C(u8 *a, u32 b);
void Call_0804A3FC(void);
s8 Call_0804A40C(void);
u32 Call_08024384(u32 a);
u32 Call_0800B368(u32 a, u32 b, u32 c, u32 d);
u32 Call_0800B308(void);
void Call_08004F80(void);

extern u8 G_02004CE0[];
extern u32 TABLE_082343B8[];

__attribute__((section(".text.w72a_080493ec")))
u8 sub_080493EC(u8 *s)
{
    Call_08004F18();
    switch (s[18085]) {
    case 0: {
        u8 *g;
        u8 *p44;
        int t;
        Call_0800BEE0(64, 128);
        Call_08005A9C(25);
        Call_08049560(s);
        g = G_02004CE0;
        p44 = g;
        p44 += 44;
        t = 1;
        t |= *p44;
        *(u16 *)(g + 40) = 16;
        *(u16 *)(g + 42) = (s8)s[18086] * 16 + 8;
        t &= ~30;
        t &= ~32;
        *p44 = t;
        {
            u32 m = 0xFFFFFC3F;
            u32 v = *(u16 *)(g + 44);
            *(u16 *)(g + 44) = v & m;
        }
        Call_0800800C(g, 0);
        s[18087] = 5;
        s[18085]++;
        /* fallthrough into case 1's shared ending */
    }
    case 1:
        Call_0804A3FC();
        s[18085]++;
        break;
    case 2: {
        s8 v = Call_0804A40C();
        if (v == -2) {
            if ((s8)s[18087] > 0) {
                s[18085]--;
                s[18087]--;
            } else {
                s[18085]++;
            }
        } else if (v != -1) {
            s[18085]++;
        }
        break;
    }
    case 3: {
        u32 x = Call_08024384(4096) - 50;
        u32 *tbl;
        x = x << 24;
        tbl = TABLE_082343B8;
        x = x >> 22;
        if ((u8)Call_0800B368(*(u32 *)((u8 *)tbl + x), 0, 0, 0))
            s[18085]++;
        break;
    }
    case 4:
        if ((u8)Call_0800B308()) {
            s[18084] = 0;
            s[18085] = 0;
        }
        break;
    default:
        break;
    }
    Call_08004F80();
    return 0;
}

__asm__(
    ".globl Call_08004F18\n.set Call_08004F18, 0x08004F18\n"
    ".globl Call_0800BEE0\n.set Call_0800BEE0, 0x0800BEE0\n"
    ".globl Call_08005A9C\n.set Call_08005A9C, 0x08005A9C\n"
    ".globl Call_08049560\n.set Call_08049560, 0x08049560\n"
    ".globl Call_0800800C\n.set Call_0800800C, 0x0800800C\n"
    ".globl Call_0804A3FC\n.set Call_0804A3FC, 0x0804A3FC\n"
    ".globl Call_0804A40C\n.set Call_0804A40C, 0x0804A40C\n"
    ".globl Call_08024384\n.set Call_08024384, 0x08024384\n"
    ".globl Call_0800B368\n.set Call_0800B368, 0x0800B368\n"
    ".globl Call_0800B308\n.set Call_0800B308, 0x0800B308\n"
    ".globl Call_08004F80\n.set Call_08004F80, 0x08004F80\n"
    ".globl G_02004CE0\n.set G_02004CE0, 0x02004CE0\n"
    ".globl TABLE_082343B8\n.set TABLE_082343B8, 0x082343B8\n"
);
