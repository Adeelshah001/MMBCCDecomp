/* MMBCCDecomp — Wave 4 batch I (worker I) staged matches, main-agbcc subset.
 * MATCHED 2026-10-20. 17/17 functions byte-identical with main agbcc
 * (-O2 -mthumb-interwork). See docs/match_notes_wave4_i.md for evidence.
 * Old-agbcc subset lives in src/wave4_i_old.c.
 *
 * Functions (all names tentative — inferred from behavior only):
 *  0x0800303C SelBlob_Ret       (26+2pad B) Text_SelectBlob(v); return (s16)v
 *  0x0800EE8C CallEwSet8_72     (10+2pad B) EwSet8_72()
 *  0x08024634 Wrap_GetRomTableU16 (18+2pad B) return GetRomTableU16(idx)
 *  0x0802465C Wrap_TblGet11     (18+2pad B) return TblGet11(idx)
 *  0x08024FF4 GetEnt_U8_24      (18 B) return GetField24_U8(base+0x18)
 *  0x0802500C GetEnt_U8_19      (18 B) return GetU8_19(base+0x18)
 *  0x08025024 GetEnt_U16_22     (18 B) return GetField22_U16(base+0x18)
 *  0x08025934 SetSlot_IfLE29    (36 B) if(a>29) return 1; SetU8_0_FF1(s+a*4+20,b)
 *  0x080265F8 Sub80_Field22     (20 B) return 0x80 - GetField22_U16(s)
 *  0x08027730 EntMgr_Reinit1    (24 B) s[1]=1,s[3]=0,s[2]=0; Teardown; Setup
 *  0x08027748 EntMgr_Reinit2    (28 B) Teardown; s[1]=2,s[3]=0,s[2]=0; Setup
 *  0x0803510C EntMgr_Reinit45   (28 B) Teardown; s[4]=2,s[5]=0; Setup; ret 0
 *  0x08035E40 EntMgr_Reinit12   (28 B) Teardown; s[1]=2,s[3]=0,s[2]=0; Setup
 *  0x080482BC EntMgr_Reinit23   (28 B) Teardown; s[2]=2,s[3]=0; Setup; ret 0
 *  0x0804DA00 Dispatch_PostInc  (32 B) tbl[*b->ptr++](a,b)
 *  0x0804DA20 CallVia_Mem2      (20 B) (*(0x0200CD80))(a,b)
 *  0x0804CA1C CallVia_Mem1      (20 B) (*(0x0200CE0C))(s)
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code.
 * The 2-byte zero pads (sPad_*) reproduce the 0000 tail pad the ROM
 * carries after 26/10/18-byte functions (cf. wave3_a GetIndexedU8).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void Text_SelectBlob(u16 idx);
extern void EwSet8_72(void);
extern u16 GetRomTableU16(u8 idx);
extern u8 TblGet11(u8 a);
extern u8 GetField24_U8(u8 *s);
extern u8 GetU8_19(u8 *s);
extern u16 GetField22_U16(u8 *s);
extern void SetU8_0_FF1(u8 *s, u8 v);
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);
extern u8 gEwram_02007090[];
extern u32 gTbl_08105F70[];
extern u8 gEwram_0200CD80[];
extern u8 gEwram_0200CE0C[];

/* 0x0800303C: Text_SelectBlob(v); return (s16)v. Tentative.
 * Param is u16 (zero-extended on entry); return is s16 (sign-extended). */
__attribute__((section(".text.w4i_selblob_ret")))
s16 SelBlob_Ret(u16 v)
{
    Text_SelectBlob(v);
    return (s16)v;
}

/* 2-byte zero pad: ROM has 0000 at 0x08003056. */
__attribute__((section(".text.w4i_selblob_ret")))
static const u8 sPad_SelBlob_Ret[2] = { 0, 0 };

/* 0x0800EE8C: EwSet8_72(). Tentative. EwSet8_72 takes void; r0 is incidental. */
__attribute__((section(".text.w4i_callewset8_72")))
void CallEwSet8_72(u8 *s)
{
    EwSet8_72();
}

/* 2-byte zero pad: ROM has 0000 at 0x0800EE96. */
__attribute__((section(".text.w4i_callewset8_72")))
static const u8 sPad_CallEwSet8_72[2] = { 0, 0 };

/* 0x08024634: return GetRomTableU16(idx). Tentative. */
__attribute__((section(".text.w4i_wrap_getromtableu16")))
u16 Wrap_GetRomTableU16(u8 idx)
{
    return GetRomTableU16(idx);
}

/* 2-byte zero pad: ROM has 0000 at 0x08024646. */
__attribute__((section(".text.w4i_wrap_getromtableu16")))
static const u8 sPad_Wrap_GetRomTableU16[2] = { 0, 0 };

/* 0x0802465C: return TblGet11(idx). Tentative. */
__attribute__((section(".text.w4i_wrap_tblget11")))
u8 Wrap_TblGet11(u8 idx)
{
    return TblGet11(idx);
}

/* 2-byte zero pad: ROM has 0000 at 0x0802466E. */
__attribute__((section(".text.w4i_wrap_tblget11")))
static const u8 sPad_Wrap_TblGet11[2] = { 0, 0 };

/* 0x08024FF4: return GetField24_U8(*(0x02007090)+0x18). Tentative.
 * The base local defeats absolute folding (else pool becomes 0x020070A8). */
__attribute__((section(".text.w4i_getent_u8_24")))
u8 GetEnt_U8_24(void)
{
    u8 *base = gEwram_02007090;
    return GetField24_U8(base + 0x18);
}

/* 0x0802500C: return GetU8_19(base+0x18). Tentative. */
__attribute__((section(".text.w4i_getent_u8_19")))
u8 GetEnt_U8_19(void)
{
    u8 *base = gEwram_02007090;
    return GetU8_19(base + 0x18);
}

/* 0x08025024: return GetField22_U16(base+0x18). Tentative. */
__attribute__((section(".text.w4i_getent_u16_22")))
u16 GetEnt_U16_22(void)
{
    u8 *base = gEwram_02007090;
    return GetField22_U16(base + 0x18);
}

/* 0x08025934: if (a > 29) return 1; SetU8_0_FF1(s+a*4+20, b); return 0.
 * Tentative. The (a*4+0x14) parens are required for the exact
 * `lsls; adds #0x14; adds r3` order. */
__attribute__((section(".text.w4i_setslot_ifle29")))
u8 SetSlot_IfLE29(u8 *s, u8 a, u8 b)
{
    if (a > 0x1d)
        return 1;
    SetU8_0_FF1(s + (a * 4 + 0x14), b);
    return 0;
}

/* 0x080265F8: return 0x80 - GetField22_U16(s). Tentative.
 * No u16 local: the call result must feed `subs` directly, else agbcc
 * truncates early. */
__attribute__((section(".text.w4i_sub80_field22")))
u16 Sub80_Field22(u8 *s)
{
    return 0x80 - GetField22_U16(s);
}

/* 0x08027730: s[1]=1; s[3]=0; s[2]=0; Teardown(); Setup(). Tentative.
 * The `u8 zero` local forces the zero into r2 (not reusing r1). */
__attribute__((section(".text.w4i_entmgr_reinit1")))
void EntMgr_Reinit1(u8 *s)
{
    u8 zero = 0;
    s[1] = 1;
    s[3] = zero;
    s[2] = zero;
    EntryMgr_Teardown();
    EntryMgr_Setup();
}

/* 0x08027748: Teardown(); s[1]=2; s[3]=0; s[2]=0; Setup(). Tentative. */
__attribute__((section(".text.w4i_entmgr_reinit2")))
void EntMgr_Reinit2(u8 *s)
{
    EntryMgr_Teardown();
    {
        u8 zero = 0;
        s[1] = 2;
        s[3] = zero;
        s[2] = zero;
    }
    EntryMgr_Setup();
}

/* 0x0803510C: Teardown(); s[4]=2; s[5]=0; Setup(); return 0. Tentative. */
__attribute__((section(".text.w4i_entmgr_reinit45")))
u32 EntMgr_Reinit45(u8 *s)
{
    EntryMgr_Teardown();
    {
        u8 zero = 0;
        s[4] = 2;
        s[5] = zero;
    }
    EntryMgr_Setup();
    return 0;
}

/* 0x08035E40: Teardown(); s[1]=2; s[3]=0; s[2]=0; Setup(). Tentative. */
__attribute__((section(".text.w4i_entmgr_reinit12")))
void EntMgr_Reinit12(u8 *s)
{
    EntryMgr_Teardown();
    {
        u8 zero = 0;
        s[1] = 2;
        s[3] = zero;
        s[2] = zero;
    }
    EntryMgr_Setup();
}

/* 0x080482BC: Teardown(); s[2]=2; s[3]=0; Setup(); return 0. Tentative. */
__attribute__((section(".text.w4i_entmgr_reinit23")))
u32 EntMgr_Reinit23(u8 *s)
{
    EntryMgr_Teardown();
    {
        u8 zero = 0;
        s[2] = 2;
        s[3] = zero;
    }
    EntryMgr_Setup();
    return 0;
}

/* 0x0804DA00: tbl[*b->ptr++](a, b). Tentative.
 * b is a struct with a u8* at +0x40; the explicit `off` local puts the
 * function pointer in r2 so agbcc emits bl _call_via_r2. */
typedef struct { u8 _00[0x40]; u8 *ptr; } Ctx4DA00;
__attribute__((section(".text.w4i_dispatch_postinc")))
void Dispatch_PostInc(u8 *a, Ctx4DA00 *b)
{
    u8 idx = *b->ptr++;
    u32 *tbl = gTbl_08105F70;
    u32 off = idx << 2;
    u32 fn = *(u32 *)((u32)tbl + off);
    ((void (*)(u8 *, Ctx4DA00 *))fn)(a, b);
}

/* 0x0804DA20: (*(u32*)0x0200CD80)(a, b). Tentative. */
__attribute__((section(".text.w4i_callvia_mem2")))
void CallVia_Mem2(u8 *a, u32 b)
{
    u32 fn = *(u32 *)gEwram_0200CD80;
    ((void (*)(u8 *, u32))fn)(a, b);
}

/* 0x0804CA1C: (*(u32*)0x0200CE0C)(s). Tentative. */
__attribute__((section(".text.w4i_callvia_mem1")))
void CallVia_Mem1(u8 *s)
{
    u32 fn = *(u32 *)gEwram_0200CE0C;
    ((void (*)(u8 *))fn)(s);
}

__asm__(
    ".globl gEwram_02007090\n.set gEwram_02007090, 0x02007090\n"
    ".globl gTbl_08105F70\n.set gTbl_08105F70, 0x08105F70\n"
    ".globl gEwram_0200CD80\n.set gEwram_0200CD80, 0x0200CD80\n"
    ".globl gEwram_0200CE0C\n.set gEwram_0200CE0C, 0x0200CE0C\n"
);
