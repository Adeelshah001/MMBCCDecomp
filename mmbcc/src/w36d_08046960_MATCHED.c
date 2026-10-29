/* Wave 36-D MATCHED (C + .s patch w36d_08046960_patch.py, old_agbcc, 0 diffs over 140 B true extent 0x08046960-0x08046a00; pinned s=r5/flag=r4, shared check beq+fallthrough inc, inc moved before case3, case3 fallthrough), 140 B, extent next-func 0x08046a00. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_08004F18(void);
__asm__(".set Sub_08004F18, 0x08004f18");
extern u8 Sub_0800B148(u32 a, u32 b, u32 c);
__asm__(".set Sub_0800B148, 0x0800b148");
extern u8 Sub_0800B320(u32 a, u32 b, u32 c, u32 d);
extern void Sub_0800B448(u32 a, u32 b, u32 c);
__asm__(".set Sub_0800B448, 0x0800b448");
extern u8 Sub_0800B308(void);
__asm__(".set Sub_0800B308, 0x0800b308");
extern u8 Sub_0800B2B4(void);
__asm__(".set Sub_0800B2B4, 0x0800b2b4");
extern void Sub_08004F80(void);
__asm__(".set Sub_08004F80, 0x08004f80");

__attribute__((section(".text.w36d_08046960")))
void Sub_08046960(u8 *s)
{
    register u8 *s5 __asm__("r5") = s;
    register u8 *flag __asm__("r4") = (u8 *)0x0200b7a8;
    Sub_08004F18();
    (void)s5;
    switch (*flag) {
    case 0:
        if (Sub_0800B148(1, 133, 1) != 0)
            goto inc;
        break;
    case 1:
        if (Sub_0800B320(0x08232e8c, 0, 0, 0) == 0)
            break;
        Sub_0800B448(0, 0x8d5, 0);
        goto inc;
    case 2:
        if (Sub_0800B308() != 0)
            goto inc;
        break;
    case 3:
        if (Sub_0800B2B4() == 0)
            break;
        {
            u32 s2new = s5[2] + 1;
            u32 zero = 0;
            s5[2] = s2new;
            *flag = zero;
        }
        break;
    default:
        break;
    }
    goto end;
inc:
    (*flag)++;
end:
    Sub_08004F80();
}
