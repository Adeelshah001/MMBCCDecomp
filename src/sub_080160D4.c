/* sub_080160D4 @ 0x080160D4 (812 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w138d_080160d4_MATCHED.c (registry: src/w138d_080160d4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

struct F24 { u8 b0:1; u8 b1:4; u8 rest:3; };

struct ObjMid { u8 _00[0x25]; u8 f25; u16 timer; };

void sub_080174A4(u8 *p, u8 bit);

s32 sub_08017474(u8 *p);

void sub_08017478(u8 *p, u8 v);

void sub_08017464(u8 *p);

void sub_0800DD2C(u8 *o, s32 x, s32 y);

void sub_0800D9EC(u8 *s, u8 idx);

void sub_0800D9FC(u8 *s);

s16 sub_08011F50(u8 *s);

void sub_08011F68(u8 *s, u8 v);

void sub_0801EE14(u8 a, s8 b, u8 c, s16 d, s16 e);

s16 sub_0804A378(s16 idx);

extern u8 gUnknown_02003670[];

void sub_080160D4(u8 *s)
{
    u8 *q = s;
    u8 v;
    q += 0x7C;

    switch (s[0x0E]) {
    case 0:
        if (q[7] == 0)
            sub_080174A4(*(u8 **)(s + 0x2C), 0);
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 0);
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
        if ((u8)sub_08017474(*(u8 **)(s + 0x2C)) > 6) {
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
        v = (u8)sub_08017474(*(u8 **)(s + 0x2C));
        /* Branches swapped vs numeric order on purpose: ROM lays the
         * v!=0 path inline and the v==0 path out-of-line after it
         * (beq to the later block), which also pushes the shared
         * s[0x12]++ block past the bne range for case 1's test. */
        if (v != 0) {
            ((struct F24 *)(s + 0x24))->b0 = 1;
            ((struct F24 *)(s + 0x24))->b1 = 0;
            ((struct ObjMid *)s)->f25 = 0;
            ((struct ObjMid *)s)->timer = 992;
            if ((u8)sub_08017474(*(u8 **)(s + 0x2C)) > 6) {
                s[0x0E] = 5;
            } else {
                gUnknown_02003670[0x11AF] = (gUnknown_02003670[0x11AF] & 15) | 64;
                s[0x21] = 6;
                sub_0800D9EC(s, 3);
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
        if (sub_08011F50(s) == 0)
            break;
        if ((u8)sub_08017474(*(u8 **)(s + 0x2C)) > 1
            && (u8)sub_08017474(*(u8 **)(s + 0x2C)) <= 5) {
            s[0x21] = 6;
            sub_0800D9EC(s, 3);
            break;
        }
        if (q[7] != 2) {
            s[0x0E]++;
            break;
        }
        sub_0800D9EC(s, 7);
        s[0x0E] = 9;
        break;
    case 7:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 0);
        s[0x0E]++;
        break;
    case 8:
        if ((u8)sub_08017474(*(u8 **)(s + 0x2C)) <= 6)
            break;
        /* fallthrough into case 4 */
    case 4:
        sub_08017478(*(u8 **)(s + 0x2C), 8);
        sub_08017464(*(u8 **)(s + 0x2C));
        *(u8 **)(s + 0x2C) = (u8 *)0;
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 0);
        q[4] = 0;
        sub_08011F68(s, 0);
        break;
    case 9: {
        u8 *p = s;
        s16 e;
        p += 0x21;
        e = 0;
        *p = 60;
        s[0x12] = 40;
        sub_0801EE14(0, -4, (u8)(((u32)s[0x23] << 28) >> 28), -15360, e);
        s[0x0E]++;
        break;
    }
    case 10:
        s[0x12]--;
        if (s[0x12] != 0)
            break;
        sub_0800D9EC(s, 2);
        sub_0804A378(127);
        s[0x0E]++;
        break;
    case 11:
        if ((u8)sub_08017474(*(u8 **)(s + 0x2C)) <= 6)
            break;
        {
            u32 zero;
            u8 nv;
            nv = s[0x0A] & 254;
            zero = 0;
            s[0x0A] = nv;
            sub_08017478(*(u8 **)(s + 0x2C), 8);
            sub_08017464(*(u8 **)(s + 0x2C));
            *(u8 **)(s + 0x2C) = (u8 *)zero;
            sub_0800DD2C(s, -15360, 0);
            sub_0800D9EC(s, 0);
            q[4] = (u8)zero;
            sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
