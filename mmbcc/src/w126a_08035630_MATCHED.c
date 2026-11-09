/* Wave 126-A v6 (case 2 pointer+zero declaration order closes the last 19 diffs -> 0-diff, exact size; manual method; extern-array keystate/table): 0x08035630, TRUE extent 520 B (next fn 0x08035838).
 * Hand decode from ROM disassembly. Key-scan + switch menu handler.
 *   r4 = s (u8*), r6 = table[0x0822ea88 + s[20]], r2 = key mask, r7 = ret (0/1).
 *   Scan: kp = (u16*)0x02002f50; keystate_02002f50[0] = held, keystate_02002f50[2] = +4 field, keystate_02002f50[3] = +6 field.
 *   Checks in order 0x20(+6), 0x10(+6), 0x40(+4), 0x80(+4), 0x02(+4), 0x08(+4),
 *   0x100(+4); later match overwrites earlier (plain ifs, not else-if).
 *   Switch (balanced cmp tree in ROM): 32 -> cursor-- wrap to max-1, call 5BC8;
 *   16 -> cursor++ clamp to max-1 (in-range: call 5BC8; overflow: full refresh);
 *   64/128 -> if max>12: cursor>12 ? cursor-=13 (clamp >=0) : cursor+=13 (clamp <=max-1),
 *     then call 5BC8; 2 -> s[0x46a8]=3, s[0x46a9]=0, sound 0x67, ret=1;
 *   8 -> s[0x46a8]=0, s[0x46a9]=0, sound 0x67, ret=1; 256 -> full refresh (5DA4,
 *   s[0x46ac]=28, sound 0x77, 5AFC, 5C5C).
 * Compiler+flags (filename O-token): old_agbcc -O2 -mthumb-interwork.
 * FINDING (Wave 126-A): the v5 wall was a single allocator-ordering effect in case 2.
 * ROM case 2 emits: ldr pool46a8; adds addr; movs r2,#0; movs r0,#3; strb; ldr pool46a9;
 * adds addr; strb r2. A block-local zero alone (probe blockzero) cut 19 -> 6 diffs and
 * restored cases 8/256 exactly (allocator rotation cascade: fixing case 2's temp order
 * restored the later blocks' pool registers), leaving only the position of the zero
 * materialisation (block entry vs after the first address computation). Declaring the
 * address first (u8 *p = s + 0x46a8;) and the zero second (u8 z = 0;) emits declarations
 * in order -- ldr/adds, then movs -- matching ROM instruction for instruction. Case 8
 * keeps the plain two-store form; case 256 keeps the plain refresh form. No pin, inline
 * asm, barrier, or alias used.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

extern u8 table_0822ea88[];
extern u16 keystate_02002f50[];

void Sub_08035BC8(u8 *s);
void Sub_08035DA4(u8 *s);
void Sub_0804A378(int x);
void Sub_08035AFC(u8 *s);
void Sub_08035C5C(u8 *s);

__attribute__((section(".text.w126a_08035630")))
int Sub_08035630(u8 *s)
{
    int key = 0;
    int ret = 0;
    u8 max = table_0822ea88[s[20]];
    /* kp is keystate_02002f50 (extern array, .set below) */

    if ((keystate_02002f50[0] & 0x20) != 0) {
        if ((keystate_02002f50[3] & 0x20) != 0)
            key = 0x20;
    }
    if ((keystate_02002f50[0] & 0x10) != 0) {
        if ((keystate_02002f50[3] & 0x10) != 0)
            key = 0x10;
    }
    if ((keystate_02002f50[0] & 0x40) != 0) {
        if ((keystate_02002f50[2] & 0x40) != 0)
            key = 0x40;
    }
    if ((keystate_02002f50[0] & 0x80) != 0) {
        if ((keystate_02002f50[2] & 0x80) != 0)
            key = 0x80;
    }
    if ((keystate_02002f50[0] & 0x02) != 0) {
        if ((keystate_02002f50[2] & 0x02) != 0)
            key = 0x02;
    }
    if ((keystate_02002f50[0] & 0x08) != 0) {
        if ((keystate_02002f50[2] & 0x08) != 0)
            key = 0x08;
    }
    if ((keystate_02002f50[0] & 0x100) != 0) {
        if ((keystate_02002f50[2] & 0x100) != 0)
            key = 0x100;
    }

    switch (key) {
    case 64:
    case 128:
        if (max > 12) {
            if ((s8)s[0x46aa] > 12) {
                if ((s8)(s[0x46aa] -= 13) < 0)
                    s[0x46aa] = 0;
            } else {
                s[0x46aa] += 13;
                if ((s8)s[0x46aa] > max - 1)
                    s[0x46aa] = max - 1;
            }
            Sub_08035BC8(s);
        }
        break;
    case 32:
        if ((s8)--s[0x46aa] < 0)
            s[0x46aa] = max - 1;
        Sub_08035BC8(s);
        break;
    case 16:
        s[0x46aa]++;
        if ((s8)s[0x46aa] >= max) {
            s[0x46aa] = max - 1;
            Sub_08035DA4(s);
            s[0x46ac] = 28;
            Sub_0804A378(0x77);
            Sub_08035AFC(s);
            Sub_08035C5C(s);
        } else {
            Sub_08035BC8(s);
        }
        break;
    case 2: {
        u8 *p = s + 0x46a8;
        u8 z = 0;
        *p = 3;
        s[0x46a9] = z;
        Sub_0804A378(0x67);
        ret = 1;
        break;
    }
    case 8:
        s[0x46a8] = 0;
        s[0x46a9] = 0;
        Sub_0804A378(0x67);
        ret = 1;
        break;
    case 256:
        Sub_08035DA4(s);
        s[0x46ac] = 28;
        Sub_0804A378(0x77);
        Sub_08035AFC(s);
        Sub_08035C5C(s);
        break;
    default:
        break;
    }
    return ret;
}

/* LANDING NOTE: no .set stub for Sub_08035C5C in this file: that symbol is
   already defined by the landed w40b_08035c5c_MATCHED.c at the same address,
   and a .set stub would collide at link time (multiple definition). The
   extern declaration above resolves to the real definition instead; the
   emitted bl targets the same address, so the built bytes are unchanged
   (verified by the post-landing clean-build region diff). */
__asm__(
    ".globl Sub_08035BC8\n.set Sub_08035BC8, 0x08035BC8\n"
    ".globl Sub_08035DA4\n.set Sub_08035DA4, 0x08035DA4\n"
    ".globl Sub_0804A378\n.set Sub_0804A378, 0x0804A378\n"
    ".globl Sub_08035AFC\n.set Sub_08035AFC, 0x08035AFC\n"
    /* landing: Sub_08035C5C .set omitted — already landed as w40b (see note below) */
    ".globl table_0822ea88\n.set table_0822ea88, 0x0822ea88\n"
    ".globl keystate_02002f50\n.set keystate_02002f50, 0x02002f50\n"
);
