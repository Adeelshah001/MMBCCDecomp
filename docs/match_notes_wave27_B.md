# Wave 27-B Match Notes (Worker B: .s sed + scheduler family)

## Summary
- **MATCHED (1):** 0x080482d8 (Dispatch_080482D8, 168 B, 0 diffs, main agbcc)
- **BLOCKED (3):** 0x0803643c (patch script delivered), 0x0801f254, 0x08003fc8

All staging in `staging/wave27_B/`. Section names `.text.w27b_<addr>`.

---

## MATCHED

### 0x080482d8: Dispatch_080482D8 (168 B, 0 diffs, main agbcc)
State machine with indirect dispatch via `_call_via_r1` thunk.

**What it does:** Switch on `s[3]`. Case 0: calls `Call4E60_4E44()`, `PalModeSet_4DFC(g_02004F80[2])`, `s[3]++`, falls through. Case 1: computes `r5p = s+0x46a4`, `idx = *r5p`, `fn = ((u32*)0x08234328)[idx]`, `ret = fn(s)` (u8 return). Dispatches on ret: 0→return 0; 2→`s[2]=4,s[3]=0,*r5p=4,*(s+0x46a5)=0`; 5→`s[2]=4,s[3]=0,*r5p=ret,*(s+0x46a5)=0`; 6→`s[2]=4,s[3]=0,*(s+0x46b7)=ret`; else→`s[2]=3,s[3]=0`. Returns 0.

**True extent:** 168 B (0x080482d8–0x0804837f). Pools: 0x02004F80, 0x08234328, 0x46a4, 0x46a5 (x2, must not CSE), 0x46b7.

**Decisive idioms:**
1. **Real indirect call, not inline asm:** `ret = ((u8 (*)(u8 *))fn)(s)` with `fn` pinned to r1 emits `bl _call_via_r1` naturally (agbcc -mthumb-interwork). The w26c inline-asm version caused the phantom `adds r1,r2,#0`.
2. **u8 ret pinned to r2:** `register u32 retr __asm__("r2") = ((u8(*)(u8*))fn)(s)` — the u8 return zero-extends via `lsls r0,r0,#24; lsrs r2,r0,#24`, and pinning to r2 kills the phantom `adds r1,r2,#0` copy.
3. **Table base pinned to r1:** `register u32 tblv __asm__("r1") = (u32)g_08234328` ensures the table address is in r1 for the `adds r0,r0,r1` and the call. **CATCH:** Do NOT clobber r1 in a barrier while tblv is live — gcc eliminates the init load (miscompile).
4. **Opaque barrier for offset:** `u32 off = (u32)g_46A4; __asm__ volatile("" : "+r"(off) : : "r5")` prevents coalescing into r5v, forcing `ldr r0; adds r5,r4,r0`.
5. **Temp vars for grouped movs:** `u8 zero = 0, four = 4;` groups the `movs` instructions (scheduler). Declaration order controls mov order.
6. **Dual pins for offset/address:** In each ret case, pin offset to r2 (or r1) and address to r0 (or r1) to get ROM's exact `ldr; adds; strb` sequences. Example ret==2: `register u32 off2 __asm__("r2"); register u32 pp2 __asm__("r0"); ... off2 = ...; pp2 = (u32)s + off2; *(u8*)pp2 = zero;` → `ldr r2; adds r0,r4,r2; strb r1,[r0]`.
7. **u32 pins for zero/four:** `register u32 zero __asm__("r0") = 0; register u32 four __asm__("r1") = 4;` forces specific regs for the movs (ret==5, ret==6).

**Verification:** Hardened protocol PASS (clean-room recompile, link at 0x080482d8, objcopy -j .text.w27b_080482d8, dd with file-offset skip, cmp -l zero diffs, non-empty asserts at every step, 168 B exact).

**Staged:** `staging/wave27_B/w27b_080482d8_MATCHED.c` (also `v_080482d8/f.c` working copy).

---

## BLOCKED

### 0x0803643c: WalkBits_0803643C (444 B, 60 diffs — patch script delivered)
Table-walk/bit-test function. Calls `SelBlob_Ret` (0x0800303C).

**True extent:** 444 B (0x0803643c–0x080365f8). Pools: 3× 0x0200BCE8, 2× 0x0822EED8.

**Blocker:** Two-fold: (1) The 0x10000 materialization for u16 increments, (2) Register allocation divergence (gcc r5/r7/r9 vs ROM r6/r8/ip/r9).

**The 0x10000 problem:** ROM has three instances of u16 increment as:
```
lsls r0, rX, #16
movs r1, #128
lsls r1, r1, #9    ; r1 = 0x10000
adds r0, r0, r1
lsrs rY, r0, #16
```
gcc's loop optimizer transforms `cnt++` (u16) into `adds rX,#1` + shifts, avoiding the 0x10000 entirely. In non-loop contexts, gcc DOES emit the 0x10000 pattern, but hoists it out of loops (w24d: 14 -fno-* flags failed, undefeatable).

**Deliverable:** `staging/wave27_B/w27b_0803643c_patch.py` — Python script that converts gcc's loop-optimized `add r0,rX,#1; lsl r0,r0,#16; lsr rY,r0,#16` to ROM's 0x10000 pattern at the 3 sites (cnt++ x2, slc++ x1). Usage: `python3 w27b_0803643c_patch.py file.s` (modifies in-place; GAS recalculates pool offsets).

**Remaining:** Register allocation divergence. The v3 C (staging/wave25_D/w25d_0803643c_v3.c) has 60 diffs beyond the 0x10000. Needs C-level register pin work (coordinator-level). The patch script is a building block, not a complete solution.

### 0x0801f254: Reset_0801F254 (164 B, 8 B short — BLOCKED)
Struct reset + table-driven field update. Sibling of 0x0801fcd0/0x0802375c/0x0802298c.

**What it does:** Zeroes `*(s+108)`, sets `s[10] = (s[10]|2)&0xFE`, clamps `s[17]` to 39 (remainder to `s[121]`), computes `b = s[120] | ((s[35]&15) ? 0x100 : 0)`, calls `Wrapper_D728(s, b, s[121])`, table lookup via `0x081705b0`/`0x020031e4` to set `s[69]` bits, `s[34] = 16`, calls `F_20230(s, *(s+40), 0)`.

**Blocker:** v/c register allocation. ROM: v→r1, c→r2. The `s+121` address must go to r1 (ROM: `adds r1,r4,#0; adds r1,#121`), then copied to r2 via `adds r2,r1,#0` before the `cmp` (freeing r1 for the `b` computation). w26c best (156 B) via clobber-reservation gets v→r1,c→r2 but the s+121 address allocates r3 (not r1), cascading.

**Tried:** w26c f_best.c (clobber-reservation). Not re-attempted in w27b (time constraints after 0x080482d8 success).

**True extent:** 164 B (0x0801f254–0x0801f2f8). Pools: 0x081705b0, 0x020031e4.

### 0x08003fc8: Setup_08003FC8 (176 B, 150 diffs — BLOCKED)
Bitfield struct setup with high-register pressure.

**What it does:** `SetU32_4(s, 0x08004079)`, manipulates `s[13]`/`s[17]` bitfields, zeroes `s[18]`/`s[19]`/`s[12]`, stores param `b` to `*(s+8)`, derives fields from param `c` (`(c>>2)<<6`, `(c&3)<<6`), masks `*(s+16)` with `0x3FF`/`0xFFFFFC00` using param `d`, masks `*(s+14)` with `0xFFFFFE00`.

**Blocker:** High-reg allocator wall. ROM: `push {r4,r5,r6,lr}` + save r8/r9/sl; `sl=b`, `r8=(u8)c`, `r9=0`, `r5=c`, `r6=d` (all callee-saved, live across `bl SetU32_4`). Also needs `-33`/`-13` as `negs` (not `& 223`/`& 243`).

**Tried:** u32 pins: `sl`→b, `r8`→(u8)c, `r6`→(u16)d, `r9`→0. Prologue matches (sl, r8, r6, r9 set correctly). `u32 m=33; m=-m;` idiom produces `negs` but in wrong regs (r4/r7 vs ROM r2/r3). Body allocation diverges (150 diffs). The pins shift the entire allocation (s moves from r4 to r5).

**True extent:** 176 B. Pools: 0x08004079, 0x3FF, 0xFFFFFC00, 0xFFFFFE00.

---

## Lessons
1. **Real indirect call > inline asm:** For `_call_via_rN` thunks, a natural function-pointer call with the target pinned to rN is cleaner than inline asm and avoids phantom copies (0x080482d8).
2. **Pin the call result:** `register u32 retr __asm__("r2")` for a u8 return kills gcc's dual-homing copy (0x080482d8).
3. **Do NOT clobber a pinned reg:** A `"r1"` clobber on a barrier while a variable is pinned to r1 causes gcc to eliminate the pin's initializer (miscompile). Narrow clobber live ranges (0x080482d8).
4. **Temp vars group movs:** `u8 zero = 0, four = 4;` causes the scheduler to emit both `movs` before the stores. Declaration order = mov order (0x080482d8).
5. **Dual pins for address computation:** Pin offset and address separately to control `ldr`/`adds` dest regs (0x080482d8).
6. **u16 increment in loops:** gcc loop-optimizes `cnt++` to `adds #1`, avoiding the 0x10000 pattern. The 0x10000 pattern (`mov r1,#128; lsl r1,#9`) only appears in non-loop contexts or via sed (0x0803643c).
