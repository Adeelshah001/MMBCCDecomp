/* Wave 36-B MATCHED: 0x08010b30, 112 B, old_agbcc -O2 -mthumb-interwork,
   C + .s patch (w36b_08010b30_patch.py).
   Extent basis: next function start 0x08010ba0 - 0x08010b30 = 112,
   incl. 16 B literal pool (0x020051b0, 0x08173eb8, 0x020053c0 in the
   main pool; 0x08173eb8 again in the flag-path pool).
   Variant count: 2 (v2 = inverted condition, direct derefs for the
   reloaded x). Key idioms: the two branches use the SAME table
   (0x08173eb8) but via TWO pool words -- one numeric constant, one
   extern symbol Table2 (harness symdef) -- so gcc emits both pool
   entries; the indirect calls go through _call_via_r1 (extern-only,
   harness symdef _call_via_r1=0x0804dcd0, already matched in build).
   Patch (asserted exactly-1, all reorder/rename, no size change):
   flag test constant-first; else-path table load first with index in
   r2; flag-path index in r2.
   Callees: Sub_08004F18 + Sub_0800D568 + Sub_0800D59C + Sub_0801112C +
   Sub_08004F80 via .set; _call_via_r1 + Table2 via harness symdefs.
   Harness: ./verify_patch.sh 0x08010b30 112 .text.w36b_08010b30
   w36b_08010b30_MATCHED.c old w36b_08010b30_patch.py
   _call_via_r1=0x0804dcd0 Table2=0x08173eb8 -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef u8 (*Func)(u8 *s);
extern u8 _call_via_r1(u8 *s);
extern Func Table2[];
extern void Sub_08004F18(void);
__asm__(".set Sub_08004F18, 0x08004f18");
extern void Sub_0800D568(u32 x);
__asm__(".set Sub_0800D568, 0x0800d568");
extern void Sub_0800D59C(u32 x);
__asm__(".set Sub_0800D59C, 0x0800d59c");
extern void Sub_0801112C(u8 x);
extern void Sub_08004F80(void);
__asm__(".set Sub_08004F80, 0x08004f80");
__attribute__((section(".text.w36b_08010b30")))
void Sub_08010B30(void)
{
    u8 *base = (u8 *)0x020051b0;
    if ((1 & base[15]) == 0) {
        Sub_08004F18();
        base[4] = ((Func *)0x08173eb8)[base[4]](base);
        if (base[20] != 0) {
            base[20]--;
        }
        Sub_0800D568(*(u32 *)0x020053c0);
        Sub_0800D59C(*(u32 *)0x020053c0);
        Sub_0801112C(base[2]);
        Sub_08004F80();
    } else {
        base[4] = Table2[base[4]](base);
    }
}
