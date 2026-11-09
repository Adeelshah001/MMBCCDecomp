/* Wave 138-D v8 (STAGED ONLY, NOT LANDED). 0x080160D4, TRUE extent 812 B
 * (next func 0x08016400). Hand-decoded from ROM disassembly
 * (staging/w138d_/work/dis_080160d4.txt): a 12-case state machine on
 * s[0x0E] (u8, cases 0..11, default = tick only), ending in a shared
 * ChipSlot_Tick(s) tail. q = s + 0x7C (so q[7] = s[0x83], q[4] = s[0x80]).
 * Callees (file-scope .set stubs at end, NOT inline asm in the body):
 *  174A4 SetBit16(sub, bit): sub[16] |= 1 << bit.
 *  17474 GetField17: returns sub[17]; declared int here because every
 *   ROM caller truncates with lsls #24 / lsrs #24 (a (u8) cast of an
 *   int return); the landed wave3_a declaration (u8 return) would drop
 *   those shifts, so this prototype is a landing question, not a given.
 *  17478 MaxAssign_17(sub, 8); 17464 DecIfNonZero_18(sub).
 *  0DD2C Vec2_SetMirrored(s, -15360, 0); 0D9EC ChipSlot_IncUse(s, idx);
 *  0D9FC ChipSlot_Tick(s); 11F50 returns s16 (s[0x77] in {3,4});
 *  11F68 resets s[0x0D..0x0F] = v,0,0 and q[5] = v;
 *  1EE14 spawns (0, -4, s[0x23] low nibble, -15360, 0);
 *  4A378 Text_SelectBlobIdx(127), return ignored.
 * Case order in this switch follows the ROM block layout (case 8 falls
 * through into case 4), not numeric order. Shared tails (state++ at
 * 63A2, state=5 at 6248, counter++ at 62AE) are left for the compiler's
 * cross-jumping to merge; they are NOT hand-duplicated as gotos.
 * Flags byte at s+0x24: idiom A = set bit0, then set bits1-4 to
 * s[0x12] & 15 (mask -31 = ~0x1E, keeps bit0 and bits5-7); idiom B =
 * set bit0 then clear bits1-4 (single store after DSE).
 * Case 5's RAM byte: base 0x02003670 + 0x11AF, written as two
 * statements so the compiler loads both literals and adds (ROM does
 * ldr base, ldr offset, adds, not a single folded literal).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* Bitfield bytes (see bftest2: with a memory-loaded count, old_agbcc
 * reproduces ROM idiom A exactly: two stores, movs #31 + negs mask;
 * bitfield B (b0=1, b1=0) reproduces ROM idiom B as a single store
 * with or-then-and order; the +0x23 low nibble read reproduces the
 * case-9 lsls #28 / lsrs #28 extraction). */
struct F23 { u8 lo:4; u8 mid:3; u8 flip:1; };
struct F24 { u8 b0:1; u8 b1:4; u8 rest:3; };
struct ObjMid { u8 _00[0x25]; u8 f25; u16 timer; };

void Call138_080174A4(u8 *p, u8 bit);
s32 Call138_08017474(u8 *p);
void Call138_08017478(u8 *p, u8 v);
void Call138_08017464(u8 *p);
void Call138_0800DD2C(u8 *o, s32 x, s32 y);
void Call138_0800D9EC(u8 *s, u8 idx);
void Call138_0800D9FC(u8 *s);
s16 Call138_08011F50(u8 *s);
void Call138_08011F68(u8 *s, u8 v);
void Call_0801EE14(u8 a, s8 b, u8 c, s16 d, s16 e);
s16 Call138_0804A378(s16 idx);
extern u8 gW138dRamBase[];

__attribute__((section(".text.w138d_080160d4")))
void sub_080160D4(u8 *s)
{
    u8 *q = s;
    u8 v;
    q += 0x7C;

    switch (s[0x0E]) {
    case 0:
        if (q[7] == 0)
            Call138_080174A4(*(u8 **)(s + 0x2C), 0);
        Call138_0800DD2C(s, -15360, 0);
        Call138_0800D9EC(s, 0);
        s[0x12] = 0;
        if (q[7] == 0)
            s[0x0E]++;
        else
            s[0x0E] = 5;
        break;
    case 1:
        ((struct F24 *)(s + 0x24))->b0 = 1;
        ((struct F24 *)(s + 0x24))->b1 = s[0x12] & 15;
        ((struct ObjMid *)s)->f25 = 0;
        ((struct ObjMid *)s)->timer = 992;
        if (s[0x12] == 15) {
            s[0x13] = 0;
            s[0x0E]++;
        } else {
            s[0x12]++;
        }
        break;
    case 2:
        if ((u8)Call138_08017474(*(u8 **)(s + 0x2C)) > 6) {
            s[0x0E]++;
            s[0x0A] |= 1;
        } else {
            s[0x13]++;
            if ((s[0x13] & 4) == 0)
                s[0x0A] |= 1;
            else
                s[0x0A] &= 254;
        }
        break;
    case 3:
        ((struct F24 *)(s + 0x24))->b0 = 1;
        ((struct F24 *)(s + 0x24))->b1 = s[0x12] & 15;
        ((struct ObjMid *)s)->f25 = 0;
        ((struct ObjMid *)s)->timer = 992;
        if (s[0x12] == 0)
            s[0x0E]++;
        else
            s[0x12]--;
        break;
    case 5: {
        v = (u8)Call138_08017474(*(u8 **)(s + 0x2C));
        /* Branches swapped vs numeric order on purpose: ROM lays the
         * v!=0 path inline and the v==0 path out-of-line after it
         * (beq to the later block), which also pushes the shared
         * s[0x12]++ block past the bne range for case 1's test. */
        if (v != 0) {
            ((struct F24 *)(s + 0x24))->b0 = 1;
            ((struct F24 *)(s + 0x24))->b1 = 0;
            ((struct ObjMid *)s)->f25 = 0;
            ((struct ObjMid *)s)->timer = 992;
            if ((u8)Call138_08017474(*(u8 **)(s + 0x2C)) > 6) {
                s[0x0E] = 5;
            } else {
                gW138dRamBase[0x11AF] = (gW138dRamBase[0x11AF] & 15) | 64;
                s[0x21] = 6;
                Call138_0800D9EC(s, 3);
                s[0x0E]++;
            }
        } else {
            ((struct F24 *)(s + 0x24))->b0 = 1;
            ((struct F24 *)(s + 0x24))->b1 = s[0x12] & 15;
            s[0x25] = v;
            ((struct ObjMid *)s)->timer = 992;
            if (s[0x12] <= 14)
                s[0x12]++;
        }
        break;
    }
    case 6:
        if (Call138_08011F50(s) == 0)
            break;
        if ((u8)Call138_08017474(*(u8 **)(s + 0x2C)) > 1
            && (u8)Call138_08017474(*(u8 **)(s + 0x2C)) <= 5) {
            s[0x21] = 6;
            Call138_0800D9EC(s, 3);
            break;
        }
        if (q[7] != 2) {
            s[0x0E]++;
            break;
        }
        Call138_0800D9EC(s, 7);
        s[0x0E] = 9;
        break;
    case 7:
        if (Call138_08011F50(s) == 0)
            break;
        Call138_0800D9EC(s, 0);
        s[0x0E]++;
        break;
    case 8:
        if ((u8)Call138_08017474(*(u8 **)(s + 0x2C)) <= 6)
            break;
        /* fallthrough into case 4 */
    case 4:
        Call138_08017478(*(u8 **)(s + 0x2C), 8);
        Call138_08017464(*(u8 **)(s + 0x2C));
        *(u8 **)(s + 0x2C) = (u8 *)0;
        Call138_0800DD2C(s, -15360, 0);
        Call138_0800D9EC(s, 0);
        q[4] = 0;
        Call138_08011F68(s, 0);
        break;
    case 9: {
        u8 *p = s;
        s16 e;
        p += 0x21;
        e = 0;
        *p = 60;
        s[0x12] = 40;
        Call_0801EE14(0, -4, (u8)(((u32)s[0x23] << 28) >> 28), -15360, e);
        s[0x0E]++;
        break;
    }
    case 10:
        s[0x12]--;
        if (s[0x12] != 0)
            break;
        Call138_0800D9EC(s, 2);
        Call138_0804A378(127);
        s[0x0E]++;
        break;
    case 11:
        if ((u8)Call138_08017474(*(u8 **)(s + 0x2C)) <= 6)
            break;
        {
            u32 zero;
            u8 nv;
            nv = s[0x0A] & 254;
            zero = 0;
            s[0x0A] = nv;
            Call138_08017478(*(u8 **)(s + 0x2C), 8);
            Call138_08017464(*(u8 **)(s + 0x2C));
            *(u8 **)(s + 0x2C) = (u8 *)zero;
            Call138_0800DD2C(s, -15360, 0);
            Call138_0800D9EC(s, 0);
            q[4] = (u8)zero;
            Call138_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    Call138_0800D9FC(s);
}

__asm__(
    ".globl Call138_080174A4\n.set Call138_080174A4, 0x080174A4\n"
    ".globl Call138_08017474\n.set Call138_08017474, 0x08017474\n"
    ".globl Call138_08017478\n.set Call138_08017478, 0x08017478\n"
    ".globl Call138_08017464\n.set Call138_08017464, 0x08017464\n"
    ".globl Call138_0800DD2C\n.set Call138_0800DD2C, 0x0800DD2C\n"
    ".globl Call138_0800D9EC\n.set Call138_0800D9EC, 0x0800D9EC\n"
    ".globl Call138_0800D9FC\n.set Call138_0800D9FC, 0x0800D9FC\n"
    ".globl Call138_08011F50\n.set Call138_08011F50, 0x08011F50\n"
    ".globl Call138_08011F68\n.set Call138_08011F68, 0x08011F68\n"
    ".globl Call_0801EE14\n.set Call_0801EE14, 0x0801EE14\n"
    ".globl Call138_0804A378\n.set Call138_0804A378, 0x0804A378\n"
    ".globl gW138dRamBase\n.set gW138dRamBase, 0x02003670\n"
);
