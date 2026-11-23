typedef signed short s16;

extern u8 gUnknown_02004830[];
extern u32 gUnknown_08171EE0[];
extern void sub_08006AD8(void *ctx, u32 t, s16 x, s16 y, u8 d, u8 e);

void sub_08007378(u8 mode, u16 x, u16 y, u8 z)
{
    register u32 t = 0;
    u8 *base = gUnknown_02004830;
    
    if (base[0x265])
        return;
    
    if (mode != 0) {
        u32 *tbl = gUnknown_08171EE0;
        int m = mode - 1;
        t = tbl[m];
    }
    
    sub_08006AD8(base, t, (s16)x, (s16)y, 2, z);
}
