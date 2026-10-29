/* MMBCCDecomp — Wave 4 batch I (worker I) staged matches, old-agbcc subset.
 * MATCHED 2026-10-20. 45/45 functions byte-identical ONLY with old_agbcc
 * (tools/agbcc/bin/old_agbcc, -O2 -mthumb-interwork); main agbcc
 * mis-allocates the table-base/index registers (ldrb r1 vs r3).
 * See docs/match_notes_wave4_i.md for evidence.
 * Main-agbcc subset lives in src/wave4_i.c.
 *
 * The dominant shape is the indirect dispatcher:
 *   ((void (*)(u8 *))tbl[s[OFF]])(s)   via bl _call_via_r1
 * with u8/s8-returning variants. All names tentative.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void CpuFastSet(void *src, void *dst, unsigned mode);
extern u16 GetU16_Off14(u8 *p);
extern u16 GetU16_10(u8 *s);
extern u8 GetByte1_25A08(u8 *p);
extern u8 _call_via_r3(u8 *a, u16 b, u8 c, u32 fn);
extern void EntryMgr_Teardown(void);

extern u8 gEwram_02002F80[];
extern u32 gTbl_0816E2C0[];
extern u32 gTbl_0816E304[];
extern u8 gRom_0805633C[];
extern u16 gEwram_020031E4[];
extern u8 gVram_06007000[];
extern u8 gEwram_02003668[];
extern u32 gTbl_081705A4[];
extern u32 gTbl_08173064[];
extern u8 gEwram_02000EC0[];
extern u32 gTbl_081734F4[];
extern u32 gTbl_08223D08[];
extern u32 gTbl_08223E94[];
extern u32 gTbl_08226A24[];
extern u32 gTbl_08226DD8[];
extern u32 gTbl_08226EDC[];
extern u32 gTbl_08226F2C[];
extern u32 gTbl_08226FEC[];
extern u32 gTbl_0822701C[];
extern u32 gTbl_0822709C[];
extern u32 gTbl_08227140[];
extern u32 gTbl_08227168[];
extern u32 gTbl_082271C8[];
extern u32 gTbl_082271F4[];
extern u32 gTbl_080E9C04[];
extern u8 gEwram_02007090[];
extern u32 gTbl_0822DC84[];
extern u32 gTbl_0822EA6C[];
extern u32 gTbl_0822EB58[];
extern u32 gTbl_082300F8[];
extern u32 gTbl_08230D94[];
extern u32 gTbl_08231098[];
extern u32 gTbl_08232330[];
extern u32 gTbl_082329B0[];
extern u32 gTbl_08232D2C[];
extern u32 gTbl_08232E48[];
extern u32 gTbl_08233A44[];
extern u8 gEwram_0200B7A8[];
extern u32 gTbl_08233AFC[];
extern u32 gTbl_08233C54[];
extern u32 gTbl_08234314[];
extern u32 gTbl_08234B74[];
extern u32 gTbl_08234D4C[];
extern u32 gTbl_08234D60[];
extern u8 gEwram_0200B7E0[];

/* 0x08001D98: tbl[((u8*)0x02002F80)[2]]((u8*)0x02002F80). Tentative.
 * Two pools; the 2-byte 0000 pad between code and pool is real ROM. */
__attribute__((section(".text.w4i_dispatch_0816e2c0_2")))
void Dispatch_0816E2C0_2(void)
{
    u8 *s = gEwram_02002F80;
    u32 *tbl = gTbl_0816E2C0;
    u32 idx = s[2];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0800330C: tbl[((s[0x18]<<1)|s[0x19])&3](s,b). Tentative. */
__attribute__((section(".text.w4i_dispatch_0816e304")))
void Dispatch_0816E304(u8 *s, u32 b)
{
    u32 *tbl = gTbl_0816E304;
    u32 idx = ((s[0x18] << 1) | s[0x19]) & 3;
    ((void (*)(u8 *, u32))tbl[idx])(s, b);
}

/* 0x080045F8: CpuFastSet(0x0805633C, 0x06007000+((*(u16*)0x020031E4&0xC)<<12),
 * 0x200). Tentative: ROM->VRAM copy, src bank selected by a flag nibble. */
__attribute__((section(".text.w4i_cpufastset_vram")))
void CpuFastSet_Vram(void)
{
    u8 *src = gRom_0805633C;
    u16 *flag = gEwram_020031E4;
    u8 *dst = gVram_06007000 + (u32)(((*flag) & 0xC) << 12);
    CpuFastSet(src, dst, 0x200);
}

/* 0x08004BC0: r=tbl[s[0]](s); s[4]=(u8)r; return (s8)s[4]. Tentative. */
__attribute__((section(".text.w4i_dispatch_081705a4_0")))
s8 Dispatch_081705A4_0(void)
{
    u8 *s = gEwram_02003668;
    u32 *tbl = gTbl_081705A4;
    u32 idx = s[0];
    u8 r = ((u8 (*)(u8 *))tbl[idx])(s);
    s[4] = r;
    return (s8)s[4];
}

/* 0x0800CD38: s[8]=(u8)tbl[s[0]](s). Tentative. */
__attribute__((section(".text.w4i_dispatch_081734f4_0")))
void Dispatch_081734F4_0(void)
{
    u8 *s = gEwram_02000EC0;
    u32 *tbl = gTbl_081734F4;
    u32 idx = s[0];
    s[8] = ((u8 (*)(u8 *))tbl[idx])(s);
}

/* 0x08023278: copy 3-word table to stack, then tbl[s[0xD]](s). Tentative.
 * The struct assignment is required for the ldm/stm block copy. */
typedef struct { u32 e[3]; } Tbl3;
__attribute__((section(".text.w4i_dispatch_stktbl")))
void Dispatch_StkTbl(u8 *s)
{
    Tbl3 t = *(Tbl3 *)gTbl_080E9C04;
    ((void (*)(u8 *))t.e[s[0xd]])(s);
}

/* 0x08024F08: return GetU16_Off14(b+i*144); b=*(0x02007090+0x14);
 * i=b[0x1B0]. Tentative. */
__attribute__((section(".text.w4i_getent_u16_14")))
u16 GetEnt_U16_14(void)
{
    u8 *base = gEwram_02007090;
    u8 *b = *(u8 **)(base + 0x14);
    u8 i = b[0x1b0];
    return GetU16_Off14(b + i * 144);
}

/* 0x08024F48: return GetU16_10(b+i*144). Tentative. */
__attribute__((section(".text.w4i_getent_u16_10")))
u16 GetEnt_U16_10(void)
{
    u8 *base = gEwram_02007090;
    u8 *b = *(u8 **)(base + 0x14);
    u8 i = b[0x1b0];
    return GetU16_10(b + i * 144);
}

/* 0x080251B8: return GetByte1_25A08(s+i*144); i=s[0x1B0]. Tentative. */
__attribute__((section(".text.w4i_getent_idxbyte1")))
u8 GetEnt_IdxByte1(u8 *s)
{
    u8 i = s[0x1b0];
    return GetByte1_25A08(s + i * 144);
}

/* 2-byte zero pad: ROM has 0000 at 0x080251D6. */
__attribute__((section(".text.w4i_getent_idxbyte1")))
static const u8 sPad_GetEnt_IdxByte1[2] = { 0, 0 };

/* 0x0802588C: return GetRomTableU16(s[1]) + *(u16*)(s+14). Tentative.
 * The call must be the first operand for the `adds r0,r4,r0` order. */
__attribute__((section(".text.w4i_addtbl_s14")))
u16 AddTbl_S14(u8 *s)
{
    return GetRomTableU16(s[1]) + *(u16 *)(s + 14);
}

/* 0x080258A4: return GetRomTableU16(idx) + *(u16*)(s+14). Tentative. */
__attribute__((section(".text.w4i_addtbl_s14_idx")))
u16 AddTbl_S14_Idx(u8 *s, u8 idx)
{
    return GetRomTableU16(idx) + *(u16 *)(s + 14);
}

/* 2-byte zero pad: ROM has 0000 at 0x080258BE. */
__attribute__((section(".text.w4i_addtbl_s14_idx")))
static const u8 sPad_AddTbl_S14_Idx[2] = { 0, 0 };

/* 0x08027CFC: ((u8*)0x0200B7E0)[3] &= -7; Teardown(). Tentative.
 * `int mask = -7` (not ~6) forces the movs+rsbs sequence. */
__attribute__((section(".text.w4i_entmgr_clearbit3")))
void EntMgr_ClearBit3(void)
{
    u8 *p = gEwram_0200B7E0;
    int mask = -7;
    p[3] &= mask;
    EntryMgr_Teardown();
}

/* 0x080365F8/1C/40: s[0x469F]=N; tbl[s[1]](s). Tentative. */
__attribute__((section(".text.w4i_set469f_dispatch0")))
void Set469F_Dispatch0(u8 *s)
{
    s[0x469f] = 0;
    {
        u32 *tbl = gTbl_082300F8;
        u32 idx = s[1];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}

__attribute__((section(".text.w4i_set469f_dispatch1")))
void Set469F_Dispatch1(u8 *s)
{
    s[0x469f] = 1;
    {
        u32 *tbl = gTbl_082300F8;
        u32 idx = s[1];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}

__attribute__((section(".text.w4i_set469f_dispatch2")))
void Set469F_Dispatch2(u8 *s)
{
    s[0x469f] = 2;
    {
        u32 *tbl = gTbl_082300F8;
        u32 idx = s[1];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}

/* 0x08047600: *(u16*)s=*(u16*)(p+4); return (s8)tbl[p[0]](p);
 * p=(u8*)0x0200B7A8. Tentative. */
__attribute__((section(".text.w4i_copyhdr_dispatch")))
s8 CopyHdr_Dispatch(u8 *s)
{
    u8 *dst = s;
    u8 *p = gEwram_0200B7A8;
    *(u16 *)dst = *(u16 *)(p + 4);
    {
        u32 *tbl = gTbl_08233AFC;
        u32 idx = p[0];
        return (s8)((u32 (*)(u8 *))tbl[idx])(p);
    }
}

/* 0x080400D0: return (u8)_call_via_r3(s,b,c,tbl[s[4]]). Tentative. */
__attribute__((section(".text.w4i_dispatch4_r3")))
u8 Dispatch4_R3(u8 *s, u16 b, u8 c)
{
    u32 *tbl = gTbl_082329B0;
    u32 idx = s[4];
    u32 fn = tbl[idx];
    return _call_via_r3(s, b, c, fn);
}

/* --- The 28 plain A1 dispatchers (table base + s[OFF] index) --- */

/* 0x0800AC70: tbl[s[1]](s); return 5. */
__attribute__((section(".text.w4i_dispatch_08173064_1")))
u32 Dispatch_08173064_1(u8 *s)
{
    u32 *tbl = gTbl_08173064;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
    return 5;
}

/* 0x080120F0 */
__attribute__((section(".text.w4i_dispatch_08223d08_10")))
void Dispatch_08223D08_10(u8 *s)
{
    u32 *tbl = gTbl_08223D08;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08015A48 */
__attribute__((section(".text.w4i_dispatch_08223e94_10")))
void Dispatch_08223E94_10(u8 *s)
{
    u32 *tbl = gTbl_08223E94;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0801D3A8 */
__attribute__((section(".text.w4i_dispatch_08226a24_10")))
void Dispatch_08226A24_10(u8 *s)
{
    u32 *tbl = gTbl_08226A24;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0801F224 */
__attribute__((section(".text.w4i_dispatch_08226dd8_10")))
void Dispatch_08226DD8_10(u8 *s)
{
    u32 *tbl = gTbl_08226DD8;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08020588 */
__attribute__((section(".text.w4i_dispatch_08226edc_10")))
void Dispatch_08226EDC_10(u8 *s)
{
    u32 *tbl = gTbl_08226EDC;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0802103C */
__attribute__((section(".text.w4i_dispatch_08226f2c_10")))
void Dispatch_08226F2C_10(u8 *s)
{
    u32 *tbl = gTbl_08226F2C;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08021564 */
__attribute__((section(".text.w4i_dispatch_08226fec_10")))
void Dispatch_08226FEC_10(u8 *s)
{
    u32 *tbl = gTbl_08226FEC;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0802181C */
__attribute__((section(".text.w4i_dispatch_0822701c_10")))
void Dispatch_0822701C_10(u8 *s)
{
    u32 *tbl = gTbl_0822701C;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08021E34 */
__attribute__((section(".text.w4i_dispatch_0822709c_10")))
void Dispatch_0822709C_10(u8 *s)
{
    u32 *tbl = gTbl_0822709C;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08022680 */
__attribute__((section(".text.w4i_dispatch_08227140_10")))
void Dispatch_08227140_10(u8 *s)
{
    u32 *tbl = gTbl_08227140;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0802295C */
__attribute__((section(".text.w4i_dispatch_08227168_10")))
void Dispatch_08227168_10(u8 *s)
{
    u32 *tbl = gTbl_08227168;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08023070 */
__attribute__((section(".text.w4i_dispatch_082271c8_10")))
void Dispatch_082271C8_10(u8 *s)
{
    u32 *tbl = gTbl_082271C8;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0802372C */
__attribute__((section(".text.w4i_dispatch_082271f4_10")))
void Dispatch_082271F4_10(u8 *s)
{
    u32 *tbl = gTbl_082271F4;
    u32 idx = s[0x10];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08027718 */
__attribute__((section(".text.w4i_dispatch_0822dc84_1")))
void Dispatch_0822DC84_1(u8 *s)
{
    u32 *tbl = gTbl_0822DC84;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08035DF4 */
__attribute__((section(".text.w4i_dispatch_0822eb58_1")))
void Dispatch_0822EB58_1(u8 *s)
{
    u32 *tbl = gTbl_0822EB58;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08037958 */
__attribute__((section(".text.w4i_dispatch_08230d94_1")))
void Dispatch_08230D94_1(u8 *s)
{
    u32 *tbl = gTbl_08230D94;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x08038E70 */
__attribute__((section(".text.w4i_dispatch_08231098_1")))
void Dispatch_08231098_1(u8 *s)
{
    u32 *tbl = gTbl_08231098;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x0803AE2C */
__attribute__((section(".text.w4i_dispatch_08232330_1")))
void Dispatch_08232330_1(u8 *s)
{
    u32 *tbl = gTbl_08232330;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* 0x080468EC */
__attribute__((section(".text.w4i_dispatch_08233a44_2")))
void Dispatch_08233A44_2(u8 *s)
{
    u32 *tbl = gTbl_08233A44;
    u32 idx = s[2];
    ((void (*)(u8 *))tbl[idx])(s);
}

/* u8-returning variants */

/* 0x080350B4 */
__attribute__((section(".text.w4i_dispatch_0822ea6c_4")))
u8 Dispatch_0822EA6C_4(u8 *s)
{
    u32 *tbl = gTbl_0822EA6C;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}

/* 0x08042AC8 */
__attribute__((section(".text.w4i_dispatch_08232d2c_4")))
u8 Dispatch_08232D2C_4(u8 *s)
{
    u32 *tbl = gTbl_08232D2C;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}

/* 0x08045EA0 */
__attribute__((section(".text.w4i_dispatch_08232e48_4")))
u8 Dispatch_08232E48_4(u8 *s)
{
    u32 *tbl = gTbl_08232E48;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}

/* 0x08047CA4 */
__attribute__((section(".text.w4i_dispatch_08233c54_4")))
u8 Dispatch_08233C54_4(u8 *s)
{
    u32 *tbl = gTbl_08233C54;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}

/* 0x080499EC */
__attribute__((section(".text.w4i_dispatch_08234b74_4")))
u8 Dispatch_08234B74_4(u8 *s)
{
    u32 *tbl = gTbl_08234B74;
    u32 idx = s[4];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}

/* 0x08048260 */
__attribute__((section(".text.w4i_dispatch_08234314_2")))
u8 Dispatch_08234314_2(u8 *s)
{
    u32 *tbl = gTbl_08234314;
    u32 idx = s[2];
    return (u8)((u32 (*)(u8 *))tbl[idx])(s);
}

/* s8-returning variants */

/* 0x0804AF90 */
__attribute__((section(".text.w4i_dispatch_08234d4c_0")))
s8 Dispatch_08234D4C_0(u8 *s)
{
    u32 *tbl = gTbl_08234D4C;
    u32 idx = s[0];
    return (s8)((u32 (*)(u8 *))tbl[idx])(s);
}

/* 0x0804B334 */
__attribute__((section(".text.w4i_dispatch_08234d60_0")))
s8 Dispatch_08234D60_0(u8 *s)
{
    u32 *tbl = gTbl_08234D60;
    u32 idx = s[0];
    return (s8)((u32 (*)(u8 *))tbl[idx])(s);
}

__asm__(
    ".globl gEwram_02002F80\n.set gEwram_02002F80, 0x02002F80\n"
    ".globl gTbl_0816E2C0\n.set gTbl_0816E2C0, 0x0816E2C0\n"
    ".globl gTbl_0816E304\n.set gTbl_0816E304, 0x0816E304\n"
    ".globl gRom_0805633C\n.set gRom_0805633C, 0x0805633C\n"
    ".globl gEwram_020031E4\n.set gEwram_020031E4, 0x020031E4\n"
    ".globl gVram_06007000\n.set gVram_06007000, 0x06007000\n"
    ".globl gEwram_02003668\n.set gEwram_02003668, 0x02003668\n"
    ".globl gTbl_081705A4\n.set gTbl_081705A4, 0x081705A4\n"
    ".globl gTbl_08173064\n.set gTbl_08173064, 0x08173064\n"
    ".globl gEwram_02000EC0\n.set gEwram_02000EC0, 0x02000EC0\n"
    ".globl gTbl_081734F4\n.set gTbl_081734F4, 0x081734F4\n"
    ".globl gTbl_08223D08\n.set gTbl_08223D08, 0x08223D08\n"
    ".globl gTbl_08223E94\n.set gTbl_08223E94, 0x08223E94\n"
    ".globl gTbl_08226A24\n.set gTbl_08226A24, 0x08226A24\n"
    ".globl gTbl_08226DD8\n.set gTbl_08226DD8, 0x08226DD8\n"
    ".globl gTbl_08226EDC\n.set gTbl_08226EDC, 0x08226EDC\n"
    ".globl gTbl_08226F2C\n.set gTbl_08226F2C, 0x08226F2C\n"
    ".globl gTbl_08226FEC\n.set gTbl_08226FEC, 0x08226FEC\n"
    ".globl gTbl_0822701C\n.set gTbl_0822701C, 0x0822701C\n"
    ".globl gTbl_0822709C\n.set gTbl_0822709C, 0x0822709C\n"
    ".globl gTbl_08227140\n.set gTbl_08227140, 0x08227140\n"
    ".globl gTbl_08227168\n.set gTbl_08227168, 0x08227168\n"
    ".globl gTbl_082271C8\n.set gTbl_082271C8, 0x082271C8\n"
    ".globl gTbl_082271F4\n.set gTbl_082271F4, 0x082271F4\n"
    ".globl gTbl_080E9C04\n.set gTbl_080E9C04, 0x080E9C04\n"
    ".globl gTbl_0822DC84\n.set gTbl_0822DC84, 0x0822DC84\n"
    ".globl gTbl_0822EA6C\n.set gTbl_0822EA6C, 0x0822EA6C\n"
    ".globl gTbl_0822EB58\n.set gTbl_0822EB58, 0x0822EB58\n"
    ".globl gTbl_082300F8\n.set gTbl_082300F8, 0x082300F8\n"
    ".globl gTbl_08230D94\n.set gTbl_08230D94, 0x08230D94\n"
    ".globl gTbl_08231098\n.set gTbl_08231098, 0x08231098\n"
    ".globl gTbl_08232330\n.set gTbl_08232330, 0x08232330\n"
    ".globl gTbl_082329B0\n.set gTbl_082329B0, 0x082329B0\n"
    ".globl gTbl_08232D2C\n.set gTbl_08232D2C, 0x08232D2C\n"
    ".globl gTbl_08232E48\n.set gTbl_08232E48, 0x08232E48\n"
    ".globl gTbl_08233A44\n.set gTbl_08233A44, 0x08233A44\n"
    ".globl gEwram_0200B7A8\n.set gEwram_0200B7A8, 0x0200B7A8\n"
    ".globl gTbl_08233AFC\n.set gTbl_08233AFC, 0x08233AFC\n"
    ".globl gTbl_08233C54\n.set gTbl_08233C54, 0x08233C54\n"
    ".globl gTbl_08234314\n.set gTbl_08234314, 0x08234314\n"
    ".globl gTbl_08234B74\n.set gTbl_08234B74, 0x08234B74\n"
    ".globl gTbl_08234D4C\n.set gTbl_08234D4C, 0x08234D4C\n"
    ".globl gTbl_08234D60\n.set gTbl_08234D60, 0x08234D60\n"
    ".globl gEwram_0200B7E0\n.set gEwram_0200B7E0, 0x0200B7E0\n"
);
