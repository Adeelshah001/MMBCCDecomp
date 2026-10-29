/* Phase 3 Wave 5 POOL-H2 (old_agbcc, 4 matched C, coordinator-verified).
 * Task mode handlers needing old_agbcc allocation. Evidence:
 * docs/match_notes_wave5_h2.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed char s8;
typedef unsigned int u32;

s8 sub_0804dcd0(u8 *p, u32 v);
extern u32 gRom_0822EA80[];
extern u32 gRom_0823010C[];
extern u32 gRom_08230DA8[];
extern u32 gRom_08231764[];

__attribute__((section(".text.w5h_35128")))
u32 Task_35128(u8 *p)
{
    u32 ret = 0;
    u32 *tbl = gRom_0822EA80;
    u8 *pIdx = p + 0x46a8;
    u32 tbl_val = tbl[*pIdx];
    if (sub_0804dcd0(p, tbl_val) != 0) {
        p[4] = 3;
        p[5] = ret;
    }
    if (*pIdx == 3) {
        p[0x46b7] = *pIdx;
        ret = 1;
    }
    return ret;
}

__asm__(
    ".globl gRom_0822EA80\n.set gRom_0822EA80, 0x0822EA80\n"
);

__attribute__((section(".text.w5h_366e8")))
void Task_366E8(u8 *p)
{
    u32 *tbl = gRom_0823010C;
    s8 idx = (s8)p[0x4699];
    u32 tbl_val = tbl[idx];
    if (sub_0804dcd0(p, tbl_val) != 0) {
        u32 z = 0;
        p[1] = 3;
        p[2] = z;
        p[3] = z;
    }
}

__asm__(
    ".globl gRom_0823010C\n.set gRom_0823010C, 0x0823010C\n"
);

__attribute__((section(".text.w5h_37a30")))
void Task_37A30(u8 *p)
{
    u32 *tbl = gRom_08230DA8;
    s8 idx = (s8)p[0x469c];
    u32 tbl_val = tbl[idx];
    u8 r = (u8)sub_0804dcd0(p, tbl_val);
    if (r == 1) goto L1;
    if (r == 2) goto L2;
    goto end;
L1: {
        u32 z = 0;
        p[1] = 3;
        p[3] = z;
        p[2] = z;
    }
    goto done;
L2: {
        u32 z = 0;
        p[1] = 4;
        p[3] = z;
        p[2] = z;
    }
done:
end: ;
}

__attribute__((section(".text.w5h_37a30")))
static const u8 sPad_37A30[2] = { 0, 0 };

__asm__(
    ".globl gRom_08230DA8\n.set gRom_08230DA8, 0x08230DA8\n"
);

__attribute__((section(".text.w5h_38f3c")))
void Task_38F3C(u8 *p)
{
    u32 *tbl = gRom_08231764;
    s8 idx = (s8)p[0x469c];
    u32 tbl_val = tbl[idx];
    u8 r = (u8)sub_0804dcd0(p, tbl_val);
    if (r == 1) goto L1;
    if (r == 2) goto L2;
    goto end;
L1: {
        u32 z = 0;
        p[1] = 3;
        p[2] = z;
        p[3] = z;
    }
    goto done;
L2: {
        u32 z = 0;
        p[1] = 4;
        p[2] = z;
        p[3] = z;
    }
done:
end: ;
}

__attribute__((section(".text.w5h_38f3c")))
static const u8 sPad_38F3C[2] = { 0, 0 };

__asm__(
    ".globl gRom_08231764\n.set gRom_08231764, 0x08231764\n"
);


__asm__(
    ".globl sub_0804dcd0\n.set sub_0804dcd0, 0x0804DCD0\n"
);
