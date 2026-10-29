/* Wave 23-A: sub_08002E80 (84 B) — old_agbcc. DispCnt shadow save/restore via 0x02003230 table.
 * Wave-22 p6 shape was 4 diffs under main agbcc (r1/r4 swap for disp store-addr
 * vs p[0] temp); old_agbcc emits ROM order exactly (mov r1,sp / ldrh r4,[r2,#0]).
 * Fits 0x08002e70(+16B)..0x08002ed4 exactly. */
/* Wave 22-C: 0x08002E80 (84 B). p6: explicit dp for order + clobber for reg. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__attribute__((section(".text.w23a_08002E80")))
void sub_08002E80(void)
{
    volatile u16 disp;
    u32 *p;
    volatile u16 *dsp;
    u16 *dp = &disp;

    dsp = (volatile u16 *)0x04000000;
    __asm__ volatile("" : : "r"(dsp) : "r4");
    *dp = *dsp;
    *(volatile u16 *)&disp = *(volatile u16 *)&disp & 0x1FFF;
    *(volatile u16 *)&disp = *(volatile u16 *)&disp | *(u16 *)(p = (u32 *)0x02003230);
    *dsp = *(volatile u16 *)&disp;

    *(volatile u32 *)0x04000040 = p[1];
    *(volatile u32 *)0x04000044 = p[2];
    *(volatile u32 *)0x04000048 = p[3];
}
