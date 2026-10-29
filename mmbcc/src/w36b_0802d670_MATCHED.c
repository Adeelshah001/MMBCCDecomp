/* Wave 36-B MATCHED: 0x0802d670, 112 B, old_agbcc -O2 -mthumb-interwork,
   C + .s patch (w36b_0802d670_patch.py).
   Extent basis: next function start 0x0802d6e0 - 0x0802d670 = 112,
   incl. trailing 00 00 pad (explicit .byte 0,0; gas would emit c0 46).
   No literal pool (all addresses are struct-relative).
   Variant count: 3 (v3 = no p variable + pad + patch). Key idioms:
   the element pointer must NOT be kept in a variable -- every access
   reloads it from the slot ([r4]) after each call, because the calls
   clobber the temporaries; the slot address stays in r4 (struct +
   counter*4). The counter==2 block reloads from [r5,#8] (arr[2] as a
   constant index), not from r4. Counter is u8 (2..5, cmp #5 + bls).
   Patch (asserted exactly-1): slot add operand order (offset + struct).
   Callees: Sub_0802458C + Sub_08024570 + Sub_080245FC (all (byte)) +
   Sub_0803FB9C (u16) via .set.
   Harness: ./verify_patch.sh 0x0802d670 112 .text.w36b_0802d670
   w36b_0802d670_MATCHED.c old w36b_0802d670_patch.py -> diffs: 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Obj { u8 f0; u8 f1; u8 pad2[2]; u16 f4; u16 f6; u16 f8; u16 f10; };
struct S { struct Obj *arr[6]; u32 f24; };
extern u16 Sub_0802458C(u8 x);
__asm__(".set Sub_0802458C, 0x0802458c");
extern u16 Sub_08024570(u8 x);
__asm__(".set Sub_08024570, 0x08024570");
extern u8 Sub_080245FC(u8 x);
__asm__(".set Sub_080245FC, 0x080245fc");
extern u8 Sub_0803FB9C(u16 x);
__asm__(".set Sub_0803FB9C, 0x0803fb9c");
__attribute__((section(".text.w36b_0802d670")))
void Sub_0802D670(struct S *s)
{
    u8 counter;
    s->arr[0] = 0;
    s->arr[1] = 0;
    s->f24 = 0;
    for (counter = 2; counter <= 5; counter++) {
        if (s->arr[counter] != 0) {
            s->arr[counter]->f4 = Sub_0802458C(s->arr[counter]->f0);
            s->arr[counter]->f6 = Sub_08024570(s->arr[counter]->f0);
            s->arr[counter]->f1 = Sub_080245FC(s->arr[counter]->f0);
            if (counter == 2) {
                s->arr[2]->f10 &= 128;
            } else {
                if (Sub_0803FB9C(s->arr[counter]->f8) == 0) {
                    s->arr[counter]->f10 = 0;
                }
            }
        }
    }
}
/* Trailing 00 00 pad to the next-function boundary (0x0802d6e0), as in ROM. */
__asm__(".section .text.w36b_0802d670\n\t.byte 0, 0\n\t.previous");
