/* Wave 36-B MATCHED: 0x08011eb0, 116 B, old_agbcc -O2 -mthumb-interwork,
   C + .s patch (w36b_08011eb0_patch.py).
   Extent basis: next function start 0x08011f24 - 0x08011eb0 = 116,
   incl. 4 B literal pool (0x08223cc0) + 2 B pad.
   CORRECTION: table is 0x08223cc0 (bytes c0 3c 22 08), not 0x08173cc0.
   Variant count: 2 (v2 = corrected table + buf initializer + patch).
   Key idioms: table[idx] address computed, then f12 = 1 stored, then
   dereferenced for f20 (addr variable interleaving); f10 |= via
   two-step constant-first ORs (2 then 1); mask = (f35 & 15) ? 256 : 0
   via gcc's negs/orrs/asrs/ands boolean-to-mask sequence (ternary
   in C reproduces it); buf[2] = {0,0} initializer (not assignments)
   so gcc uses fresh movs for the buf stores instead of keeping 0 in
   r5 (which would force an r5 push).
   Patch (asserted exactly-1): table sequence base-first, index in r2.
   Callees: Sub_0800D6E0(s,mask,0) + Sub_0800D9EC(s,0) +
   Sub_0801D070(0,s,buf,12) + Sub_08011F24(s) via .set.
   Harness: ./verify_patch.sh 0x08011eb0 116 .text.w36b_08011eb0
   w36b_08011eb0_MATCHED.c old w36b_08011eb0_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Ent { u32 pad; u32 f4; };
struct S { u8 pad0[9]; u8 f9; u8 f10; u8 pad11; u32 f12; u8 pad16[4]; u32 f20; u8 pad24[11]; u8 f35; u8 pad36[72]; u32 f108; };
extern void Sub_0800D6E0(struct S *s, int m, int z);
__asm__(".set Sub_0800D6E0, 0x0800d6e0");
extern void Sub_0800D9EC(struct S *s, int z);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0801D070(int a, struct S *s, u32 *buf, int n);
__asm__(".set Sub_0801D070, 0x0801d070");
extern void Sub_08011F24(struct S *s);
__attribute__((section(".text.w36b_08011eb0")))
void Sub_08011EB0(struct S *s)
{
    struct Ent **addr = ((struct Ent **)0x08223cc0) + s->f9;
    s->f12 = 1;
    s->f20 = (*addr)->f4;
    s->f108 = 0;
    s->f10 = 2 | s->f10;
    s->f10 = 1 | s->f10;
    {
        int m = (s->f35 & 15) ? 256 : 0;
        Sub_0800D6E0(s, m, 0);
    }
    Sub_0800D9EC(s, 0);
    {
        u32 buf[2] = {0, 0};
        Sub_0801D070(0, s, buf, 12);
    }
    Sub_08011F24(s);
}
