# Wave 8 XL worker notes (TAG=XL)

## Audio_MixFragment — 0x0804bcdc, 168 B — MATCHED (naked+asm)
ARM (not Thumb) fragment in the sound-driver region: software sample-mix
inner loop (ldrsb fetch, mul volume scale, bic 0xff0000 mask, ror #8 adds,
str writeback). Entered via ARM `beq` from 0x0804BBB8; internal `ble` exits
to 0x0804BC74 (earlier ARM code); ends `add r0,pc,#1; bx r0` back to Thumb
at 0x0804BD84. Matched by direct naked+asm transcription (Thumb compiler
cannot emit ARM from C); precedent ArmTrampoline. GAS quirks hit:
`ldrsbne r0,[r3,r9]!` rejected -> emitted via `.inst 0x11b300d9`; objdump
renders `movs r9,lr,lsr #23` as `lsrs` (logical, not arithmetic).

## LoadHalfTables — 0x0800B520, 162 B — BLOCKED
Copies 6 halfwords from each of 3 source tables into EWRAM 0x02004E40+100:
for i in 0..2: if ap[i]==0 break; copy *(u16*)(ap[i]+j*2) ->
*(u16*)(0x02004E40+100+i*12+j*2) for j in 0..5. Byte 0x13: low 5 bits
cleared at entry, then (old & 31) | (i << 5). If broke early (i<=2), write
0x8000 to (0x02004E40+100+j*12) for j in 0..2.
Best result 164 B (old_agbcc -O2), first 99 bytes identical. Key ROM
behaviors reproduced via idioms: goto-outer loop keeps ap[i]==0 at loop
top (agbcc rotates for-loop into do-while); empty `__asm__ volatile("":::
"memory")` in inner loop defeats LICM so ap[i] reloads via [r5] each
iteration (ROM does NOT hoist it). Remaining gaps: (1) ROM loads pool to
r3 then `mov ip,r3`, keeping p in ip with r3 reused for the `[r3,#19]`
byte access (Thumb-1 ldrb can't use [ip,#imm]); my allocator puts p in r4.
Pinning p to ip makes `p[19]` degrade to mov+adds. (2) ROM hoists
r6=i*12, r5=&ap[i], r4=p+100 as three separate values in the outer loop;
mine fuses p into the address. Tried: u32 ap[3] vs u32 *ap=&a, v-hoisted
vs reloaded, parenthesized/different dest-expr associations, q=p+100 as
function-top local (q went to ip, wrong) and inner-block local (+8 B),
-O1/-Os (Os=160 B). The dual-copy (r3+ip) allocation looks like a
different compiler generation than our agbcc/old_agbcc produce.

## HwInit2 — 0x080007D0, 178 B — BLOCKED
Hardware/init: copies 14 words 0x0804E2DC->0x03000400 (0x03000438-56),
programs DMA3 (0x040000D4: src=0x080001BC, dst=0x03000438, cnt=0x84000048),
sets *(u32*)0x03007FFC, zeroes fields at 0x03000438+off (288,292,296,300,
302,312,324,336,352,364,380,0x12f), programs 0x04000208=1, 0x04000200=0x2005,
0x04000004=40, sets byte 0x12d=1. Best 220 B (old_agbcc -O2), first 99 B
identical. Prologue matched via idioms: pin r4v to r4 (forces r4v load
first), pin src to r3, pin dst to r2, scope dma local after copy loop
(prevents constant-load hoisting). Blockers: (1) Two dead ldrb in ROM
(ldrb r0,[r2] before strb r3,[r2]; ldrb r2,[r0] before strb r1,[r0]) —
dummy expression statements optimized away; volatile loads reproduce them
but cause 46 B bloat (volatile disables optimization); hardcoded asm hits
"lo register required" (compiler picks r8 for dummy). (2) 42 B bloat from
pinned-register constraints even without dead-load hacks.

## DmaSetupBits — 0x08000A1C, 178 B — BLOCKED
DMA setup: if (*(u32*)(0x03000400+368)==0) return; loads src/dst from
+360/+364, programs 0x040000B0/B8, adjusts by (r3&0xffff)<<(1|2) based on
bits 26/21-22/23-24, spin-waits for bit 31 clear, writes final regs. Best
172 B (old_agbcc -O2), 6 B short with scattered diffs. Structure is
correct; differences likely in bit-test instruction ordering, spin-wait
loop codegen, and pool layout. Tried: temp vars for CSE of (r3&mask),
scoped dma locals, explicit int cast for sign check.

## sub_080039A4 — 0x080039A4, 456 B — BLOCKED (analysis only)
Fixed-point sprite/OAM transform loop. Structure: loads 12-byte record
array pointer from struct field, iterates with ip+=12; per-record does
extensive muls/asrs #8 fixed-point math with table lookups (pools at
0x0816E2D4/0x0816E2EC/0x0804E05C), writes 32-bit + halfwords to a cursor
buffer advancing 8 bytes/record. Early-exit if computed count < threshold.
Loop-back edge at 0x8003B34. Extremely intricate instruction scheduling;
not attempted beyond structural analysis.

## sub_080024BC — 0x080024BC, 166 B — BLOCKED (analysis only)
Fixed-point position-update loop. Prologue extracts (u22) count from
struct field, computes base pointers; loop does muls-based scaling with
ldrsb table lookups, writes to pool-addressed struct (0x8002564), updates
accumulators, decrements counter. Intricate; not attempted beyond analysis.

## ComputeFields — 0x0804CFD4, 180 B — BLOCKED
Two-block struct computation (see results.tsv). Best 180 B exact size with
old_agbcc but diffs at byte 100. ROM reloads p[0] twice (aliasing prevents
CSE); register allocation (p in r2) not reproduced. Closest: direct p[0]
uses without b0 local.

## BoundsCheck — 0x08006014, 176 B — BLOCKED
Bounds validation with s8 arithmetic. Best 196 B (20 B over). Logic
structure needs re-derivation.

## Remaining 23 — BLOCKED (triage only)
Complex functions (loops, dispatchers, division routines, inits) with
intricate register allocation or algorithms. Not attempted beyond triage;
see results.tsv for per-function notes. The two division routines
(0x0804DDA0, 0x0804DEE8) are binary div/mod algorithms. The 0x080033xx-
0x08003xxx region functions are likely related to the 0x080039A4
sprite-transform family.
