# Wave 13 Worker C (TAG=C) — sub_0800B148 @ 0x0800B148 — Match Notes

Worker: Wave 13 specialist (TAG=C). Date: 2026-10-22.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/{agbcc,old_agbcc}` (both tried); `arm-none-eabi` 2.42.
Harness: `staging/wave13_C/mk.sh` (adapted from wave12_A; hardened assertions,
file offset = addr − 0x08000000, full extent incl pools, `cmp -l`).
Staging: `~/workspace/mmbcc-decomp/staging/wave13_C/` (NEVER delete).

**Result: BLOCKED.** Best: v13 (249 diffs, 352/340 B, old_agbcc) with **42-byte
exact prefix match** (bytes 0–41). The control-flow graph is fully mapped and
validated; the blocker is instruction-level codegen (register allocation order,
scheduler decisions) that resists all tried C shapes.

## Target: sub_0800B148 @ 0x0800B148 (340 B)

A bitfield state machine related to task dispatch (Task_3AFFC callee).
Signature: `u8 (u8 a, u16 b, u8 c)`. Returns 0 (early/tail0 paths) or 1 (join path).

### Calls
- `bl 0x0800B470` with `(s16)b` (via `asrs r0,r3,#16` where r3 = b<<16)
- `bl 0x08007EEC` with `0` (conditional on `base[30] & 32`)
- `bl 0x0800B6F4` with `(base, 0)`

### Base pointer
`0x02004E40` (literal pool at 0x800B174, after the early `b.n`).
Kept in r5; copied to r9 (`mov r9,r5` at 0x800B16A, between `ands` and `cmp`!);
at join, loaded into r7 via `mov r7,r9`.

## Complete CFG Map (from ROM disassembly)

```
0x800B148: prologue
  push {r4-r7,lr}; mov r7,r9; mov r6,r8; push {r6,r7}
  a: lsls r0,r0,#24; lsrs r0,r0,#24; mov ip,r0    (a → ip)
  b: lsls r1,r1,#16; lsrs r6,r1,#16               (b → r6, zero-extended)
  c: lsls r7,r2,#24; lsrs r0,r7,#24; mov r8,r0    (c<<24 → r7, c → r8)
  ldr r5,[pc,#16]  (r5 = 0x02004E40)

0x800B162: ldrb r1,[r5,#4]        (b4 = base[4])
0x800B164: movs r2,#15
0x800B166: adds r0,r2,#0         (r0 = 15)
0x800B168: ands r0,r1            (r0 = 15 & b4)
0x800B16A: mov r9,r5             (r9 = base)  <-- BEFORE cmp!
0x800B16C: cmp r0,#0
0x800B16E: beq 0x800B178
0x800B170: movs r0,#0
0x800B172: b 0x800B290            (return 0; epilogue)
  [pool 0x02004E40 at 0x800B174]

0x800B178: movs r0,#128
0x800B17A: ands r0,r1            (r0 = 128 & b4; r1 preserved!)
0x800B17C: cmp r0,#0
0x800B17E: bne 0x800B19A
  ;; (base[4] & 128) == 0 path:
0x800B180: movs r2,#1
0x800B182: mov r1,r8             (r1 = c)
0x800B184: ands r1,r2            (r1 = c & 1)
0x800B186: movs r0,#2
0x800B188: negs r0,r0            (r0 = -2)
0x800B18A: ldrb r3,[r5,#19]
0x800B18C: ands r0,r3            (r0 = base[19] & -2)
0x800B18E: orrs r0,r1
0x800B190: strb r0,[r5,#19]      (base[19] = (base[19] & -2) | (c & 1))
0x800B192: strb r2,[r5,#5]       (base[5] = 1; r2=1)
0x800B194: ldrb r4,[r5,#21]      (v21 = base[21] → r4)
0x800B196: lsls r3,r6,#16        (r3 = b<<16)
0x800B198: b 0x800B206            (→ JOIN)

  ;; (base[4] & 128) != 0 path:
0x800B19A: ldrb r1,[r5,#21]      (v21)
0x800B19C: lsls r0,r1,#28
0x800B19E: lsrs r0,r0,#28        (r0 = ((u32)v21 << 28) >> 28)
0x800B1A0: adds r4,r1,#0         (r4 = v21)
0x800B1A2: cmp r0,ip             (cmp (v21 low nibble), a)
0x800B1A4: beq 0x800B1B6
0x800B1A6: movs r0,#5
0x800B1A8: strb r0,[r5,#5]       (base[5] = 5)
0x800B1AA: mov r0,ip             (r0 = a)
0x800B1AC: lsls r1,r0,#4         (r1 = a<<4)
0x800B1AE: adds r0,r2,#0         (r0 = 15; r2 still 15 from 0x800B164!)
0x800B1B0: ands r0,r4            (r0 = 15 & v21)
0x800B1B2: orrs r0,r1            (r0 = (15&v21) | (a<<4))
0x800B1B4: b 0x800B1DA            (→ shared strb)

0x800B1B6: ands r2,r4            (r2 = 15 & v21; r2=15 reused!)
0x800B1B8: adds r0,r2,#0
0x800B1BA: cmp r0,#2
0x800B1BC: beq 0x800B1C4
0x800B1BE: lsls r3,r6,#16        (r3 = b<<16; HOISTED, dead for cmp but LIVE for join!)
0x800B1C0: cmp r0,#4
0x800B1C2: bne 0x800B206          (→ JOIN)
0x800B1C4: lsls r0,r6,#16        (r0 = b<<16)
0x800B1C6: ldrh r3,[r5,#6]
0x800B1C8: lsls r1,r3,#16        (r1 = mem<<16)
0x800B1CA: adds r3,r0,#0         (r3 = b<<16)
0x800B1CC: cmp r1,r3
0x800B1CE: beq 0x800B206          (→ JOIN if equal)
0x800B1D0: movs r0,#5
0x800B1D2: strb r0,[r5,#5]       (base[5] = 5)
0x800B1D4: mov r1,ip             (r1 = a)
0x800B1D6: lsls r0,r1,#4         (r0 = a<<4)
0x800B1D8: orrs r0,r2            (r0 = (a<<4) | (15&v21); r2 from 0x800B1B6)
  ;; fall through to shared tail:
0x800B1DA: strb r0,[r5,#21]      (SHARED: base[21] = r0)
0x800B1DC: strh r6,[r5,#24]      (*(u16*)(base+24) = b)
0x800B1DE: lsrs r1,r7,#25        (r1 = (c<<24)>>25 = c>>1; r7=c<<24!)
0x800B1E0: movs r2,#1
0x800B1E2: ands r1,r2
0x800B1E4: lsls r1,r1,#6
0x800B1E6: movs r0,#65
0x800B1E8: negs r0,r0            (r0 = -65)
0x800B1EA: ldrb r3,[r5,#30]
0x800B1EC: ands r0,r3
0x800B1EE: orrs r0,r1
0x800B1F0: strb r0,[r5,#30]      (base[30] = (base[30] & -65) | (((c>>1)&1)<<6))
0x800B1F2: lsrs r1,r7,#27        (r1 = (c<<24)>>27 = c>>3)
0x800B1F4: ands r1,r2            (r2=1)
0x800B1F6: movs r0,#2
0x800B1F8: negs r0,r0            (r0 = -2)
0x800B1FA: ldrb r6,[r5,#31]
0x800B1FC: ands r0,r6
0x800B1FE: orrs r0,r1
0x800B200: strb r0,[r5,#31]      (base[31] = (base[31] & -2) | (((c>>3)&1)<<6))
0x800B202: movs r0,#0
0x800B204: b 0x800B290            (return 0)

0x800B206: JOIN:
0x800B206: mov r7,r9             (r7 = base from r9)
0x800B208: ldrb r2,[r7,#20]      (v20)
0x800B20A: lsrs r1,r2,#3
0x800B20C: movs r0,#32
0x800B20E: negs r0,r0            (r0 = -32)
0x800B210: ldrb r6,[r7,#30]
0x800B212: ands r0,r6
0x800B214: orrs r0,r1
0x800B216: strb r0,[r7,#30]      (base[30] = (base[30] & -32) | (v20>>3))
0x800B218: movs r0,#7
0x800B21A: ands r0,r2            (r0 = v20 & 7)
0x800B21C: movs r1,#192
0x800B21E: orrs r0,r1
0x800B220: strb r0,[r7,#20]      (base[20] = (v20&7) | 0xC0)
0x800B222: movs r1,#15
0x800B224: mov r7,ip             (r7 = a; r7 repurposed!)
0x800B226: ands r1,r7            (r1 = a & 15)
0x800B228: movs r0,#16
0x800B22A: negs r0,r0            (r0 = -16)
0x800B22C: ands r0,r4            (r0 = v21 & -16; r4=v21)
0x800B22E: orrs r0,r1
0x800B230: strb r0,[r5,#21]      (base[21] = (v21 & -16) | (a & 15); uses r5!)
0x800B232: asrs r0,r3,#16        (r0 = (s16)b; r3=b<<16 from hoisted paths)
0x800B234: bl 0x0800B470
0x800B238: mov r0,r8             (r0 = c)
0x800B23A: lsrs r1,r0,#1
0x800B23C: movs r4,#1
0x800B23E: ands r1,r4
0x800B240: lsls r1,r1,#5
0x800B242: movs r0,#33
0x800B244: negs r0,r0            (r0 = -33)
0x800B246: ldrb r2,[r5,#30]
0x800B248: ands r0,r2
0x800B24A: orrs r0,r1
0x800B24C: strb r0,[r5,#30]      (base[30] = (base[30] & -33) | (((c>>1)&1)<<5))
0x800B24E: movs r1,#32
0x800B250: ands r0,r1            (r0 = new base[30] & 32; REUSES r0!)
0x800B252: cmp r0,#0
0x800B254: beq 0x800B25C
0x800B256: movs r0,#0
0x800B258: bl 0x08007EEC
0x800B25C: mov r3,r8             (r3 = c)
0x800B25E: lsrs r1,r3,#3
0x800B260: ands r1,r4            (r4=1)
0x800B262: lsls r1,r1,#7
0x800B264: movs r0,#127
0x800B266: ldrb r6,[r5,#30]
0x800B268: ands r0,r6
0x800B26A: orrs r0,r1
0x800B26C: strb r0,[r5,#30]      (base[30] = (base[30] & 127) | (((c>>3)&1)<<7))
0x800B26E: movs r0,#4
0x800B270: ands r0,r3            (r0 = c & 4)
0x800B272: lsls r0,r0,#24
0x800B274: lsrs r0,r0,#24
0x800B276: negs r0,r0
0x800B278: asrs r0,r0,#31        (r0 = 0 or -1)
0x800B27A: movs r1,#2
0x800B27C: ands r0,r1
0x800B27E: movs r4,#0
0x800B280: strh r0,[r5,#14]      (*(u16*)(base+14) = (c&4) ? 2 : 0)
0x800B282: adds r0,r5,#0
0x800B284: movs r1,#0
0x800B286: bl 0x0800B6F4         (sub_0800B6F4(base, 0))
0x800B28A: strb r4,[r5,#9]       (base[9] = 0; r4=0)
0x800B28C: strb r4,[r5,#10]      (base[10] = 0)
0x800B28E: movs r0,#1            (return 1)

0x800B290: epilogue
  pop {r3,r4}; mov r8,r3; mov r9,r4; pop {r4-r7}; pop {r1}; bx r1
```

## Register Allocation (ROM)

- r4: v21 (u8)
- r5: base (0x02004E40)
- r6: b (u16), later temps
- r7: c<<24 (u32), then a (at join, after `mov r7,ip`)
- r8: c (u8)
- r9: base copy
- ip: a (u8)
- r0-r3: temps
- r3: b<<16 (hoisted in all join-reaching paths)

## Key Idioms Discovered

1. **`(v21 & 15) != a` via unsigned shift**: ROM uses
   `lsls r0,r1,#28; lsrs r0,r0,#28` (NOT `ands`). Reproduced by
   `(((u32)v21 << 28) >> 28) != a` under old_agbcc. Plain `(v21 & 15)`
   gives `ands` in both compilers. The shift form is required.

2. **`| -N` via `movs`+`negs`**: For masks -2, -65, -32, -16, -33, ROM uses
   `movs rX,#N; negs rX,rX`. Writing `& -2` (not `& ~2`) reproduces this.
   `& ~2` gives `movs #253; ands` instead.

3. **Hoisted `b<<16`**: `lsls r3,r6,#16` appears in three paths (0x800B196,
   0x800B1BE, 0x800B1C4). At 0x800B1BE it's "dead" for the s16-compare
   (overwritten at 0x800B1CA) but LIVE for the join's B470 call
   (`asrs r0,r3,#16`). The compiler hoisted `(s16)b` computation into
   branches.

4. **`mov r9,r5` placement**: Between `ands` and `cmp` (0x800B16A), NOT
   after the branch. Requires the copy to be scheduled early.

5. **Shared tail via cross-jump**: The two `base[21] = ...` assignments
   (with opposite operand order: `(15&v21)|(a<<4)` vs `(a<<4)|(15&v21)`)
   converge on a single `strb r0,[r5,#21]` at 0x800B1DA. Achieved via
   if/else-if/else with identical tails (compiler cross-jump), NOT
   explicit `goto`.

6. **`(c & 4) ? 2 : 0` idiom**: `lsls/lsrs #24; negs; asrs #31; ands #2`
   is old_agbcc's lowering of `(x ? 2 : 0)`.

7. **Prologue param processing**: Must keep `c<<24` live in r7 (not just `c`
   in r8). Achieved via explicit `(u32)c << 24` variable + inline asm to
   force exact instruction order (compiler groups shifts otherwise).

## Best Attempt: v13

- 249 diffs, 352/340 B (12 bytes too long), old_agbcc.
- **42-byte exact prefix match** (bytes 0–41): prologue through `mov r9,r5`.
- Uses: pinned registers (ip, r6, r7, r8, r5, r4, r9), volatile asm for
  prologue order, inline asm for `movs r2,#15; adds r0,r2,#0; ands r0,r1`.

### Precise Blockers

1. **`(b4 & 128)` operand order** (byte 43+): ROM does
   `movs r0,#128; ands r0,r1` (result in r0, r1 preserved). Ours does
   `ands r1,r0` (result in r1, overwriting b4). The compiler chooses
   in-place `ands` when the variable is dead; ROM's compiler preserved r1.
   Tried: swapping operand order, no effect.

2. **Size mismatch** (+12 bytes): Extra instructions from pinned-register
   setup and asm barriers. The `.code 16` directives (from inline asm
   without explicit Thumb mode) don't emit bytes but indicate mode
   confusion.

3. **Scheduler grouping**: The compiler groups independent `lsl`/`lsr`
   instructions; forcing order requires volatile asm which adds complexity.

4. **Body register allocation**: Beyond byte 42, the compiler makes
   different temp register choices (e.g., `ands r1,r0` vs `ands r0,r1`,
   `movs r3,#1` vs `movs r2,#1`). These are heuristic decisions that
   resist C-level control.

## Angles Tried

- v1-v3: Clean C, various if/goto structures. Best: 263 diffs (v1).
  Learned: cross-jump (not explicit goto) gives shared tail.
- v4-v6: Pinned registers for params. Learned: pinning fixes allocation
  but scheduler groups shifts.
- v7-v10: Pinned + volatile asm prologue. Achieved exact prologue bytes
  0-30. Learned: `mov r9,r5` must be between `ands`/`cmp`.
- v11-v13: Mask pinning, inline asm for `ands` sequence. Achieved 42-byte
  prefix match. Learned: `& -N` (not `& ~N`) for negs idiom; shift-form
  for `(v21&15)!=a`.
- v14: Clean C with else-if (no hacks). 287 diffs, 320 B. Confirmed:
  structure is correct but prologue/alloc wrong without pinning.
- Both old_agbcc and main agbcc tried; old_agbcc is closer.

## Recommendation

The CFG is fully validated. The remaining blockers are compiler heuristics
(register allocation order, instruction scheduling) that may require:
1. A different GCC version (the ROM may have been built with a specific
   agbcc build whose scheduler differs from both tried versions), OR
2. Accepting that this function needs hand-tuned assembly (not suitable
   for a C decomp), OR
3. More iterations on the body using the v13 prologue as a base, fixing
   each block's codegen with targeted asm (tedious but possible).

The function is a **bitfield state machine for task dispatch**: it checks
task state nibbles in `base[21]`, updates state fields in `base[5]`,
`base[19]`, `base[20]`, `base[21]`, `base[30]`, `base[31]`, and dispatches
to `sub_0800B470` (s16 param), `sub_08007EEC` (conditional), and
`sub_0800B6F4` (cleanup). Suggested name if matched:
`TaskDispatch_BitfieldState` or `UpdateTaskStateFlags`.
