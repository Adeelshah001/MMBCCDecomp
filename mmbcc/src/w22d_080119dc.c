/* Wave 22-D @0x080119DC (48 B). MATCHED with main agbcc.
 * F_080119DC: flag check + halfword accumulate + Inc4_Clear5_7; returns -1.
 * if (p->f0[13]) ChkFlag_080247E8(p->f0[13]);
 * if (*(u16 *)(p->f0 + 14)) p->f8 += *(u16 *)(p->f0 + 14);
 * Inc4_Clear5_7(p); return -1.
 *
 * Idioms: second if-block body emitted via one inline-asm block because
 * the adds (0x1808 = adds r0, r1, r0) cannot be written as GAS pre-UAL
 * text (Rd==Rm rejected) -- emitted via .short 0x1808. r1v pinned to r1
 * (word-size pin, safe) doubles as ldrh base+dest, giving ROM's
 * ldrh r1,[r1,#14]. p left unpinned: gcc keeps it in r4 itself
 * (pinning p to r4 perturbed the first block's ldrb allocation).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern u8 ChkFlag_080247E8(u8 a);
extern void Inc4_Clear5_7(u8 *s);

typedef struct {
    u8 *f0;
    u32 f4;
    u32 f8;
} Obj;

__attribute__((section(".text.w22d_080119DC")))
s32 F_080119DC(Obj *p)
{
    if (p->f0[13] != 0) {
        ChkFlag_080247E8(p->f0[13]);
    }
    {
        register u8 *r1v __asm__("r1") = p->f0;
        if (*(u16 *)(r1v + 14) != 0) {
            register u32 sum __asm__("r0");
            __asm__ volatile (
                "ldr %0, [%2, #8]\n\t"
                "ldrh %1, [%1, #14]\n\t"
                ".short 0x1808\n\t"   /* adds r0, r1, r0 */
                "str %0, [%2, #8]"
                : "=&r" (sum), "+r" (r1v)
                : "r" (p)
                : "memory"
            );
        }
    }
    Inc4_Clear5_7((u8 *)p);
    return -1;
}
