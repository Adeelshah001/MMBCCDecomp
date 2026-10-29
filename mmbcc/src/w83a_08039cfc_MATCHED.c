/* Wave 83-A claim: 0x08039CFC (from Wave 82 v3, corrected), registry-fresh. TRUE extent 416 B (next 0x08039E9C).
 * Decode: u8 F(u8 *s), return in r6 (init 0). Switch on (s8)s[0x469D]
 * (7 cases, jump table; pool word holds table base 0x08039D24).
 * case 0: if ((s8)Call_08028778(s + 0x469F, 1) == 0) { s[0x469F] = 0;
 *   s[0x469D]++; } break (no 4F80 call on this path).
 * case 1: Call_08004E44(); Call_08004DFC(G_02004F80[2]); Call_0800BEE0(64, 128);
 *   Call_0804A2DC(8); s[0x4699] = 0; s[0x469D]++; fallthrough to case 2.
 * case 2: Call_08004F18(); Call_0800B148(1, (s16)Call_08024514((u8)
 *   Call_080241F8(128 << 5)), 4); shared test (see below).
 * case 3: Call_08004F18(); Call_0800B2D8(); shared test.
 * case 4: Call_08004F18(); f = Tbl_082317FC[(u8)(Call_08024384(128 << 5) - 50)];
 *   Call_0800B368(f, *(u32*)0x08230E28, *(u32*)0x08230E30, 0); shared test.
 * shared test (cases 2/3/4): if (call result == 0) { Call_08004F80(); break; }
 *   s[0x469D]++; Call_08004F80(); break.
 * case 5: Call_08004F18(); G_02004E40[20] |= 1; if (Call_0800B308() == 0)
 *   { Call_08004F80(); break; } if ((s8)G_02004E40[8] == 0) { s[0x469D]++;
 *   Call_08004F80(); break; } s[0x469C] = 4; s[0x469D] = 0;
 *   Call_0804A328(); r = 1; Call_08004F80(); break.
 * case 6: Call_08004F18(); if (Call_0800B2B4() == 0) { Call_08004F80(); break; }
 *   s[0x469C] = 8; s[0x469D] = 0; s[4] = 0; r = 1; Call_08004F80(); break.
 * default: break. Epilogue: return r. .set stubs verification-only. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

s8 Call_08028778(u8 *a, u32 b);
void Call_08004E44(void);
void Call_08004DFC(u8 a);
void Call_0800BEE0(u32 a, u32 b);
void Call_0804A2DC(u32 a);
void Call_08004F18(void);
void Call_08004F80(void);
u8 Call_080241F8(u32 a);
s16 Call_08024514(u8 a);
u8 Call_0800B148(u8 f, s16 t, u8 mode);
u8 Call_0800B2D8(void);
u8 Call_08024384(u32 a);
u8 Call_0800B368(u32 f, u32 a, u32 b, u32 c);
u8 Call_0800B308(void);
void Call_0804A328(void);
u8 Call_0800B2B4(void);

extern u8 G_02004F80[];
extern u8 G_02004E40[];
extern u32 Tbl_082317FC[];
extern u32 G_08230E28[];
extern u32 G_08230E30[];

__attribute__((section(".text.w83a_08039cfc")))
u8 sub_08039CFC(u8 *s)
{
    u8 r = 0;
    u8 z;
    u8 *p;
    switch ((s8)s[0x469D]) {
    case 0:
        if (Call_08028778(s + 0x469F, 1) == 0) {
            s[0x469F] = 0;
            s[0x469D]++;
        }
        break;
    case 1:
        Call_08004E44();
        Call_08004DFC(G_02004F80[2]);
        Call_0800BEE0(64, 128);
        Call_0804A2DC(8);
        s[0x4699] = 0;
        s[0x469D]++;
    case 2:
        Call_08004F18();
        if (Call_0800B148(1, Call_08024514((u8)Call_080241F8(128 << 5)), 4) == 0)
            goto f80;
        goto inc;
    case 3:
        Call_08004F18();
        if (Call_0800B2D8() == 0)
            goto f80;
        goto inc;
    case 4: {
        u32 f;
        u8 idx;
        Call_08004F18();
        idx = (u8)(Call_08024384(128 << 5) - 50);
        f = Tbl_082317FC[idx];
        if (Call_0800B368(f, *G_08230E28, *G_08230E30, 0) == 0)
            goto f80;
        goto inc;
    }
    inc:
        s[0x469D]++;
        goto f80;
    case 5:
        Call_08004F18();
        G_02004E40[20] |= 1;
        if (Call_0800B308() == 0)
            goto f80;
        {
            int i = 8;
            if ((s8)G_02004E40[i] == 0)
                goto inc;
        }
        p = s + 0x469C;
        z = 0;
        *p = 4;
        s[0x469D] = z;
        Call_0804A328();
        r = 1;
    f80:
        Call_08004F80();
        break;
    case 6:
        Call_08004F18();
        if (Call_0800B2B4() == 0)
            goto f80_6;
        p = s + 0x469C;
        z = 0;
        *p = 8;
        s[0x469D] = z;
        s[4] = z;
        r = 1;
    f80_6:
        Call_08004F80();
        break;
    default:
        break;
    }
    return r;
}

__asm__(
    ".globl Call_08028778\n.set Call_08028778, 0x08028778\n"
    ".globl Call_08004E44\n.set Call_08004E44, 0x08004E44\n"
    ".globl Call_08004DFC\n.set Call_08004DFC, 0x08004DFC\n"
    ".globl Call_0800BEE0\n.set Call_0800BEE0, 0x0800BEE0\n"
    ".globl Call_0804A2DC\n.set Call_0804A2DC, 0x0804A2DC\n"
    ".globl Call_08004F18\n.set Call_08004F18, 0x08004F18\n"
    ".globl Call_08004F80\n.set Call_08004F80, 0x08004F80\n"
    ".globl Call_080241F8\n.set Call_080241F8, 0x080241F8\n"
    ".globl Call_08024514\n.set Call_08024514, 0x08024514\n"
    ".globl Call_0800B148\n.set Call_0800B148, 0x0800B148\n"
    ".globl Call_0800B2D8\n.set Call_0800B2D8, 0x0800B2D8\n"
    ".globl Call_08024384\n.set Call_08024384, 0x08024384\n"
    ".globl Call_0800B368\n.set Call_0800B368, 0x0800B368\n"
    ".globl Call_0800B308\n.set Call_0800B308, 0x0800B308\n"
    ".globl Call_0804A328\n.set Call_0804A328, 0x0804A328\n"
    ".globl Call_0800B2B4\n.set Call_0800B2B4, 0x0800B2B4\n"
    ".globl G_02004F80\n.set G_02004F80, 0x02004F80\n"
    ".globl G_02004E40\n.set G_02004E40, 0x02004E40\n"
    ".globl Tbl_082317FC\n.set Tbl_082317FC, 0x082317FC\n"
    ".globl G_08230E28\n.set G_08230E28, 0x08230E28\n"
    ".globl G_08230E30\n.set G_08230E30, 0x08230E30\n"
);
