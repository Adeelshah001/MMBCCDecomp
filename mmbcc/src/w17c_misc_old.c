/* Wave 17 worker C: old_agbcc variants. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;

extern u8 GetMaskedByte_08025324(u8 *p, u8 idx);
extern int Append_0802526C(void *s, u8 v);
extern void F_0802533c(u8 *p, u8 idx);
extern void Fill_253BC(u8 *s);

/* 0x080254e0 (66 B): GetMaskedByte/Append. */
__attribute__((section(".text.w17c_080254e0")))
void F_080254E0(u8 *s, u8 idx)
{
    if (*(u8 *)(*(u8 **)(s + 4) + idx) != (u8)GetMaskedByte_08025324(*(u8 **)s, idx)) {
        (*(u8 *)(*(u8 **)(s + 4) + idx))++;
        if (*(u8 *)(*(u8 **)(s + 4) + idx) == 1)
            Append_0802526C(s + 12, idx);
    }
}

/* 0x0802541c (70 B): F_0802533c loop + Fill_253BC. */
__attribute__((section(".text.w17c_0802541c")))
void F_0802541C(u8 *s, u8 *p, u16 n)
{
    u16 i;
    for (i = 0; i < n; i++) {
        u8 *s4;
        F_0802533c(*(u8 **)s, p[i]);
        s4 = *(u8 **)(s + 4);
        s4[p[i]]++;
    }
    Fill_253BC(s);
}
