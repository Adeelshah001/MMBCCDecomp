/* Wave 74-A v1: 0x08012880, fresh (registry-checked 2026-10-28, no row).
 * TRUE extent 376 B (tiling): code 372 B through bx at 0x129F2, + 4 pool
 * at 0x129F4 (0xFFFFC400); next function 0x080129F8. 1264C sibling:
 * void F(u8 *s); push {r4,r5,r6,lr}; sub sp,#12; Memcpy(buf,0x080E9BF3,7)
 * with buf[8] at sp+4 (sp+0 is the outgoing 5th-arg slot for the case-3
 * 1AB94 call); q = s+124; switch on s[14] (7 cases, jump-table base pool
 * 0x128AC = 0x080128B0); shared advance s[14]++ then D9FC epilogue.
 * Case 0: DD2C(s,0xFFFFC400,0); D9EC(s,2); A378(152); advance.
 * Case 1: 11F50 gate; DD2C(s,0xFFFFFA00,0); D9EC(s,1); advance
 *   (shared DD2C+D9EC block with case 5, differing pool arg).
 * Case 2: 11F50 gate; D9EC(s,21); advance (shared D9EC block w/ case 4).
 * Case 3: 11F50 gate; D9EC(s,22); 174A4([s+44],3);
 *   1AB94(buf[s[17]], s[35]&0xF, (s16)(tab[q].a-256),
 *   (s16)(tab[q].b-512), [s+44]); advance.
 * Case 4: (u8)17474([s+44])>6 gate (else -> tail, no advance);
 *   D9EC(s,2); advance.
 * Case 5: 11F50 gate; DD2C(s,0xFFFFC400,0); D9EC(s,1); advance.
 * Case 6: 11F50 gate; 17464([s+44]); [s+44]=0; DD2C(s,0xFFFFC400,0);
 *   D9EC(s,0); q[4]=0; 11F68(s,0); epilogue (no advance).
 * .set stubs verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

void *Call_0804DFA8(void *dst, const void *src, u32 len);
u32 Call_0800DD2C(u8 *s, u32 a, u32 b);
u16 Call_08011F50(u8 *s);
void Call_0800D9EC(u8 *s, u32 a);
void Call_0800D9FC(u8 *s);
u32 Call_080174A4(u32 a, u32 b);
u32 Call_08017474(u32 a);
u32 Call_08017464(u32 a);
u32 Call_08011F68(u8 *s, u32 a);
void Call_0801AB94(u8 a, u32 b, s16 c, s16 d, u32 e);
void Call_0804A378(u32 a);

extern u8 TABLE_08223ED8[];

__attribute__((section(".text.w74a_08012880")))
void sub_08012880(u8 *s)
{
    u8 buf[8];
    u8 *q;
    Call_0804DFA8(buf, (const void *)0x080E9BF3, 7);
    q = s + 124;
    switch (s[14]) {
    case 0:
        Call_0800DD2C(s, 0xFFFFC400, 0);
        Call_0800D9EC(s, 2);
        Call_0804A378(152);
        s[14]++;
        break;
    case 1:
        if (Call_08011F50(s)) {
            Call_0800DD2C(s, 0xFFFFFA00, 0);
            Call_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Call_08011F50(s)) {
            Call_0800D9EC(s, 21);
            s[14]++;
        }
        break;
    case 3:
        if (Call_08011F50(s)) {
            u8 bb;
            u32 nb;
            u8 *tbl;
            u16 *ent;
            u16 a, b;
            Call_0800D9EC(s, 22);
            Call_080174A4(*(u32 *)(s + 44), 3);
            bb = buf[s[17]];
            nb = ((u32)s[35] << 28) >> 28;
            tbl = TABLE_08223ED8;
            ent = (u16 *)(tbl + *q * 4);
            a = ent[0];
            b = ent[1];
            Call_0801AB94(bb, nb, (s16)(a - 256), (s16)(b - 512),
                          *(u32 *)(s + 44));
            s[14]++;
        }
        break;
    case 4:
        if ((u8)Call_08017474(*(u32 *)(s + 44)) > 6) {
            Call_0800D9EC(s, 2);
            s[14]++;
        }
        break;
    case 5:
        if (Call_08011F50(s)) {
            Call_0800DD2C(s, 0xFFFFC400, 0);
            Call_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 6:
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
    ".globl Call_0804DFA8\n.set Call_0804DFA8, 0x0804DFA8\n"
    ".globl Call_0800DD2C\n.set Call_0800DD2C, 0x0800DD2C\n"
    ".globl Call_08011F50\n.set Call_08011F50, 0x08011F50\n"
    ".globl Call_0800D9EC\n.set Call_0800D9EC, 0x0800D9EC\n"
    ".globl Call_0800D9FC\n.set Call_0800D9FC, 0x0800D9FC\n"
    ".globl Call_080174A4\n.set Call_080174A4, 0x080174A4\n"
    ".globl Call_08017474\n.set Call_08017474, 0x08017474\n"
    ".globl Call_08017464\n.set Call_08017464, 0x08017464\n"
    ".globl Call_08011F68\n.set Call_08011F68, 0x08011F68\n"
    ".globl Call_0801AB94\n.set Call_0801AB94, 0x0801AB94\n"
    ".globl Call_0804A378\n.set Call_0804A378, 0x0804A378\n"
    ".globl TABLE_08223ED8\n.set TABLE_08223ED8, 0x08223ED8\n"
);
