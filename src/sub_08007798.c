


extern u8 D_08172074[];
extern u32 D_02003670;
extern const u32 D_08170E7C[];
extern u8 D_0200483C[];
extern void sub_08006374(u8 *ctx, s8 a, s8 b, int c, int d, int e, u8 f, u32 g);

extern void sub_08006124(s8 a, s8 b, int c, int d, int e, u8 f);

void sub_08007798(u8 a, u8 b, u8 c, u8 d)
{
    if (d != 0) {
        u8 *tblA = D_08172074;
        u32 idx;
        u32 r4;
        
        idx = ((D_02003670 >> 3) & 3);
        tblA += 4;
        {
            u8 *addr = (u8 *)(idx + (u32)tblA);
            const u32 *tblB = D_08170E7C;
            u8 byte;
            
            byte = *addr;
            r4 = tblB[byte];
        }
        sub_08006374(D_0200483C, (s8)(a - 2), (s8)b, 2, 2, 53, c, r4);
    } else {
        sub_08006124((s8)(a - 2), (s8)b, 2, 2, 50, c);
    }
}
