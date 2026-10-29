# Wave 31-A Match Notes (Worker A, 0x0801E77C)

Worker A, 2026-10-24. Staging: `staging/wave31_A/` (C sources, verify.sh).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: 0x0801e77c NOT-IN-REGISTRY (was BLOCKED at 176 diffs, never
claimed). No claim made (coordinator lands; DO-NOT-LAND).

## MATCHED (1)

### 0x0801E77C — ChipFxTick2_0801E77C (256 B, 0 diffs) ✅

**True extent:** 256 B (0x801E77C–0x801E87C). Layout: prologue, dispatch,
case bodies, mid-code pool at 0x801E864 (1 word, after `b.n` at 0x801E860),
epilogue `add sp,#8; pop {r4,r5}; pop {r0}; bx r0`, 2 B zero pad.
Pools: 0x801E7A8 `[0x020051C8]`, 0x801E83C `[0x020031E0, 0x0000EDFF,
0x0000DBFF]`, 0x801E864 `[0x082243D8]` — all reproduced via the pool-barrier
mechanism (barriers: `b.n` at 0x801E7A4, `b.n` at 0x801E838, `b.n` at
0x801E860; no CFG steering needed, the switch structure emits them).

**Compiler:** old_agbcc, pure C — NO .s patch required (unlike the sibling
0x0801C428 which needed fix_0801c428.py).

**Staged:** `staging/wave31_A/w31a_0801e77c_MATCHED.c`
Verify: `./verify.sh 0x0801e77c 256 .text.w31a_0801e77c w31a_0801e77c_MATCHED.c old ChipSlot_IncUse=0x0800d9ec NewNode_0801D278=0x0801d278 SelBlob_Ret=0x0800303c Set_08004E24=0x08004e24 Cmp_08004E0C=0x08004e0c Fwd_10BA0=0x08010ba0`
→ `sizes: o=1400 elf=2948 bin=256`, `rom extract: 256 bytes`, `diffs: 0`.

**Name:** ChipFxTick2_0801E77C — chip-FX state machine, sibling of
ChipFxTick_0801C428. Behavior: p[14] state 0/1/2/3; state 0 inits
(ChipSlot_IncUse(p,8), 60-tick timer at p+120, NewNode_0801D278(p, p+19,
&zeroPair)); state 1 ticks the timer down, plays sound 110 (SelBlob_Ret)
at zero; shared tail advances state when `(u8)(p[119]-3) <= 1`; state 2
conditionally clears EWRAM bits `*(u16*)0x020031E0 &= 0xEDFF & 0xDBFF`;
state 3 table-drives via `0x020051C8 + p[16]*12` (tbl[6]/tbl[1]) and
`0x082243D8[p[9]]`.

**Variant history (12 C variants):**
- v1–v7: wave-30 attempts (176 diffs best; prologue pool→r1 wall).
- v8: prologue breakthrough — 98 diffs.
- v9: tbl→r2 pin, case-1 ldrsh idiom, case-3 pool→r1 pin — 14 diffs.
- v10: off→r0 pin (fixes multiply reg) — 11 diffs.
- v11: case-2 pins, case-3 memory-barrier ordering, zero-fill tail — 6 diffs.
- v12: case-2 ldrh via asm output, case-3 operand swap — **0 diffs**.
- MATCHED: v12 renamed (function/section), header comment added — 0 diffs.

**Key techniques (new idioms):**
1. **Pool-const pin (block-scoped) — the prologue wall killer.** Wave 30
   concluded "pinning pool→r1 ignored for constants". Wrong for this
   formulation: `{ register u32 base __asm__("r1") =
   (u32)&gAddrZero[0x20051c8]; tbl = (u8 *)(off + base); }` emits
   `ldr r1, [pc, #N]` reliably (tested in isolation: block-scope,
   function-scope, and static-const-source variants ALL honor it).
   Generalizes: pin any pool constant to its desired destination reg
   (used 4× in this function: prologue→r1, case-2 g→r2/0xEDFF→r0/
   0xDBFF→r1, case-3 0x082243D8→r1).
2. **Two-movs zeroing idiom.** `{ register u32 z0 __asm__("r0") = 0;
   register u32 z1 __asm__("r1") = 0; sp0 = z0; sp1 = z1; }` +
   `__asm__ volatile("" :: "m"(sp0), "m"(sp1));` gives ROM's exact
   `movs r0,#0; movs r1,#0; str r0,[sp,#0]; str r1,[sp,#4]`
   (gcc otherwise merges to one mov and reverses store order).
3. **Memory-barrier for store-before-load order (case 3).** ROM:
   `adds r0,r0,r1; movs r1,#2; str r1,[r4,#12]; ldr r0,[r0];
   ldr r0,[r0,#8]` — gcc hoists the load above the independent store.
   Fix: compute only the ADDRESS first (`u32 e = (idx << 2) +
   (u32)tbase;`), store, then `__asm__ volatile("" : "+r"(e) ::
   "memory");` before the double-deref. The "memory" clobber is the
   load-bearing part (a pure "+r" barrier still lets the load cross).
4. **Pinned-reg deref-init can be ignored — use asm output.** `register
   u32 t __asm__("r1") = *g;` silently allocated t to r3; replacing with
   `__asm__("ldrh %0, [%1]" : "=r"(t) : "r"(g));` forces `ldrh r1,[r2]`.
   (Applies to agbcc's missing ldrh-from-C too, like the ldrsh idiom.)
5. **Operand order steers adds dest.** `e = (idx << 2) + (u32)tbase`
   gives `adds r0,r0,r1`; the reversed `(u32)tbase + (idx << 2)` gives
   `adds r1,r1,r0`. First-operand-in-r0 wins.
6. **Zero-fill section tail.** File-scope `__asm__(".section
   .text.NAME\n.align 2, 0\n.previous");` AFTER the function forces
   0x0000 (not 0x46c0 nop) for section-end alignment padding
   (precedent: w30d_0801c428.c).

**For coordinator:** Pure-C match, old_agbcc. Suggested Makefile stanza
(per-file OLDAGBCC rule, cf. w30d_0801c428.o):
```
$(BUILD)/w31a_0801e77c.o: src/w31a_0801e77c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
```
No post-process script needed. Registry claim: ChipFxTick2_0801E77C,
0x0801e77c, wave 31, MATCHED, src/w31a_0801e77c.c.

## New idioms discovered (durable)

1. Pool-const pin (block-scoped `register T v __asm__("rN") = CONST;`)
   forces literal-pool destination register — the general answer to
   "pool→rX" walls. Supersedes wave-30's "ignored for constants".
2. Two-movs zeroing idiom (pinned z0/z1 + m-constraints).
3. `"memory"`-clobber volatile barrier to pin store-before-load order
   against the scheduler (pure "+r" barrier insufficient).
4. Pinned-reg variable initialized by dereference may be silently
   reallocated — prefer inline-asm output operand for forced dest reg.
5. Adds operand order: first operand's register wins as dest base
   (`(idx<<2) + base` → `adds r0,r0,r1`).

## Tooling

- `staging/wave31_A/verify.sh` — harness (wave30_D paths adapted).
- `staging/wave31_A/prol_test.c`, `prol_test2.c` — prologue experiment rigs.
- `staging/wave31_A/w31a_0801e77c_v8.c` … `v12.c` — iteration history.
- `staging/wave31_A/w31a_0801e77c_MATCHED.c` — 0-diff staged claim.

## Summary for coordinator

- **MATCHED:** 0x0801E77C (ChipFxTick2_0801E77C, 256 B, old_agbcc, pure C,
  0 diffs). Staged at `staging/wave31_A/w31a_0801e77c_MATCHED.c`.
  Needs registry claim + landing (Makefile OLDAGBCC stanza, no patch
  script). Recommend landing as `src/w31a_0801e77c.c`.
- **Progress:** 1/1 target matched. Wave-30's 176-diff BLOCKED is closed.
- **No asm transcription needed** — the wall fell in C (12 variants).
