/* Wave 36-E MATCHED: 0x080272e0 (148 B, old_agbcc ONLY, 0 diffs).
 * v10: case-1 idx pinned r2 + off pinned r0 (ldrb r2; lsls r0, r2, #2;
 * adds r0, r0, r1; ldr r1, [r0]; bl _call_via_r1). Under main agbcc
 * v10 is 4 diffs (case-0 mask load after value load); old_agbcc
 * emits ROM's mask-before-value order (ldr r0 pool; ldrh r2).
 * Callees via .set; coordinator strips .set for MATCHED ones
 * (0x08004e44, 0x0800520c, 0x08004dfc, 0x080275b4, 0x08004f18,
 * 0x08004f80, 0x080267b4, _call_via_r1 thunk) and keeps .set for
 * unmatched 0x08021c2c. Pools (LE): 0x020031E0 @0x2732C,
 * 0x0000EDFF @0x27330, 0x0822D968 @0x27358, 0x020031F4 @0x2735C,
 * 0x020070F0 @0x27370. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 pad0;
    u8 mode;
    u8 f2;
    u8 f3;
    u8 f4;
} S;

extern void Call4E60_4E44(int a);
extern void BitCtl_520C(int a);
extern void PalModeSet_4DFC(int a);
__asm__(".set PalModeSet_4DFC, 0x08004dfc");
extern void Unk_080275B4(void);
__asm__(".set Unk_080275B4, 0x080275b4");
extern void Unk_08021C2C(void);
__asm__(".set Unk_08021C2C, 0x08021c2c");
extern void EntryMgr_Teardown(void);
extern void EntryMgr_Setup(void);
extern void InitRec8_267B4(u32 *p, int kind);
extern void _call_via_r1(void);

typedef void (*Fn)(S *s);

__attribute__((section(".text.w36e_080272e0")))
void Sub_080272E0(S *s)
{
    u8 m = s->mode;
    switch (m) {
    case 0:
        s->mode = 1;
        s->f3 = m;
        s->f2 = m;
        Call4E60_4E44(1);
        BitCtl_520C(1);
        PalModeSet_4DFC(2);
        Unk_080275B4();
        {
            register u16 *pp __asm__("r1") = (u16 *)0x020031E0;
            register u16 mask __asm__("r0") = 0xEDFF;
            *pp &= mask;
        }
        Unk_08021C2C();
        s->f4 = 255;
        break;
    case 1: {
        EntryMgr_Teardown();
        {
            register Fn *tbl __asm__("r1") = (Fn *)0x0822D968;
            __asm__ volatile("" : "+r"(tbl));
            {
                register u8 idx __asm__("r2") = s->f2;
                register u32 off __asm__("r0") = idx << 2;
                Fn fn = *(Fn *)(off + (u32)tbl);
                fn(s);
            }
        }
        *(u16 *)0x020031F4 -= 4;
        EntryMgr_Setup();
        break;
    }
    case 2:
        InitRec8_267B4((u32 *)0x020070F0, 4);
        break;
    }
}
