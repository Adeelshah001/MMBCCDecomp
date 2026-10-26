# Installation

## Prerequisites

- `make`, `git`, and a C compiler toolchain
- `binutils-arm-none-eabi` (ARM cross-binutils)
- `agbcc` — the era-appropriate GBA C compiler (see `tools/`)
- `gbagfx` and `gbafix` — graphics and header tools
- `armips` (optional, for assembly patches)

## Build

1. Place your legally obtained copy of Mega Man Battle Chip Challenge (USA) in the repository root as `baserom.gba`. It is never committed.
2. Verify it:
   ```
   make check
   ```
3. Build the ROM:
   ```
   make
   ```
4. Verify the build is byte-identical to the original:
   ```
   make compare
   ```

`make compare` gates on SHA-1 `72309736f3820470c6f372d6a05ad1f16bc5a946` (8,388,608 bytes, header title `BATTLECHIPGP`, game code `A89E`).
