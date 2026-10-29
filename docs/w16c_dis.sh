#!/bin/bash
# Disassemble function bytes from the baserom: w16c_dis.sh 0xADDR BYTES
set -u
ADDR="$1"; BYTES="$2"
ROM=/home/hatch/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba
T=~/workspace/mmbcc-decomp/staging/verify_w16c; mkdir -p "$T"
OFF=$((ADDR - 0x08000000))
dd if="$ROM" of="$T/raw.bin" bs=1 skip=$OFF count=$BYTES status=none
arm-none-eabi-objdump -b binary -m arm -M force-thumb --adjust-vma=$ADDR -D "$T/raw.bin" | sed -n '/^ *[0-9a-f]/p' | head -80
