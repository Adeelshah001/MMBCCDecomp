/* W39-C: 0x08042b60, 164 B, old_agbcc -O2 -mthumb-interwork, pure C.
 * W38-C (168/112) fixed, all in C:
 *  - b pinned r3 (was callee-saved r4, pushing s/ret up a register);
 *    bt pinned r1 (was r2); s=r4, ret=r5, push {r4,r5,lr} now match ROM.
 *  - mask constants via in-place `-=` on the strh variable (subs, not
 *    mov+neg/copy+sub): v24 -= 55, v24 -= 2.
 *  - t as block-scoped int pinned r2 (was u8 in r1 with a copy).
 *  - case-1 condition inverted (t2 != 5 path first) so gcc falls through
 *    to the else path and jumps forward to the t==5 block, as ROM does;
 *    pools then land between the else path and the t==5 block.
 *  - default returns via a `retpt` label after EntryMgr_Setup (ROM's
 *    default branch skips Setup; `return ret` folded to `return 0`).
 *  - else-path tmp/z split so the zero materializes into r1 between the
 *    ldrb and the first strb, as in ROM.
 *  - mask via a u32 variable so the literal pool carries the full
 *    0xFFFFFC3F (a u16 &= lets gcc pool the truncated 0x0000FC3F).
 * Callee .set blocks at END (GAS idiom).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Call4E60_4E44(void);
extern void PalModeSet_4DFC(u8 v);
extern void SyncObjFlagBits_BEE0(int a, int b);
extern void ShiftPair_Copy_800C(u8 *p, int v);
extern void EntryMgr_Teardown(void);
extern u8 Sub_08042D80(u8 *s);
extern void EntryMgr_Setup(void);

__attribute__((section(".text.w39c_08042b60")))
u8 Sub_08042B60(u8 *s)
{
    u8 ret = 0;
    switch (s[5]) {
    case 0: {
        register u8 *base __asm__("r0");
        register u8 *b __asm__("r3");
        register int bt __asm__("r1");
        u32 mask;
        int v24;
        u8 *gp;
        Call4E60_4E44();
        gp = (u8 *)0x02004f80;
        PalModeSet_4DFC(gp[2]);
        SyncObjFlagBits_BEE0(64, 128);
        base = (u8 *)0x02004ce0;
        b = base + 44;
        bt = *b;
        bt |= 1;
        *(u16 *)(base + 40) = 16;
        v24 = 24;
        *(u16 *)(base + 42) = v24;
        v24 -= 55;
        bt &= v24;
        v24 -= 2;
        bt &= v24;
        *b = bt;
        mask = ~0x3c0;
        *(u16 *)(base + 44) &= mask;
        ShiftPair_Copy_800C(base, 0);
        s[5]++;
        /* fall through */
    }
    case 1: {
        register int t2 __asm__("r2");
        int tmp;
        int z;
        EntryMgr_Teardown();
        t2 = Sub_08042D80(s);
        if (t2 == 0)
            goto done;
        if (t2 != 5) {
            tmp = s[4];
            z = 0;
            s[7] = tmp;
            s[4] = t2;
            s[5] = z;
            s[6] = z;
            goto done;
        }
        s[0x46b7] = 1;
        ret = 5;
        goto done;
    }
    default:
        goto retpt;
    }
done:
    EntryMgr_Setup();
retpt:
    return ret;
}

