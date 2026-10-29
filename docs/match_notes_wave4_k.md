# Wave 4 Batch K — Match Notes

7/12 matched. 5 blocked with precise byte-level diffs below.

## Matched (7)

| Addr | Name | Bytes | Compiler | Key idiom |
|---|---|---|---|---|
| 0x08035e0c | Task_35E0C | 52 | main agbcc | — |
| 0x08035eb0 | Task_35EB0 | 92 | old_agbcc | r0/r1 swap in mask-clear; old_agbcc allocates mask to r0 |
| 0x08035f0c | Task_35F0C | 66 | main agbcc | — |
| 0x080360b0 | Task_360B0 | 18 | main agbcc | +2 pad stripped (next fn immediate) |
| 0x08036664 | Task_36664 | 68 | main agbcc | literal `0` (not `u8 z=0`) forces pool loads for 0x4698/0x469C; 0x4699 derived via `subs r3,#3` |
| 0x08036724 | Task_36724 | 92 | old_agbcc | `u8 z;` at if-body top, `z = 0;` placed mid-ands-block → correct `movs` scheduling |
| 0x08036780 | Task_36780 | 96 | main agbcc | if/else chain (not switch) for linear cmp/bne; `p[0x469F]` used directly (no `v` local) so no `adds r1,r0,#0` |

## Blocked (5)

### 0x08035f50 — Task_35F50 (352 B)

Big switch on `p[3]` with cases 0–3 and default. Structure decoded:

- Prologue: `push {r4-r7,lr}`, save r8; `r8=ret=0`, `r6=flag=0`, `r4=ew=0x02002F50`, `r7=v0=ew[2]`, `r5=p`.
- Switch dispatch: `cmp #1; beq case1; cmp #1; bgt; cmp #0; beq case0; b default; …; cmp #2; beq case2; cmp #3; bne default; b case3`.
- case0 (falls through to case1): `(u8)(sub_08024384(0x1000)-0x32)` table-index idiom → `sub_0803618C`; `p[0x469A]=0`; loop `for(i=0;i<=6;i++) sub_08036318(gRom_0822EB50[i])`; `sub_0803639C(0)`; `sub_08036374(gRom_0822EB50[p[0x46B7]])`; `p[3]++`.
- case1: `sub_080361DC()`; `p[0x469A]++`; if `> 0x2D` then `p[3]++`.
- case2: flag logic — `r6=1` if `(1&ew[0])&&(1&ew[2])`, `r6=2` if `(2&ew[0])&&(2&ew[2])`; `p[0x46B7]=sub_0803639C(v0)+1`; if flag==1: `Text_SelectBlobIdx(0x67)`, `p[3]++`; if flag==2: optional `sub_0804990C()`, `*(u32*)(p+0x18)|=flag`, `*(u32*)(p+0x1C)` mask-negation idiom (`u32 m=3; m=-m;`), `Text_SelectBlobIdx(0x68)`, `p[0x46B7]=8`, `ret=1`.
- case3: `sub_080361DC()`; if `(s8)sub_080363D4()==1` then `ret=1`.
- Epilogue: compiler DUPLICATED `bl sub_080361E8` — shared copy at 0x08036086 (`bl; b return`) for cases 1/2, separate copy at 0x080360a0 (`bl`, fallthrough) for case 3. Default jumps directly to return (0x080360a4), skipping both.

Best attempt: 159/352 bytes differ (built 344). The duplicated epilogue and exact case-body scheduling were not reproduced. Likely needs the `bl` explicitly in each case body with the compiler tail-merging cases 1+2.

### 0x080366a8 — Task_366A8 (64 B)

```c
s8 v = (s8)sub_08004E0C(0);
if (v) { p[1] = 2; p[2] = v; p[3] = v; }
```

3-byte diff. Reference:

```
0x080366c0  asrs r1, r0, #24   ; sign-extend
0x080366c2  cmp  r1, #0
0x080366c4  beq  #0x080366d6
```

Both agbcc and old_agbcc emit:

```
lsrs r1, r0, #24   ; zero-extend (0x080366c0: 0x0A49 vs ref 0x0849)
cmp  r0, #0        ; (0x080366c2: 0x2800 vs ref 0x2900)
beq               ; (0x080366c4: 0xD006 vs ref 0xD106)
```

The sign-extension is unobservable (`v!=0` and byte stores don't need the sign), so the compiler optimizes it away. Tried: `(int)v` cast, init-at-declaration, no-cast, `int w=v` intermediate, volatile (worse — stack spills). The asrs appears to be a missed optimization in the original build that cannot be forced from C without changing semantics.

### 0x08036ba8 — Task_36BA8 (256 B)

Teardown; `gEwram_02004E40[0x14] |= 1`; switch on `p[5]`:

- case0: `idx=p[0x469F]`; `fn=((u32*)gRom_082300D4)[idx]`; `sub_0800B368(fn, *gRom_0822EEF4, *gRom_0822EEFC, 0)`; if nonzero: `sub_0800B3F8(0, *gRom_0822FF4C[idx], 0)`; `p[5]++`.
- case1: if `sub_0800B308()`: `g8=g[8]`; if g8: `p[0x4699]=p[5]`, `p[5]=0`; else: `idx=p[0x469F]`, `v=*(u16*)(gRom_0822FE60+idx*6)`, if `sub_08040060(gEwram020070F0,v)`: `p[0x4699]=7,p[5]=0` else `Text_SelectBlobIdx(0x78)`, `p[0x4699]=5`, `p[5]=0`, `sub_080374B8(p)`, `sub_08037598(p)`.
- Setup; return 0.

188/256 bytes differ. Prologue register allocation not reproduced. Reference:

```
push {r4,r5,r6,lr}; adds r4,r0,#0; bl Teardown
ldr r6,[pc] → 0x02004E40; movs r0,#1; ldrb r1,[r6,#0x14]; orrs r0,r1; strb r0,[r6,#0x14]
ldrb r5,[r4,#5]   ; p=r4, mode=r5, g=r6
```

old_agbcc gives the right `movs`-before-`ldrb` scheduling but allocates `p=r5, mode=r4` (swapped). Main agbcc gives `ldrb`-before-`movs`. The exact `p=r4, mode=r5, g=r6` allocation was not achieved.

### 0x08036ca8 — Task_36CA8 (260 B)

Near-twin of Task_36BA8. Differences: table `gRom_0822FF58` (not `...4C`), `*(u16*)(gRom_0822FE60+2+idx*6)` (try `u8 *t=gRom_0822FE60; t+=2;`), `p[0x4699]=6` (not 5). Not attempted in detail; same prologue allocation blocker as 0x08036ba8.

### 0x08037440 — Task_37440 (120 B)

Teardown; `g[0x14]|=1`; switch `p[5]`: case0 `idx=p[0x469F]`, `fn=gRom_082300E0[idx]`, if `sub_0800B368(fn,0,0,0)`: `p[5]++`; case1: if `sub_0800B308()`: `p[0x4699]=mode` (r4 holds mode), `p[5]=0`; Setup; return 0.

61/120 bytes differ. Prologue scheduling not reproduced. Reference:

```
ldr r1,[pc] → 0x02004E40; movs r0,#1; ldrb r2,[r1,#0x14]; orrs r0,r2; strb r0,[r1,#0x14]
```

Closest attempt (nested block with `u8 v=1; u8 w=g[0x14]; v|=w; g[0x14]=v;`):

```
movs r2,#1; ldr r1,[pc]; ldrb r0,[r1,#20]; orrs r0,r2; strb r0,[r1,#20]
```

g in r1 correct, but v in r2 (ref r0), w in r0 (ref r2). Register permutation not resolved.

## Recomp-relevant discoveries

These are task mode/state handlers that drive the mode dispatchers (batch F):

- **Task init pattern**: zero task struct fields (`p[1..5]`, `p[0x4698..0x46B7]` region), call `sub_0804A2DC(n)` (n=6/7), then `EntryMgr_Teardown()` / `EntryMgr_Setup()`. The `0x4698`/`0x469C` 32-bit stores in Task_36664 zero 8 bytes at once.
- **Mode dispatch**: switch on `p[2]`/`p[3]`/`p[5]`/`p[0x469F]`, gating on poll functions (`sub_08004E0C`, `sub_0800B308`, `sub_0800B368`, `sub_080400D0`, `sub_080363D4`).
- **ROM fn-pointer tables**: `0x082300D4`, `0x082300E0`, `0x0822FF4C`/`0x0822FF58` — dispatch through these must be preserved.
- **Global flag**: `gEwram_02004E40[0x14] |= 1` at handler entry (0x08036ba8/0x08036ca8/0x08037440).
- **Text blobs**: `Text_SelectBlobIdx(0x67/0x68/0x78)` selects UI text for modes.
- **Bitflags**: `*(u32*)(p+0x18)` / `*(u32*)(p+0x1C)` with mask-negation idiom (`u32 m=3; m=-m;`) in Task_35F50 case2.
- **New symbol**: `gEwram_020031E0` (0x020031E0) — bitmask cleared with `&= 0xEDFF &= 0xDBFF`; `.set` added in wave4_k.c (was not defined anywhere).

## New idioms

- **old_agbcc r0/r1 allocation**: when main agbcc swaps r0/r1 in a mask-clear sequence (`ldr r1,mask; ldrh r0,[r2]` vs `ldr r0,mask; ldrh r1,[r2]`), old_agbcc may have the reference allocation. Probe old_agbcc for r0/r1 swaps, not just general regalloc issues.
- **Literal-0 pool forcing** (Task_36664): using literal `0` in `*(u32*)(p+0x4698)=0` (instead of `u8 z=0`) keeps the `movs r1,#0` from killing the 0x4698 constant, forcing a real pool load for 0x469C, then 0x4699 is derived via `subs r3,#3`.
- **Mid-block zero placement** (Task_36724): declaring `u8 z;` at if-body top but placing `z = 0;` in the middle of the ands-block gets the `movs r3,#0` scheduling right.
- **Direct field use for linear dispatch** (Task_36780): using `p[0x469F]` directly in each `if` condition (not a `v` local) avoids the `adds r1,r0,#0` move; the compiler CSEs the load into r0.
