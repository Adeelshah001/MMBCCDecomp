# Wave 9 Batch D — Match Notes

## Matched (7)

### ShiftPair_Copy_800C @ 0x0800800c (36B, old_agbcc)
Copies two s16 values (shifted <<8) to word slots [8] and [9] of output struct,
then does a table lookup: `o[0x1A] = rom_table[idx]`.

**New idiom**: `u32 a = idx; a += (u32)romSym;` yields `adds r1,r1,r2` (result in
the addend's register) with the pool load staying late. This controls operand
order for the address computation.

### Ewram5160_Init_10508 @ 0x08010508 (36B, old_agbcc)
Struct init at EWRAM 0x02005160: `[0]=v (u8); [2]=[1]=[3]=0; [6]=[4]=0 (u16);
[70]=0 (u16 via split-adds q=p;q+=70); [72]=0`.

Uses existing `gEwram5160` from wave3_e.o — **strip the .set when landing**
(staging used a test-local .set only for standalone link).

### CheckPair_258D8 @ 0x080258d8 (32B, old_agbcc)
Checks two bytes at `[p + idx*4 + 20]`: returns 0 if first is 0, 1 if second
is 255, else 2.

Idiom: `((u32)idx << 16) >> 14` gives `lsls r1,r1,#16; lsrs r1,r1,#14` (mask +
x4 in one go). The `off += 20; q = p + off;` split ensures `adds r1,#20` before
`adds r1,r0,r1`.

### StoreIdx2_25638 @ 0x08025638 (28B, old_agbcc)
Stores a byte at `[p+idx+2]`, with a curious branch: if (idx>9) does
`p[idx+2]=val` via `r = q+idx; r[2]=val`, else does `q+=2; q[idx]=val`.
Both paths are semantically equivalent; the branch is a compiler artifact.

**New idiom**: `register u8 *q __asm__("r0") = p;` pins q to r0, preventing the
compiler from saving p in r3 when p is modified in a branch. The pin must be
a declaration-init (not a later assignment) to be honored.

### Ewram4E40_Init_0B4E4 @ 0x0800b4e4 (60B, old_agbcc)
Writes 0x8000 to 3 halfwords at `EWRAM 0x02004E40 + 136 + i*36` (i=0..2),
then sets bit 2 at `[0x02004E40+20]`.

Uses `gEwram_02004E40` (defined via `.globl`+`.set` in this TU since wave4_f.c
is not in the build).

**New idiom**: When the compiler systematically picks the wrong operand order
for `adds` (e.g., `adds r0,r0,r4` vs ROM's `adds r0,r4,r0`), use targeted
inline asm: `__asm__ volatile("add %0, %1, %2" : "=r"(dst) : "r"(a), "r"(b))`.
Note: GAS 2.42 requires pre-UAL `add`, not `adds`, in inline asm.

Other idioms used:
- `register u8 *p __asm__("r4") = base;` pins p to r4.
- `v = 0x8000;` as a separate assignment (not decl-init) prevents the scheduler
  from hoisting it before `p += 136`.

### Buf_RemoveAt_25290 @ 0x08025290 (64B, old_agbcc)
Removes the byte at `idx` from a `(buf,count)` list (buf at +0, count at +6):
saves `buf[idx]`, shifts `buf[idx+1..count-1]` down, writes 255 to the last
slot, decrements count, returns the saved byte. Returns 255 if `idx >= count`.

**New idiom**: The ROM reloads `count` from `[p+6]` three times (instead of
keeping it in a register). To match, do NOT use a `count` variable; read
`*(u16 *)(p+6)` at each use site. This reduces register pressure and matches
the ROM's aggressive reuse (r1 for count, then buf, then end).

### Check_2D440 @ 0x0802d440 (32B, old_agbcc)
Returns 6 if `(a != 2 && b == c && b != 0)`, else 0. The `&&` chain gives the
ROM's `beq`/`bne`/`beq` skip structure with a single `movs r3,#6` in the middle.

## Blocked (3)

### CtrTick5_400A8 @ 0x080400a8 (40B, 20 callers) — PARKED
Ticks a u16 counter at `0x020070F0+8`: `x = v + 0x8D94; t = x*5;
w = ((t&0xFF)<<8) | (u8)t; store; return reload`.

**Diff**: Best attempt (main agbcc, p pinned r2) gives
`ldrh r1,[r2,#8]; ldr r0; add r1,r1,r0` (ROM wants `ldr r3` for the constant,
then `adds r0,r1,r3`). The allocation divergence is in how the constant
0x8D94 is loaded and which register holds the intermediate.

Tried: old/main agbcc, pins on p/v/c/x, decl-init vs assignment, block-scope
pins, `-O1`/`-Os`, dummy param. None reproduces the ROM's `ldr r3` +
`adds r0,r1,r3` sequence.

### FlagBit_Set_11D68 @ 0x08011d68 (72B, 10 callers) — PARKED
Bitfield set/clear using `gEwram02005260` (0x02005260, in wave3_d.o).
ROM: `lsls r2,r0,#16; lsrs r4,r2,#16; lsls r1,r1,#24; lsrs r5,r1,#24;
cmp r4,#0; beq; cmp r4,#127; bhi; ldr r0; lsrs r1,r2,#19`.

Got pins s→r2 and i→r4 working individually, but the scheduler emits the v-mask
before s (ROM order is s,i,v), and folds `off=s>>19` into in-place
`lsr r2,r2,#19` (ROM: `lsrs r1,r2,#19`). Two separate `if`s fixed the branch
(`(i-1)>126` mis-opt), but the scheduler order remains wrong.

### Get_25654 @ 0x08025654 (40B) — PARKED
Returns `p[2+idx]` if idx<=9, 0 if idx>11, else `p[12+(idx-10)]`.

**Diff**: The scheduler interleaves the `pp` init (`add r2,r0,#0`) with the `i`
mask (`lsl r1,r1,#16; lsr r1,r1,#24`), producing `lsl; add; lsr` instead of
ROM's `add; lsl; lsr`. Tried: pins on pp (r2) and i (r1), volatile asm for pp,
reordering declarations, explicit volatile mask. The scheduler consistently
moves the independent `add` into the lsl/lsr delay slot. A true dependency
between pp and i is needed, but none exists in the source semantics.

## New Idioms Summary

1. **`a += (u32)romSym` with `u32 a = idx`**: Yields `adds r1,r1,r2` (result in
   addend's reg), pool load stays late. Controls operand order.
2. **Pin via declaration-init**: `register T v __asm__("rN") = <const/symbol>;`
   works. Later assignment (`v = const;`), block-scope decl-init, and computed
   init (`= *(u16*)(p+8)`) are IGNORED by the pin.
3. **Pin to prevent save**: `register u8 *q __asm__("r0") = p;` stops the
   compiler from saving p in another register when p is modified in a branch.
4. **Inline asm for adds order**: `__asm__ volatile("add %0,%1,%2" : "=r"(d)
   : "r"(a), "r"(b))` with pre-UAL `add` (not `adds`) for GAS 2.42.
5. **Reload instead of variable**: If ROM reads a memory value 3x, don't use
   a C variable; read it at each site to match register reuse.
6. **`q = p; q += 70;` split-adds**: Reproduces `adds r3,r1,#0; adds r3,#70`.

## Notes

- **Duplicate caught**: 0x0804DFA8 (MemCpy) was already MATCHED in Wave 9-C as
  `Memcpy_4DFA8` (94B). My 96B version was a duplicate — removed from batch.
  Always grep match_status.tsv for the address before starting, not just the
  wave8 duplicates.
- **Binutils outage**: `arm-none-eabi-as` vanished mid-task. The cached .deb
  was gone from /tmp (ephemeral). Downloaded fresh from
  `archive.ubuntu.com` and installed via `sudo dpkg -i`. If it recurs, the
  .deb is now at `/tmp/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb`.
- **Landing hygiene**: `gEwram_02004E40` is defined in wave4_f.c which is NOT
  in the build, so the `.globl`+`.set` was added to wave9_d_old.c. `gEwram5160`
  is in wave3_e.o (build), so extern only. `rom08172126` uses local `.set`.
