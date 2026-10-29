/* Phase 3 Wave 5 blocked-revisit: HBlank_VCountUpdate @0x08000978 —
 * MATCHED 2026-10-20 (old_agbcc), coordinator-verified 0 diffs over
 * 160 bytes in built ROM.
 * V-blank raster bookkeeping: re-reads VCOUNT, masks/sets bit 1 of
 * IWRAM 0x03000400[0x167], bumps the dword at +0x160 on vcount==0,
 * fires the fn pointer at +0x15C when vcount matches [0x166],
 * writes REG_VCOUNT (0x04000005), then XORs [0x167] with 2.
 * Idioms: split-adds anti-folding (`u8 *p = base; p += 0x167;` as
 * separate statements prevents `ldr rX,=base+const` folding);
 * wave4_g inline-asm dest-r0 idiom for AND/OR
 * (`__asm__("movs %0,#2\n\tand %0,%1" ...)`); old_agbcc needed for
 * INSTRUCTION ORDER (movs-before-ldrb), not just regalloc.
 * The indirect fn() call compiles to `bl _call_via_r0` (thunks.s).
 * Evidence: docs/match_notes_wave5_blk.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 gIwram_03000400[];

__attribute__((section(".text.w5b_vcount")))
void HBlank_VCountUpdate(void)
{
    volatile u16 vcount;
    u8 b;
    u8 t;

    vcount = *(volatile u16 *)0x04000006;

    b = gIwram_03000400[0x167];
    __asm__("movs %0,#2\n\tand %0,%1" : "=l"(t) : "l"(b));
    if (t == 0) {
        __asm__("movs %0,#2\n\torr %0,%1" : "=l"(t) : "l"(b));
        gIwram_03000400[0x167] = t;
        if (vcount == 0)
            (*(u32 *)(gIwram_03000400 + 0x160))++;
        if (vcount == gIwram_03000400[0x166]) {
            void (*fn)(void) = *(void (**)(void))(gIwram_03000400 + 0x15c);
            if (fn)
                fn();
        }
        if (vcount < gIwram_03000400[0x166])
            *(volatile u8 *)0x04000005 = gIwram_03000400[0x166];
        else
            *(volatile u8 *)0x04000005 = 0;
        {
            u8 *p = gIwram_03000400;
            u8 v;
            p += 0x167;
            v = 2;
            v ^= *p;
            *p = v;
        }
    }
}
__asm__(
    ".globl gIwram_03000400\n.set gIwram_03000400, 0x03000400\n"
);
