# Wave 7 TAG=C Matching Notes

## ObjInit_TypeC @ 0x08021594 (148 B) — MATCHED (old_agbcc, 0 diffs)

Object initializer; `ChipSlot_Setup(s, 0x1600, 0)`.

### Source (verified byte-identical)
```c
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern u8 gEwram_02003670[];

__attribute__((section(".text.w7c_08021594")))
void ObjInit_TypeC(u8 *s)
{
    u8 t; u32 idx; int mask = -13; u8 *p; u32 sh;
    register int c __asm__("r0");

    *(u32 *)(s + 108) = 0;
    t = 2; t |= s[10]; s[10] = t | 1;
    ChipSlot_Setup(s, 0xB0 << 5, 0);
    ChipSlot_IncUse(s, ((u8 *)0x08227020)[s[17]]);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    __asm__("movs %0,%1" : "=r"(c) : "r"(idx));
    if (c > 3) idx = 3;
    p = s; p += 0x45; sh = idx << 2;
    *p = (*p & mask) | sh;
    {
        u8 four = 4;
        u8 *q = s; q += 0x11A0;  // via gEwram_02003670[0x11AE] extern
        *q = four;  // actually: gEwram_02003670[0x11AE] = 4
    }
    // s16 table at 0x08227192, etc.
}
```

### Key idioms
- **ObjInit clamp** (old_agbcc): `u32 idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;` then `register int c __asm__("r0"); __asm__("movs %0,%1": "=r"(c): "r"(idx)); if (c > 3) idx = 3;`
- `int mask = -13;` as variable (literal `-13` folds to `& 243` on u8 targets)
- Nested block declaring `u8 four = 4;` *after* pointer computation to get `adds,adds,movs,strb` order
- `gEwram_02003670[0x11AE]` via extern symbol → two pools + adds; literal base folds to single `0x0200481E`
- Anti-CSE zero: `u8 z; __asm__("movs %0, #0": "=r"(z));` prevents gcc keeping zero live
- `ChipSlot_Setup(s, 0xB0 << 5, 0)` for 0x1600

## ObjInit_2184C @ 0x0802184c (164 B) — MATCHED (old_agbcc, 0 diffs)

Table-driven chip slots + s16 params; two-statement base ldrsh idiom.

### Key idioms
- **Barrier-forced table loads**: `u16 *tbl = (u16 *)0x08227028; __asm__ volatile("" : "+r"(tbl));` forces the `ldr` to be scheduled before the barrier (which is placed right after init, before use). Without the barrier, gcc schedules the `ldr` late (after the `ldrb`).
- **r2-pinned zero**: `register u8 z __asm__("r2"); __asm__("movs %0, #0" : "=r"(z));` then `s[0x22] = z;` keeps z in r2 live for later `s[0x12] = z`. The `s+0x22` address is computed via `u8 *p = s; p += 0x22;` BEFORE the `movs` to get the ROM's order (adds, adds, movs, strb).
- **off-before-tbl+=2**: For the second ldrsh, compute `u8 idx = s[17]; u32 off = idx << 2;` BEFORE `tbl += 2;` to get the ROM's order (ldrb, lsls, adds r1,#2, adds).
- **s16 table at 0x08227036** (NOT 0x08227192 — that was the 2298c pool; corrected during matching).
- The `(s[17] << 2) + tbl` order (not `tbl + (s[17]<<2)`) gives `adds r0, r0, r1` (ROM) vs `adds r0, r1, r0` (mine).

### Source structure
```c
ChipSlot_Setup(s, tbl1[s[17]], 0);  // tbl1 = (u16*)0x08227028, barrier-forced
ChipSlot_IncUse(s, tbl2[s[17]]);    // tbl2 = (u8*)0x08227020, barrier-forced
// clamp block (same as TypeC)
// s[0x22] = 0 via r2-pinned z
{
    u8 *tbl = (u8 *)0x08227036;
    q = (s16 *)((s[17] << 2) + tbl);
    *(u32 *)(s + 0x50) = q[0] << 8;
    {
        u8 idx = s[17];
        u32 off = idx << 2;
        tbl += 2;
        q = (s16 *)(tbl + off);
        *(u32 *)(s + 0x54) = q[0] << 8;
    }
}
s[0x12] = z;  // z still in r2
```

## In-progress / Blocked

### ObjInit_211EC @ 0x080211ec (164 B) — BLOCKED on tbl+4 scheduling
Similar to 2184C but with `ChipSlot_Setup(s, 0x1600 | tbl[s[17]], 0)` where tbl is u8* at 0x08226F34, and `ChipSlot_IncUse(s, 1)` (constant). The s16 table at 0x08226F46 uses `(tbl + 4 + (s[17]<<3))` for the first access, then `tbl += 6` for the second. The challenge: gcc folds `tbl+4` into the pool (0x08226F4A) if tbl is a literal, or does `adds r0, #4` (folding into off) instead of the ROM's `adds r1, r2, #4` (tbl+4 in separate register). Using an extern symbol prevents pool folding but the instruction scheduling remains difficult. The r3-pinned zero (for s[0x22] and s[0x12]) works.

### ObjInit_1B47C @ 0x0801b47c (164 B) — IN PROGRESS
Vec2_AddMirrored variant; s in r6 (achieved via natural allocation). ChipSlot_Setup(s, 0x255, 0) with pool-loaded 0x255. The s16 table at 0x0822672a has complex scheduling for the Vec2 x/y computation. The `tbl+2`, `tbl+4`, `tbl+6` offsets with specific register allocation (r4 for tbl) are difficult to reproduce exactly.

### Gfx_Load4Tiles @ 0x080097cc (148 B) — IN PROGRESS (37 diffs)
4-tile VRAM copy via Memcpy16. The prologue and v computation match. The table load order (dst0 before t1) and r5/r6 allocation for t1/p need work. The `a<<2` scheduling (ldr before lsrs) is the main blocker.

### Validate_263A4 @ 0x080263a4 (140 B) — IN PROGRESS (52 diffs)
Field validator with s8 loop i=1..9. The loop matches but the fail-block positioning differs (ROM has fail block in middle at 0x8026408, mine at end). The `t = s+1` in r6 works. The control-flow layout is the blocker.

### Others (not started or minimal progress)
- ObjInit_20B60, ObjInit_3FC8, BlendPalettes_0DDE4/21B3C/224E4, Text_3AC4C, ObjInit_2298C, Gfx_96BC, DmaQueue_02A1C: Behavior notes available in match_notes_wave6_l2.md, but not yet re-derived under the hardened protocol.

## Callee addresses used
- ChipSlot_Setup: 0x0800D6E0
- ChipSlot_IncUse: 0x0800D9EC
- Vec2_AddMirrored: 0x0800DD4C (u8 *s, s32 x, s32 y)
- Text_SelectBlobIdx: 0x0804A378
- Memcpy16: 0x08000758 (u8 *src, u8 *dst, u32 size)
- TblGet11: 0x08026710
- CpuSet: 0x0804DB28

## Verification protocol
All matches verified via `/tmp/wave7_c/check.sh` which:
1. Compiles with old_agbcc (or main)
2. Links with minimal `ld` script placing `.text.w7c_*` at the target address
3. Uses `objcopy -j.text` (NOT `-j.text.<sec>` — the minimal link merges sections)
4. Asserts non-empty .o/.elf/.bin
5. Extracts ROM bytes via `skip = addr - 0x08000000`
6. `cmp -l`s the full extent (code + pools)
7. Reports "MATCHED" only on 0 diffs
