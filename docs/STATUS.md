# Status

Current state, verified 2026-10-29 from the match registry (`docs/match_status.tsv`):

- **C-matched: 1280 / 1677 functions (76.3%)**
- Assembly-verified: 13 functions
- **Byte-identical total: 1293 functions**
- Build: 8,388,608 bytes, reproducible — staging build SHA-1 `03970057b4a502a5ce77b804d9120bc7db034484` (in-progress build, not yet byte-identical to the baserom)
- Next milestone: 80% (1342/1677, 62 short)

## Phases

- Phase 0 Toolchain: complete (agbcc @da598c1, binutils-arm-none-eabi 2.42)
- Phase 1 Disassembly: complete
- Phase 2 Boundaries / naming: complete
- Phase 3 Matching C: in progress, 76.3%
- Phase 4 Assets: pending — text codec (custom Capcom container) still unknown; audio is a proprietary Capcom driver (stretch goal)
- Phase 5 Byte-identical build: pending `make compare`

## Notes

- Target: Mega Man Battle Chip Challenge (USA, GBA), game code `A89E`, 8 MB.
- Completion gate: SHA-1 `72309736f3820470c6f372d6a05ad1f16bc5a946`.
- Function total is 1677; three additional denominator candidates are under review.
- The original ROM is never included in this repository.
- The project logo (`docs/logo.jpg`) was uploaded separately and is already on the repository; it is not part of this snapshot.
