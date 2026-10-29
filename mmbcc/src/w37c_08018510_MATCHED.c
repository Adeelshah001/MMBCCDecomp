/* W37-C MATCHED via .s patch (see w37c_08018510.patch.txt; patch verified
 * 0 diffs over true 152 B extent, old_agbcc): 0x08018510, 152 B.
 * Move-task step.
 * Prologue: AddMirrored(s,f88,f92); f88+=f96; f92+=f100;
 * CopyMirrored(out,s); x=out[0] (used); y=out[1] (dead load kept in r2);
 * case 0: if x<=12800 ret 0; ChipInit(93, nibble, 15360, 0xFFFFE700, f44);
 *   f88=mode; f96=mode; ChipSlot_IncUse(s,1); f18=6; mode++; ret 0.
 * case 1: if --f18 != 0 ret 0; MaxAssign_17(f44,7); return 1.
 * default: ret 0.
 * Extern callees + addresses: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED/permanent, .set),
 * ChipInit_080178A8 0x080178a8 (MATCHED), ChipSlot_IncUse 0x0800d9ec
 * (MATCHED), MaxAssign_17 0x08017478 (MATCHED).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u8 pad0[13];
    u8 mode;
    u8 pad1[4];
    u8 f18;
    u8 pad2[16];
    u8 f35;
    u8 pad3[8];
    u32 f44;
    u8 pad4[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void Vec2_AddMirrored(S *s, u32 x, u32 y);
extern void Vec2_CopyMirrored(u32 *out, S *s);
__asm__(".set Vec2_CopyMirrored, 0x0800dd08");
extern void ChipInit_080178A8(u32 a, u32 b, u32 c, u32 d, u32 e);
extern void ChipSlot_IncUse(S *s, u32 idx);
extern void MaxAssign_17(u32 a, u32 b);

__attribute__((section(".text.w37c_08018510")))
u32 Sub_08018510(S *s)
{
    u32 out[2];
    s32 x;
    register u32 y __asm__("r2");
    u8 mode;
    Vec2_AddMirrored(s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    Vec2_CopyMirrored(out, s);
    x = out[0];
    y = *(volatile u32 *)&out[1];
    mode = s->mode;
    if (mode == 0)
        goto case0;
    if (mode == 1)
        goto case1;
    goto ret0;
case0:
    if (x <= 12800)
        goto ret0;
    ChipInit_080178A8(93, (u32)(*(u8 *)((u8 *)s + 35)) << 28 >> 28, 15360,
                      0xffffe700, s->f44);
    s->f88 = mode;
    s->f96 = mode;
    ChipSlot_IncUse(s, 1);
    s->f18 = 6;
    s->mode++;
    goto ret0;
case1:
    if (--s->f18 != 0)
        goto ret0;
    MaxAssign_17(s->f44, 7);
    return 1;
ret0:
    return 0;
}

/* Trailing zero pad: ROM ends this 152 B section with 00 00 after bx;
 * without it GAS pads the section end with mov r8,r8 (0x46c0). */
__asm__(".hword 0x0000");
