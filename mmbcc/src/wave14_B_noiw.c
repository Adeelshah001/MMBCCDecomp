/* Wave 14 worker B: no-interwork agbcc matches.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave14_B.md, docs/wave14_B_results.tsv.
 *
 * 0x0804E008 (82 B) is emitted via BYTE() in ldscript.ld: GAS pads the
 * C section to 84 with c046, but ROM has 82 bytes (next function follows
 * immediately). The verified bytes are the no-interwork agbcc output.
 */
typedef unsigned char u8;
typedef unsigned int u32;

#if 0 /* Documented source for BYTE() block in ldscript.ld (GAS c046 tail
          pad does not match ROM). Not compiled. */
/* Aligned memset: fills with byte replication when dst is word-aligned
 * and n > 3; 16-byte unrolled word loop, 4-byte tail, byte tail.
 * Decisive idioms: no-interwork for pop{r4,r5,pc} epilogue (main/old emit
 * pop{r1};bx r1); explicit u32 t=n-- temp defeats the -1 loop transform;
 * *pw++ x4 unrolled stores -> stmia. */
__attribute__((section(".text.w14b_0804e008")))
void *MemsetAligned_4E008(void *dst, u32 val, u32 n)
{
    u8 *d = (u8 *)dst;
    if (n > 3 && ((u32)dst & 3) == 0) {
        u32 *pw = (u32 *)dst;
        u32 w;
        val &= 0xff;
        w = val << 8;
        w |= val;
        w |= w << 16;
        while (n > 15) {
            *pw++ = w;
            *pw++ = w;
            *pw++ = w;
            *pw++ = w;
            n -= 16;
        }
        while (n > 3) {
            *pw++ = w;
            n -= 4;
        }
        d = (u8 *)pw;
    }
    while (1) {
        u32 t = n--;
        if (t == 0)
            break;
        *d++ = val;
    }
    return dst;
}
#endif
