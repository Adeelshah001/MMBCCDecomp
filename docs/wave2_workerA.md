# Wave 2 Worker A notes (2026-10-20)

Worker: matching-C, targets 0x0800D9EC / 0x0800D9FC / 0x0800D6E0.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place,
never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) / `old_agbcc`.
Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i && agbcc -O2
-mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link each `.o` against 2-byte Thumb stubs placed at the real
callee addresses (`bx lr`, `.thumb_func`), then `objcopy -O binary
--only-section` and byte-diff vs ROM. Scratch: `/tmp/wave2_A/`
(`build.sh`, `verify.sh`, `cmp.py`, `ChipSlot_*.c`, probes).

## 1. `ChipSlot_IncUse` @ 0x0800D9EC — MATCHED (16/16 bytes, agbcc)

```c
extern void sub_08004258(u8 *p, u8 idx);
__attribute__((section(".text.chipslot_incuse")))
void ChipSlot_IncUse(u8 *s, u8 idx)
{
    sub_08004258(s + 0x70, idx);
}
```
- Behavior: thin wrapper — truncates arg1 to u8 (`lsls/lsrs #24`, emitted
  because both params are u8), adds 0x70 to the struct pointer, tail-calls
  `sub_08004258` (216 bl-callers). Callee does indexed table-slot
  bookkeeping (counter increment + state transitions on a 8-byte record).
- Section `.text.chipslot_incuse`, 16 bytes, no padding.
- Verify: `./verify.sh ChipSlot_IncUse 0x0800D9EC 16 sub_08004258:0x08004258`
  → `diffs: 0 len-ok: True`.

## 2. `ChipSlot_Setup` @ 0x0800D6E0 — MATCHED (34/34 bytes, agbcc)

```c
extern void sub_0800D800(u8 *s, u8 a, u16 b, u8 c, u8 d);
__attribute__((section(".text.chipslot_setup")))
void ChipSlot_Setup(u8 *s, u16 b, u8 c)
{
    sub_0800D800(s, 0, b, c, 0);
}
```
- Behavior: wrapper around `sub_0800D800` (95 bl-callers). Passes
  `(s, 0, (u16)arg1, (u8)arg2, 0)`; the 5th arg goes on the stack
  (`sub sp,#4` / `str r1,[sp,#0]`). Callee splits the u16 into bytes at
  `s[28]/s[29]`, calls `sub_08004244`, then flag updates.
- **Landing caveat:** the compiled section is 36 bytes — gas pads the
  34-byte function with a 2-byte `46c0` nop (agbcc emits `.align 2,0` per
  section). ROM has `00 00` at 0xD702–0xD703. The function bytes
  (first 34) are identical; the landing must not emit the pad (explicit
  `. = 0x0800D704` for the next section + zero-fill, or strip trailing pad).
- Verify: first-34 diffs = 0.

## 3. `ChipSlot_Tick` @ 0x0800D9FC — BLOCKED

Big per-slot state update (302 B, 148 insns, 121 bl-callers). Calls
`sub_080042B8(s+112)`, `sub_0800244C`, `sub_08002904`; 5-literal pool
(`08173978, 08173654, 02005030, 08173760, 081738F2`); uses hi regs
`ip` (table `0x08173978`) and `r8` (`0x02005030`) due to register pressure.
Semantics fully mapped (see analysis below); best C attempt is in
`/tmp/wave2_A/ChipSlot_Tick.c` (attempt 2).

### Hard blocker (4 bytes, unmatchable with available toolchain)

ROM `0x0800DA2A–0x0800DA2D`:
```
800da2a: lsls r0, r2, #24
800da2c: lsrs r0, r0, #24
```
i.e. an explicit `(u8)` truncation of `r2 = ((s[10]>>4)&1)` in the
else-branch of `p48[24] = (s[35]&0x80) ? (1^r2) : (u8)r2`, before
`strb r0,[r6,#24]`.

**15+ source variants tried; both `agbcc` and `old_agbcc` (at -O2, and
also -O1/-Os) ALWAYS eliminate the cast** via range analysis
(`(x>>4)&1` is provably 0/1, so `(u8)` is a no-op). Tried: direct cast,
cast via u8 temp, cast after the join (`u32 t; ...; p48[24]=(u8)t`),
ternary, `if/else` with swapped branches, `u8`/`int`/`u32` types for the
bit variable, mask-as-`u32`-local, mask-as-`u8`-local, mask-as-parameter,
`%2` instead of `&1`, volatile pointer, address-taken local, speculative
precomputation of both branches, separate-statement splits
(`b = s[10]>>4; b &= 1;`). The compiler either collapses the diamond to
`beq; eors; strb` or (ternary) re-derives it as `b ^ ((s[35]>>7)&1)`.
The ROM's explicit diamond shape + truncation cannot be produced.

Because the diamond collapses without the cast, the divergence is not
just 4 bytes — all downstream code shifts by 2 bytes (branch/pool
targets move), so the function cannot be made byte-identical.

### Secondary divergences (in best attempt)

- **Scheduler ordering** in the `p48[26]` lookup block: ROM computes
  `jj=(s8)s[117]` (`ldrb`+`lsl#24`/`asr#24`) *before* loading the table
  entry `e` (`ldr r1,[r1]` at `0xDA50`); agbcc hoists the independent
  `e` load earlier. Probes show the choice is anti-correlated with the
  `(s8)` codegen (`ldrsb` vs `ldrb`+extend): e-as-variable → right jj
  codegen but wrong order; e-inline → right order but `ldrsb`. No probed
  shape gives both.
- **Register allocation**: ROM keeps table `0x08173978` in `ip` and
  `0x02005030` in `r8` across long live ranges; my attempts keep them in
  lo regs (or emit a dead `mov ip,r2`). Reproducing the pressure needs
  the exact live-range structure, which I did not converge on.
- **Second EWRAM store**: ROM recomputes `(s8)tbl[s[28]]` from scratch
  for the `pairs[pi].y` store address (via `ip`); my attempt either
  reuses the register (wrong: `strh [r4,#2]`) or drops the `+2`.

### Semantics mapped (for future/recomp use)

`s` = slot struct (u8*), `p48 = s+48`.
1. `sub_080042B8(s+112)` (decrements a counter; drives a state machine).
2. `p48[24] = (s[35]&0x80) ? (1^((s[10]>>4)&1)) : ((s[10]>>4)&1)`;
   `p48[25] = (s[10]>>5)&1`.
3. `p48[26] = *(u8*)( *(u32*)(*(u32*)(s+112) + s[116]*4) + (s8)s[117]*2 )`.
4. If `(s8)tbl_08173978[s[28]] == -1` return; if `s[30] == p48[26]` return.
5. `ptrA = *(u32*)(tbl_08173654[s[28]] + s[29]*4)`; `s[30] = p48[26]`;
   cache `p48[8]` (=s+56) if changed; `r3v = *(ptrA + p48[26]*8 + 5)`.
6. EWRAM pair array at `0x02005030`, indexed by `(s8)tbl_08173978[s[28]]`
   (8-byte entries, two s16 halves): if `pair.x != (s[28]<<8|s[29])` or
   `pair.y != r3v`, store both.
7. `row = tbl_08173760[s[28]] + s[29]*4`; `p = row + *(u32*)row + r3v*20`;
   `sub_0800244C(p, *(u16*)(p48+22)*32 + 0x10000)`; `p += 12`;
   `sub_08002904(p, s[31]>>4, tbl_081738F2[s[28]*2])`.

### Idiom discoveries (new)

- `ldrsb Rd,[Rn,Rm]` with Rm=0 is agbcc's codegen for `(s8*)tbl[idx]`
  when the table pointer has signed-char type (probe: `g4/g5`); the same
  table accessed as `(s8)(u8*)tbl[idx]` gives `ldrb`+`lsl#24`/`asr#24`
  (probe: `h2`). Both forms occur for table `0x08173978` in this
  function — the source mixes `(s8*)tbl[...]` and `(s8)tbl[...]` views.
- `(v22<<5) + 0x10000` materializes as `movs r2,#128; lsls r2,#9`
  (no pool entry) — write the constant so the compiler can build it from
  shifts, or use `(128<<9)` if `0x10000` pools.
- `r3*20` strength-reduces to `(r3*4+r3)*4` (`lsls#2; adds; lsls#2`).
- Byte table with stride 2 (`tbl[s28*2]`, `lsls r0,r5,#1`) — likely
  `u8 tbl[][2]` or explicit `*2` indexing.
- Relative-offset tables: `row = base + *(u32*)row` (u32 offset added to
  its own address) — seen in the `tbl_08173760` walk.
