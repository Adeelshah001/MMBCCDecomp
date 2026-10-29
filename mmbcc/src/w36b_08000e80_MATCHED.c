/* Wave 36 Worker B2 — 0x08000e80, TRUE extent 56 B, old_agbcc -O2 -mthumb-interwork, C + .s patch.
 * Extent: code + 4-word pool to 0x08000eb8. The task-list 120 B is the func_list gap
 * to 0x08000ef8; the bytes 0x08000eb8-0x08000ef7 are SEPARATE functions (at
 * 0x08000eb8, 0x08000ed4, ...) NOT part of this claim — flag to coordinator as
 * func_list gaps; do NOT extend this file to 120 B.
 * Variant count: 3 (v3 + patch). Callee Sub_08000328 via .set; Base via harness
 * symdef Base=0x030005c0 (extern array symbol, so gcc loads the address directly).
 * Key idioms: base + large offsets kept unfolded (extern base prevents folding);
 * idx*24 as (idx<<1+idx)<<3; elemBase computed before adding idx*24.
 * Patch: first part to ROM order (base in r3, idx*24 before offset2 load). */
/* v3: extern array base, elemBase variable */
typedef unsigned char u8;
typedef unsigned int u32;
extern u8 Base[];
extern void Sub_08000328(u32 x);
__asm__(".set Sub_08000328, 0x08000328");
__attribute__((section(".text.w36b_08000e80")))
void Sub_08000E80(u32 arg0)
{
    u8 *base = Base;
    u32 idx = *(u32 *)(base + 0x1e50);
    u8 *elemBase = base + 0x1e08;
    u8 *elem = elemBase + idx * 24;
    elem[1] = 1;
    *(u32 *)(elem + 4) = arg0;
    Sub_08000328(*(u32 *)0x02000800);
}
