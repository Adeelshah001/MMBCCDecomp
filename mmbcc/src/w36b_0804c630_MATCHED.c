/* Wave 36 Worker B2 — 0x0804c630, 120 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: next start 0x0804c6a8 (func_list v2). Pool: 9 words in first-use order.
 * Variant count: 4 (v4 + patch). Callees Sub_0804DB28, Sub_0804CA30, Sub_0804C8EC,
 * Sub_0804CBCC, Sub_0804CD70 via .set. Val/Arg2/Cnt via harness symdefs
 * (Val=0x0804ba05, Arg2=0x03000000, Cnt=7) as array symbols so gcc loads the
 * values directly (not via pointer dereference).
 * Key idioms: first-arg mask is ~1 (clear bit 0), not ~2; table loads after the
 * count check (for pool order); f0 kept in r4 across the loop's call.
 * Patch: swap table/count registers (r5<->r6; push/pop lists are bitmasks so
 * the swap is safe there); count setup truncates in r0, checks r0, then moves
 * to r6 after the table load (net +2 B, eliminating the pool-alignment pad). */
/* v4: mask ~1, table after count check */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 Val[];
extern u8 Arg2[];
extern u8 Cnt[];
extern void Sub_0804DB28(u32 a, u32 b, u32 c);
extern void Sub_0804CA30(u32 a);
extern void Sub_0804C8EC(u32 a);
extern void Sub_0804CBCC(u32 a);
extern void Sub_0804CD70(u32 a, u32 b, u32 c);
__asm__(".set Sub_0804DB28, 0x0804db28");
__asm__(".set Sub_0804CA30, 0x0804ca30");
__asm__(".set Sub_0804C8EC, 0x0804c8ec");
__asm__(".set Sub_0804CBCC, 0x0804cbcc");
__asm__(".set Sub_0804CD70, 0x0804cd70");
typedef struct { u32 f0; u32 f4; u8 f8; u8 f9; u16 f10; } Ent;
__attribute__((section(".text.w36b_0804c630")))
void Sub_0804C630(void)
{
    int count;
    Ent *t;
    Sub_0804DB28((u32)Val & ~1, (u32)Arg2, 0x04000100);
    Sub_0804CA30(0x0200bdd0);
    Sub_0804C8EC(0x0200ce10);
    Sub_0804CBCC(0x0095fa00);
    count = (u16)Cnt;
    if (count == 0) return;
    t = (Ent *)0x08106d7c;
    for (; count != 0; count--) {
        u32 f0 = t->f0;
        Sub_0804CD70(f0, t->f4, t->f8);
        *(u8 *)(f0 + 11) = (u8)t->f10;
        *(u32 *)(f0 + 24) = 0x0200d090;
        t++;
    }
}
