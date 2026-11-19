/* Sub_08046960 @ 0x08046960 (140 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08046960_MATCHED.c (registry: mmbcc/src/w36d_08046960_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004F18(void);

extern u8 sub_0800B148(u32 a, u32 b, u32 c);

extern u8 sub_0800B320(u32 a, u32 b, u32 c, u32 d);

extern void sub_0800B448(u32 a, u32 b, u32 c);

extern u8 sub_0800B308(void);

extern u8 sub_0800B2B4(void);

extern void sub_08004F80(void);

void sub_08046960(u8 *s)
{
    register u8 *s5 = s;
    register u8 *flag = (u8 *)0x0200b7a8;
    sub_08004F18();
    (void)s5;
    switch (*flag) {
    case 0:
        if (sub_0800B148(1, 133, 1) != 0)
            goto inc;
        break;
    case 1:
        if (sub_0800B320(0x08232e8c, 0, 0, 0) == 0)
            break;
        sub_0800B448(0, 0x8d5, 0);
        goto inc;
    case 2:
        if (sub_0800B308() != 0)
            goto inc;
        break;
    case 3:
        if (sub_0800B2B4() == 0)
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
    sub_08004F80();
}
