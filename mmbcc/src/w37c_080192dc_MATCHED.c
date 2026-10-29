/* W37-C MATCHED via .s patch (see w37c_080192dc.patch.txt; patch verified
 * 0 diffs over true 152 B extent, old_agbcc): 0x080192dc, 152 B.
 * Move-task step, same family as
 * 0x08018510. Prologue: AddMirrored(s,f88,f92); f88+=f96; f92+=f100;
 * CopyMirrored(out,s); x=out[0]; y=out[1] (dead load kept in r2);
 * case 0: if y <= -1280 ret 0; SetBit16(f44,3);
 *   ChipInit(84, nibble, 15360, 0, f44); f88=f92=f100=mode;
 *   f10 = f10 & 253 & 254; mode++; ret 0.
 * case 1: if (u8)GetField17_U8(f44) > 5 return 1; else ret 0.
 * default: ret 0.
 * Extern callees + addresses: Vec2_AddMirrored 0x0800dd4c (MATCHED),
 * Vec2_CopyMirrored 0x0800dd08 (BLOCKED/permanent, .set),
 * SetBit16 0x080174a4 (MATCHED), ChipInit_080178A8 0x080178a8 (MATCHED),
 * GetField17_U8 0x08017474 (MATCHED).
 * Pool (LE): 0xfffffb00.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u8 pad0[10];
    u8 f10;
    u8 pad1[2];
    u8 mode;
    u8 pad2[21];
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
extern void SetBit16(u32 a, u32 b);
extern void ChipInit_080178A8(u32 a, u32 b, u32 c, u32 d, u32 e);
extern u8 GetField17_U8(u32 a);

__attribute__((section(".text.w37c_080192dc")))
u32 Sub_080192DC(S *s)
{
    u32 out[2];
    register s32 x __asm__("r1");
    register s32 y __asm__("r2");
    u8 mode;
    Vec2_AddMirrored(s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    Vec2_CopyMirrored(out, s);
    x = *(volatile s32 *)&out[0];
    y = *(volatile s32 *)&out[1];
    mode = s->mode;
    switch (mode) {
    case 0:
        if (y <= -1280)
            return 0;
        SetBit16(s->f44, 3);
        ChipInit_080178A8(84, (u32)(*(u8 *)((u8 *)s + 35)) << 28 >> 28, 15360,
                          0, s->f44);
        s->f88 = mode;
        s->f92 = mode;
        s->f100 = mode;
        {
            int t = s->f10 & 253;
            t &= 254;
            s->f10 = t;
        }
        s->mode++;
        return 0;
    case 1:
        if (GetField17_U8(s->f44) > 5)
            return 1;
        return 0;
    default:
        return 0;
    }
}
