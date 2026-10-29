# Installation

## Prerequisites

- `make`, `git`, a host C compiler, `python3`
- `binutils-arm-none-eabi` 2.42 (ARM cross-binutils)
- `agbcc` — the era-appropriate GBA C compiler, commit `da598c1` from
  [pret/agbcc](https://github.com/pret/agbcc) (both `agbcc` and `old_agbcc`
  variants are used)
- `gbafix` and `gbagfx` — header and graphics tools (sources vendored under
  `mmbcc/tools/`; see below)

## Toolchain setup (do this once)

The compiler and helper binaries are intentionally not committed. Set them up
as follows:

1. Build `gbafix` from its vendored sources:

   ```sh
   make -C mmbcc/tools/gbafix
   ```

2. Build `agbcc` from [pret/agbcc](https://github.com/pret/agbcc) at commit
   `da598c1` and install the resulting tree (with `bin/`, `lib/` and
   `include/`) as `mmbcc/tools/agbcc/`.

## Build

1. Place your legally obtained copy of Mega Man Battle Chip Challenge (USA)
   as `mmbcc/baserom.gba`. It is never committed.
2. From the `mmbcc/` directory, verify it:

   ```sh
   cd mmbcc
   make check
   ```

3. Build the ROM:

   ```sh
   make
   ```

4. Verify the build is byte-identical to the original:

   ```sh
   make compare
   ```

`make compare` gates on SHA-1 `72309736f3820470c6f372d6a05ad1f16bc5a946`
(8,388,608 bytes, header title `BATTLECHIPGP`, game code `A89E`). The project
is done when `make compare` passes. Until then, matched functions are verified
individually by build and diff.
