/* Wave 82-A v1: 0x0802FDA0, registry-fresh. TRUE extent 416 B (next 0x0802FF40).
 * Decode: u8 F(u8 *s), return in r5 (init 0). Entry Call_08034CA0(s).
 * G_02005160[58] = s[28].
 * if ((s[6] & 16) == 0 && (*(u16*)(0x02002F50+4) & 2) != 0) Call_0800EE50().
 * if ((s[6] & 1) != 0) { EDE4((s16)s[12]); EDF0((s16)s[14]); }
 * else { EDE4((s16)s[34]); EDF0((s16)s[178]); }
 * Switch on s[2] (9 cases, jump table; pool word holds table base).
 * case 0, case 4, default: Call_0800EA4C(0); break.
 * case 1: r = Call_0802FF40(s); if (r == 0) break; if (r == 11) { s[2]=0; s[3]=0; break; }
 *   s[2]=2; s[3]=0; break. (r is the return value.)
 * case 2: r = Call_0803048C(s); if (r == 0) break; s[2]=0; s[3]=0; break.
 * case 3: r = Call_08030AD4(s); if (r == 0) break; G_02005168[7]=0; G_02005168[27]=0;
 *   s[2]=0; s[3]=0; break.
 * case 5: r = Call_08033DE4(s); (same tail as case 3).
 * case 6: t = Call_080344F0(s); switch (t) { case 1: r=6; break;
 *   case 2: if (s[7] <= 9) s[7]++; s[0]=0; s[1]=0; r=9; break;
 *   case 3: s[0]=0; s[1]=0; r=10; break; case 11: r=11; break; }
 *   if (t != 0) { s[2]=0; s[3]=0; } break.
 * case 7: r = Call_0803449C(s); if (r == 0) break; if (r == 11) { s[2]=0; s[3]=0; break; }
 *   s[2]=2; s[3]=0; break.
 * case 8: t = Call_08033AC8(s); switch (t) { case 1: r=8; break;
 *   case 2: s[0]=0; s[1]=0; r=9; break; case 3: s[0]=0; s[1]=0; r=10; break; }
 *   if (t != 0) { s[1]=0; s[11]=0; } break.
 * Epilogue: return r. .set stubs verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

void Call_08034CA0(u8 *s);
void Call_0800EE50(void);
void Call_0800EDE4(s16 a);
void Call_0800EDF0(s16 a);
u8 Call_0802FF40(u8 *s);
u8 Call_0803048C(u8 *s);
u8 Call_08030AD4(u8 *s);
u8 Call_08033DE4(u8 *s);
u8 Call_080344F0(u8 *s);
u8 Call_0803449C(u8 *s);
u8 Call_08033AC8(u8 *s);
void Call_0800EA4C(u32 a);

extern u8 G_02005160[];
extern u8 G_02005168[];
extern u8 G_02002F50[];
extern u16 G_02002F50_16[];

__attribute__((section(".text.w83a_0802fda0")))
u8 sub_0802FDA0(u8 *s)
{
    u8 r = 0;
    Call_08034CA0(s);
    G_02005160[58] = s[28];
    if ((s[6] & 16) == 0 && (G_02002F50_16[2] & 2) != 0)
        Call_0800EE50();
    if ((s[6] & 1) == 0) {
        Call_0800EDE4(*(s16 *)(s + 34));
        Call_0800EDF0(*(s16 *)(s + 178));
    } else {
        Call_0800EDE4(*(s16 *)(s + 12));
        Call_0800EDF0(*(s16 *)(s + 14));
    }
    switch (s[2]) {
    case 0:
        goto ea4c;
    case 1:
        r = Call_0802FF40(s);
        goto tail17;
    case 2:
        r = Call_0803048C(s);
        if (r == 0)
            break;
        s[2] = 0;
        s[3] = 0;
        break;
    case 3:
        r = Call_08030AD4(s);
        goto tail35;
    case 4:
        goto ea4c;
    case 5:
        r = Call_08033DE4(s);
    tail35: {
        u8 *p;
        if (r == 0)
            break;
        p = G_02005168;
        p[7] = 0;
        p += 20;
        p[7] = 0;
        s[2] = 0;
        s[3] = 0;
        break;
    }
    case 7:
        r = Call_0803449C(s);
    tail17:
        if (r == 0)
            break;
        if (r == 11) {
            s[2] = 0;
            s[3] = 0;
            break;
        }
        {
            u8 b = 0;
            u8 a = 2;
            s[2] = a;
            s[3] = b;
        }
        break;
    case 8: {
        u8 t = Call_08033AC8(s);
        switch (t) {
        case 1:
            r = 8;
            break;
        case 2:
            s[0] = 0;
            s[1] = 0;
            r = 9;
            break;
        case 3:
            s[0] = 0;
            s[1] = 0;
            r = 10;
            break;
        default:
            break;
        }
        if (t != 0) {
            s[1] = 0;
            s[11] = 0;
        }
        break;
    }
    case 6: {
        u8 t = Call_080344F0(s);
        switch (t) {
        case 11:
            r = 11;
            break;
        case 1:
            r = 6;
            break;
        case 2:
            if (s[7] <= 9)
                s[7]++;
            s[0] = 0;
            s[1] = 0;
            r = 9;
            break;
        case 3:
            s[0] = 0;
            s[1] = 0;
            r = 10;
            break;
        default:
            break;
        }
        if (t != 0) {
            s[2] = 0;
            s[3] = 0;
        }
        break;
    }
    default:
    ea4c:
        Call_0800EA4C(0);
        break;
    }
    return r;
}

/* 2-byte zero pad: ROM has 00 00 at +414/+415; GAS would otherwise end the
 * 414-byte section with its default nop fill (c0 46). Pure-C pad object,
 * same-section, per the landed chipslot.c / text_idx.c precedent. */
__attribute__((section(".text.w83a_0802fda0")))
static const u8 s2FDA0Pad[2] = { 0, 0 };

__asm__(
    ".globl Call_08034CA0\n.set Call_08034CA0, 0x08034CA0\n"
    ".globl Call_0800EE50\n.set Call_0800EE50, 0x0800EE50\n"
    ".globl Call_0800EDE4\n.set Call_0800EDE4, 0x0800EDE4\n"
    ".globl Call_0800EDF0\n.set Call_0800EDF0, 0x0800EDF0\n"
    ".globl Call_0802FF40\n.set Call_0802FF40, 0x0802FF40\n"
    ".globl Call_0803048C\n.set Call_0803048C, 0x0803048C\n"
    ".globl Call_08030AD4\n.set Call_08030AD4, 0x08030AD4\n"
    ".globl Call_08033DE4\n.set Call_08033DE4, 0x08033DE4\n"
    ".globl Call_080344F0\n.set Call_080344F0, 0x080344F0\n"
    ".globl Call_0803449C\n.set Call_0803449C, 0x0803449C\n"
    ".globl Call_08033AC8\n.set Call_08033AC8, 0x08033AC8\n"
    ".globl Call_0800EA4C\n.set Call_0800EA4C, 0x0800EA4C\n"
    ".globl G_02005160\n.set G_02005160, 0x02005160\n"
    ".globl G_02005168\n.set G_02005168, 0x02005168\n"
    ".globl G_02002F50\n.set G_02002F50, 0x02002F50\n"
    ".globl G_02002F50_16\n.set G_02002F50_16, 0x02002F50\n"
);
