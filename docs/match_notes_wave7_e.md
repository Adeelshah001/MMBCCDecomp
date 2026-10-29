# Wave 7 Batch E (TAG=E) Match Notes

Worker: Wave 7 matching-decompilation worker (TAG=E)
Date: 2026-10-20
Batch: 50 functions, leaves-up LARGE layer (120–956 bytes), all n_bl=0 (verified by direct disassembly — no `bl` mnemonics found).

## Summary
- MATCHED: 2
- BLOCKED: 1 (systematic register allocation divergence)
- NOT_ATTEMPTED: 47 (time constraints)

## MATCHED (2)

### Rank_FromValue @ 0x08047538 (154 B, 0 diffs, old_agbcc)
s8 switch with jump table: cases 0,5,10,15,20,25 map to 0,1,2,3,4,5; default/out-of-range returns 0.
- Prologue: `movs r2,#0` (no push — true leaf); `lsls r0,#24; asrs r0,#24` (s8 sign-extend); `cmp r0,#25; bhi` (unsigned range check).
- Jump table base from pool at 0x0804754c (value 0x08047550); 26 entries.
- Each case: `movs r2,#N; b` to shared `adds r0,r2,#0; bx lr`.
- Key: old_agbcc does NOT emit `push {lr}` (main agbcc does); old_agbcc matches exactly.
- C: `/tmp/wave7_e/w7e_08047538.c` (section `.text.w7e_08047538`).
- Note: isolated build has 2-byte align pad at end (156 vs 154); first 154 bytes identical.

### FilterCopy @ 0x08025578 (122 B, 0 diffs, main agbcc)
u8 filter-copy with forward/backward modes.
- Params: `(u8 *p, u8 a, u8 b)`; `if (a>6) a=0; if (b>1) b=0`.
- Base pool 0x082297E8; `n = *(u16*)(base+28)`; `src = *(u8**)(base + a*4)`; `dst = *(u8**)(p+8)`.
- If b==0: forward loop (src++ after n--); else: backward (src += n-1, then src-- after n--).
- Loop body: `v = *src; if (*(u8*)(*(u8**)(p+4) + v)) *dst++ = v;` with u16 n-- (lsls/lsrs wrap).
- Critical ordering: n-- BEFORE src++/src-- (not post-increment in load).
- C: `/tmp/wave7_e/w7e_08025578.c` (section `.text.w7e_08025578`).
- Note: isolated build has 2-byte align pad at end (124 vs 122); first 122 bytes identical.

## BLOCKED (1)

### Script_StepState @ 0x0803F480 (964 B) — register allocation divergence
Large switch (24 cases, 0..46 even, jump table at 0x0803F4CC) on a state byte looked up through two index tables.
- Semantics: `q = p+0x46A4; flag = (sel==0)?1:0; v = q[p[0x464C + p[0x46A0] + sel]]; switch(v) { case 0,2: ...=16; ... case 44,46: ...=48; } q[p[0x464C + p[0x46A0] + flag]]++;`
- Blocker: ROM keeps index sum in r1 (`adds r1,r0,r2`) and loads 0x464C fresh into r6 (`ldr r6,[pc]`). Both main and old_agbcc put the sum in r0 (`adds r0,r0,r2`) and fold 0x464C via `subs r1,#0x54` (0x46A0-0x54). The fold is impossible in ROM because r1 is live (holds sum).
- Tried: main/old_agbcc at -O2/-O1/-Os; explicit parens `*(p+0x464C+(p[0x46A0]+sel))`; u32 k-local (gets forward-substituted); `register u32 k __asm__("r1")` (pins r1 function-wide, breaking param allocation: p→r2, sel→r3); block-scoped pin (same issue in gcc-2.95).
- The `adds r1,r0,r2` vs `adds r0,r0,r2` is a systematic allocator difference. May need a different source structure or compiler version.
- Best C: `/tmp/wave7_e/f480_best.c` (matches flag, q, dispatch, jump table; diverges at index computation).
- True extent 964 bytes (956 code + 8 tail pool at 0x0803F83C); batch size 956 excludes tail pool.

## NOT ATTEMPTED (47) — brief triage notes
- 0x080039A4/0x08003CB8 (456/452 B): Complex fixed-point arithmetic with ldrsh table lookups; same family as 0x08003408/0x08003508.
- 0x08000F28 (266 B): HW init (straight-line, many pools: 0x0400010C, 0x04000200, etc.); pools follow function (302 B total extent).
- 0x0804DDA0/0x0804DEE8 (196/182 B): Signed/unsigned division routines (binary long-division with rors/tst bit tricks).
- 0x08047538: MATCHED (see above).
- 0x08025578: MATCHED (see above).
- 0x08028880 (126 B): Struct init with bit tests (p=0x0200B810); close — p in r3 vs ROM r4.
- 0x0800C50C (122 B): Palette blend (5-5-5 RGB); close — allocation differs.
- 0x080107CC (120 B): Complex bit magic (lsls/lsrs sequences).
- 0x0804BCDC (168 B): ARM code (not Thumb) — needs ARM disassembly.
- Remainder: various complex functions; time did not permit.

## New idioms / observations
- old_agbcc omits `push {lr}` for true-leaf switch functions where main agbcc emits it (0x08047538).
- Jump table base pool: `ldr r1,[pc]` loads table base from a pool word immediately before the table (0x0804754c → 0x08047550).
- Filter-copy loop ordering: n-- before src++/src-- (separate instructions, not post-increment).
- u16 loop counter decrement via `lsls r0,#16; lsrs r3,r0,#16` (wrap).
- The `adds r1,r0,r2` (sum into r1, reusing dead const reg) vs `adds r0,r0,r2` allocator difference appears systematic for `p[const1 + p[const2] + idx]` shapes — worth investigating as a general pattern.
