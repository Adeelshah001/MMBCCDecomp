/* Wave 15-C: ChipInit_0801C3FC @ 0x0801c3fc (old_agbcc). Coordinator-landed, 0-diff verified. */
/* ChipInit_0801C3FC @0x0801C3FC — wave15_C_redo2 candidate (old_agbcc).
 * Body: Wrapper_D770(p,0x82a,0); ChipSlot_IncUse(p,0);
 * Anti-folding mask idiom: p[10]=(p[10]&253)&254 done as two separate ands:
 *   { u8 b=p[10]; b&=253; b&=254; p[10]=b; } */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Wrapper_D770_0800D770(u8 *p, u16 x, u8 y);
extern void ChipSlot_IncUse_0800D9EC(u8 *p, u8 x);

__attribute__((section(".text.w15c2_0801C3FC")))
void ChipInit_0801C3FC(u8 *p)
{
    u8 b;
    Wrapper_D770_0800D770(p, 0x82a, 0);
    ChipSlot_IncUse_0800D9EC(p, 0);
    b = p[10];
    b &= 253;
    b &= 254;
    p[10] = b;
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl Wrapper_D770_0800D770\n"
    ".set Wrapper_D770_0800D770, 0x0800D770\n"
    ".thumb\n"
    ".thumb_func\n"
    ".globl ChipSlot_IncUse_0800D9EC\n"
    ".set ChipSlot_IncUse_0800D9EC, 0x0800D9EC\n"
);
