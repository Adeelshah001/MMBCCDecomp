/* Wave 36 Worker B2 — 0x08010750, 124 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: next start 0x080107cc (func_list v2). Split pool: middle pool
 * (0x02003670 ptr, 525) + end pool (table 0x08173e2c, s 0x02005168).
 * Variant count: 3 (v3 + patch). Callees Sub_080062B4 (7 args, 3 on stack),
 * Sub_080107CC, Sub_08010844 via .set.
 * Key idioms: 0x02003670 is a POINTER (load the value from it, then shift);
 * boolean (b != 0) as a 0/1 value via negs+orrs+lsrs; stack args interleaved
 * (stack0 early, stack1 in branch arms, stack2 after table load); s loaded
 * after the big call (not before).
 * Patch: 3 in r3 for the stack1=3 store; stack stores interleaved; middle pool
 * split out (pool1 ptr + 525) with table/s in the end pool; all reorder,
 * net +4 B (the branch-arm stores) matching ROM's 124 B. */
/* v2: pool1 is a pointer */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Sub_080062B4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);
extern void Sub_080107CC(u8 *s);
extern void Sub_08010844(u8 *s, u32 x);
__asm__(".set Sub_080062B4, 0x080062b4");
__asm__(".set Sub_080107CC, 0x080107cc");
__asm__(".set Sub_08010844, 0x08010844");
__attribute__((section(".text.w36b_08010750")))
void Sub_08010750(u8 *arg0)
{
    u8 b = arg0[68];
    int boolean = (b != 0);
    u32 *p = (u32 *)0x02003670;
    int bit = (*p >> (3 - boolean)) & 1;
    u32 stack0 = 525;
    int stack1 = boolean ? 3 : 5;
    u32 *table = (u32 *)0x08173e2c;
    u32 stack2 = table[bit];
    u8 *s;
    Sub_080062B4(13, 19, 4, 1, stack0, stack1, stack2);
    s = (u8 *)0x02005168;
    Sub_080107CC(s);
    Sub_08010844(s, 0);
    Sub_080107CC(s + 20);
    Sub_08010844(s + 20, 1);
}
