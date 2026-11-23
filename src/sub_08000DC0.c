typedef signed short s16;
typedef signed int s32;

extern u8 gUnknown_030005C0[];
extern u32 D_02000800;
extern void sub_08000300(void *, void *, u32);

void sub_08000DC0(int arg0) {
    s32 r3 = arg0;
    u8 *r2 = gUnknown_030005C0;
    u32 r1 = 0x1E50;
    u32 *r0 = (u32 *)(r2 + r1);
    u32 idx = *r0;
    u32 r0_val = idx * 2;
    u8 *r1_ptr;
    r0_val += idx;
    r0_val <<= 3;
    r1 = 0x1E08;
    r2 += r1;
    r1_ptr = (u8 *)(r0_val + (u32)r2);
    if (r3 != 0) {
        *(u16 *)(r1_ptr + 2) = r3;
        r1_ptr[0] = 4;
        sub_08000300(r1_ptr + 4, r1_ptr + 8, D_02000800);
    }
}
