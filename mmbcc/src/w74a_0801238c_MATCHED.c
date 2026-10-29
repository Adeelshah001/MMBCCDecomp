/* Wave 74-A v3 (v2 + b constant corrected 11264 -> 11520: ROM pool 0xFFFFD300 = -11520):
 * 0x0801238C, fresh. TRUE extent 376 B: code 372 B through bx at 0x124FE,
 * + 4 pool at 0x12500 (0xFFFFC400); next function 0x08012504.
 * v1 was 364 B / 261 diffs: nb hoisted before the s[17] tests (ROM computes
 * it inside each branch, after the pair/byte loads), pair second-index used
 * index+1 (ROM: base+1), and the s16-table base was loaded after *q
 * (ROM: pool first, then *q). .set stubs verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

u32 Call_0800DD2C(u8 *s, u32 a, u32 b);
u16 Call_08011F50(u8 *s);
void Call_0800D9EC(u8 *s, u32 a);
void Call_0800D9FC(u8 *s);
u32 Call_08017464(u32 a);
u32 Call_08011F68(u8 *s, u32 a);
void Call_0804A378(u32 a);
void Call_0801AA70(u8 a, u8 b, u32 c, s16 d, s16 e, u32 f);
void Call_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);
void Call_0801BBB4(u8 a, u32 b, s16 c, s16 d, u32 e);

extern u8 TABLE_08223D47[];
extern u8 TABLE_08223D44[];
extern u8 TABLE_08223ED8[];

__attribute__((section(".text.w74a_0801238c")))
void sub_0801238C(u8 *s)
{
    u8 *q;
    q = s + 124;
    switch (s[14]) {
    case 0:
        Call_0800DD2C(s, 0xFFFFC400, 0);
        Call_0800D9EC(s, 15);
        s[14]++;
        break;
    case 1:
        if (Call_08011F50(s)) {
            s[14]++;
            Call_0800D9EC(s, 16);
            if ((u8)(s[17] - 19) <= 5) {
                u8 *bp;
                int ix;
                u8 p0, p1;
                u32 nb;
                u8 *tbl;
                u16 *ent;
                s16 a, b;
                Call_0804A378(131);
                bp = TABLE_08223D47;
                ix = (s[17] - 19) * 2;
                p0 = bp[ix];
                bp++;
                p1 = bp[ix];
                nb = ((u32)s[35] << 28) >> 28;
                tbl = TABLE_08223ED8;
                ent = (u16 *)(tbl + *q * 4);
                a = ent[0];
                b = ent[1];
                Call_0801AA70(p0, p1, nb, a, b, *(u32 *)(s + 44));
            } else if ((u8)(s[17] - 16) <= 2) {
                u8 by;
                u32 nb;
                Call_0804A378(146);
                by = TABLE_08223D44[s[17] - 16];
                nb = ((u32)s[35] << 28) >> 28;
                Call_0801AB94(by, nb, 15360, -6400, *(u32 *)(s + 44));
            } else {
                u8 sv;
                u32 nb;
                u8 *tbl;
                u16 *ent;
                u16 a, b;
                Call_0804A378(131);
                sv = s[17];
                nb = ((u32)s[35] << 28) >> 28;
                tbl = TABLE_08223ED8;
                ent = (u16 *)(tbl + *q * 4);
                a = ent[0];
                b = ent[1];
                Call_0801BBB4(sv, nb, (s16)(a - 15360),
                              (s16)(b - 11520), *(u32 *)(s + 44));
            }
        }
        break;
    case 2:
        if (Call_08011F50(s)) {
            Call_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            Call_0800DD2C(s, 0xFFFFC400, 0);
            Call_0800D9EC(s, 0);
            q[4] = 0;
            Call_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    Call_0800D9FC(s);
}

__asm__(
    ".globl Call_0800DD2C\n.set Call_0800DD2C, 0x0800DD2C\n"
    ".globl Call_08011F50\n.set Call_08011F50, 0x08011F50\n"
    ".globl Call_0800D9EC\n.set Call_0800D9EC, 0x0800D9EC\n"
    ".globl Call_0800D9FC\n.set Call_0800D9FC, 0x0800D9FC\n"
    ".globl Call_08017464\n.set Call_08017464, 0x08017464\n"
    ".globl Call_08011F68\n.set Call_08011F68, 0x08011F68\n"
    ".globl Call_0804A378\n.set Call_0804A378, 0x0804A378\n"
    ".globl Call_0801AA70\n.set Call_0801AA70, 0x0801AA70\n"
    ".globl Call_0801AB94\n.set Call_0801AB94, 0x0801AB94\n"
    ".globl Call_0801BBB4\n.set Call_0801BBB4, 0x0801BBB4\n"
    ".globl TABLE_08223D47\n.set TABLE_08223D47, 0x08223D47\n"
    ".globl TABLE_08223D44\n.set TABLE_08223D44, 0x08223D44\n"
    ".globl TABLE_08223ED8\n.set TABLE_08223ED8, 0x08223ED8\n"
);
