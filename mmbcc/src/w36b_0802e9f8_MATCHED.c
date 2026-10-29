/* Wave 36-B MATCHED: 0x0802e9f8, 108 B, old_agbcc -O2 -mthumb-interwork, pure C.
   Extent basis: next function start 0x0802ea64 (func_list v2) - 0x0802e9f8 = 108,
   no literal pool.
   Variant count: 2 (v2 = i=0 initialized before z, so gcc emits the
   mov r8, r6 zero-copy; v1 had z first and materialized a second zero).
   Key idioms: struct-fill loop in store order f0, f2, f6, f4, f8, f10, f1;
   zero variable kept in r8 across the loop's calls; i==0 selects the
   1-arg first-call form, else the 2-arg form.
   Callees: Sub_080241D0 + Sub_080242A8 + Sub_08024554 + Sub_08024570 +
   Sub_0802458C + Sub_080245E0 + Sub_080245FC via .set (all unmatched).
   Harness: ./verify.sh 0x0802e9f8 108 .text.w36b_0802e9f8
   w36b_0802e9f8_MATCHED.c old -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct E { u8 f0; u8 f1; u16 f2; u16 f4; u16 f6; u16 f8; u16 f10; };
extern u8 Sub_080241D0(u16 a);
extern u8 Sub_080242A8(u16 a, u8 i);
__asm__(".set Sub_080242A8, 0x080242a8");
extern u16 Sub_08024554(u8 v);
__asm__(".set Sub_08024554, 0x08024554");
extern u16 Sub_08024570(u8 v);
__asm__(".set Sub_08024570, 0x08024570");
extern u16 Sub_0802458C(u8 v);
__asm__(".set Sub_0802458C, 0x0802458c");
extern u16 Sub_080245E0(u8 v);
__asm__(".set Sub_080245E0, 0x080245e0");
extern u8 Sub_080245FC(u8 v);
__asm__(".set Sub_080245FC, 0x080245fc");
__attribute__((section(".text.w36b_0802e9f8")))
void Sub_0802E9F8(u16 a, struct E *p)
{
    u8 i = 0;
    u16 z = 0;
    for (; i <= 11; i++) {
        u8 v = (i == 0) ? Sub_080241D0(a) : Sub_080242A8(a, i);
        p->f0 = v;
        p->f2 = Sub_08024554(v);
        p->f6 = Sub_08024570(v);
        p->f4 = Sub_0802458C(v);
        p->f8 = Sub_080245E0(v);
        p->f10 = z;
        p->f1 = Sub_080245FC(v);
        p++;
    }
}
