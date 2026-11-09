/* Wave 143-A (STAGED ONLY, NOT LANDED): 0x08048F3C v6, manual method.
 * *** CLEAN 0-DIFF, 760/760 B EXACT, old -O2 -mthumb-interwork ***
 * FLAG FOR COORDINATOR: independent re-verification + .set-stub scan of
 * mmbcc/src/ required before any landing (per brief, this worker does
 * NOT land). Closing lever: case-2 tests routed through a block-scoped
 * INT temp (int v2 = s[0x46a9] after the store; tests on v2, not on
 * s[0x46a9] directly). The int temp (unlike the Wave 142 s8 temp, which
 * exploded to 488/496) keeps the ldrb load and the cmp #0 / bge +
 * cmp #4 / ble pair that old_agbcc otherwise folds to cmp #4 / bls,
 * AND flips the allocator coloring function-wide to the ROM homes
 * (s->r5, val->r4, res STILL r6) -- the legitimate-fix condition proven
 * in Wave 142, achieved here with a semantically identical variable
 * (v2 is loaded immediately after the store; s[0x46a9] is not written
 * between the store and the tests, so v2 == s[0x46a9] at every test).
 * No pins, no inline body asm, no barrier forms; plain .set stubs only.
 * TRUE extent 760 B (next fn 0x08049234). Prior best v5 90/90.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern int Sub_08024384(int a);
extern void Sub_08004F18(void);
extern void Sub_08004F80(void);
extern void Sub_0804A3FC(void);
extern int Sub_0804A40C(void);
extern int Sub_08024FD8(u8 *a, u8 *b);
extern int Sub_08024FF4(int a);
extern int Sub_0800B368(u32 a, int b, int c, int d);
extern int Sub_0800B308(void);
extern int Sub_0802500C(void);
extern void Sub_0802508C(int a);
extern u32 T_082343E8[];
extern u32 T_08234448[];
extern u32 T_08234460[];
extern u32 T_08234430[];
extern u32 T_08234478[];
extern u32 T_08234490[];
extern u32 T_082344A8[];
extern u32 G_08233CBC;
extern u32 G_08233CC4;
extern u8 G_02004E40[];

__asm__(".set Sub_08024384, 0x08024384");
__asm__(".set Sub_08004F18, 0x08004F18");
__asm__(".set Sub_08004F80, 0x08004F80");
__asm__(".set Sub_0804A3FC, 0x0804A3FC");
__asm__(".set Sub_0804A40C, 0x0804A40C");
__asm__(".set Sub_08024FD8, 0x08024FD8");
__asm__(".set Sub_08024FF4, 0x08024FF4");
__asm__(".set Sub_0800B368, 0x0800B368");
__asm__(".set Sub_0800B308, 0x0800B308");
__asm__(".set Sub_0802500C, 0x0802500C");
__asm__(".set Sub_0802508C, 0x0802508C");
__asm__(".set T_082343E8, 0x082343E8");
__asm__(".set T_08234448, 0x08234448");
__asm__(".set T_08234460, 0x08234460");
__asm__(".set T_08234430, 0x08234430");
__asm__(".set T_08234478, 0x08234478");
__asm__(".set T_08234490, 0x08234490");
__asm__(".set T_082344A8, 0x082344A8");
__asm__(".set G_08233CBC, 0x08233CBC");
__asm__(".set G_08233CC4, 0x08233CC4");
__asm__(".set G_02004E40, 0x02004E40");

__attribute__((section(".text.w143a_08048F3C_v6")))
int Sub_08048F3C(u8 *s)
{
    int res = 0;
    u8 val = (u8)(Sub_08024384(0x1000) - 50);

    Sub_08004F18();
    switch (s[0x46a5]) {
    case 0:
        Sub_0804A3FC();
        s[0x46a5]++;
        break;
    case 1: {
        s8 t = (s8)Sub_0804A40C();
        if (t == -2) {
            s8 *p = (s8 *)(s + 0x46a7);
            if (*p > 0) {
                s[0x46a5]--;
                s[0x46a7]--;
            } else {
                s[0x46a5]++;
            }
        } else if (t == -1) {
        } else {
            s[0x46a5]++;
        }
        break;
    }
    case 2: {
        int v2;
        s[0x46a9] = Sub_08024FF4(Sub_08024FD8(s + 0x45ac, s + 0x45b4));
        v2 = s[0x46a9];
        if (v2 == 0) {
            if ((u8)Sub_0800B368(T_082343E8[val], 0, 0, 0) != 0)
                s[0x46a5] = 3;
        } else if (v2 >= 0) {
            if (v2 <= 4)
                s[0x46a5] = 4;
        }
        break;
    }
    case 3:
        if ((u8)Sub_0800B308() != 0) {
            s[0x46a4] = 4;
            s[0x46a5] = 3;
        }
        break;
    case 4:
        switch (s[0x46a9]) {
        case 3:
            res = (u8)Sub_0800B368(T_08234430[val], 0, 0, 0);
            break;
        case 1:
            res = (u8)Sub_0800B368(T_08234448[val], 0, 0, 0);
            break;
        case 2:
            res = (u8)Sub_0800B368(T_08234460[val], 0, 0, 0);
            break;
        case 4:
            res = (u8)Sub_0800B368(T_08234478[val], 0, 0, 0);
            break;
        default:
            break;
        }
        if (res != 0)
            s[0x46a5]++;
        break;
    case 5:
        if ((u8)Sub_0800B308() != 0) {
            if (s[0x46a9] == 2)
                s[0x46a5]++;
            else {
                s[0x46a4] = 0;
                s[0x46a5] = 3;
            }
        }
        break;
    case 6:
        if ((u8)Sub_0800B368(T_08234490[val], G_08233CBC, G_08233CC4, 0) != 0)
            s[0x46a5]++;
        break;
    case 7:
        if ((u8)Sub_0800B308() != 0) {
            if ((s8)G_02004E40[8] == 0)
                s[0x46a5]++;
            else {
                s[0x46a4] = 0;
                s[0x46a5] = 3;
            }
        }
        break;
    case 8:
        if ((u8)Sub_0800B368(T_082344A8[val], 0, 0, 0) != 0) {
            Sub_0802508C((u8)Sub_0802500C());
            Sub_08024FD8(s + 0x45ac, s + 0x45b4);
            s[0x46a5]++;
        }
        break;
    case 9:
        if ((u8)Sub_0800B308() != 0) {
            s[0x46a4] = 4;
            s[0x46a5] = 3;
        }
        break;
    default:
        break;
    }
    Sub_08004F80();
    return 0;
}
