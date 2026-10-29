/* Wave 36-B MATCHED: 0x08028900, 112 B, old_agbcc -O2 -mthumb-interwork,
   C + .s patch (w36b_08028900_patch.py).
   Extent basis: next function start 0x08028970 - 0x08028900 = 112,
   incl. 12 B literal pool (0x0822de04, 0x0200b810 in the main pool;
   0x0200b810 again in the end-block pool) + 2 B pad.
   CORRECTION: table1 is 0x0822de04 (bytes 04 de 22 08), NOT 0x082204de
   (an earlier misread of the objdump pool display swapped the first
   two bytes; the byte-level diff caught it).
   Variant count: 2 (v2 = corrected table address). Key idioms: the
   two branches use the same struct (0x0200b810) via two pool words
   (numeric constant + extern symbol Struct2, harness symdef); the
   value tests are two separate ifs (if v==11 set 5, fall through;
   if v==9 set 3 + jump to end; else if v==10 set 4); the end block
   (ret1 == 4) sets r5 = struct[4] >> 4 and clears struct[0]/[1].
   Patch (asserted exactly-1): first-table load order (table first,
   struct second, index in r2) + pool word swap; flag test
   constant-first; end-block byte into r2.
   Callees: Sub_0802FDA0 via .set; _call_via_r1 + Struct2 via harness
   symdefs (_call_via_r1=0x0804dcd0, Struct2=0x0200b810).
   Harness: ./verify_patch.sh 0x08028900 112 .text.w36b_08028900
   w36b_08028900_MATCHED.c old w36b_08028900_patch.py
   _call_via_r1=0x0804dcd0 Struct2=0x0200b810 -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef u8 (*Func)(u8 *s);
extern u8 _call_via_r1(u8 *s);
extern u8 Struct2[];
extern u8 Sub_0802FDA0(u8 *s);
__asm__(".set Sub_0802FDA0, 0x0802fda0");
__attribute__((section(".text.w36b_08028900")))
int Sub_08028900(void)
{
    int r5 = 0;
    Func *t = (Func *)0x0822de04;
    u8 *s = (u8 *)0x0200b810;
    u8 ret1 = t[s[0]](s);
    if ((s[6] & 8) == 0) {
        if (ret1 != 0) {
            u8 v = Sub_0802FDA0(s);
            if (v == 11) {
                r5 = 5;
            }
            if (v == 9) {
                r5 = 3;
            } else if (v == 10) {
                r5 = 4;
            }
        }
    }
    if (ret1 == 4) {
        r5 = Struct2[4] >> 4;
        Struct2[0] = 0;
        Struct2[1] = 0;
    }
    return r5;
}
