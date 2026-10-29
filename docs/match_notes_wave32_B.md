# Wave 32 Worker B Notes: 0x08006FE8 / 0x08024A30

## 0x08024A30 — ChipDispatch (268 B, no pool) — BLOCKED

**Semantics** (verified from disassembly):
```c
u8 ChipDispatch(u8 *s, u8 a, u8 b) {
    // r5=s, r7=a, sl=a, r6=b, r9=orig b, r8=0x1B0, r4=temp
    if (b > 29) return 1;
    q = *(u32*)(s+20) + (*(u8*)(*(u32*)(s+20)+0x1B0))*144;  // recomputed 4x
    if (CheckPair_258D8(q, b) == 2) return 5;
    if (*(u16*)(s+18) == 0) return (u16)F_0802493C(s, b);
    if (a >= *(u16*)(s+18)) return 1;
    if (CheckPair_258D8(q, b) == 0) {
        r4 = GetBoundedByte_18(s, a);
        DecByte(s, a);
        SetSlot_IfLE29(q, b, r4);
        return 0;
    }
    b = GetBoundedByte_18(s, a);
    r4 = GetStride4Byte20(q, orig_b);
    if (b == r4) return 0;
    SetSlot_IfLE29(q, orig_b, b);
    Sub_254E0(s, r4);
    DecByte(s, a);
    return 0;
}
```

**Variants** (28 total: w31 v1-v3 + w32 v1-v25):
- v1 (235): opaque asm prologue (perfect) + u8 pins; re-extension issues
- v2 (193): u32 pins + laundered decls; r7 not saved
- v3 (249): C-init + barriers; scheduler chaos
- v4 (238): barriers; worse
- v5 (232): w31v2 + pins; init order wrong
- v6 (248): barrier; worse
- v7 (224): mixed pins; prologue perfect
- v8-v10 (224-228): block-scoped r1 pin; no improvement
- v11 (223): C Q(); decl fixes
- v12 (222): no lim var
- v13-v14 (222-221): pin a7; unpin t4
- v15 (184): minimal pins (r8/r9/sl); s->r4, b->r5
- v16 (204): +t4->r4 pin; init perfect!
- v17-v18 (204): const via asm; perfect `mov r1,#216`
- v19 (202): init order fixed
- v20 (217): barrier; worse
- v21-v22 (202): u16 return for #16
- v23 (202→143): Q1 inline asm for first recompute
- v24 (141): Q inline asm for later recomputes
- v25 (140): t4 plain (extend at assignment)

**Best**: v25 at 140 diffs.

**Walls** (interdependent):
1. Init order: `mov sl,r7` vs `lsl r2` swap. C scheduler reorders; barriers make worse.
2. First q-recompute: ROM does `ldr r0` before const, and uses r1 directly (no `mov r1,r8`).
   Fixed via Q1 inline asm, but...
3. Inline asm Q() causes gcc to generate garbage (`mov r8, r0` clobbers pinned r8!).
4. t4: needs `adds r4,r0,#0; lsls r4,#24; lsrs r4,#24` (extend at assignment).
   Pinned -> no extend; plain -> extend but may not choose r4.
5. F_0802493C: needs #16 extend, requires u16 return (dishonest for u8 function).

**Recommendation**: Sanctioned asm transcription. 28 variants exhaust C design space.

## 0x08006FE8 — PatternRowsBlit (264 B, no pool) — BLOCKED

**Semantics** (from disassembly):
```c
void PatternRowsBlit(u8 *ctx, u16 *p1, u16 p2, u16 p3, u8 p5, u8 p6) {
    // sl=ctx, r9=(s16)p3, r8=(s8)p5, r7=(u16)p2 then W, r6=(u8)p5 then i
    // 16B frame: [sp,0]=p1, [sp,4]=(u16)p3, [sp,8]=(u8)p6, [sp,12]=y<<16
    if ((s16)p3 < 0) return;
    if ((s16)p3 >= (s8)FlagA_8680(ctx)) return;
    if ((s16)p2 < 0) { p5 = (u8)((s8)p5 + p2); p2 = 0; }
    bound = (s16)p2 + (s8)p5;
    if (bound >= (s8)FlagA_8628(ctx))
        p5 = (u8)(FlagA_8628(ctx) - p2);
    if ((s8)p5 <= 0) return;
    W = 0xB000;
    if (p6 == 2 && (((p3-1)>>1)&1)) W = 0xC000;
    else if (p6 == 3) W = 0xC000;
    dst = GetPtr(ctx) + ((s16)p3 << ((s8)FlagA_8654(ctx)+1)) + p2*2;
    for (i=0; (s16)i < (s8)p5; i++) {
        SetIfXZero(dst, W | *p1++, 0);
        dst++;
    }
}
```

**Variants** (4):
- v1 (234): pure C with pins; prologue wrong (sub sp,#12)
- v2 (245): asm prologue + frame array; constraint errors
- v3 (211): h8 used, push correct; body mismatched
- v4: pure C, no pins; too short (260B, TRUNC FAILED)

**Walls**:
1. 16B frame with specific offsets; asm prologue must write [sp,#0/#4/#8].
2. r8/r9/sl must be saved AND used; gcc spills without pins.
3. Complex nested control flow with early returns; 6 params.
4. Loop uses u16 counter with (s16) compare and shift-first increment.

**Recommendation**: Needs more C variants or asm transcription. 4 variants is below the 5+ bar;
recommend 2-3 more focused attempts on the body structure before transcription.

## New idioms discovered

1. **Plain asm outputs are trusted**: `__asm__ volatile(... : "=r"(plain_u8))` —
   gcc trusts the output as (u8)-clean, no re-extension. Pinned (`__asm__("rN")`)
   outputs are DISTRUSTED, causing re-extension.
2. **Pinned r7 save/restore is unreliable**: sometimes saved (v1, v7, v13),
   sometimes not (probes, new-v2). Depends on whether gcc uses r7 as scratch.
   Do not rely on it; verify prologue bytes.
3. **`(216 << 1)` for 0x1B0**: materializes as `movs r1,#216; lsls r1,#1`,
   but only if r1 is free. Inline asm `mov r1,#216; lsl r1,#1; mov %0,r1`
   with `"=r"` output forces it.
4. **u16 return for #16 extend**: `return (u16)F()` in a u8 function optimizes
   to #24. Must declare function as u16 (dishonest) or patch.
5. **Statement-expression Q()**: `({ ...; })` with inline asm can force exact
   instruction sequences, but disrupts surrounding allocation and can cause
   gcc to generate incorrect code (clobbering pinned regs).

## Staged files

- `staging/wave32_B/w32b_08024a30_v1.c` … `v25.c` (25 variants)
- `staging/wave32_B/w32b_08024a30_BLOCKED.txt`
- `staging/wave32_B/w32b_08006fe8_v1.c` … `v4.c` (4 variants)
- `staging/wave32_B/verify.sh` (harness)
- `staging/wave32_B/rom_06fe8.bin`, `rom_24a30.bin` (264B/268B ROM extracts)
- `staging/wave32_B/dis_06fe8.txt`, `dis_24a30.txt`
