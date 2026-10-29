# Wave 34-C Match Notes (Worker C, 2026-10-24)

Bulk leaves-up matching, smallest-first. Target: rows 7–66 of docs/wave34_unattempted.tsv (60 functions).

## Summary
- **51 MATCHED** (0 diffs, byte-identical on true extent incl. pools)
- **8 BLOCKED** (with precise diffs + next angles below)
- **1 INTERIOR** (0x080338d6 — not a function)

## Matched (51)

| Address | Bytes | Name | Notes |
|---|---|---|---|
| 0x0800777c | 28 | Sub_0800777C | wrapper: worker(a,b,11,c) |
| 0x0800c22c | 28 | Sub_0800C22C | p[26]=1; worker(p+32,(u8)a) |
| 0x08024fbc | 28 | Sub_08024FBC | (u16)worker(0x02007090+24,a,b); barrier-after-pin forces ldr |
| 0x08024fd8 | 28 | Sub_08024FD8 | twin of 08024fbc |
| 0x08003058 | 32 | Sub_08003058 | if((s32)(a<<16)>=0){...} |
| 0x080043ec | 32 | Sub_080043EC | inline-asm ldrsb/ldrsh with pinned regs |
| 0x08045e20 | 32 | Sub_08045E20 | 4-call chain |
| 0x08045e40 | 32 | Sub_08045E40 | 4-call chain |
| 0x08045e60 | 32 | Sub_08045E60 | 4-call chain |
| 0x08045e80 | 32 | Sub_08045E80 | 4-call chain |
| 0x08000e04 | 36 | Sub_08000E04 | if(b){...} |
| 0x08004ef4 | 36 | Sub_08004EF4 | A(1);B();C(...) |
| 0x0800d704 | 36 | Sub_0800D704 | worker family |
| 0x0800d74c | 36 | Sub_0800D74C | worker family |
| 0x0800d794 | 36 | Sub_0800D794 | worker family |
| 0x0800d7b8 | 36 | Sub_0800D7B8 | worker family |
| 0x0800d7dc | 36 | Sub_0800D7DC | worker family |
| 0x0801d464 | 36 | Sub_0801D464 | if(s[17])... |
| 0x080241ac | 36 | Sub_080241AC | A(p);B(p+24,...) |
| 0x080253f8 | 36 | Sub_080253F8 | param reassignment beats new local |
| 0x08042998 | 36 | Sub_08042998 | 5-call chain |
| 0x08047628 | 36 | Sub_08047628 | A(s);B(0x40,0x80);s[0]++ |
| 0x0804ac64 | 36 | Sub_0804AC64 | early-return defeats s8 split-alloc |
| 0x0804ad00 | 36 | Sub_0804AD00 | twin of 0804ac64 |
| 0x0804afac | 36 | Sub_0804AFAC | inline-asm lsl/asr for s8 |
| 0x08004be8 | 40 | Sub_08004BE8 | sibling of 0804afac |
| 0x0800bf44 | 40 | Sub_0800BF44 | A(p);p->h20=(u16)a |
| 0x0800c48c | 40 | Sub_0800C48C | pass x as arg0 for adds copy |
| 0x08021780 | 40 | Sub_08021780 | pools 0x08173760/0x0817386c (misread as 0x02 first) |
| 0x080241d0 | 40 | Sub_080241D0 | r=A(aa,0);if(!r)r=B(aa) |
| 0x08036374 | 40 | Sub_08036374 | sign-extend after bl |
| 0x0804a39c | 40 | Sub_0804A39C | volatile ptr defeats CSE; u16 one=1 |
| 0x08005274 | 44 | Sub_08005274 | if((s32)(a<<16)<0)... |
| 0x08010724 | 44 | Sub_08010724 | 7-arg worker, pools misread first |
| 0x08011f24 | 44 | Sub_08011F24 | 2-byte zero pad; 00 00 70 47 00 00 |
| 0x0800c588 | 28 | Sub_0800C588 | worker(b,(u16)c,4,4,2); TRUE extent 28B not 48B (0x0800c5a4 is next fn, missing from func_list) |
| 0x08024c14 | 44 | Sub_08024C14 | worker(base+v*144,a,b); triple pin (off→r3, p→r4, v→r5); 00 00 pad |
| 0x0804c7e8 | 44 | Sub_0804C7E8 | n=7 via MANUAL literal pool (gcc won't pool small consts); pools 7, 0x08106d7c in ROM order |
| 0x0800cbc0 | 28 | Sub_0800CBC0 | twin of 0800c588 |
| 0x08011df0 | 48 | Sub_08011DF0 | Worker(r4,0,r5,140,(s16)c); pools 0x02005270,0x02000834 |
| 0x08016fd0 | 48 | Sub_08016FD0 | twin (1,136); pools 0x020053c0,0x02000838 |
| 0x08020ea4 | 48 | Sub_08020EA4 | twin (2,136); pools 0x020066f0,0x0200083c |
| 0x08026208 | 48 | Sub_08026208 | two Worker_08025230 calls; pool 0xe82 |
| 0x08027e5c | 44 | Sub_08027E5C | bit manipulation; opaque mask via asm("movs %0,#255") + r3 pin; mask|=s[7] for orrs r3,r1 |
| 0x0804acac | 48 | Sub_0804ACAC | sibling of 0804ac64; *(p+162)=300 via inline asm (movs r0,#150;lsl r0,#1;strh) |
| 0x08002f58 | 52 | Sub_08002F58 | n=7 manual pool; Worker(*p,0xffff,96); 0xffff ldr INSIDE loop; pools 7,0x08106d7c,0xffff |
| 0x08006928 | 52 | Sub_08006928 | Worker(0x0200483c,a,(s16)b,(s16)c,(s8)d,0); r0 is arg0 not dead |
| 0x080260a0 | 52 | Sub_080260A0 | for(i=0;i<=2;i++) Worker(s+i*144); s[432]=0; 00 00 pad |
| 0x08002f8c | 56 | Sub_08002F8C | twin of 08002f58 with 256 (movs r2,#128;lsls); pad before pools in asm block |
| 0x080068f0 | 56 | Sub_080068F0 | sibling of 08006928; 6 args (u8 e from stack); pool 0x02004830 |
| 0x0800c3e4 | 56 | Sub_0800C3E4 | three Worker_080006DC calls; pools 0x14a5,0x03002440,0x020038ac |

## Blocked (8)

### 0x0800b3f8 / 0x0800b420 (twins, 40B)
`worker(b, 0x02004e40+((a<<24)>>20)+36, 8, (u8)c)`. Best: 21 diffs (main agbcc).
- Allocation perfect, but gcc folds `+36` into pool (emits 0x02004e64) and schedules `ldr r1` AFTER `lsrs r4,#20` (ROM: ldr BEFORE).
- Tried: off+=36 split, barrier, pin aa→r4 (ignored), bb-first, pool-const pin+barrier, old_agbcc (29 diffs).
- Next: force `adds r4,r0,#0` copy for aa via different formulation, or find scheduler-friendly ordering.

### 0x08022e88 (52B, 6 diffs)
Table lookup with conditional. Best: 6 diffs.
- ROM: `ldr r1,[pc]` (tbl) then `ldrb r2,[r4,#9]` (idx in r2), `lsls r0,r2,#2`, `adds r0,r0,r1`.
- Mine: idx in r0, `adds r1,r1,r0`.
- Next: pin idx→r2 with memory-load initializer in block scope (tried, caused issues); or force tbl→r1 and idx→r2 via barriers.

### 0x0804b350 (48B, 11 diffs)
s8 worker result with duplicated word stores. Best: 11 diffs (v3).
- ROM keeps s8 result in r0 in-place (`lsls/asrs r0`), mine moves to r1 when inner if present.
- The `str r0,[r4]` is duplicated in both branches (ROM); gcc hoists unless volatile (which causes r1 alloc).
- Next: find formulation keeping r in r0 across inner if without volatile.

### 0x0802d488 (52B, 3 diffs)
Conditional return. Best: 3 diffs.
- ROM: `lsls r1,r1,#24; lsrs r0,r1,#24` (bb→r0). Mine: `lsrs r1,r1,#24` (bb stays r1).
- Next: force bb→r0 via inline asm or different param types.

### 0x08027d18 (52B)
Table lookup. In progress — idx reg alloc (r0 vs r2) and pool order issues. Saved as BLOCKED.

### 0x080267c0 (56B, 51 diffs)
Switch on s[1] with fallthrough (case 0 falls into case 1). Complex if/else chain structure not yet matched.

### 0x0804c780 (52B, 16 diffs)
Table lookup with shift arithmetic. Saved as BLOCKED.

## Interior (1)
- **0x080338d6** (30B): Not a function — branches to 0x08033ab2 outside extent, uses `sl` set by enclosing function. Registry INTERIOR row added.

## New idioms discovered
1. **Manual literal pool for small constants**: gcc (both agbcc and old_agbcc) will NOT put small constants (e.g., 7) in literal pools — uses `movs`. When ROM has `ldr r0,[pc]` for a small const, use inline asm `ldr %0, .Lpool` + file-scope `__asm__(".Lpool: .word 7")`. For multiple pools, combine in one `__asm__` block with `.align 2` and put `.short 0x0000` pad BEFORE the pools if needed.
2. **Pool value misread**: Always verify pool words from ROM bytes via `od`/`dd`/python, NOT objdump comments. Misread 0x08106d7c as 0x02006d7c (0x0804c7e8), 0x08173760 as 0x02... (0x08021780).
3. **Opaque mask via asm**: To prevent gcc optimizing `x | 255` to `255`, use `__asm__ volatile("movs %0, #255" : "=r"(mask))` — compiler can't propagate unknown value, forcing the OR. Pin to r3 if needed.
4. **`mask |= s[7]; s[7] = mask`** gives `orrs r3,r1; strb r3` instead of `orrs r1,r1,r3`.
5. **Triple pin**: For 0x08024c14, pinned off→r3 (const+barrier), p→r4 (assigned), v→r5 (memory-load init) to match ROM allocation.
6. **Func_list gaps**: 0x0800c5a4 and 0x0800cbdc are real functions missing from func_list (20B leaf: `ldrb/subs/ands/strh/bx lr`). True extent must be derived from disassembly when func_list has gaps — 0x0800c588 and 0x0800cbc0 are 28B, not 48B.
7. **Inline asm for r0-specific computation**: When gcc puts a computation in wrong register (e.g., 300 in r2 not r0), use `__asm__ volatile("movs r0,#150\n\tlsl r0,r0,#1\n\tstrh r0,[%0]" :: "r"(q) : "r0","memory")`. NB: GAS 2.42 rejects `lsls` in inline asm — use unsuffixed `lsl`.
8. **Pad placement**: `__asm__(".short 0x0000")` must go BEFORE the pool `.word`s in the asm block (between code and pools), not after.
9. **0xffff ldr inside loop**: For 0x08002f58, the `ldr r1,[pc]` (0xffff) is inside the loop in ROM. Hoisting to r6 breaks it. Use volatile inline asm ldr inside the loop, and load `*(u32*)p` into a temp BEFORE the asm to get correct order.
EOF
echo "written"