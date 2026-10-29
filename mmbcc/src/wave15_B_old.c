/* Wave 15 worker B: bulk leaves-up rows 0-90 (old_agbcc, 3 functions)
 * Coordinator-landed after independent clean-room re-verification (0 diffs).
 * Evidence: docs/match_notes_wave15_B.md, docs/wave15_B_results.tsv.
 */
typedef unsigned short u16;
typedef unsigned char u8;
struct Ew02007090 { u8 _00[20]; u8 *f20; };
extern struct Ew02007090 ew02007090;
extern u16 F_08025790(u8 *p);
typedef unsigned int u32;
extern int TblValidate_300C(u16 x);
extern void F_0804C84C(u32 w, u32 n);
extern u8 CheckPair_258D8(u8 *p, u16 idx);

__attribute__((section(".text.w15b_08024ee0")))
u16 F_08024EE0(void)
{
    u8 *base = ew02007090.f20;
    u8 idx = *(base + (0xD8 << 1));
    return (u16)F_08025790(base + idx * 144);
}

__attribute__((section(".text.w15b_08002fd4")))
void F_08002FD4(u16 x)
{
    u16 v = x;
    if (TblValidate_300C(v)) {
        u8 *t1 = (u8 *)0x08106D7C;
        u8 *t2 = (u8 *)0x08106DD0;
        __asm__ volatile("" : "+r" (t1), "+r" (t2));
        {
            u16 h = *(u16 *)(t2 + v * 8 + 4);
            u32 w = *(u32 *)(t1 + h * 12);
            F_0804C84C(w, 6);
        }
    }
}

__attribute__((section(".text.w15b_08024848")))
u8 F_08024848(u16 idx)
{
    u8 *base = ew02007090.f20;
    u8 i2 = *(base + (0xD8 << 1));
    return CheckPair_258D8(base + i2 * 144, idx);
}

/* Absolute callee aliases (not defined in the build; must FOLLOW code per GAS .set ordering rule). */
__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl TblValidate_300C\n"
    ".set TblValidate_300C, 0x0800300c\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl F_0804C84C\n"
    ".set F_0804C84C, 0x0804c84c\n"
);
