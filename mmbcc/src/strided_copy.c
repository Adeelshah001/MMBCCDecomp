/* StridedCopy @0x08000C68 — MATCHED 2026-10-20 (Wave 5 blocked-revisit,
 * coordinator-verified 0 diffs over 52 bytes in built ROM).
 * Halfword strided copy engine. Descriptor:
 *   +0: unk0, +2: unk2, +4: dst, +8: count (halfwords),
 *   +10: dst_step byte, +11: src_step byte, +12: src.
 * Idioms: register pinning (d=r4, dst=r3, sstep=r5) via
 * register __asm__; ROM-matching load order; shifts hoisted before
 * the loop; inline asm with earlyclobber scratch to force
 * `lsls r0,r5,#24` (pinning alone breaks the scratch pattern).
 * Evidence: docs/match_notes_wave5_blk.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct StridedDesc {
    u16 unk0;
    u16 unk2;
    u32 dst;
    u16 count;
    u8 dst_step;
    u8 src_step;
    u32 src;
};

__attribute__((section(".text.strided_copy")))
void StridedCopy(struct StridedDesc *d_in)
{
    register struct StridedDesc *d __asm__("r4") = d_in;
    register u32 dst __asm__("r3");
    register int sstep __asm__("r5");
    u32 src;
    u8 dstep;
    u16 count;
    int ds;
    int scratch;

    src = d->src;
    dst = d->dst;
    sstep = d->src_step;
    dstep = d->dst_step;
    count = d->count;

    if (count == 0)
        goto done;
    ds = (dstep << 24) >> 23;
    __asm__("lsl %0,%2,#24\n\tasr %1,%0,#23" : "=&l"(scratch), "=l"(sstep) : "l"(sstep));
    do {
        *(u16 *)dst = *(u16 *)src;
        dst += ds;
        src += sstep;
        count--;
    } while (count != 0);
done:
    d->src = src;
}
