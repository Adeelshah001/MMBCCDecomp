/* Wave 16-D: TblLookup_0804C7B4 @ 0x0804c7b4 (52 B: 44 code + 8 pool).
 * Coordinator-landed, 0-diff verified vs ROM (bl immediate is
 * R_ARM_THM_CALL reloc). Compiler: main agbcc.
 * Behavior: base=(u8*)(0x8106dd0+idx*8); v=*(u16*)(base+4);
 * p=(u32*)(0x8106d7c+v*12); q=(u32*)*p; if (*q==*(u32*)base)
 * ClearSignBit_0804C5F4(q).
 * Idioms: (u32)idx<<16 then >>=13 split by volatile tied-opaque pool loads
 * (forces lsls/ldr r2/ldr r1/lsrs interleaving); pinned tbl1->r2, tbl2->r1;
 * divided-syntax "add %0,%0,%1" forces adds r1,r1,r2 operand order
 * (v*12+tbl1); u16 v via ldrh. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
void ClearSignBit_0804C5F4(u32 *p);
void TblLookup_0804C7B4(u16 idx) __attribute__((section(".text.w16d_0804c7b4")));
void TblLookup_0804C7B4(u16 idx)
{
    u32 t = (u32)idx << 16;
    register u32 *tbl1 __asm__("r2");
    register u8 *tbl2 __asm__("r1");
    u8 *base;
    u16 v;
    u32 *p;
    u32 *q;
    __asm__ volatile("" : "=r" (tbl1) : "0" ((u32 *)0x8106d7c));
    __asm__ volatile("" : "=r" (tbl2) : "0" ((u8 *)0x8106dd0));
    t >>= 13;
    base = (u8 *)(t + (u32)tbl2);
    v = *(u16 *)(base + 4);
    {
        int v12 = v * 12;
        __asm__ volatile("add %0, %0, %1" : "+r" (v12) : "r" (tbl1));
        p = (u32 *)v12;
    }
    q = (u32 *)*p;
    if (*q == *(u32 *)base)
        ClearSignBit_0804C5F4(q);
}
