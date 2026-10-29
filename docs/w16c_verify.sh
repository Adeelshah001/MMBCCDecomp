#!/bin/bash
# Wave16-C verify: compile C, auto-generate address stubs for undefined callees
# (zipping bl-targets from ROM disasm with reloc symbols in the .o), link the
# section at its exact ROM address, extract, and byte-compare vs the ROM.
# Usage: w16c_verify.sh CFILE ADDR COMP [SIZE]
set -u
CFILE="$1"; ADDR="$2"; COMP="$3"; SIZE="${4:-0}"
ROM=/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba
T=~/workspace/mmbcc-decomp/staging/verify_w16c; mkdir -p "$T"; rm -f "$T"/*
B="$T/base"
SECT=$(grep -o '\.text\.[a-zA-Z0-9_]*' "$CFILE" | head -1 | sed 's/\.text\.//')
[ -n "$SECT" ] || { echo "FAIL($ADDR): no section in $CFILE"; exit 1; }
case "$COMP" in
  main) AG=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/agbcc; IW="-mthumb-interwork";;
  old)  AG=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/old_agbcc; IW="-mthumb-interwork";;
  *) echo "FAIL($ADDR): bad compiler $COMP"; exit 1;;
esac
cpp -I ~/workspace/mmbcc-decomp/mmbcc/include "$CFILE" -o "$B.i" 2>/dev/null
"$AG" -O2 $IW -Wimplicit -Wparentheses -o "$B.s" "$B.i" || { echo "FAIL($ADDR): agbcc"; exit 1; }
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o "$B.o" "$B.s" || { echo "FAIL($ADDR): as"; exit 1; }
OSZ=$(stat -c%s "$B.o"); [ "$OSZ" -gt 0 ] || { echo "FAIL($ADDR): empty .o"; exit 1; }
# --- auto stubs for undefined symbols ---
UNDEFS=$(arm-none-eabi-nm -u "$B.o" 2>/dev/null | awk '$2 != "" {print $2}' | sort -u)
STUBOBJS=""
if [ -n "$UNDEFS" ]; then
  [ "$SIZE" -gt 0 ] || { echo "FAIL($ADDR): need SIZE to resolve callees"; exit 1; }
  OFF=$((ADDR - 0x08000000))
  dd if="$ROM" of="$B.raw" bs=1 skip=$OFF count=$SIZE status=none
  mapfile -t TARGS < <(arm-none-eabi-objdump -b binary -m arm -M force-thumb --adjust-vma=$ADDR -D "$B.raw" 2>/dev/null | grep -oE '(bl|blx)\s+0x[0-9a-f]+' | awk '{print $2}')
  mapfile -t SYMS < <(arm-none-eabi-objdump -dr "$B.o" 2>/dev/null | grep -E 'R_ARM_(THM_CALL|CALL|JUMP24|THM_JUMP24)' | awk '{print $NF}')
  : > "$B.stub.s"
  echo ".thumb" >> "$B.stub.s"
  declare -A SEEN
  i=0
  for s in "${SYMS[@]}"; do
    if [ -z "${SEEN[$s]:-}" ]; then
      SEEN[$s]=1
      if [ $i -lt ${#TARGS[@]} ]; then
        echo ".global $s" >> "$B.stub.s"
        echo ".set $s, ${TARGS[$i]}" >> "$B.stub.s"
        i=$((i+1))
      fi
    fi
  done
  if [ ${#SYMS[@]} -gt 0 ] && [ $i -eq 0 ]; then
    echo "FAIL($ADDR): could not map ${#SYMS[@]} undef syms to ${#TARGS[@]} bl targets"; exit 1
  fi
  arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o "$B.stub.o" "$B.stub.s" || { echo "FAIL($ADDR): stub as"; exit 1; }
  STUBOBJS="$B.stub.o"
fi
cat > "$B.ld" <<LDEOF
OUTPUT_FORMAT("elf32-littlearm")
SECTIONS { .text.$SECT $ADDR : { *(.text.$SECT) } }
LDEOF
arm-none-eabi-ld -T "$B.ld" -o "$B.elf" "$B.o" $STUBOBJS 2>"$B.lderr" || { echo "FAIL($ADDR): ld:"; head -3 "$B.lderr"; exit 1; }
ESZ=$(stat -c%s "$B.elf"); [ "$ESZ" -gt 0 ] || { echo "FAIL($ADDR): empty .elf"; exit 1; }
arm-none-eabi-objcopy -O binary -j ".text.$SECT" "$B.elf" "$B.bin"
BSZ=$(stat -c%s "$B.bin"); [ "$BSZ" -gt 0 ] || { echo "FAIL($ADDR): empty bin"; exit 1; }
# GAS pads isolated sections to 4-byte alignment with c046; the function's true
# extent is SIZE (code+pools per TSV). Truncate harness pad, never code.
if [ "$SIZE" -gt 0 ] && [ "$BSZ" -gt "$SIZE" ]; then
  dd if="$B.bin" of="$B.trunc" bs=1 count="$SIZE" status=none; mv "$B.trunc" "$B.bin"; BSZ=$SIZE
fi
[ "$SIZE" -eq 0 ] || [ "$BSZ" -ge "$SIZE" ] || { echo "FAIL($ADDR): bin $BSZ < size $SIZE"; exit 1; }
OFF=$((ADDR - 0x08000000))
dd if="$ROM" of="$B.rom" bs=1 skip=$OFF count="$BSZ" status=none
RSZ=$(stat -c%s "$B.rom"); [ "$RSZ" -eq "$BSZ" ] || { echo "FAIL($ADDR): rom extract $RSZ != $BSZ"; exit 1; }
if cmp -s "$B.bin" "$B.rom"; then echo "OK $ADDR ($COMP, $SECT): full $BSZ bytes zero-diff"; else echo "FAIL($ADDR): diffs:"; cmp -l "$B.bin" "$B.rom" | head -8; fi
