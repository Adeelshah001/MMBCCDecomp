/* H-blank raster engine (Wave 1) — MATCHED 2026-10-20.
 * Byte-identical C for sub_08000AD4 / 08000B54 / 08000BAC / 08000C04.
 * Flags: agbcc -O2 -mthumb-interwork (see Makefile).
 *
 * Notes on the match:
 * - The ISRs snapshot VCOUNT into a volatile u16 stack slot and re-read it
 *   (hence mov rX,sp / ldrh pairs instead of a register-held value).
 * - REG_DISPSTAT / REG_IE updates are followed by a dummy (void) re-read.
 *   This is a write-posting read in the original code; without it the
 *   trailing ldrh is missing and the bytes differ.
 * - HBlank_RasterSetup arms one of three ISRs from the table at 0x0816E22C
 *   ({NULL, Raster0, Raster1, Raster01}) selected by sel: 1 = desc0 only,
 *   2 = desc1 only, 3 = both. sel is a short, hence the lsl/asr sequences.
 * - The ISR vector is written to [0x03000404], derived in-code as
 *   ((unsigned int *)desc - 0x60)[1] (desc = 0x03000580).
 * - The empty asm barrier on `t` defeats CSE constant-forwarding of the
 *   table address: without it GCC's commutative-operand swap emits the
 *   sel*4 shift before the table-base load, breaking the byte-match.
 *   It generates no instructions. */

#define REG_VCOUNT   (*(volatile unsigned short *)0x04000006)
#define REG_DISPSTAT (*(volatile unsigned short *)0x04000004)
#define REG_IE       (*(volatile unsigned short *)0x04000200)

#define HBLANK_DESC0 ((void *)0x03000580)
#define HBLANK_ISR_TABLE ((unsigned int *)0x0816E22C)

void StridedCopy(void *desc);

__attribute__((section(".text.hblank_setup")))
void HBlank_RasterSetup(void)
{
    short sel = 0;
    unsigned int *desc = (unsigned int *)HBLANK_DESC0;
    unsigned int *desc2;

    if (desc[2] != 0) {
        desc[3] = desc[0];
        StridedCopy(desc);
        sel = 1;
    }
    desc2 = desc;
    desc2 += 7;
    if (desc2[2] != 0) {
        desc2[3] = desc[7];
        StridedCopy(desc2);
        sel += 2;
    }
    if (sel != 0) {
        unsigned int *vec;
        unsigned int *t;

        REG_DISPSTAT |= 0x10;
        (void)REG_DISPSTAT;
        vec = (unsigned int *)desc - 0x60;
        t = HBLANK_ISR_TABLE;
        asm volatile("" : "+r" (t)); /* keep table load before sel*4 (see note) */
        vec[1] = t[sel];
        REG_IE |= 0x2;
        (void)REG_IE;
    }
}

__attribute__((section(".text.hblank0")))
void HBlank_Raster0(void)
{
    volatile unsigned short vcount = REG_VCOUNT;

    if (vcount > 159)
        return;
    StridedCopy((void *)0x03000580);
    if (vcount != 159)
        return;
    REG_DISPSTAT &= ~0x10;
    (void)REG_DISPSTAT;
    REG_IE &= ~0x2;
    (void)REG_IE;
}

__attribute__((section(".text.hblank1")))
void HBlank_Raster1(void)
{
    volatile unsigned short vcount = REG_VCOUNT;

    if (vcount > 159)
        return;
    StridedCopy((void *)0x0300059C);
    if (vcount != 159)
        return;
    REG_DISPSTAT &= ~0x10;
    (void)REG_DISPSTAT;
    REG_IE &= ~0x2;
    (void)REG_IE;
}

__attribute__((section(".text.hblank01")))
void HBlank_Raster01(void)
{
    volatile unsigned short vcount = REG_VCOUNT;

    if (vcount > 159)
        return;
    {
        unsigned int *desc = (unsigned int *)HBLANK_DESC0;

        StridedCopy(desc);
        desc += 7;
        StridedCopy(desc);
    }
    if (vcount != 159)
        return;
    REG_DISPSTAT &= ~0x10;
    (void)REG_DISPSTAT;
    REG_IE &= ~0x2;
    (void)REG_IE;
}
