#!/usr/bin/env python3
"""Assemble docs/func_list_v2_3_addendum.txt from verified v2.3 findings."""
import struct
import gen_func_list_v2 as g

rom = g.rom
def u16(off): return struct.unpack_from('<H', rom, off)[0]

# --- 25 thunk-span D->B promotions with caller counts and known callees ---
# (caller counts from region-wide BL scan; callees from thunk_descent2.py;
#  all validate_target T=True; all callers visited-boundary genuine)
thunk = [
    # (off, ncallers, known_callees, was)
    (0x2BCE2, 3, ["2D7A0"], "contains_v1_02BD66"),
    (0x2BCF8, 1, ["2D7A0", "2FBA4", "2FC70"], "contains_v1_02BD14"),
    (0x2BD14, 1, ["2D7A0", "2FBA4", "2FC70"], "contains_v1_02BD66"),
    (0x2BD66, 31, ["2FC70"], "contains_v1_02BDEE"),
    (0x2BD72, 1, ["2D7A0", "2FC70"], "contains_v1_02BDEE"),
    (0x2BDEE, 1, [], "contains_v1_02C71E"),
    (0x2BDF6, 15, ["2D7A0", "2FBA4", "2FCFC"], "contains_v1_02BEA2"),
    (0x2BEA2, 3, ["2FCFC"], "contains_v1_02C71E"),
    (0x2C010, 1, ["2D7A0"], "contains_v1_02C6E6"),
    (0x2C068, 1, ["2D7A0", "2FC28"], "contains_v1_02C71E"),
    (0x2C196, 1, ["2D7A0", "2D5A8"], "contains_v1_02C71E"),
    (0x2C23C, 1, [], "contains_v1_02C6E6"),
    (0x2C2CE, 1, [], "contains_v1_02C71E"),
    (0x2C344, 1, [], "contains_v1_02C71E"),
    (0x2C3C0, 1, ["2D7A0", "2FC28", "3FACC"], "contains_v1_02C71E"),
    (0x2C4C0, 1, ["2D7A0", "2FC28", "3FACC"], "contains_v1_02C71E"),
    (0x2C5C0, 1, ["2D7A0"], "contains_v1_02C71E"),
    (0x2C5F6, 1, [], "contains_v1_02C6E6"),
    (0x2C618, 1, ["2D7A0"], "contains_v1_02C71E"),
    (0x2C64A, 1, ["2D7A0"], "contains_v1_02C71E"),
    (0x2C686, 1, ["2D7A0"], "contains_v1_02C71E"),
    (0x2C6B8, 1, ["2D7A0"], "contains_v1_02C6E6"),
    (0x2C6E6, 1, [], "contains_v1_02C71E"),
    (0x2C6EC, 1, ["2D7A0"], "contains_v1_02C71E"),
    (0x2C71E, 26, [], "contains_v1_02C7A4"),
]
# --- other D->B ---
other_d = [
    (0x033962, 1, ["04AD00"], "contains_v1_033AB2",
     "1 genuine caller (030B0C), calls known sub_0804AD00, tail-branches to known sub_08033AB2"),
]
# --- pointer-table discoveries ---
ptrtab = [
    (0x00A18, 12, "2-byte bx-lr stub; 12 table-runs"),
    (0x044F4, 29, "bx-lr-terminated body; 29 table-runs"),
    (0x11E98, 2, "12-byte bx-lr function; 2 table-runs"),
    (0x17084, 19, "12-byte bx-lr function (idem 11E98/20F58); 19 table-runs"),
    (0x20F58, 8, "12-byte bx-lr function (idem 11E98/17084); 8 table-runs"),
    (0x04C4FC, 2, "push{r4,r5} prologue, coherent body; 2 table-runs"),
]

lines = []
lines.append("# MMBCC func_list v2.3 addendum (Phase 2 unknown-region sweep, 2026-10-20)")
lines.append("#")
lines.append("# 32 tier-B additions: 25 thunk-span wrongful D-demotions (contains_v1_*")
lines.append("# misfire class, cf. v2.2 04DE70/04DEE8) + 1 other wrongful D-demotion +")
lines.append("# 6 pointer-table discoveries (function-pointer tables in ROM data area).")
lines.append("#")
lines.append("# KEY CORRECTION vs the v2.2 audit note: the 100x '381c 4946 5246 089b'")
lines.append("# idiom instances over 029AC4-02C70C are NOT 100 function starts. Proven:")
lines.append("# zero BLs target any idiom start; zero data pointers target them; every")
lines.append("# idiom is fallthrough-reached interior code (prev halfword decodes 'fall');")
lines.append("# the span contains no bx-lr/pop-pc terminators. The idiom is an inline")
lines.append("# call-helper pattern inside larger bodies. The REAL starts in the span are")
lines.append("# the 25 BL-targeted D entries below (each 1-31 genuine BL callers, all")
lines.append("# caller sites verified as visited instruction boundaries in a recursive")
lines.append("# descent of the span; each validate_target T=True; most BL-call known")
lines.append("# v2 functions: 2D7A0/2FC70/2FBA4/2FC28/2FCFC/2D5A8/3FACC).")
lines.append("#")
lines.append("# Format: <offset> B <mode> <symbol> # v2.3: <evidence>")
for off, n, callees, was in thunk:
    cal = ("; calls known " + ",".join("sub_080"+c for c in callees)) if callees else ""
    lines.append(f"{off:05X} B T sub_080{off:05X} # v2.3: {n} genuine BL callers"
                 f" (visited-boundary verified), validate_target T{cal}; was D {was}")
for off, n, callees, was, note in other_d:
    lines.append(f"{off:05X} B T sub_080{off:05X} # v2.3: {note}; was D {was}")
for off, nruns, note in ptrtab:
    lines.append(f"{off:05X} B T sub_080{off:05X} # v2.3: pointer-table discovery: {note}")
lines.append("#")
lines.append("# Explicitly NOT promoted (rejected):")
lines.append("# - 02A846: 2 genuine BL callers (029B40, 029C06), 131-insn coherent body")
lines.append("#   calling known 2D7A0/2FC28, but validate_target T=False: body reaches a")
lines.append("#   switch jump table (mov pc,r0 @2AA92) whose data defeats the validator.")
lines.append("#   Probable real function; needs manual Phase 3 review. Conservative exclude.")
lines.append("# - 049856: 1 BL caller, but caller sits after an unconditional branch")
lines.append("#   (dead code/data); target does not decode as code. Data false-positive.")
lines.append("# - 04DDA0: upholds v2.2 rejection (13 genuine callers confirmed, but it is an")
lines.append("#   alternate entry 4B inside A-tier sub_0804DD9C; no-split rule keeps it D).")
lines.append("# - 03B3E8: validate=False, 0 callers; 04B514/04B528/04B52C/04B530/04B534/04B538:")
lines.append("#   validate=True but 0 callers and no prologue/integration; stay D.")
lines.append("# - 69 further pointer-table targets: strong_shape (bx-lr) but only a single")
lines.append("#   table reference each; insufficient evidence under the conservative rule.")
lines.append("# - The 100 idiom instances themselves: proven interior points, NOT starts")
lines.append("#   (see header). The 10x 1C38/4649/9A0E/9B08 and 2x 1C38/4649/2202/9B08")
lines.append("#   idiom variants are likewise interior inline patterns.")
lines.append("#")
lines.append("# Verified totals after v2.3: A=51, B=1630 (1598 + 32), D=38 (64 - 26).")
lines.append("# Working function count: 1681.")

with open('func_list_v2_3_addendum.txt', 'w') as f:
    f.write("\n".join(lines) + "\n")
print(f"wrote {len(lines)} lines")
# sanity: all 32 offsets distinct and unlisted
offs = [o for o,_,_,_ in thunk] + [o for o,_,_,_,_ in other_d] + [o for o,_,_ in ptrtab]
assert len(offs) == len(set(offs)) == 32, "dup!"
listed = set()
for fn in ('func_list_v2.txt', 'func_list_v2_1_addendum.txt', 'func_list_v2_2_addendum.txt'):
    for line in open(fn):
        line=line.strip()
        if line and not line.startswith('#'):
            p = line.split()
            if p[1] in ('A','B'):
                listed.add(int(p[0],16))
overlap = [o for o in offs if o in listed]
assert not overlap, f"overlap with A/B: {overlap}"
print("all 32 distinct and not in A/B lists")
