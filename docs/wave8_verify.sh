#!/bin/bash
# Wave 8 clean-room verification harness (coordinator side).
# Usage: wave8_verify.sh <cfile> <addr_hex> <compiler: main|old|noiw> <section> <expected_size_bytes>
# Exit 0 + "VERIFY-OK" only on a full-extent zero-diff cmp.
set -u
CFILE="$1"; ADDR="$2"; COMP="$3"; SECT="$4"; EXPECT="$5"
ROM=/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba
T=~/workspace/mmbcc-decomp/staging/verify
mkdir -p "$T"; rm -f "$T"/*
B="$T/base"
case "$COMP" in
  main)   AG=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/agbcc; IW="-mthumb-interwork";;
  old)    AG=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/old_agbcc; IW="-mthumb-interwork";;
  noiw)   AG=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/agbcc; IW="";;
  *) echo "VERIFY-FAIL: bad compiler $COMP"; exit 1;;
esac
cpp -I ~/workspace/mmbcc-decomp/mmbcc/include "$CFILE" -o "$B.i" || { echo "VERIFY-FAIL: cpp"; exit 1; }
"$AG" -O2 $IW -Wimplicit -Wparentheses -o "$B.s" "$B.i" || { echo "VERIFY-FAIL: agbcc"; exit 1; }
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o "$B.o" "$B.s" || { echo "VERIFY-FAIL: as"; exit 1; }
[ -s "$B.o" ] || { echo "VERIFY-FAIL: empty .o"; exit 1; }
arm-none-eabi-ld -Ttext "$ADDR" --section-start .text."$SECT"="$ADDR" -o "$B.elf" "$B.o" || { echo "VERIFY-FAIL: ld"; exit 1; }
# Default ld script merges .text.* into .text, breaking -j extraction:
# relink with a custom script that keeps the named section separate.
cat > "$B.ld" <<EOF
OUTPUT_FORMAT("elf32-littlearm")
SECTIONS { .text.$SECT $ADDR : { *(.text.$SECT) } }
EOF
arm-none-eabi-ld -T "$B.ld" -o "$B.elf" "$B.o" || { echo "VERIFY-FAIL: ld(script)"; exit 1; }
[ -s "$B.elf" ] || { echo "VERIFY-FAIL: empty .elf"; exit 1; }
arm-none-eabi-objcopy -O binary -j .text."$SECT" "$B.elf" "$B.bin" || { echo "VERIFY-FAIL: objcopy"; exit 1; }
BSZ=$(stat -c%s "$B.bin"); echo "bin: $BSZ bytes"
[ "$BSZ" -gt 0 ] || { echo "VERIFY-FAIL: empty .bin (section pattern?)"; exit 1; }
OFF=$((ADDR - 0x08000000))
dd if="$ROM" of="$B.rom" bs=1 skip=$OFF count="$EXPECT" status=none
RSZ=$(stat -c%s "$B.rom"); echo "rom: $RSZ bytes"
[ "$RSZ" -eq "$EXPECT" ] || { echo "VERIFY-FAIL: rom extract $RSZ != $EXPECT"; exit 1; }
[ "$BSZ" -eq "$EXPECT" ] || { echo "VERIFY-FAIL: bin $BSZ != expected $EXPECT"; exit 1; }
if cmp -l "$B.bin" "$B.rom" | head -5 | grep -q .; then
  echo "VERIFY-FAIL: diffs:"; cmp -l "$B.bin" "$B.rom" | head -10; exit 1
fi
echo "VERIFY-OK: $CFILE @ $ADDR ($COMP) $BSZ bytes zero-diff"
