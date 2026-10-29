#!/bin/bash
# Verify a worker C file: extract section name from source, compile, link, compare full section.
set -u
CFILE="$1"; ADDR="$2"; COMP="$3"
ROM=/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba
T=~/workspace/mmbcc-decomp/staging/verify_w15; mkdir -p "$T"; rm -f "$T"/*
B="$T/base"
SECT=$(grep -o '\.text\.[a-zA-Z0-9_]*' "$CFILE" | head -1 | sed 's/\.text\.//')
[ -n "$SECT" ] || { echo "FAIL($ADDR): no section in $CFILE"; exit 1; }
case "$COMP" in
  main) AG=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/agbcc; IW="-mthumb-interwork";;
  old)  AG=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/old_agbcc; IW="-mthumb-interwork";;
esac
cpp -I ~/workspace/mmbcc-decomp/mmbcc/include "$CFILE" -o "$B.i" 2>/dev/null
"$AG" -O2 $IW -Wimplicit -Wparentheses -o "$B.s" "$B.i" || { echo "FAIL($ADDR): agbcc"; exit 1; }
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o "$B.o" "$B.s" || { echo "FAIL($ADDR): as"; exit 1; }
cat > "$B.ld" <<LDEOF
OUTPUT_FORMAT("elf32-littlearm")
SECTIONS { .text.$SECT $ADDR : { *(.text.$SECT) } }
LDEOF
arm-none-eabi-ld -T "$B.ld" -o "$B.elf" "$B.o" 2>/dev/null || { echo "FAIL($ADDR): ld"; exit 1; }
arm-none-eabi-objcopy -O binary -j ".text.$SECT" "$B.elf" "$B.bin"
BSZ=$(stat -c%s "$B.bin"); [ "$BSZ" -gt 0 ] || { echo "FAIL($ADDR): empty bin"; exit 1; }
OFF=$((ADDR - 0x08000000))
dd if="$ROM" of="$B.rom" bs=1 skip=$OFF count="$BSZ" status=none
if cmp -s "$B.bin" "$B.rom"; then echo "OK $ADDR ($COMP, $SECT): full $BSZ bytes zero-diff"; else echo "FAIL($ADDR): diffs:"; cmp -l "$B.bin" "$B.rom" | head -6; fi
