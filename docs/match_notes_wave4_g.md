# Wave 4 Batch G — Match Notes (worker G)

## MATCHED

### 0x08000CD4 TaskMgr_Update (130 B)
Byte-identical. See `mmbcc/src/wave4_g.c`.
- Task/object manager: iterates 3 entries of 0x18 bytes at 0x030023C8.
- Entry layout: +0 u8 state, +1 u8 flag, +2 u16 counter, +4 u32 arg, +8 u32 arg.
- Logic: if (state&9)==0: if (state&4)!=0: if (*(s16*)(e+2))==0: *e=2 else { e[2]--; if ((s16)e[2]==0) *e=2 }. If *e==2: if e[1]!=0 Task_Register(cnt, e[4]); sub_080002dc(e, e[4], e[8], 0x02000800).
- Outer loop repeats while *(u32*)0x030023C4 != 0.
- Idiom: `(s0 & 4)` needs inline asm `movs %0,#4; and %0,%1` — pure C puts AND dest in var reg (r1), ROM has dest r0 (const reg). Both encode as 0x4008; capstone renders ROM's as `ands r0,r1`.
- Calls sub_080002dc (0x080002DC) which is UNMATCHED — forward reference for coordinator.
- Pool (5 words) is at 0x08000D58, after the 130-byte code region.

## BLOCKED

### 0x08000978 HBlank_VCountUpdate (160 B) — 9-byte diff
151/160 bytes match. VCOUNT read + DISPSTAT VCOUNT-match update + IWRAM state at 0x03000400.

Semantics:
- vcount = *(volatile u16*)0x04000006 (saved to stack slot, reloaded 3x — requires `volatile u16` local)
- base = 0x03000400 (NOT hoisted; used via extern array `gIwram_03000400[]` at each site to prevent const-folding)
- if ((*(base+0x167) & 2)==0: set bit; if vcount==0: (*(u32*)(base+0x160))++; if vcount==*(base+0x166): call *(fn*)(base+0x15c) via _call_via_r0; *(u8*)0x04000005 = (vcount < *(base+0x166)) ? *(base+0x166) : 0; *(base+0x167) ^= 2

Byte-level diff (mine vs ROM):
- OR at 0x08000996: need `orrs r0,r1; strb r0,[r3]` (dest r0). Pure C `v|2` gives `orr r1,r1,r0` (dest r1). Fixed via inline asm `movs %0,#2; orr %0,%1` with `"=l"` (compiler picks r0).
- XOR at 0x08000A02: need `adds r1,r3,r0; movs r0,#2; ldrb r2,[r1]; eor r0,r2; strb r0,[r1]`. Best pure-C+asm gives `adds r1,r3,r0; ldrb r2,[r1]; movs r0,#2; eor r0,r2` (ldrb before movs). The combiner will not schedule movs before the load when the load defines the asm input. Tried: split asm (volatile disrupts regs), reordering (addr needs r0 free but xor_res occupies it). 4-byte order diff remains.

New idioms discovered:
- `volatile u16` local forces stack slot with `strh [sp]` + `mov r0,sp; ldrh r0,[r0]` reloads.
- Direct absolute indexing via `extern u8 base[]` (not hoisted local) keeps base in r2 within blocks, reloads after calls.
- `and r0,r0,r1` and `ands r0,r1` are the SAME encoding (0x4008); capstone renders 2-operand form.

### 0x08017F8C ObjInit_TypeA (200 B) — structural diff
Object initializer with TWO branches (s[0x10]==2 vs !=2), each with duplicated idx-calc.

Semantics:
- ChipSlot_Setup(s, 0x21c, 0); ChipSlot_IncUse(s, 0)
- idx = (*(u8*)(0x020031E4 + ((*(u16*)0x081705B0 >> 4) << 1)) & 3); clamp to 3
- s[0x45] = (s[0x45] & -0xd) | (idx<<2)
- If s[0x10]==2: s[0x22]=0x11; *(s+0x58)=0x600; Vec2_AddMirrored(s, 0x3300, 0xffffe100)
- Else: s[0x22]=0x0c; *(s+0x58)=0x706; Vec2_AddMirrored(s, 0x2c00, 0xffffeb00)

Blockers:
- The `-0xd` mask: ROM does `movs r0,#0xd; rsbs r0,r0,#0` (runtime negation). Pure C `& -0xd` with u8 operand gets optimized to `movs r0,#0xf3` (8-bit truncated immediate).
- The idx-calc `movs r1,#3` comes BEFORE `ldrb` in ROM; pure C schedules ldrb first.
- Pool layout: ROM has separate pools for each branch; compiler merges differently.

### 0x0801DCC0 ObjInit_TypeB (122 B) — dest-reg diffs
Object initializer, straight-line.

Semantics:
- *(s+0x6c)=0; s[0xa] |= 3 (as two ORs: `2|t` then `|1`); ChipSlot_Setup(s, 0x501, 0); ChipSlot_IncUse(s, 0xb)
- s[0x41] = (s[0x41] & -0xd) | 4
- idx calc from *(u16*)0x081705B2; s[0x45] = (s[0x45] & -0xd) | (idx<<2)
- s[0x22] = s[0x12]; *(*(s+0x28)+0x21) = 8

Blockers:
- Double-OR `s[0xa] = 2 | s[0xa] | 1`: ROM does `movs r0,#2; orr r0,r1; movs r1,#1; orr r0,r1` (both dest r0). Pure C and various asm formulations either pick wrong dest regs or add extra moves. The `"=l"` + earlyclobber approach gets close but leaves a redundant `add r0,r1,#0`.
- The `-0xd` mask issue (same as above).

## Recomp-relevant discoveries
- 0x08000CD4: Task manager at 0x030023C8 (3 entries), counter at 0x03002410, flag at 0x030023C4, calls Task_Register and an unmatched 0x080002DC.
- 0x08000978: VCOUNT/DISPSTAT handler; IWRAM 0x03000400 state block (0x15c callback ptr, 0x160 counter, 0x166 compare byte, 0x167 flag).
- 0x08017F8C / 0x0801DCC0: Object initializers using ChipSlot_Setup/IncUse, Vec2_AddMirrored; ROM table at 0x081705B0, EWRAM table at 0x020031e4.
