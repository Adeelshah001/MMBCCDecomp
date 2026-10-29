# Wave 4 batch H worker notes (2026-10-20)

Worker: matching-C, batch H (66 medium functions, 40-119 bytes).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place,
never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) / `old_agbcc`.
Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i && agbcc -O2
-mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link each `.o` with section placed at ROM address via `ld -T`
linker script (with hand-assembled 2-byte Thumb stubs at callee addresses —
see wave3_b notes on `--defsym` veneer issue), `objcopy -O binary
--only-section`, byte-diff vs ROM. Scratch: `/tmp/wave4_h/`.

Result: 4 MATCHED, 1 BLOCKED (62 not attempted — time).

## Matched (4)

All in `mmbcc/src/wave4_h.c`, one `.text.w4h_<name>` section per function.
Absolute symbols in trailing `__asm__` `.set` block (GAS 2.42 rule).

| Addr | Name (tentative) | Bytes | Semantics |
|------|------------------|-------|-----------|
| 0x08000758 | Memcpy16 | 120 | 16-bit memcpy: aligns src/dst, uses CpuFastSet for bulk (32B+), CpuSet for unaligned/tail. No 0x01000000 bit (copy mode). |
| 0x080028D0 | Copy8_28D0 | 46 | If `*(u16*)(s+4)!=0` and `s[6]==0`: CpuFastSet copy 8 bytes from `s+*(u32*)s+(a<<5)` to `0x03002420+(b<<5)`. |
| 0x080216A8 | Init_216A8 | 42 | `*(u32*)(s+0x6C)=0; s[0xA]|=3 (two-step); ChipSlot_Setup(s, 0x1600, 0); *(u32*)(s+0x50)=0; *(u32*)(s+0x54)=0.` |
| 0x08011C80 | TableLookup_11C80 | 44 | Returns `0x0817A9C4 + (idx<<5)` (32-byte entries) if `0 < idx < GetLimit_11C50()` (0x4867), else NULL. |

## Blocked (1)

### 1. Memset16 @ 0x080006DC — BLOCKED (register allocation)

ROM (124 B): 16-bit fill with val-first signature `void F(u16 val, u8 *dst, u32 size)`.
Uses CpuFastSet (fill mode, 0x01000000) for bulk 32-byte chunks, CpuSet (fill
mode) for tail. Aligns dst, handles odd size.

**Precise diff**: Prologue mismatch.
- ROM: `adds r6,r1; adds r5,r2; lsls r0,r0,#16; lsrs r1,r0,#16; adds r7,r1,#0`
  (val truncated to r1, then copied to r7 — live-range split: r1 for early
  uses `strh r1,[r6]` and pat computation, r7 for late `strh r7,[sp+4]`).
- Mine: `adds r5,r2; lsls r0,r0,#16; lsrs r7,r0,#16; adds r6,r1`
  (val directly to r7, no r1 intermediate; also different assignment order).

**Tried**:
- Basic C with `u16 v = val` → spills v to stack early.
- Separate `w` variable for CpuSet source → keeps v in r7 but no r1 copy.
- `v1 = val; v2 = v1` two-variable → compiler merges to single r7.
- `asm volatile("" : "+r"(d))` barriers → fixes assignment ORDER (d,n,v) but
  not the r1/r7 split.
- old_agbcc → same prologue as main agbcc.

The `lsrs r1` + `adds r7,r1` sequence indicates the original compiler performed
live-range splitting (keeping val in caller-saved r1 for pre-call uses, copying
to callee-saved r7 for post-call use). This agbcc allocates val directly to r7.
Not reproducible with C constructs tried.

**Recomp relevance**: This is a 16-bit memset (val, dst, size). The CpuFastSet
uses fill mode (bit 24 set), CpuSet uses fill mode. The `(n<<10)>>11` for the
tail count equals `n/2` (n even, <32).

## New idioms discovered

1. **Hoisted shift-truncation**: `(u32)(u8)b << 5` computed at prologue gives
   `lsls r2,r2,#24; lsrs r2,r2,#19` (net `<<5` with truncation). If the shift
   is done later, compiler emits separate `lsls #24; lsrs #24; lsls #5`.
   (Used in Copy8_28D0.)

2. **Two-step OR for exact sequence**: `v=2; v|=s[0xA]; v|=1; s[0xA]=v` gives
   `movs r0,#2; ldrb r1; orrs r0,r1; movs r1,#1; orrs r0,r1; strb`
   whereas `s[0xA] |= 3` gives `ldrb; movs r1,#3; orrs; strb`.
   (Used in Init_216A8.)

3. **Stepwise count for CpuSet**: `cnt=n; cnt&=0x1F; cnt>>=1; CpuSet(s,d,cnt)`
   gives `movs r2,#31; ands r2,r4; lsrs r2,r2,#1` whereas
   `CpuSet(s,d,(n&0x1F)>>1)` may allocate the `&` to r0.
   (Used in Memcpy16.)

4. **Hand-assembled stubs required**: For `bl` callees, `--defsym` causes ld
   to insert `__*_from_thumb` veneers. Must assemble 2-byte Thumb stubs
   (`.thumb_func; bx lr`) and place at real callee addresses via linker script.
   (Confirmed from wave3_b notes; verified working for CpuFastSet/CpuSet.)

## Recomp-relevant discoveries

- **WRAM 0x03002420**: Destination base for Copy8_28D0 and DecompCopy_288C
  (not yet matched). Likely a sprite/OAM or tile buffer (32-byte strides).
- **ROM table 0x0817A9C4**: 32-byte entries, indexed by u16 with limit 0x4867
  (from GetLimit_11C50). TableLookup_11C80 provides bounded access.
- **Memcpy16/Memset16**: The game's 16-bit memory primitives. Memcpy16 does
  NOT set bit 24 (copy mode); Memset16 DOES set bit 24 (fill mode). Both use
  `& 0x1FFFFF` mask for CpuFastSet length (21 bits).
