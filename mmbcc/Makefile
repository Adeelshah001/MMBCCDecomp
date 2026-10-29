# MMBCC — Mega Man Battle Chip Challenge (USA) matching decomp
#
# Phase-0 skeleton: assembles rom_header + crt0 stub, links, pads to 8 MiB,
# applies the 0x7B header quirk. `make compare` gates byte-identity.
#
# The baserom is NEVER in this repo. Supply your own legally-obtained dump:
#   make BASEROM=/path/to/your/dump.gba check
# `make check` verifies it is the expected dump by SHA-1 before anything
# else trusts it.

# Default goal must be explicit: per-file override rules below would
# otherwise become the default goal (first explicit target wins).
.DEFAULT_GOAL := all

TITLE      := BATTLECHIPGP
GAME_CODE  := A89E
MAKER_CODE := 08
REVISION   := 0
FILE_NAME  := mmbcc
BASEROM    ?= baserom.gba
EXPECTED_SHA1 := 72309736f3820470c6f372d6a05ad1f16bc5a946

TOOLS   := tools
GBAFIX  := $(TOOLS)/gbafix/gbafix
AS      := arm-none-eabi-as
LD      := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy
AGBCC   := $(TOOLS)/agbcc/bin/agbcc

BUILD   := build
SRCS_S  := $(wildcard src/*.s) $(wildcard asm/*.s)
# Explicit C source list (NOT a wildcard): worker staging files
# (mmbcc/src/wave3_<letter>.c) must not enter the build until the
# coordinator verifies and lands them (ldscript slots + this list).
# Add each landed file here at landing time.
SRCS_C  := src/bios.c src/chipslot.c src/entrymgr.c src/gateddispatch.c \
           src/gfx.c src/hblank.c src/hwinit.c src/mainloop.c src/sram.c \
           src/strided_copy.c src/task_register.c src/text.c \
           src/text_idx.c src/vec2.c src/wave3_c.c src/wave3_b.c \
           src/wave3_d.c src/wave3_d_noiw.c src/wave3_e.c src/wave3_e_old.c \
           src/wave3_a.c src/wave4_i.c src/wave4_i_old.c \
           src/wave4_j_old.c src/wave4_h.c src/wave4_g.c \
           src/wave4_k.c src/wave4_k_old.c \
           src/wave5_blk.c src/wave5_blk_old.c \
           src/wave5_h1.c src/wave5_h1_old.c src/wave5_g2.c \
           src/wave5_g1_old.c src/wave5_h2.c src/wave5_h2_old.c \
           src/wave6_blka.c src/wave6_blka_old.c src/wave6_l1_old.c \
           src/wave6_blkb_old.c src/wave6_l4_old.c src/wave6_l3_old.c \
           src/wave7_e.c src/wave7_e_old.c \
           src/wave7_d.c src/wave7_d_old.c src/wave7_b.c \
           src/wave7_f.c src/wave7_f_old.c src/wave7_g2.c src/wave7_g2_old.c \
           src/wave7_c_old.c src/wave8_r.c src/wave8_r_old.c src/wave8_b_old.c \
           src/wave8_xl.c src/wave8_m.c src/wave8_m_old.c src/wave8_u_old.c \
           src/wave8_s_old.c src/wave9_a_old.c src/wave9_f_old.c \
           src/wave9_c_noiw.c src/wave9_b_old.c src/wave9_d_old.c \
           src/wave9_e_old.c src/wave10_T_old.c src/wave10_R_old.c \
           src/wave10_H_old.c src/wave10_L_old.c src/wave11_D_old.c \
           src/wave11_B_old.c src/wave11_A_old.c src/wave12_C_old.c \
           src/wave12_B_old.c src/wave13_B.c src/wave13_D_old.c \
           src/wave14_D_old.c src/wave14_B.c src/wave14_B_old.c \
           src/wave14_B_noiw.c src/wave14_C.c src/wave14_C_old.c \
           src/wave15_D.c \
           src/wave15_B.c src/wave15_B_old.c \
           src/w15c_08000630.c src/w15c_08000d6c.c src/w15c_08003078.c src/w15c_0800c5ec.c src/w15c_0800c69c.c src/w15c_0800e400.c src/w15c_0800e650.c src/w15c_0800e690.c \
           src/w15c_0800e7c8.c src/w15c_0800e808.c src/w15c_0800e848.c src/w15c_0800e888.c src/w15c_0800e8c8.c src/w15c_0800e90c.c src/w15c_0800e950.c src/w15c_0800eac4.c \
           src/w15c_0800eaf4.c src/w15c_0800eb24.c src/w15c_0800eb70.c src/w15c_0800eba0.c src/w15c_0800ec18.c src/w15c_0800ecd8.c src/w15c_08011a0c.c src/w15c_080181ac.c \
           src/w15c_08018310.c src/w15c_08018e1c.c src/w15c_08019b64.c src/w15c_0801a6ac.c src/w15c_0801c3fc.c src/w15c_0801c540.c src/w15c_0801f9ec.c src/w15c_080200ec.c \
           src/w15c_080246fc.c src/w15c_0804c814.c src/w15c_0804d7c0.c src/w15c_0804d834.c \
           src/w16d_0803618c.c src/w16d_08005fc0.c src/w16d_08021e64.c \
           src/w16d_0804c7b4.c src/w16d_08027c84.c src/w16d_0802fd68.c \
           src/w16b_08017000.c src/w16b_08020ed4.c src/w16b_0804580c.c \
           src/w16b_08025754.c src/w16b_08024434.c src/w16b_08025054.c \
           src/w16b_08010ba0.c src/w16b_080467dc.c src/w16b_0800ea30.c \
           src/w16b_0800ebf0.c src/w16b_0801ab34.c src/w16b_080253bc.c \
           src/w16b_080257fc.c src/w16b_0802666c.c src/w16b_080266ac.c \
           src/w16c_0804b110.c src/w16c_0804b954.c src/w16c_0800ebd0.c \
           src/w16c_08037914.c src/w16c_0801bd7c.c src/w16c_0802316c.c \
           src/w16c_0801bea0.c src/w16c_08019e0c.c src/w16c_0801962c.c \
           src/w16c_0801974c.c src/w16c_08019a3c.c src/w16c_08011b64.c \
           src/w17a_0800b148.c \
           src/w18c_0800e6d0.c src/w18c_0803aed0.c \
           src/w18d_08049704.c src/w18d_0801f154.c src/w18d_0801cdac.c \
           src/w18d_0801f1a8.c src/w18d_0801f050.c src/w18d_0802030c.c \
           src/w18d_080203a4.c src/w18d_0801ee14.c \
           src/w18b_080114b8.c src/w18b_08011be0.c src/w18b_0801d24c.c \
           src/w18b_080217a8.c src/w18b_08021da8.c src/w18b_08021dd0.c \
           src/w18b_080225e4.c src/w18b_0802260c.c src/w18b_08022f88.c \
           src/w18b_08022fb0.c src/w18b_08024eb8.c src/w18b_08025524.c \
           src/w18b_080257bc.c src/w18b_08026144.c src/w18b_08037970.c \
           src/w18b_08038e88.c src/w18b_0803ae44.c \
           src/w17d_0803ae90.c src/w17d_0800b6a4.c src/w17d_080226b0.c\
           src/w17d_08037a7c.c src/w17d_08038f88.c src/w17d_0803af3c.c\
           src/w17d_080250a8.c src/w17d_0802508c.c src/w17d_080228bc.c\
           src/w17d_0800b3b0.c src/w17d_08016e0c.c src/w17d_0801d048.c\
           src/w17d_0801f12c.c src/w17d_08020514.c src/w17d_0802278c.c\
           src/w17d_08027c28.c src/w17d_08035170.c src/w17d_080379f0.c\
           src/w17d_08038efc.c src/w17d_08048380.c src/w17d_080254e0.c\
           src/w17c_chipinit.c src/w17c_table.c src/w17c_misc_old.c \
           src/w19c_0800fff4.c src/w19c_0801009c.c \
           src/w19c_08017620.c src/w19c_08017d00.c \
           src/w20c_0801d2c8.c src/w20c_0801e14c.c src/w20c_080173d4.c \
           src/w20c_0801787c.c src/w20c_0804a450.c src/w20c_0803e9bc.c \
           src/w20c_08047cc0.c \
           src/w21c_08043630.c \
           src/w21c_08001e30.c \
           src/w19d_080250bc.c src/w19d_08022868.c src/w19d_08020340.c \
           src/w19b_08017434.c src/w19b_080214f4.c src/w19b_0801f180.c \
           src/w19b_080228e0.c src/w19b_080236b0.c src/w19b_0801d308.c \
           src/w19b_08021cac.c src/w19b_0801d278.c \
           src/w20d_08005f44.c src/w20d_080247e8.c src/w20d_0801029c.c src/w20d_08010ec4.c \
           src/w20d_0800eb30.c src/w20d_0800ec3c.c src/w20d_0802611c.c \
           src/w20b_0801dfc4.c src/w20b_08021d10.c src/w20b_08024bc8.c \
           src/w21d_08010e7c.c src/w21d_08010ea0.c src/w21d_08010270.c \
           src/w21d_080439d8.c src/w21d_08024f30.c src/w21d_08024f70.c \
           src/w21b_08010308.c src/w21a_0803affc.c src/w21b_08042ae4.c \
           src/w22b_0800ed20.c src/w22b_0800ecf8.c src/w22b_0802493c.c src/w22d_080405d8.c src/w22d_080119dc.c src/w22d_08010f34.c src/w22d_0800e3a0.c src/w22d_08001ebc.c \
           src/w22c_08011a78.c \
           src/w22c_08016d2c.c src/w22a_08011e20.c \
           src/w23a_08002e80.c src/w23a_08002cb0.c src/w23d_scriptops.c src/w23d_080378b8.c \
           src/w24a_0804af20.c \
           src/w24d_08002ef4.c src/w24d_08001c88.c \
           src/w24b_080097cc.c src/w24b_08026184.c src/w24b_08007728.c \
           src/w24c_0800a6bc.c src/w24c_0800e748.c src/w24c_0800e224.c \
           src/w25c_0803f844.c src/w25c_08046810.c src/w25c_08045914.c \
           src/w25c_0804a1f0.c src/w25c_0803ad48.c src/w25c_08041890.c \
           src/w25b_08004998.c src/w25b_08026740.c \
           src/w25d_08045838.c \
           src/w26b_080259a4.c src/w26b_0800e440.c \
           src/w26c_0801bf10.c src/w26c_08042c04.c \
           src/w26d_08016efc.c src/w26d_0800d1e0.c \
           src/w27a_08006ad8.c src/w27a_08007134.c src/w27a_080065bc.c \
           src/w27a_08006374.c src/w27b_080482d8.c \
           src/w28a_080224e4.c src/w28a_08021b3c.c src/w28b_0801b0dc.c \
           src/w28c_0801f254.c src/w28c_0802375c.c src/w28c_0802298c.c \
           src/w28d_0802d6e0.c src/w32a_080096bc.c \
           src/w32c_080249b8.c src/w32c_0802d574.c src/w32_08024a30.c \
           src/w29b_0801c030.c src/w29c_08049560.c src/w29c_08002a1c.c \
           src/w30b_0803643c.c src/w30a_0803ac4c.c src/w30d_0801c428.c \
           src/w30c_080046b0.c \
           src/w31a_0801e77c.c src/w31c_08000ca8.c \
           src/w31d_080363ec.c src/w31d_080070f0.c src/w31d_080073d4.c \
           src/w31d_08007378.c src/w31d_080062b4.c src/w31d_08006518.c \
           src/w31d_08006aa0.c src/w31d_08006318.c src/w31d_0803639c.c \
           src/w31d_08036338.c src/w33a_08006fe8.c \
           src/w33b_0800cd5c.c src/w33b_08008b08.c src/w33c_080221cc.c \
           src/w33d_0804c8a4.c src/w33d_080260d4.c src/w33d_08005268.c src/w33d_0800b3ec.c \
           src/w33d_08004e50.c src/w33d_0804ad3c.c src/w33d_08024cc0.c \
           src/w33d_08007f3c.c src/w33d_0800ea14.c src/w33d_0800ee70.c \
           src/w33d_080111b4.c \
           src/w34c_08000e04_MATCHED.c \
           src/w34c_08002f58_MATCHED.c \
           src/w34c_08002f8c_MATCHED.c \
           src/w34c_08003058_MATCHED.c \
           src/w34c_080043ec_MATCHED.c \
           src/w34c_08004be8_MATCHED.c \
           src/w34c_08004ef4_MATCHED.c \
           src/w34c_08005274_MATCHED.c \
           src/w34c_080068f0_MATCHED.c \
           src/w34c_08006928_MATCHED.c \
           src/w34c_0800777c_MATCHED.c \
           src/w34c_0800bf44_MATCHED.c \
           src/w34c_0800c22c_MATCHED.c \
           src/w34c_0800c3e4_MATCHED.c \
           src/w34c_0800c48c_MATCHED.c \
           src/w34c_0800c588_MATCHED.c \
           src/w34c_0800cbc0_MATCHED.c \
           src/w34c_0800d704_MATCHED.c \
           src/w34c_0800d74c_MATCHED.c \
           src/w34c_0800d794_MATCHED.c \
           src/w34c_0800d7b8_MATCHED.c \
           src/w34c_0800d7dc_MATCHED.c \
           src/w34c_08010724_MATCHED.c \
           src/w34c_08011df0_MATCHED.c \
           src/w34c_08011f24_MATCHED.c \
           src/w34c_08016fd0_MATCHED.c \
           src/w34c_0801d464_MATCHED.c \
           src/w34c_08020ea4_MATCHED.c \
           src/w34c_08021780_MATCHED.c \
           src/w34c_080241ac_MATCHED.c \
           src/w34c_080241d0_MATCHED.c \
           src/w34c_08024c14_MATCHED.c \
           src/w34c_08024fbc_MATCHED.c \
           src/w34c_08024fd8_MATCHED.c \
           src/w34c_080253f8_MATCHED.c \
           src/w34c_080260a0_MATCHED.c \
           src/w34c_08026208_MATCHED.c \
           src/w34c_08027e5c_MATCHED.c \
           src/w34c_08036374_MATCHED.c \
           src/w34c_08042998_MATCHED.c \
           src/w34c_08045e20_MATCHED.c \
           src/w34c_08045e40_MATCHED.c \
           src/w34c_08045e60_MATCHED.c \
           src/w34c_08045e80_MATCHED.c \
           src/w34c_08047628_MATCHED.c \
           src/w34c_0804a39c_MATCHED.c \
           src/w34c_0804ac64_MATCHED.c \
           src/w34c_0804acac_MATCHED.c \
           src/w34c_0804ad00_MATCHED.c \
           src/w34c_0804afac_MATCHED.c \
           src/w34c_0804c7e8_MATCHED.c \
           src/w34d_08042a64.c \
           src/w34d_08007678.c \
           src/w34d_08035e5c.c \
           src/w35b_0800b3f8_MATCHED.c src/w35b_0800b420_MATCHED.c \
           src/w35b_08022e88_MATCHED.c src/w35b_0802d488_MATCHED.c \
           src/w35b_0804b350_MATCHED.c src/w35b_08027d18_MATCHED.c \
           src/w35b_080267c0_MATCHED.c src/w35b_0804c780_MATCHED.c \
           src/w35b_0804c288_MATCHED.c \
           src/w35d_0804c820_MATCHED.c src/w35d_0804990c_MATCHED.c \
           src/w35d_0801b630_MATCHED.c \
           src/w35a_0800d9fc.c \
           src/w35c_0800c5a4_MATCHED.c src/w35c_0800cbdc_MATCHED.c \
           src/w35c_08026dbc_MATCHED.c src/w35c_080375c8_MATCHED.c \
           src/w35c_08000e28_MATCHED.c src/w35c_08006e30_MATCHED.c \
           src/w35c_080079f0_MATCHED.c src/w35c_0800c748_MATCHED.c \
           src/w35c_0800c8f0_MATCHED.c src/w35c_0800ee98_MATCHED.c \
           src/w35c_08004dbc_MATCHED.c src/w35c_08022f48_MATCHED.c \
           src/w35c_0804cecc_MATCHED.c src/w35c_0801112c_MATCHED.c \
           src/w35c_0801d89c_MATCHED.c src/w35c_080275b4_MATCHED.c \
           src/w35c_08002d84_MATCHED.c src/w35c_080047a4_MATCHED.c \
           src/w35c_0800741c_MATCHED.c src/w35c_0800b320_MATCHED.c \
           src/w35c_0801f9a4_MATCHED.c src/w35c_0802756c_MATCHED.c \
           src/w35c_08027cb4_MATCHED.c src/w35c_080110e0_MATCHED.c \
           src/w36e_0802873c_MATCHED.c \
           src/w36e_08001c08_MATCHED.c \
           src/w36e_0802fbf0_MATCHED.c \
           src/w36e_080272e0_MATCHED.c \
           src/w36e_0801a9ac_MATCHED.c \
           src/w36e_0801b8d0_MATCHED.c \
           src/w36e_0801cc94_MATCHED.c \
           src/w36e_08027d48_MATCHED.c \
           src/w36a_08007c8c_MATCHED.c \
           src/w36a_08007e9c_MATCHED.c \
           src/w36a_08007eec_MATCHED.c \
           src/w36a_08007324_MATCHED.c \
           src/w36a_0800dea4_MATCHED.c \
           src/w36a_080008c0_MATCHED.c \
           src/w36a_0800b470_MATCHED.c \
           src/w36a_0801054c_MATCHED.c \
           src/w36a_080429e0_MATCHED.c \
           src/w36a_0801db40_MATCHED.c \
           src/w36a_08023110_MATCHED.c \
           src/w36a_0802f550_MATCHED.c \
           src/w36a_080060c4_MATCHED.c \
           src/w36a_0800675c_MATCHED.c \
           src/w36a_08015a60_MATCHED.c \
           src/w36a_08046904_MATCHED.c \
           src/w36c_0801e0d0_MATCHED.c \
           src/w36c_08026a84_MATCHED.c \
           src/w36c_08019f38_MATCHED.c \
           src/w36c_0801a81c_MATCHED.c \
           src/w36c_0801cac4_MATCHED.c \
           src/w36c_08021628_MATCHED.c \
           src/w36c_08018f34_MATCHED.c \
           src/w36c_08019c94_MATCHED.c \
           src/w36c_0801a19c_MATCHED.c \
           src/w36c_0801ae70_MATCHED.c \
           src/w36c_08011f88_MATCHED.c \
           src/w36c_08012108_MATCHED.c \
           src/w36c_0801a2bc_MATCHED.c \
           src/w36c_0801a568_MATCHED.c \
           src/w36c_0801c108_MATCHED.c \
           src/w36c_0801c628_MATCHED.c \
           src/w36c_08038520_MATCHED.c \
           src/w36d_080054d0_MATCHED.c \
           src/w36d_080188f4_MATCHED.c \
           src/w36d_08018c84_MATCHED.c \
           src/w36d_08018ea4_MATCHED.c \
           src/w36d_08019248_MATCHED.c \
           src/w36d_08019374_MATCHED.c \
           src/w36d_080194b4_MATCHED.c \
           src/w36d_0801a3f0_MATCHED.c \
           src/w36d_0801af58_MATCHED.c \
           src/w36d_0801b04c_MATCHED.c \
           src/w36d_0801b1b8_MATCHED.c \
           src/w36d_0801b244_MATCHED.c \
           src/w36d_0801c254_MATCHED.c \
           src/w36d_0801c774_MATCHED.c \
           src/w36d_0801c91c_MATCHED.c \
           src/w36d_08022700_MATCHED.c \
           src/w36d_080227dc_MATCHED.c \
           src/w36d_08024b3c_MATCHED.c \
           src/w36d_08024e2c_MATCHED.c \
           src/w36d_08027374_MATCHED.c \
           src/w36d_0802daf8_MATCHED.c \
           src/w36d_0802fc70_MATCHED.c \
           src/w36d_08046960_MATCHED.c \
           src/w36d_080053a0_MATCHED.c \
           src/w36d_0800cde8_MATCHED.c \
           src/w36d_0800ce7c_MATCHED.c \
           src/w36d_08020f70_MATCHED.c \
           src/w36d_08022290_MATCHED.c \
           src/w36b_0801aacc_MATCHED.c \
           src/w36b_08021ed4_MATCHED.c \
           src/w36b_0802329c_MATCHED.c \
           src/w36b_0800419c_MATCHED.c \
           src/w36b_0804b5cc_MATCHED.c \
           src/w36b_080098c4_MATCHED.c \
           src/w36b_0800cc94_MATCHED.c \
           src/w36b_0800ed44_MATCHED.c \
           src/w36b_0800eed4_MATCHED.c \
           src/w36b_0802142c_MATCHED.c \
           src/w36b_08025e5c_MATCHED.c \
           src/w36b_080280e8_MATCHED.c \
           src/w36b_0802e9f8_MATCHED.c \
           src/w36b_08045fcc_MATCHED.c \
           src/w36b_08007cf4_MATCHED.c \
           src/w36b_0800c41c_MATCHED.c \
           src/w36b_08010b30_MATCHED.c \
           src/w36b_0801b91c_MATCHED.c \
           src/w36b_0801cce0_MATCHED.c \
           src/w36b_08023d68_MATCHED.c \
           src/w36b_08028900_MATCHED.c \
           src/w36b_0802d670_MATCHED.c \
           src/w36b_0800e994_MATCHED.c \
           src/w36b_08011eb0_MATCHED.c \
           src/w36b_08023bc4_MATCHED.c \
           src/w36b_08034eb8_MATCHED.c \
           src/w36b_0803ff0c_MATCHED.c \
           src/w36b_08000e80_MATCHED.c \
           src/w36b_080114e8_MATCHED.c \
           src/w36b_0801a9f8_MATCHED.c \
           src/w36b_0804c630_MATCHED.c \
           src/w36b_0800a0d4_MATCHED.c \
           src/w36b_08010750_MATCHED.c \
           src/w36b_0801bfb4_MATCHED.c \
           src/w36d_0800288c_MATCHED.c \
           src/w36d_080050f0_MATCHED.c \
           src/w36bulk_08007798_MATCHED.c \
           src/w36d_0800b448_MATCHED.c \
           src/w36d_0800c878_MATCHED.c \
           src/w36a_0800cb70_MATCHED.c \
           src/w36a_0800ec7c_MATCHED.c \
           src/w36d_0800edb0_MATCHED.c \
           src/w36a_08010d84_MATCHED.c \
           src/w36d_080112cc_MATCHED.c \
           src/w36d_080129f8_MATCHED.c \
           src/w36d_08017670_MATCHED.c \
           src/w36a_0801b428_MATCHED.c \
           src/w36a_0801b520_MATCHED.c \
           src/w36a_0801b880_MATCHED.c \
           src/w36bulk_0801dd48_MATCHED.c \
           src/w36a_0801e93c_MATCHED.c \
           src/w36bulk_08021c2c_MATCHED.c \
           src/w36d_0802366c_MATCHED.c \
           src/w36a_080248c4_MATCHED.c \
           src/w36bulk_08024c40_MATCHED.c \
           src/w36d_080256e0_MATCHED.c \
           src/w36a_08028970_MATCHED.c \
           src/w36a_0803449c_MATCHED.c \
           src/w36bulk_0804380c_MATCHED.c \
           src/w36bulk_0804afd0_MATCHED.c \
           src/w36a_0804c72c_MATCHED.c \
           src/w37a_08009238_MATCHED.c \
           src/w37b_08000eb8_MATCHED.c \
           src/w37b_08000ed4_MATCHED.c \
           src/w37b_08007c04_MATCHED.c \
           src/w37b_08007f24_MATCHED.c \
           src/w37b_08011530_MATCHED.c \
           src/w37b_080174f4_MATCHED.c \
           src/w37b_0801aa50_MATCHED.c \
           src/w37b_0801b96c_MATCHED.c \
           src/w37b_0801cd30_MATCHED.c \
           src/w37b_0801e970_MATCHED.c \
           src/w37b_080402e0_MATCHED.c \
           src/w37b_0804044c_MATCHED.c \
           src/w37d_0801ece8_MATCHED.c \
           src/w37d_0801d6cc_MATCHED.c \
           src/w37d_0801ffbc_MATCHED.c \
           src/w37coord_0801edf4_MATCHED.c \
           src/w37c_08042d80_MATCHED.c \
           src/w37c_08016c94_MATCHED.c \
           src/w37c_080185a8_MATCHED.c \
           src/w37c_080192dc_MATCHED.c \
           src/w37c_08018510_MATCHED.c \
           src/w37c_0801986c_MATCHED.c \
           src/w37c_08038488_MATCHED.c \
           src/w37c_0804cbcc_MATCHED.c \
           src/w37c_08005434_MATCHED.c \
           src/w37c_08009edc_MATCHED.c \
           src/w37c_08018474_MATCHED.c \
           src/w37c_0801a220_MATCHED.c \
           src/w37c_0801ac58_MATCHED.c \
           src/w37c_0802d5d4_MATCHED.c \
           src/w37c_0804713c_MATCHED.c \
           src/w37c_0801ad60_MATCHED.c \
           src/w37c_0801757c_MATCHED.c \
           src/w37c_0801ec44_MATCHED.c \
           src/w37c_0804cb28_MATCHED.c \
           src/w37c_08017dc4_MATCHED.c \
           src/w37c_0801e028_MATCHED.c \
           src/w37c_08021144_MATCHED.c \
           src/w37c_080231d0_MATCHED.c \
           src/w37c_0801a344_MATCHED.c \
           src/w37c2_08042e14_MATCHED.c \
           src/w37c2_0801969c_MATCHED.c \
           src/w37c2_080197bc_MATCHED.c \
           src/w37c2_08017ed8_MATCHED.c \
           src/w37c2_08018640_MATCHED.c \
           src/w37c2_08019400_MATCHED.c \
           src/w37c2_08019aac_MATCHED.c \
           src/w37c2_08019bdc_MATCHED.c \
           src/w37c2_08019e7c_MATCHED.c \
           src/w37c2_0801a5f0_MATCHED.c \
           src/w37c2_08017984_MATCHED.c \
           src/w37c2_08017a24_MATCHED.c \
           src/w38d_08030ad4_MATCHED.c \
           src/w38c_08017600_MATCHED.c \
           src/w38c_08023264_MATCHED.c \
           src/w38c_08023a7c_MATCHED.c \
           src/w38c_0801bde4_MATCHED.c \
           src/w38c_0801c6b0_MATCHED.c \
           src/w38c_080234c8_MATCHED.c \
           src/w38c_0800e144_MATCHED.c \
           src/w38b_0800adc8_MATCHED.c \
           src/w38b_080361e8_MATCHED.c \
           src/w38b_0800c268_MATCHED.c \
           src/w38b_08004e60_MATCHED.c \
           src/w38b_08034c1c_MATCHED.c \
           src/w38a_0801823c_MATCHED.c \
           src/w38a_08005130_MATCHED.c \
           src/w38a_08012f4c_MATCHED.c \
           src/w38a_08013528_MATCHED.c \
           src/w38a_080139fc_MATCHED.c \
           src/w38a_08017a94_MATCHED.c \
           src/w38a_08018fb8_MATCHED.c \
           src/w38a_0802106c_MATCHED.c \
           src/w38a_08035a24_MATCHED.c \
           src/w38a_08013ad4_MATCHED.c \
           src/w38a_08014078_MATCHED.c \
           src/w38a_0801a484_MATCHED.c \
           src/w38a_0801572c_MATCHED.c \
           src/w38a_0801b728_MATCHED.c \
           src/w39d_08009140_MATCHED.c \
           src/w39d_0803b898_MATCHED.c \
           src/w39a_080285c4_MATCHED.c \
           src/w39a_08048084_MATCHED.c \
           src/w39a_0803895c_MATCHED.c \
           src/w39b_0802f5ac_MATCHED.c \
           src/w39c_08015278_MATCHED.c \
           src/w39c_0801a72c_MATCHED.c \
           src/w39c_08013708_MATCHED.c \
           src/w39c_0801519c_MATCHED.c \
           src/w39c_08042b60_MATCHED.c \
           src/w39c_08023f28_MATCHED.c \
           src/w40a_080171c0_MATCHED.c \
           src/w40a_0801e890_MATCHED.c \
           src/w40b_08003874_MATCHED.c \
           src/w40b_080118a4_MATCHED.c \
           src/w40b_08019904_MATCHED.c \
           src/w40b_08035c5c_MATCHED.c \
           src/w40c_08017b6c_MATCHED.c \
           src/w40c_0802129c_MATCHED.c \
           src/w40c_080173bc_MATCHED.c \
           src/w40c_08017ce0_MATCHED.c \
           src/w40d_0804b7f0_MATCHED.c \
           src/w40d_08049780_MATCHED.c \
           src/w41a_08023c38_MATCHED.c \
           src/w41b_08003b70_MATCHED.c \
           src/w41b_08003e80_MATCHED.c \
           src/w41c_08015ac4_MATCHED.c \
           src/w41c_0802d928_MATCHED.c \
           src/w41d_08020870_MATCHED.c \
           src/w42a_0801b9e8_MATCHED.c \
           src/w42c_0800e068_MATCHED.c \
           src/w42d_0804ca30_MATCHED.c \
           src/w42d_08046cfc_MATCHED.c \
           src/w43b_08026430_MATCHED.c \
           src/w43c_08018398_MATCHED.c \
           src/w43c_0801b2d0_MATCHED.c \
           src/w43a_0803ff80_MATCHED.c \
           src/w44d_08018af4_MATCHED.c \
           src/w45b_080380b8_MATCHED.c \
           src/w45c_0800bd20_MATCHED.c \
           src/w45d_0801a89c_MATCHED.c \
           src/w46a_08020660_MATCHED.c \
           src/w46c_0801c800_MATCHED.c \
           src/w46c_08001ae4_MATCHED.c \
           src/w46d_0801c2e0_MATCHED.c \
           src/w46d_0801bb94_MATCHED.c \
           src/w46d_0801ba94_MATCHED.c \
           src/w47a_08001bf8_MATCHED.c \
           src/w47c_0801c9a8_MATCHED.c \
           src/w47d_08044630_MATCHED.c \
           src/w47d_0804472c_MATCHED.c \
           src/w48c_0804b634_MATCHED.c \
           src/w49c_08041fbc_MATCHED.c \
           src/w49c_080420d0_MATCHED.c \
           src/w49c_080421e4_MATCHED.c \
           src/w49d_0801d488_MATCHED.c \
           src/w49d_080275f8_MATCHED.c \
           src/w50b_0801ebd0_MATCHED.c \
           src/w50b_0800d278_MATCHED.c \
           src/w50c_08042878_MATCHED.c \
           src/w50d_0801200c_MATCHED.c \
           src/w50d_08012190_MATCHED.c \
           src/w50d_0800d59c_MATCHED.c \
           src/w50d_08013280_MATCHED.c \
           src/w50d_08014fb4_MATCHED.c \
           src/w51a_08015644_MATCHED.c \
           src/w51c_0800fee0_MATCHED.c \
           src/w51d_08000418_MATCHED.c \
           src/w51c_0801eac4_MATCHED.c \
           src/w52a_0800fc64_MATCHED.c \
           src/w52b_080240cc_MATCHED.c \
           src/w52d_08011560_MATCHED.c \
           src/w53a_0800bfd0_MATCHED.c \
           src/w53b_080170d4_MATCHED.c \
           src/w54c_080059a8_MATCHED.c \
           src/w54d_08013434_MATCHED.c \
           src/w54d_08014154_MATCHED.c \
           src/w54d_08014318_MATCHED.c \
           src/w54d_0801440c_MATCHED.c \
           src/w54d_080145cc_MATCHED.c \
           src/w54d_08019d18_MATCHED.c \
           src/w55d_0800695c_MATCHED.c \
           src/w55d_08013904_MATCHED.c \
           src/w55d_08013bb0_MATCHED.c \
           src/w55d_08014eb8_MATCHED.c \
           src/w55d_08023fd0_MATCHED.c \
           src/w55a_08027e8c_MATCHED.c \
           src/w55d_08028778_MATCHED.c \
           src/w56d_08014944_MATCHED.c \
           src/w56d_0801509c_MATCHED.c \
           src/w57a_08010138_MATCHED.c \
           src/w57a_08025a64_MATCHED.c \
           src/w57c_0801d070_MATCHED.c \
           src/w57d_08018d18_MATCHED.c \
           src/w58b_080067bc_MATCHED.c \
           src/w59d_08028fec_MATCHED.c \
           src/w59c_08021fdc_MATCHED.c \
           src/w60b_0804a694_MATCHED.c \
           src/w60b_0802f364_MATCHED.c \
           src/w60c_08013600_MATCHED.c \
           src/w60c_08015378_MATCHED.c \
           src/w60c_08015538_MATCHED.c \
           src/w60d_08014a44_MATCHED.c \
           src/w60d_08013024_MATCHED.c \
           src/w60d_08012274_MATCHED.c \
           src/w60d_080137e4_MATCHED.c \
           src/w61c_08010bb4_MATCHED.c \
           src/w61c_0801bc70_MATCHED.c \
           src/w63c_0802cce4_MATCHED.c \
           src/w64a_080466ac_MATCHED.c \
           src/w65b_0800cf10_MATCHED.c \
           src/w65d_0804a0a4_MATCHED.c \
           src/w65d_0801910c_MATCHED.c \
           src/w66a_080147fc_MATCHED.c \
           src/w66a_08012a3c_MATCHED.c \
           src/w66a_08025b60_MATCHED.c \
           src/w67a_080289c4_MATCHED.c \
           src/w67d_08015f90_MATCHED.c \
           src/w68c_080146c0_MATCHED.c \
           src/w68a_08013138_MATCHED.c \
           src/w68a_08012504_MATCHED.c \
           src/w68a_08026238_MATCHED.c \
           src/w69a_08013cac_MATCHED.c \
           src/w69d_08018064_MATCHED.c \
           src/w70a_08012d28_MATCHED.c \
           src/w70a_08013f24_MATCHED.c \
           src/w70a_08024cd8_MATCHED.c \
           src/w72a_080493ec_MATCHED.c \
           src/w73a_08041e58_MATCHED.c \
           src/w73a_0801264c_MATCHED.c \
           src/w74a_0801238c_MATCHED.c \
           src/w74a_08012880_MATCHED.c \
           src/w78d_08037f38_MATCHED.c \
           src/w83a_08014b54_MATCHED.c \
           src/w83a_0802fda0_MATCHED.c \
           src/w83a_08039cfc_MATCHED.c \
           src/w84d_0804367c_MATCHED.c


# Wave 6 BLK-A: sub_08017D50 needs old_agbcc (ands dest-reg idiom).
# Evidence: docs/match_notes_wave6_blkA.md.
$(BUILD)/wave6_blka_old.o: src/wave6_blka_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 6 L1: Task_38AD4 needs old_agbcc (r1/r3 ladder allocation).
# Evidence: docs/match_notes_wave6_l1.md.
$(BUILD)/wave6_l1_old.o: src/wave6_l1_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 6 L3: all 15 need old_agbcc.
# Evidence: docs/match_notes_wave6_l3.md.
$(BUILD)/wave6_l3_old.o: src/wave6_l3_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 7 batch E: Rank_FromValue needs old_agbcc (omits push {lr} for
# true-leaf switch; main agbcc emits it). Evidence: docs/match_notes_wave7_e.md.
$(BUILD)/wave7_e_old.o: src/wave7_e_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 7 batch D: ObjInit_TypeA/TypeB/205B8 need old_agbcc (combiner
# dest-reg, double-OR allocation). Evidence: docs/match_notes_wave7_d.md.
$(BUILD)/wave7_d_old.o: src/wave7_d_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 7 batch B: Task_367E0 needs old_agbcc (dispatcher regalloc).
# Evidence: docs/match_notes_wave7_b.md.
$(BUILD)/wave7_b.o: src/wave7_b.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 7 batch F/G2 old_agbcc files.
# Evidence: docs/match_notes_wave7_f.md, docs/match_notes_wave7_g2.md.
$(BUILD)/wave7_f_old.o: src/wave7_f_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
$(BUILD)/wave7_g2_old.o: src/wave7_g2_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 7 batch C: ObjInit_TypeC/2184C need old_agbcc.
# Evidence: docs/match_notes_wave7_c.md.
$(BUILD)/wave7_c_old.o: src/wave7_c_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 8 batch R: 9 re-derived G1 claims need old_agbcc.
# Evidence: docs/match_notes_wave8_R.md.
$(BUILD)/wave8_r_old.o: src/wave8_r_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 8 batch B: Tst_0800B2D8/B2F0 need old_agbcc.
# Evidence: docs/match_notes_wave8_B.md.
$(BUILD)/wave8_b_old.o: src/wave8_b_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 8 batch M: Ewram_BumpAlloc needs old_agbcc.
# Evidence: docs/match_notes_wave8_M.md.
$(BUILD)/wave8_m_old.o: src/wave8_m_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 8 batch U: unattempted-pool cracks need old_agbcc.
# Evidence: docs/match_notes_wave8_U.md.
$(BUILD)/wave8_u_old.o: src/wave8_u_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 8 batch S: 23 small-leaf matches need old_agbcc.
# Evidence: docs/match_notes_wave8_S.md.
$(BUILD)/wave8_s_old.o: src/wave8_s_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 9 batch A: ObjInit_1D3C0 needs old_agbcc (else-branch prologue
# scheduler order: movs r0,#1 before movs r1,#0 via single volatile asm;
# memory barrier defeats the s+0x50+28 combiner fold).
# Evidence: docs/match_notes_wave9_A.md.
$(BUILD)/wave9_a_old.o: src/wave9_a_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 9 batch F: blocked revisits (FlagToggle_080481FC, TableLookup_U16).
# Both need old_agbcc (pinned-register allocation, inline-asm idioms).
# Evidence: docs/match_notes_wave9_F.md.
$(BUILD)/wave9_f_old.o: src/wave9_f_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 9 batch B: Script_StepState @0x0803F480 (964B) needs old_agbcc.
# Evidence: docs/match_notes_wave9_B.md.
$(BUILD)/wave9_b_old.o: src/wave9_b_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 9 batch D: leaves-up bulk batch 1 (old_agbcc).
# Evidence: docs/match_notes_wave9_D.md.
$(BUILD)/wave9_d_old.o: src/wave9_d_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 9 batch E: leaves-up bulk batch 2 (old_agbcc).
# Evidence: docs/match_notes_wave9_E.md.
$(BUILD)/wave9_e_old.o: src/wave9_e_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 10 worker T: Task_3AFFC unblock path — sub_0800B368 (72 B).
# Needs old_agbcc (inverted-if beq layout, store scheduling).
# Evidence: docs/match_notes_wave10_T.md.
$(BUILD)/wave10_T_old.o: src/wave10_T_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 10 worker R: W9 staging blockers (FlagBit_Get_11D34,
# FlagBit_Set_11D68, BitCtl_520C). Needs old_agbcc.
# Evidence: docs/match_notes_wave10_R.md.
$(BUILD)/wave10_R_old.o: src/wave10_R_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 10 worker H: ComputeFields @0x0804CFD4 (180 B). Needs old_agbcc
# (opaque-ldrb pinning + r1->r3 save + adds-dest asm).
# Evidence: docs/match_notes_wave10_H.md.
$(BUILD)/wave10_H_old.o: src/wave10_H_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 10 batch L: leaves-up bulk batch (7 functions, old_agbcc).
# Evidence: docs/match_notes_wave10_L.md.
$(BUILD)/wave10_L_old.o: src/wave10_L_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 11 worker D: sub_0803FACC (IsSpecialChip_3FACC) needs old_agbcc
# (bx lr epilogue; main agbcc always emits push {lr} / pop {pc}).
# Evidence: docs/match_notes_wave11_D.md.
$(BUILD)/wave11_D_old.o: src/wave11_D_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 11 worker B: 7 functions, all need old_agbcc (branched-leaf bx lr
# epilogues; main agbcc emits push {lr} / pop {pc}).
# Evidence: docs/match_notes_wave11_B.md.
$(BUILD)/wave11_B_old.o: src/wave11_B_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 11 worker A: 26 functions, all need old_agbcc (branched-leaf bx lr
# epilogues; main agbcc emits push {lr} / pop {pc}).
# Evidence: docs/match_notes_wave11_A.md.
$(BUILD)/wave11_A_old.o: src/wave11_A_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 9 batch C: division-block/libc no-interwork TU (Memcpy_4DFA8,
# DivZeroStub_4DD90). agbcc emits `pop {pc}` / `pop {r4,r5,pc}` epilogues
# only WITHOUT -mthumb-interwork.
# Evidence: docs/match_notes_wave9_C.md.
$(BUILD)/wave9_c_noiw.o: src/wave9_c_noiw.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) -O2 -Wimplicit -Wparentheses -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 6 L4: all 29 need old_agbcc.
# Evidence: docs/match_notes_wave6_l4.md.
$(BUILD)/wave6_l4_old.o: src/wave6_l4_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 6 BLK-B: sub_080230A0/Task_37440 need old_agbcc.
# Evidence: docs/match_notes_wave6_blkB.md.
$(BUILD)/wave6_blkb_old.o: src/wave6_blkb_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 5 POOL-G1/H2: these match only with old_agbcc.
# Evidence: docs/match_notes_wave5_g1.md, docs/match_notes_wave5_h2.md.
$(BUILD)/wave5_g1_old.o: src/wave5_g1_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
$(BUILD)/wave5_h2_old.o: src/wave5_h2_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 5 POOL-H1: TableDispatch_9380 matches only with old_agbcc
# (r0/r1 allocation). Evidence: docs/match_notes_wave5_h1.md.
$(BUILD)/wave5_h1_old.o: src/wave5_h1_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 5 blocked-revisit: HBlank_VCountUpdate matches only with
# old_agbcc (needed for instruction ORDER: movs-before-ldrb, not
# just regalloc). Evidence: docs/match_notes_wave5_blk.md.
$(BUILD)/wave5_blk_old.o: src/wave5_blk_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 4 batch K: Task_35EB0/Task_36724 match only with old_agbcc
# (main agbcc swaps r0/r1 in the mask-clear sequence). Evidence:
# docs/match_notes_wave4_k.md.
$(BUILD)/wave4_k_old.o: src/wave4_k_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 4 batch J: Wrap_0804DF9E is intentionally NOT in SRCS_C. Its 8-byte
# function (push{lr}; bl 0x0804DD9C; movs r0,#0; pop{pc}) is emitted via
# BYTE() in ldscript.ld — GAS pads the C section with a 2-byte nop the
# ROM does not have (next function at 0x0804DFA8). The .c file
# (src/wave4_j_noiw.c) remains as the documented, build-verified source
# (no-interwork TU, cf. DivZeroStub_4DEDE precedent).

# Wave 4 batch J: 4 pointer-table functions match only with old_agbcc
# (main agbcc mis-allocates one register each). Evidence:
# docs/match_notes_wave4_j.md.
$(BUILD)/wave4_j_old.o: src/wave4_j_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 4 batch I: 45 functions match only with old_agbcc (indirect
# dispatcher shape: ROM keeps index in r3, main agbcc merges into r1).
# Evidence: docs/match_notes_wave4_i.md.
$(BUILD)/wave4_i_old.o: src/wave4_i_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 3: no-interwork TU (SRAM/libgcc-style region). agbcc emits
# `pop {pc}` epilogues only WITHOUT -mthumb-interwork. Evidence:
# docs/match_notes_wave3_d.md, docs/match_notes_wave3_e.md.
$(BUILD)/wave3_d_noiw.o: src/wave3_d_noiw.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) -O2 -Wimplicit -Wparentheses -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# (wave3_e_noiw.c is intentionally NOT in SRCS_C: its 10-byte function is
# emitted via BYTE() in ldscript.ld — see the .text.w3e_divzero_4dede note.
# The .c file remains as the documented, build-verified source.)

# Wave 3 batch 5: ConstZeroS16_2472C needs old_agbcc (main agbcc DCEs the
# kept `lsls r0,r0,#24`). Evidence: docs/match_notes_wave3_e.md.
$(BUILD)/wave3_e_old.o: src/wave3_e_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
OBJS    := $(patsubst %.s,$(BUILD)/%.o,$(notdir $(SRCS_S))) $(patsubst %.c,$(BUILD)/%.o,$(notdir $(SRCS_C)))

$(BUILD)/%.o: asm/%.s
	@mkdir -p $(BUILD)
	$(AS) $(ASFLAGS) -o $@ $<
ASFLAGS := -mcpu=arm7tdmi

# Phase 3: C matching. agbcc emits asm (-o file.s), then gas assembles.
# All Phase-3 C targets are Thumb; ARM files (later) need -marm instead
# of -mthumb and $(TOOLS)/agbcc/bin/agbcc_arm.
# NOTE: this agbcc driver accepts only a minimal flag set (no -I, no -c)
# and does NOT preprocess — so the Makefile runs system cpp first.
# ARM files (later) need -marm instead of -mthumb and
# $(TOOLS)/agbcc/bin/agbcc_arm.
CPP     := cpp
CPPFLAGS:= -I include
CFLAGS  := -O2 -mthumb-interwork -Wimplicit -Wparentheses

$(BUILD)/%.o: src/%.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/$*.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/$*.s $(BUILD)/$*.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/$*.s


# Wave 17-D: 2 files need old_agbcc (worker-verified 0-diff).
# Evidence: docs/match_notes_wave17_D.md.
$(BUILD)/w17d_0800b6a4.o: src/w17d_0800b6a4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w17d_0800b6a4.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w17d_0800b6a4.s $(BUILD)/w17d_0800b6a4.i
	python3 $(TOOLS)/fix_tail_align.py $(BUILD)/w17d_0800b6a4.s .text.w17d_0800B6A4
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w17d_0800b6a4.s
$(BUILD)/w17d_08016e0c.o: src/w17d_08016e0c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w17d_08016e0c.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w17d_08016e0c.s $(BUILD)/w17d_08016e0c.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w17d_08016e0c.s

# Wave 17-D: 3 files need fix_tail_align.py (2B c046 tail, worker-verified).
# Evidence: docs/match_notes_wave17_D.md.
$(BUILD)/w17d_0800b3b0.o: src/w17d_0800b3b0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w17d_0800b3b0.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w17d_0800b3b0.s $(BUILD)/w17d_0800b3b0.i
	@echo '	.align	1, 0' >> $(BUILD)/w17d_0800b3b0.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w17d_0800b3b0.s
$(BUILD)/w17d_080254e0.o: src/w17d_080254e0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w17d_080254e0.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w17d_080254e0.s $(BUILD)/w17d_080254e0.i
	python3 $(TOOLS)/fix_tail_align.py $(BUILD)/w17d_080254e0.s .text.w17d_080254E0
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w17d_080254e0.s
$(BUILD)/w17d_080228bc.o: src/w17d_080228bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w17d_080228bc.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w17d_080228bc.s $(BUILD)/w17d_080228bc.i
	python3 $(TOOLS)/fix_tail_align.py $(BUILD)/w17d_080228bc.s .text.w17d_080228BC
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w17d_080228bc.s


# Wave 15 worker B: bulk leaves-up rows 0-90, main agbcc (17 functions).
# fix_tail_align for the 4 sections without mid-section pools
# (0x08000624, 0x08024648, 0x0801e87c, 0x08016e4c); the 4 with mid-section
# pools (0x080247c4, 0x08024918, 0x080104cc, 0x0804a340) keep the 2B c046
# tail (known artifact, function extents verified 0-diff).
# Evidence: docs/match_notes_wave15_B.md, docs/wave15_B_results.tsv.
$(BUILD)/wave15_B.o: src/wave15_B.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w15b_08000624 .text.w15b_08024648 .text.w15b_0801e87c .text.w15b_08016e4c
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 15 worker B: bulk leaves-up rows 0-90, old_agbcc (3 functions).
# Evidence: docs/match_notes_wave15_B.md, docs/wave15_B_results.tsv.
$(BUILD)/wave15_B_old.o: src/wave15_B_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)


# Wave 15 worker C: bulk leaves-up rows 91-180, main agbcc (23 functions).
# fix_tail_align for 4 sections (0x08000630, 0x0804c814, 0x0800ecd8, 0x080246fc).
# Evidence: docs/match_notes_wave15_C.md.
$(BUILD)/wave15_C.o: src/wave15_C.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w15c1_08000630 .text.w15c1_0804C814 .text.w15c1_0800ECD8 .text.w15c2_080246FC
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 15 worker C: bulk leaves-up rows 91-180, old_agbcc (13 functions).
# Evidence: docs/match_notes_wave15_C2.md.
$(BUILD)/wave15_C_old.o: src/wave15_C_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)



# Wave 15-C: old_agbcc files (bulk leaves-up rows 91-180).
$(BUILD)/w15c_0800eaf4.o: src/w15c_0800eaf4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_08011a0c.o: src/w15c_08011a0c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_080181ac.o: src/w15c_080181ac.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_08018310.o: src/w15c_08018310.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_08018e1c.o: src/w15c_08018e1c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_08019b64.o: src/w15c_08019b64.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0801a6ac.o: src/w15c_0801a6ac.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0801c3fc.o: src/w15c_0801c3fc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0801c540.o: src/w15c_0801c540.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0801f9ec.o: src/w15c_0801f9ec.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_080200ec.o: src/w15c_080200ec.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0804d7c0.o: src/w15c_0804d7c0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0804d834.o: src/w15c_0804d834.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 15-C: 4 sections need fix_tail_align.py (2B c046 tail).
$(BUILD)/w15c_08000630.o: src/w15c_08000630.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w15c1_08000630
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0804c814.o: src/w15c_0804c814.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w15c1_0804C814
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_0800ecd8.o: src/w15c_0800ecd8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w15c1_0800ECD8
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w15c_080246fc.o: src/w15c_080246fc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w15c2_080246FC
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Per-file compiler overrides. Some functions only match with old_agbcc
# (the pre-patched variant in tools/agbcc/bin); the newer agbcc changes
# register allocation on them. Workers: add your file here when you
# prove the need, with the evidence in docs/match_notes_<group>.md.
OLDAGBCC := $(TOOLS)/agbcc/bin/old_agbcc
$(BUILD)/text.o: src/text.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 2: Vec2 mirror helpers need old_agbcc (main agbcc mis-allocates
# the (u8 *)o / p += 35 shape). Evidence: docs/match_notes_wave2.md.
$(BUILD)/vec2.o: src/vec2.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 2: EntryMgr setup/teardown need old_agbcc (scheduler divergence:
# main agbcc emits ldrb before movs and mis-allocates the flag pointer).
# Evidence: docs/match_notes_wave2.md. gateddispatch.c uses main agbcc.
$(BUILD)/entrymgr.o: src/entrymgr.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

all: $(FILE_NAME).gba

$(BUILD)/%.o: src/%.s
	@mkdir -p $(BUILD)
	$(AS) $(ASFLAGS) -o $@ $<

$(FILE_NAME).elf: $(OBJS) ldscript.ld
	$(LD) -T ldscript.ld -o $@ $(OBJS)

$(FILE_NAME).gba: $(FILE_NAME).elf $(GBAFIX)
	$(OBJCOPY) -O binary $< $@
	$(GBAFIX) $@ -t"$(TITLE)" -c$(GAME_CODE) -m$(MAKER_CODE) -r$(REVISION)
	python3 $(TOOLS)/finish_rom.py $@

# Wave 12 worker C: bulk leaves-up layer (5 functions). All need old_agbcc
# (register pinning, explicit asm, pool-load scheduling).
# Evidence: docs/match_notes_wave12_C.md.
$(BUILD)/wave12_C_old.o: src/wave12_C_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 12 worker B: r1/r2/r3 allocation-forcing cluster (4 functions).
# All need old_agbcc (pinned copy registers). The generated .s has its
# compiler-emitted ".align 2, 0" rewritten to ".align 1, 0" so GAS does
# not pad the 30-B (B5) and 50-B (B7) sections with "mov r8, r8".
# Evidence: docs/match_notes_wave12_B.md.
$(BUILD)/wave12_B_old.o: src/wave12_B_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w12b_0804d7a0 .text.w12b_0802d8f4
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 13 worker B: 3 Task_3AFFC callees, all main agbcc (verified
# byte-identical). The .s needs "\t.align\t2, 0" appended after the
# .size of the BEE0/241F8 sections so GAS emits 00 00 (not 46c0) tail
# pads. The 24384 section (174 B) is NOT placed from this .o — GAS pads
# it to 176 with c046; its verified bytes are emitted via BYTE() in
# ldscript.ld. Evidence: docs/match_notes_wave13_B.md.
$(BUILD)/wave13_B.o: src/wave13_B.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/append_section_align.py $(@:.o=.s) .text.w12a_0800bee0 .text.w12a_080241f8
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 13 worker D: 4 leaves-up matches, all old_agbcc.
# Evidence: docs/match_notes_wave13_D.md.
$(BUILD)/wave13_D_old.o: src/wave13_D_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 14 worker D: blocked revisits, old_agbcc.
# Evidence: docs/match_notes_wave14_D.md.
$(BUILD)/wave14_D_old.o: src/wave14_D_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 14 worker B: 7 leaves-up matches, main agbcc.
# Evidence: docs/match_notes_wave14_B.md.
# 0x08004DFC (14 B) and 0x0802FC28 (34 B) are emitted via BYTE() in
# ldscript.ld (GAS c046 tail pad does not match ROM).
$(BUILD)/wave14_B.o: src/wave14_B.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 14 worker B: 5 leaves-up matches, old_agbcc.
# Evidence: docs/match_notes_wave14_B.md.
# 0x0802567C (86 B) is emitted via BYTE() in ldscript.ld.
$(BUILD)/wave14_B_old.o: src/wave14_B_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 14 worker B: 1 leaves-up match, no-interwork agbcc.
# Evidence: docs/match_notes_wave14_B.md.
# 0x0804E008 (82 B) is emitted via BYTE() in ldscript.ld.
$(BUILD)/wave14_B_noiw.o: src/wave14_B_noiw.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) -O2 -Wimplicit -Wparentheses -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 14 worker C: 28 bulk leaves-up matches, main agbcc.
# Coordinator-landed from staging/wave14_C/ (harness-verified 0-diff).
# Evidence: docs/match_notes_wave14_C.md, docs/wave14_C_results.tsv.
$(BUILD)/wave14_C.o: src/wave14_C.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 14 worker C: 6 bulk leaves-up matches, old_agbcc.
# Coordinator-landed from staging/wave14_C/ (harness-verified 0-diff).
# Evidence: docs/match_notes_wave14_C.md, docs/wave14_C_results.tsv.
$(BUILD)/wave14_C_old.o: src/wave14_C_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)


rom.sha1:
	@echo "$(EXPECTED_SHA1)  $(FILE_NAME).gba" > $@

compare: $(FILE_NAME).gba rom.sha1
	sha1sum -c rom.sha1

# Verifies the user-supplied baserom (never committed).
check:
	@test -f $(BASEROM) || (echo "error: baserom not found at '$(BASEROM)'. Place your legally-obtained dump there; it is never committed." && exit 1)
	@echo "$(EXPECTED_SHA1)  $(BASEROM)" | sha1sum -c - && echo "baserom OK"

clean:
	rm -rf $(BUILD) $(FILE_NAME).elf $(FILE_NAME).gba rom.sha1

.PHONY: all compare check clean

# Wave 16-D: 6 blocked-revisit matches (coordinator-verified 0-diff).
$(BUILD)/w16d_0803618c.o: src/w16d_0803618c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16d_08005fc0.o: src/w16d_08005fc0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16d_08021e64.o: src/w16d_08021e64.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16d_0804c7b4.o: src/w16d_0804c7b4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16d_08027c84.o: src/w16d_08027c84.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16d_0802fd68.o: src/w16d_0802fd68.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 16-B: 15 leaves-up matches (coordinator-verified 0-diff).
$(BUILD)/w16b_08017000.o: src/w16b_08017000.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_08020ed4.o: src/w16b_08020ed4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_0804580c.o: src/w16b_0804580c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w16b_0804580c
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_08025754.o: src/w16b_08025754.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_08024434.o: src/w16b_08024434.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_08025054.o: src/w16b_08025054.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_08010ba0.o: src/w16b_08010ba0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_080467dc.o: src/w16b_080467dc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_0800ea30.o: src/w16b_0800ea30.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_0800ebf0.o: src/w16b_0800ebf0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_0801ab34.o: src/w16b_0801ab34.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_080253bc.o: src/w16b_080253bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_080257fc.o: src/w16b_080257fc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w16b_080257fc
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_0802666c.o: src/w16b_0802666c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w16b_0802666c
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16b_080266ac.o: src/w16b_080266ac.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w16b_080266ac
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 16-C: 12 leaves-up matches (coordinator-verified 0-diff).
$(BUILD)/w16c_0804b110.o: src/w16c_0804b110.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_0804b954.o: src/w16c_0804b954.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w16c_0804b954
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_0800ebd0.o: src/w16c_0800ebd0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_tail_align.py $(@:.o=.s) .text.w16c_0800ebd0
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_08037914.o: src/w16c_08037914.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_0801bd7c.o: src/w16c_0801bd7c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_0802316c.o: src/w16c_0802316c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_0801bea0.o: src/w16c_0801bea0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_08019e0c.o: src/w16c_08019e0c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_0801962c.o: src/w16c_0801962c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_0801974c.o: src/w16c_0801974c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_08019a3c.o: src/w16c_08019a3c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w16c_08011b64.o: src/w16c_08011b64.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 17A: sub_0800B148 needs old_agbcc (mask/load const-first ordering,
# pinned-register allocator tuning). Evidence: docs/match_notes_wave17_A.md.
$(BUILD)/w17a_0800b148.o: src/w17a_0800b148.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 17C: ChipInit family (main agbcc).
$(BUILD)/w17c_chipinit.o: src/w17c_chipinit.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 17C: table functions (main agbcc).
$(BUILD)/w17c_table.o: src/w17c_table.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 17C: misc old_agbcc variants (F_080254E0, F_0802541C need old_agbcc regalloc).
# Evidence: docs/match_notes_wave17_C.md.
$(BUILD)/w17c_misc_old.o: src/w17c_misc_old.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 18-C: 2 blocked revisits cracked (coordinator-verified 0-diff, main agbcc).
# Evidence: docs/match_notes_wave18_C.md. Extern aliases renamed to real build
# symbols (Poke80_08016f74, _call_via_r1); PalModeSet_4DFC already .set in w16d.
$(BUILD)/w18c_0800e6d0.o: src/w18c_0800e6d0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_08049704.o: src/w18d_08049704.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_0801f154.o: src/w18d_0801f154.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_0801cdac.o: src/w18d_0801cdac.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_0801f1a8.o: src/w18d_0801f1a8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_0801f050.o: src/w18d_0801f050.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_0802030c.o: src/w18d_0802030c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_080203a4.o: src/w18d_080203a4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18d_0801ee14.o: src/w18d_0801ee14.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18c_0803aed0.o: src/w18c_0803aed0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 18-B: 17 leaves-up (16 main, 1 old_agbcc). Coordinator-verified 0-diff.
# Evidence: docs/match_notes_wave18_B.md. F_0802533C renamed to F_0802533c (case).
$(BUILD)/w18b_080114b8.o: src/w18b_080114b8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08011be0.o: src/w18b_08011be0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_0801d24c.o: src/w18b_0801d24c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_080217a8.o: src/w18b_080217a8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08021da8.o: src/w18b_08021da8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08021dd0.o: src/w18b_08021dd0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_080225e4.o: src/w18b_080225e4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_0802260c.o: src/w18b_0802260c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08022f88.o: src/w18b_08022f88.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08022fb0.o: src/w18b_08022fb0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08025524.o: src/w18b_08025524.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_080257bc.o: src/w18b_080257bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08026144.o: src/w18b_08026144.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08037970.o: src/w18b_08037970.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08038e88.o: src/w18b_08038e88.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_0803ae44.o: src/w18b_0803ae44.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w18b_08024eb8.o: src/w18b_08024eb8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 19-C: twin scheduler pair (old_agbcc; pinned-r2 barrier idiom).
$(BUILD)/w19c_0800fff4.o: src/w19c_0800fff4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19c_0801009c.o: src/w19c_0801009c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 19-C: ChipInit twins (main agbcc; 78 B needs FIXALIGN1 for exact-size sections).
$(BUILD)/w19c_08017620.o: src/w19c_08017620.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19c_08017d00.o: src/w19c_08017d00.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 19-D: pool-placement blocker (main agbcc; FIXALIGN1-extended: replace ALL
# .align 2,0 — the pool's own .align also forces 4-byte section alignment).
$(BUILD)/w19d_080250bc.o: src/w19d_080250bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/g' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 19-B: 8 NewNode-family matches (coordinator independently re-verified 0-diff).
$(BUILD)/w19b_08017434.o: src/w19b_08017434.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19b_080214f4.o: src/w19b_080214f4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19b_0801f180.o: src/w19b_0801f180.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19b_080228e0.o: src/w19b_080228e0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19b_080236b0.o: src/w19b_080236b0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19b_0801d308.o: src/w19b_0801d308.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19b_08021cac.o: src/w19b_08021cac.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w19b_0801d278.o: src/w19b_0801d278.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-D: Setup_08005F44 (main agbcc; 124 B section incl. pool in gap).
# Evidence: docs/match_notes_wave20_D.md.
$(BUILD)/w20d_08005f44.o: src/w20d_08005f44.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-D: ChkFlag_080247E8 (main agbcc; 48 B, mid-function pool).
# Evidence: docs/match_notes_wave20_D.md.
$(BUILD)/w20d_080247e8.o: src/w20d_080247e8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-D: Setup_0801029C (main agbcc; 86 B needs FIXALIGN1 for exact-size section).
# Only the section-leading .align is rewritten (pool's .align must stay 2 for ldr).
# Evidence: docs/match_notes_wave20_D.md.
$(BUILD)/w20d_0801029c.o: src/w20d_0801029c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i '0,/\.align\s*2, 0/s//.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-D: F_08010EC4 (main agbcc; 110 B needs FIXALIGN1 for exact-size section).
# Evidence: docs/match_notes_wave20_D.md.
$(BUILD)/w20d_08010ec4.o: src/w20d_08010ec4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i '0,/\.align\s*2, 0/s//.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-D: Setup twins 0800EB30/0800EC3C (main agbcc; 64 B each).
# Evidence: docs/match_notes_wave20_D.md.
$(BUILD)/w20d_0800eb30.o: src/w20d_0800eb30.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w20d_0800ec3c.o: src/w20d_0800ec3c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-B: NewNode_0801DFC4 (main agbcc + FIXALIGN1; 98 B).
# Evidence: docs/match_notes_wave20_B.md.
$(BUILD)/w20b_0801dfc4.o: src/w20b_0801dfc4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align[[:space:]]*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-B: BuildList_08021D10 (main agbcc + custom pool sed; 114 B).
# Pool's .align 2,0 replaced with .short 0x0000 to avoid 4-byte section
# padding (pool stays 4-aligned at +0x14 by construction).
# Evidence: docs/match_notes_wave20_B.md.
$(BUILD)/w20b_08021d10.o: src/w20b_08021d10.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i '0,/\.align[[:space:]]*2, 0/s//.align 1, 0/' $(@:.o=.s)
	sed -i 's/^\t\.align\t2, 0$$/\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-B: Sub_08024BC8 (old_agbcc; 76 B).
# Evidence: docs/match_notes_wave20_B.md.
$(BUILD)/w20b_08024bc8.o: src/w20b_08024bc8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-D: Setup wrappers 08010E7C/08010EA0 (main agbcc; 36 B each, twins).
# Codegen-shaped callee extern ((u8,s8,s8,s8,u8)->u32). Evidence:
# docs/match_notes_wave21_D.md.
$(BUILD)/w21d_08010e7c.o: src/w21d_08010e7c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
$(BUILD)/w21d_08010ea0.o: src/w21d_08010ea0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-D: F_08010270 (main agbcc + FIXALIGN1; 42 B exact-size section).
# Wrapper around Setup_0801029C. Evidence: docs/match_notes_wave21_D.md.
$(BUILD)/w21d_08010270.o: src/w21d_08010270.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i '0,/\.align\s*2, 0/s//.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-D: DrawObj_080439D8 (old_agbcc; 184 B + 12 B pool).
# old_agbcc scheduler matches ROM's lsr-before-address order; pinned r4/r6.
# Evidence: docs/match_notes_wave21_D.md.
$(BUILD)/w21d_080439d8.o: src/w21d_080439d8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-D: F_08024F30 (main agbcc; 20 B + 4 B pool).
# Empty-asm barrier prevents base+20 pool folding.
# Evidence: docs/match_notes_wave21_D.md.
$(BUILD)/w21d_08024f30.o: src/w21d_08024f30.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
$(BUILD)/w21d_08024f70.o: src/w21d_08024f70.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-D: F_080119DC (main agbcc; 48 B exact, no pool).
# Second if-block body via inline asm (.short 0x1808 for GAS-rejected
# adds r0,r1,r0). Evidence: staging/wave22_D/w22d_080119DC.c.
$(BUILD)/w22d_080119dc.o: src/w22d_080119dc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-D: Entry_TryActivate_08010F34 (main agbcc; 84 B incl. mid-function pool).
$(BUILD)/w22d_08010f34.o: src/w22d_08010f34.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-D: ChipState_Tick_0800E3A0 (main agbcc; 86 B + 2 pad + 8 B pool).
$(BUILD)/w22d_0800e3a0.o: src/w22d_0800e3a0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-D: Sram_TryInitSlot_08001EBC (main agbcc; 90 B + 2 pad, pools interior).
$(BUILD)/w22d_08001ebc.o: src/w22d_08001ebc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-D: DrawObj_080405D8 (main agbcc + FIXALIGN1; 180 B + 12 B pool).
# Prologue emitted via one inline-asm block (.short 0x1808 for the
# GAS-rejected adds r0,r1,r0). Evidence: staging/wave22_D/w22d_080405D8.c.
$(BUILD)/w22d_080405d8.o: src/w22d_080405d8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i '0,/\.align\s*2, 0/s//.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-C: F_08011A78 (main agbcc + explicit .short 0x0000 pad; 80 B).
# q pinned r1 but later uses go through p->f0 (ROM kills q in ldrb r1 then
# reloads); eight (r6) initialized after *r2=z for movs order. 78 B code +
# 2 B zero pad: trailing nop replaced via explicit pad (linker-padding idiom).
# Evidence: docs/match_notes_wave22_C.md.
$(BUILD)/w22c_08011a78.o: src/w22c_08011a78.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tr1$$/\tbx\tr1\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-C: sub_08016D2C (old_agbcc; 128 B incl. 12 B trailing pool).
# Clobber-reservation for tbl/tab2 pool loads (-> r1); tied asm keeps the
# int copy before the clamp; int m=-13 for movs+negs mask.
# Evidence: docs/match_notes_wave22_C.md.
$(BUILD)/w22c_08016d2c.o: src/w22c_08016d2c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-A: Node_PopAndInit_11E20 @0x08011E20 (120 B incl. trailing pool; main agbcc).
# Sibling of w16b_08017000. Pinned-barrier pool loads + array-index idiom
# steer tbl->r1/index->r0. Evidence: docs/match_notes_wave22_A.md.
$(BUILD)/w22a_08011e20.o: src/w22a_08011e20.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 23-A: sub_08002E80 @0x08002E80 (84 B; old_agbcc).
# DispCnt shadow save/restore via 0x02003230 table. Wave-22 p6 shape was 4
# diffs under main agbcc (r1/r4 swap: disp store-addr vs p[0] temp);
# old_agbcc emits ROM order exactly (mov r1,sp / ldrh r4,[r2,#0] /
# orrs r0,r4 / strh r0,[r1,#0]). Fits 0x08002e70(+16B)..0x08002ed4 exactly.
# Evidence: docs/match_notes_wave23_A.md.
$(BUILD)/w23a_08002e80.o: src/w23a_08002e80.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 23-A: sub_08002CB0 @0x08002CB0 (112 B; main agbcc + sed fixups).
# DMA3 setup: *p=(*p&0xFFF8)|0x1300 via (u16*)0x020031E0; q=(vu32*)0x040000D4
# with q[0]=&spv(zero), q[1]=p+4, q[2]=0x8500000E; p[2..5]=C008/4205/4406/4807;
# bl DispCntRestore_Dma3 (matched/global, plain extern). Single-expression
# v=(*p&m)|0x1300 gives the sibling-&= load order (ldr r2/r0, ldrh r1,
# ands r0,r1). The scheduler will NOT hoist movs r3,#0 after the ands nor put
# the 0x1300 materialization in r4, so sed fixes: push{r4,lr}; insert
# mov r3,#0 after the and; mat r3->r4; drop mov r0,#0; str r3,[sp];
# pool ldr r3->r4 (x2); pop{r4}+pop{r0}. Fits 0x08002c74(+60B)..0x08002D20.
# Evidence: docs/match_notes_wave23_A.md.
$(BUILD)/w23a_08002cb0.o: src/w23a_08002cb0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i -e 's/^\tpush\t{lr}$$/\tpush\t{r4, lr}/' -e '/^\tand\tr0, r0, r1$$/a\\tmov\tr3, #0' -e 's/^\tmov\tr3, #152$$/\tmov\tr4, #152/' -e 's/^\tlsl\tr3, r3, #5$$/\tlsl\tr4, r4, #5/' -e 's/^\tadd\tr1, r3, #0$$/\tadd\tr1, r4, #0/' -e '/^\tmov\tr0, #0$$/d' -e 's/^\tstr\tr0, \[sp\]$$/\tstr\tr3, [sp]/' -e 's/^\tldr\tr3, \.L3+20$$/\tldr\tr4, .L3+20/' -e 's/^\tldr\tr3, \.L3+28$$/\tldr\tr4, .L3+28/' -e 's/^\tadd\tr0, r3, #0$$/\tadd\tr0, r4, #0/g' -e 's/^\tpop\t{r0}$$/\tpop\t{r4}\n\tpop\t{r0}/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-A: InitRec28_4AF20 @0x0804AF20 (112 B, main agbcc + sed fixups).
# Zeroes a 28-byte record at p, then fills: p[8]=TblGetByte_24384(a),
# p[10]=TblGetByte_24384(c), p[12]=Sub200_08024514(b), p[14]=Sub200_08024514(d),
# p[20]=a, p[22]=c. Two findings closed it: (1) hand-decode of 0x82A7 is
# strh r7,[r4,#20] with r7=a (objdump scales strh/ldrh immediates by 2, so
# the field is 10) -- wave-23's "p+20=b" reading was wrong; with =a/=c, b is
# dead after call 1 so b->r2 (caller-saved) is gcc-consistent. (2) gcc
# hoists 0x10000 out of any call-free loop (undefeatable: 14 -fno-* flags,
# old_agbcc -O2/-O1/-Os, noiw all still hoist) -- fixed via sed (prologue
# reorder + in-loop movs r5,#128/lsls r5,#9 + register renames, byte-neutral).
# Evidence: docs/match_notes_wave24_A.md, staging/wave24_A/w24a_0804af20.c.
$(BUILD)/w24a_0804af20.o: src/w24a_0804af20.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i -e '/^\tadd\tr4, r0, #0$$/d' \
	        -e 's/^\tldr\tr0, \[sp, #24\]$$/\tldr\tr4, [sp, #24]/' \
	        -e 's/^\tlsr\tr1, r1, #16$$/\tlsr\tr7, r1, #16/' \
	        -e '/^\tmov\tr8, r1$$/d' \
	        -e 's/^\tlsr\tr5, r2, #16$$/\tlsr\tr2, r2, #16/' \
	        -e 's/^\tlsr\tr7, r3, #16$$/\tlsr\tr6, r3, #16/' \
	        -e '0,/^\tlsl\tr0, r0, #16$$/s//\tlsl\tr4, r4, #16/' \
	        -e '/^\tlsr\tr6, r0, #16$$/a\\tmov\tr8, r4\n\tadd\tr4, r0, #0' \
	        -e 's/^\tlsr\tr6, r0, #16$$/\tlsr\tr4, r4, #16/' \
	        -e 's/^\tmov\tr2, #0$$/\tmov\tr3, #0/' \
	        -e '/^\tmov\tr3, #128$$/d' \
	        -e '/^\tlsl\tr3, r3, #9$$/d' \
	        -e 's/^\tstrb\tr2, \[r1\]$$/\tstrb\tr3, [r1]/' \
	        -e 's/^\tadd\tr0, r0, r3$$/\tmov\tr5, #128\n\tlsl\tr5, r5, #9\n\tadd\tr0, r0, r5/' \
	        -e 's/^\tlsl\tr0, r5, #24$$/\tlsl\tr0, r2, #24/' \
	        -e '/^\tlsl\tr0, r6, #24$$/i\\tmov\tr1, r8' \
	        -e 's/^\tlsl\tr0, r6, #24$$/\tlsl\tr0, r1, #24/' \
	        -e '/^\tadd\tr0, r7, #0$$/s//\tadd\tr0, r6, #0/' \
	        -e '0,/^\tmov\tr0, r8$$/s//\tadd\tr0, r7, #0/' \
	        -e '/^\tmov\tr0, r8$$/d' \
	        -e 's/^\tstrh\tr0, \[r4, #20\]$$/\tstrh\tr7, [r4, #20]/' \
	        -e 's/^\tstrh\tr7, \[r4, #22\]$$/\tstrh\tr6, [r4, #22]/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-D: SetAA_Clr2_08002EF4 @0x08002EF4 (48 B incl pool, main agbcc).
# Calls F_0804C630, writes (u16)0xAA to *(u32*)0x02003244, clears
# *(u8*)0x02000818/0x02000819. The pool-loaded 0xAA is impossible from a
# pure constant (agbcc always folds to movs r0,#170 -- brute-forced 19
# spellings x 2 compilers); instead (u32)&gAddrZero[0xAA] with gAddrZero an
# absolute symbol at 0x0 forces a pool word that links to exactly 0xAA.
# The 0x02000818/0x02000819 pool-forcing uses the tied empty-asm idiom from
# matched Clr2_08002f24. Evidence: docs/match_notes_wave24_D.md.
$(BUILD)/w24d_08002ef4.o: src/w24d_08002ef4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-D: CallTwice_08001C88 @0x08001C88 (32 B, main agbcc).
# Plain do-while calling sub_08001ca8 (BLOCKED, absolute-symbol stub) twice
# with p=(u8*)0x02002F50, p+=24, i<=1. No steering needed.
# Evidence: docs/match_notes_wave24_D.md.
$(BUILD)/w24d_08001c88.o: src/w24d_08001c88.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-B: Load4Tiles @0x080097cc (148 B, main agbcc + sed fixups).
# Copies 4x32B tiles from ROM tables (0x081720B4/0x081720CC) to VRAM.
# extern-array pool ordering idiom (forces pool-load-before-index-shift).
# sed fixes: ldrh temp-reg allocation r0->r1/r2/r1/r5 across the 4 copies
# + copy4 tail (add r6->r0, ldr r0->r1, add r4, drop `add r0,r6,#0`).
# Evidence: docs/match_notes_wave24_B.md.
$(BUILD)/w24b_080097cc.o: src/w24b_080097cc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i -e '0,/^\tldrh\tr0, \[r5\]$$/s//\tldrh\tr1, [r5]/' -e '0,/^\tlsl\tr0, r0, #5$$/s//\tlsl\tr0, r1, #5/' -e '0,/^\tldrh\tr0, \[r5, #2\]$$/s//\tldrh\tr2, [r5, #2]/' -e '0,/^\tlsl\tr0, r0, #5$$/s//\tlsl\tr0, r2, #5/' -e '0,/^\tldrh\tr0, \[r5, #4\]$$/s//\tldrh\tr1, [r5, #4]/' -e '0,/^\tlsl\tr0, r0, #5$$/s//\tlsl\tr0, r1, #5/' -e '0,/^\tldrh\tr0, \[r5, #6\]$$/s//\tldrh\tr5, [r5, #6]/' -e '0,/^\tlsl\tr0, r0, #5$$/s//\tlsl\tr0, r5, #5/' -e 's/^\tadd\tr6, r6, r0$$/\tadd\tr0, r6, r0/' -e 's/^\tldr\tr0, \.L3+20$$/\tldr\tr1, .L3+20/' -e 's/^\tadd\tr4, r4, r0$$/\tadd\tr4, r4, r1/' -e '/^\tadd\tr0, r6, #0$$/d' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-B: F_08026184 @0x08026184 (132 B, main agbcc + sed fixups).
# Two Fill_0802520C inits + Append loop 1..127. sed fuses the 0x8000
# materialization: mov r2,#128; lsl r2,#8; add r0,r2,#0; strh -> mov r0,#128;
# lsl r0,#8; strh r0,[r1,#22] (byte-neutral, fixes allocation).
# Evidence: docs/match_notes_wave24_B.md.
$(BUILD)/w24b_08026184.o: src/w24b_08026184.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 tools/patch_w24b_26184.py $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-B: F_08007728 @0x08007728 (84 B, main agbcc).
# EWRAM byte checks/sets at 0x02004830+620..622, conditional
# NodeInit_08022FB0. extern-array idiom prevents offset folding.
# Evidence: docs/match_notes_wave24_B.md.
$(BUILD)/w24b_08007728.o: src/w24b_08007728.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-C: Ewram4830_StateReset_0800A6BC @0x0800A6BC (152 B, old_agbcc).
# EWRAM 0x02004830 state reset. Pinned-sh-r1 + honest-s8 + asm-barrier-base.
# Coordinator-verified 0-diff (clean-room + built ROM).
# Evidence: docs/match_notes_wave24_C.md.
$(BUILD)/w24c_0800a6bc.o: src/w24c_0800a6bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-C: ChipState_Tick_0800E748 @0x0800E748 (128 B, main agbcc).
# Chip-init state machine: switch + asm-ternary + volatile-reload + S2-base.
# Byte12_Gt1_080170c4 is UNMATCHED (TU-local absolute-symbol stub).
# Coordinator-verified 0-diff (clean-room + built ROM).
# Evidence: docs/match_notes_wave24_C.md.
$(BUILD)/w24c_0800e748.o: src/w24c_0800e748.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 24-C: ChipList_Setup_0800E224 @0x0800E224 (168 B, main agbcc).
# Chip list setup: movs-first-orr + zero-reuse. Callees all real build symbols.
# Coordinator-verified 0-diff (clean-room + built ROM).
# Evidence: docs/match_notes_wave24_C.md.
$(BUILD)/w24c_0800e224.o: src/w24c_0800e224.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 23-D: hand-written script-interpreter asm cluster (0x0804BDE0-0x0804C03C),
# 20 functions ASM-STAGED as file-scope __asm__ (mov ip,lr / bx ip, pop {r0} /
# bx r0, tst, tail-call `b` into mid-function entries — agbcc cannot emit).
# Cracks two BLOCKED: ListWalk_0804BDE0 (tst wall) and ValidateScriptPtr_0804BE2A.
# Evidence: staging/wave23_D/w23d_scriptops.c, docs/match_notes_wave23_D.md.
$(BUILD)/w23d_scriptops.o: src/w23d_scriptops.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 23-D: F_080378B8 (main agbcc; 88 B + 4 pool). Flag-dispatch returning
# 0-4; callees ChkFlag_080247E8/TblGet_f0A/F_080247C4.
# Evidence: staging/wave23_D/w23d_080378b8.c, docs/match_notes_wave23_D.md.
$(BUILD)/w23d_080378b8.o: src/w23d_080378b8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-B: Sub_08010308 (main agbcc + FIXALIGN1 all-occurrences; 90 B).
# Mid-function pool at +0x48 (4-aligned by construction). Sibling-shape from
# w20d_0801029c.c. Evidence: docs/match_notes_wave21_B.md.
$(BUILD)/w21b_08010308.o: src/w21b_08010308.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/g' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-B: Sub_08042AE4 (main agbcc; 124 B incl. trailing pool).
# Struct init with large offsets (18088+). Mid-function pool + trailing pool
# (18099 not CSE'd across branches). Evidence: docs/match_notes_wave21_B.md.
$(BUILD)/w21b_08042ae4.o: src/w21b_08042ae4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-A: Task_3AFFC @0x0803AFFC (932 B section incl. trailing pool; old_agbcc).
# 16-case switch on p[0x469d]. Clobber-reservation idiom steers the 0x469d
# pool-load regs (case 14 -> r0 via clobber "r2"; store6 -> r2 via clobber
# "r0","r1"); second empty volatile asm kills dest-reg coalescing. No
# FIXALIGN1: section is already the exact 932 B ROM footprint.
# Evidence: docs/match_notes_wave21_A.md.
$(BUILD)/w21a_0803affc.o: src/w21a_0803affc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-C: F_0801D2C8 (main agbcc + FIXALIGN1; 62 B).
# Evidence: docs/match_notes_wave20_C.md.
$(BUILD)/w20c_0801d2c8.o: src/w20c_0801d2c8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-C: SlotCopy_0801E14C (old_agbcc; 40 B section incl. pool).
# Evidence: docs/match_notes_wave20_C.md.
$(BUILD)/w20c_0801e14c.o: src/w20c_0801e14c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-C: TblSlotInit_080173D4 (old_agbcc; 40 B section incl. pool).
# Evidence: docs/match_notes_wave20_C.md.
$(BUILD)/w20c_080173d4.o: src/w20c_080173d4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-C: SlotClear_0801787C (old_agbcc; 44 B section incl. pool).
# Evidence: docs/match_notes_wave20_C.md.
$(BUILD)/w20c_0801787c.o: src/w20c_0801787c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-C: F_0804A450 (main agbcc; 68 B section incl. pools).
# Evidence: docs/match_notes_wave20_C.md.
$(BUILD)/w20c_0804a450.o: src/w20c_0804a450.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 20-C: F_0803E9BC (main agbcc; 96 B section incl. pools).
# Evidence: docs/match_notes_wave20_C.md.
$(BUILD)/w20c_0803e9bc.o: src/w20c_0803e9bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-C: sub_08047CC0 (main agbcc; 36 B section incl. pool).
# Staged/verified by Wave 20 worker C (dead-reg reuse: pin off->r3, reassign
# to 0); unlanded then because callees EntryMgr_Teardown/Setup were not in
# the build. Both are MATCHED in src/entrymgr.c. Re-verified 0-diff over
# full 36 B (0x47CC0-0x47CE4 incl. 0x46B4 pool) by Wave 21 worker C.
# Evidence: docs/match_notes_wave20_C.md, docs/match_notes_wave21_C.md.
$(BUILD)/w20c_08047cc0.o: src/w20c_08047cc0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-C: F_08043630 (main agbcc; 76 B = 62 code + 2 pad + 12 pool).
# Blocked-revisit of the wave-15 near-miss (2-byte allocator diff):
# early-zero idiom (u8 z = 0 while r0=y live, r3 dead -> movs r3,#0),
# u32 CountNonzeroStride decl suppresses the u8 return zero-extend,
# barrier keeps the 3 pools separate. Unmatched callees via .set;
# sub_08005A9C/CountNonzeroStride/Gfx_Blit3 resolve from the build.
# Evidence: docs/match_notes_wave21_C.md.
$(BUILD)/w21c_08043630.o: src/w21c_08043630.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 21-C: Sram_08001E30 (main agbcc + FIXALIGN1; 66 B code, 2 B 00 fill).
# Blocked-revisit (wave-6 L4): pin au->r6 + st->r4 + base->r5 (pushed
# callee-saved), sh1 temp hoists (au<<13) above base init. Callee
# Sram_RetryWrapper resolves from src/sram.c (no .set).
# Evidence: docs/match_notes_wave21_C.md.
$(BUILD)/w21c_08001e30.o: src/w21c_08001e30.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/\.align\s*2, 0/.align 1, 0/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-B: Setup10308_Flag15_0800ED20 (main agbcc; 34 B). Setup_08010308
# wrapper: store 15 into byte 0x20 of 0x02005130 when setup returns 1.
# Twin of Setup10270_Flag14_0800ECF8. Evidence: docs/match_notes_wave22_B.md.
$(BUILD)/w22b_0800ed20.o: src/w22b_0800ed20.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-B: Setup10270_Flag14_0800ECF8 (main agbcc; 38 B). Setup_08010270
# wrapper: store 14 into byte 0x20 of 0x02005130 when setup returns 1.
# Evidence: docs/match_notes_wave22_B.md.
$(BUILD)/w22b_0800ecf8.o: src/w22b_0800ecf8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 22-B: F_0802493C (old_agbcc; 124 B). Index validator dispatching to
# CheckPair_258D8/GetStride4Byte20/Clear20_Set21_FF/F_080254E0.
# Evidence: docs/match_notes_wave22_B.md.
$(BUILD)/w22b_0802493c.o: src/w22b_0802493c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-C: ShiftPairCfg_3F844 @0x0803F844 (220 B incl pool, old_agbcc).
# ShiftPair_Copy_800C config wrapper; sibling-shape transfer family template.
# Evidence: docs/match_notes_wave25_C.md, staging/wave25_C/w25c_0803f844.c.
$(BUILD)/w25c_0803f844.o: src/w25c_0803f844.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-C: ShiftPairCfg_46810 @0x08046810 (220 B incl pool, old_agbcc).
# Sibling of 3F844; c128 hoisted to r4 via pin+asm (q2 in r5 variant).
# Evidence: docs/match_notes_wave25_C.md, staging/wave25_C/w25c_08046810.c.
$(BUILD)/w25c_08046810.o: src/w25c_08046810.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-C: ShiftPairCfg_45914 @0x08045914 (228 B incl pool, old_agbcc).
# Sibling; asm movs/lsl for 292; c128 hoist; EWRAM 0x02004DB0/0x02004DE4.
# Evidence: docs/match_notes_wave25_C.md, staging/wave25_C/w25c_08045914.c.
$(BUILD)/w25c_08045914.o: src/w25c_08045914.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-C: ShiftPairCfg_4A1F0 @0x0804A1F0 (220 B incl pool, old_agbcc).
# Sibling; direct copy of 3F844 template, 0 diffs first try.
# Evidence: docs/match_notes_wave25_C.md, staging/wave25_C/w25c_0804a1f0.c.
$(BUILD)/w25c_0804a1f0.o: src/w25c_0804a1f0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-C: ShiftPairCfg_3AD48 @0x0803AD48 (228 B incl pool, old_agbcc).
# Sibling; pool 0xFFFC via u32; negs(31) mask.
# Evidence: docs/match_notes_wave25_C.md, staging/wave25_C/w25c_0803ad48.c.
$(BUILD)/w25c_0803ad48.o: src/w25c_0803ad48.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-C: ShiftPairCfg_41890 @0x08041890 (228 B incl pool, old_agbcc + sed).
# Sibling; ROM epilogue uniquely uses pop {r1}; bx r1 (sed renames r0->r1).
# Evidence: docs/match_notes_wave25_C.md, staging/wave25_C/w25c_08041890.c.
$(BUILD)/w25c_08041890.o: src/w25c_08041890.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tpop\t{r0}$$/\tpop\t{r1}/; s/^\tbx\tr0$$/\tbx\tr1/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-D: HexFormat_08004998 @0x08004998 (108 B incl pool, main agbcc, pure C).
# Hex-formats u32 into 16-byte stack buffer; calls DrawText_048B4.
# Pool-const pin (r1=0xFFFF0000, init at declaration) + combiner-defeating
# mask (volatile "+r" barrier) + explicit copy asm; no post-process patch.
# True extent 108 B (not 102). Evidence: docs/match_notes_wave33_D.md.
$(BUILD)/w25b_08004998.o: src/w25b_08004998.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-B: Task_Clock_08026740 @0x08026740 (116 B incl pool, main agbcc).
# Clock task; pinned regs + if/else swap fixes bhi/bls inversion;
# S[18]=0 is inside if(S[19]!=99) (control-flow correction).
# True extent 116 B (not 112). Evidence: docs/match_notes_wave25_B.md.
$(BUILD)/w25b_08026740.o: src/w25b_08026740.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 25-D: FlagPairDispatch_08045838 @0x08045838 (220 B incl pool, old_agbcc).
# Two-stage s8-flag dispatch on p[0x46B0]/p[0x46B1]; value 1 programs EWRAM
# structs + calls ShiftPair_Copy_800C; value 3 clears bit 1; cross-jump
# shared store-back. Inline-asm ldrsb (agcc never emits ldrsb from C);
# byte-swapped pool misreads caught (0x46B1, 0x02004D7C).
# Evidence: docs/match_notes_wave25_D.md, staging/wave25_D/w25d_08045838.c.
$(BUILD)/w25d_08045838.o: src/w25d_08045838.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 26-B: Tbl_SwapAndUpdate_080259A4 @0x080259A4 (100 B incl 2B pad, main agbcc).
# Full 98-byte naked-asm transcription (prologue save-set compiler-impossible);
# explicit .short 0 pad (gcc pads c0 46). Evidence: docs/match_notes_wave26_B.md.
$(BUILD)/w26b_080259a4.o: src/w26b_080259a4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 26-B: ChipState_F_0800E440 @0x0800E440 (128 B incl pool, main agbcc).
# Sibling-shape transfer from ChipState_Tick_0800E748; inline-asm branchy
# ternary; ROM calls Byte12_Gt1_080170C4. Evidence: docs/match_notes_wave26_B.md.
$(BUILD)/w26b_0800e440.o: src/w26b_0800e440.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 26-C: ChipState_Advance_0801BF10 @0x0801BF10 (164 B, old_agbcc).
# State dispatch on s[13]; ((u32)s[35]<<28)>>28 shift-mask idiom.
# Evidence: docs/match_notes_wave26_C.md.
$(BUILD)/w26c_0801bf10.o: src/w26c_0801bf10.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 26-C: EntryState_08042C04 @0x08042C04 (172 B, old_agbcc).
# Switch on s[5] with EntryMgr teardown/setup; split-&= anti-fold.
# Evidence: docs/match_notes_wave26_C.md.
$(BUILD)/w26c_08042c04.o: src/w26c_08042c04.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 26-D: ObjInit_08016EFC @0x08016EFC (120 B incl pool, old_agbcc).
# 6-param object init; natural ldrsh from C (s16 array-index pattern).
# Evidence: docs/match_notes_wave26_D.md.
$(BUILD)/w26d_08016efc.o: src/w26d_08016efc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 26-D: NodeInitSwitch_0800D1E0 @0x0800D1E0 (152 B incl pool, old_agbcc).
# 4-pointer switch state machine; opaque +r barrier forces runtime negs.
# Evidence: docs/match_notes_wave26_D.md.
$(BUILD)/w26d_0800d1e0.o: src/w26d_0800d1e0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 27-A: TilemapRectFill_6AD8 @0x08006AD8 (768 B, asm transcription).
# 15 C variants exhausted on the allocator spill-slot wall; sanctioned asm
# transcription via dis2asm2.py. Evidence: docs/match_notes_wave27_A.md.
$(BUILD)/w27a_08006ad8.o: src/w27a_08006ad8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 27-A: RectFill_7134 @0x08007134 (480 B, asm transcription).
$(BUILD)/w27a_08007134.o: src/w27a_08007134.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 27-A: FillRect_65BC @0x080065BC (416 B, asm transcription).
$(BUILD)/w27a_080065bc.o: src/w27a_080065bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 27-A: FillRect_6374 @0x08006374 (420 B, asm transcription).
# Calls FillRect_65BC (landed this wave) — .set removed, real symbol used.
$(BUILD)/w27a_08006374.o: src/w27a_08006374.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 27-B: Dispatch_080482D8 @0x080482D8 (168 B, main agbcc).
# Real indirect call pinned to r1 emits bl _call_via_r1 naturally; do NOT
# clobber a pinned reg (miscompile). Evidence: docs/match_notes_wave27_B.md.
$(BUILD)/w27b_080482d8.o: src/w27b_080482d8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 28-A: BlendCopy_080224E4 @0x080224E4 (206 B, sanctioned asm transcription).
# Best C at 94 diffs; RTL dumps prove the 3 mismatched copies are reload-generated
# (C-unavoidable). Precedent: wave-27 rect-fill family. Evidence: docs/match_notes_wave28_A.md.
$(BUILD)/w28a_080224e4.o: src/w28a_080224e4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 28-A: BlendCopy_08021B3C @0x08021B3C (206 B, sanctioned asm transcription).
# Twin of 0x080224E4; identical except the bl Memcpy16 encoding.
$(BUILD)/w28a_08021b3c.o: src/w28a_08021b3c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 28-B: ChipSetup_0801B0DC @0x0801B0DC (220 B incl pool, old_agbcc).
# int t (not u8) gives ROM's signed ble; single-instruction inline asm forces the
# coalesced copy. Evidence: docs/match_notes_wave28_B.md.
$(BUILD)/w28b_0801b0dc.o: src/w28b_0801b0dc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 28-C: Reset_0801F254 @0x0801F254 (164 B, sanctioned asm transcription).
# v/c allocation wall (ROM v->r1,c->r2) proven C-unreachable across ~20 variants.
$(BUILD)/w28c_0801f254.o: src/w28c_0801f254.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 28-C: sub_0802375C @0x0802375C (198 B, sanctioned asm transcription).
# Sibling of 0x0801F254. Pools in middle -> manual .word + .align 1.
$(BUILD)/w28c_0802375c.o: src/w28c_0802375c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 28-C: sub_0802298C @0x0802298C (236 B incl pools, sanctioned asm transcription).
# Sibling of 0x0801F254.
$(BUILD)/w28c_0802298c.o: src/w28c_0802298c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 28-D: MenuTick_0802D6E0 @0x0802D6E0 (192 B, old_agbcc).
# Case 0 falls through into case 1; case 3 falls through into case 4.
$(BUILD)/w28d_0802d6e0.o: src/w28d_0802d6e0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 29-B: ChipState_0801C030 @0x0801C030 (216 B, main agbcc).
# s32-laundering on ChipInit_0801B98C extern params (byte-verified).
$(BUILD)/w29b_0801c030.o: src/w29b_0801c030.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 29-C: GfxSetup_08049560 @0x08049560 (328 B, main agbcc).
$(BUILD)/w29c_08049560.o: src/w29c_08049560.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 29-C: sub_08002A1C @0x08002A1C (224 B incl pool, old_agbcc).
$(BUILD)/w29c_08002a1c.o: src/w29c_08002a1c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 30-B: WalkBits_0803643C @0x0803643C (444 B, sanctioned asm transcription;
# coordinator-verified 0-diff; SelBlob_Ret resolves from src/wave4_i.c).
$(BUILD)/w30b_0803643c.o: src/w30b_0803643c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 30-A: Task_SelectBlobIdx_0803AC4C @0x0803AC4C (252 B, old_agbcc + python
# post-process: pin + post-process for fixed r7 push/pop, B32/B16/tail ldr+adds
# register rewrites. All rewrites semantically neutral. Evidence:
# docs/match_notes_wave30_A.md).
$(BUILD)/w30a_0803ac4c.o: src/w30a_0803ac4c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 tools/fix_0803ac4c.py $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 31-A: ChipFxTick2_0801E77C @0x0801E77C (256 B incl pools, old_agbcc,
# pure C. 0 diffs coordinator-verified from clean-room build. Chip-FX state
# machine, sibling of ChipFxTick_0801C428. Pool-const pin idiom killed the
# pool->r1 wall. Evidence: docs/match_notes_wave31_A.md).
$(BUILD)/w31a_0801e77c.o: src/w31a_0801e77c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 31-C: Init_08000CA8 @0x08000CA8 (44 B, old_agbcc, pure C. 0 diffs
# coordinator-verified from clean-room build. Evidence:
# docs/match_notes_wave31_C.md).
$(BUILD)/w31c_08000ca8.o: src/w31c_08000ca8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 31-D: leaves-up layer (10 functions, coordinator-verified 0-diff
# from clean-room builds). Evidence: docs/match_notes_wave31_D.md.
$(BUILD)/w31d_080363ec.o: src/w31d_080363ec.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_0803639c.o: src/w31d_0803639c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_08036338.o: src/w31d_08036338.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_080070f0.o: src/w31d_080070f0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_080073d4.o: src/w31d_080073d4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_08007378.o: src/w31d_08007378.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_080062b4.o: src/w31d_080062b4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_08006518.o: src/w31d_08006518.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_08006aa0.o: src/w31d_08006aa0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w31d_08006318.o: src/w31d_08006318.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 30-D: ChipFxTick_0801C428 @0x0801C428 (280 B, old_agbcc + python
# post-process: scheduler reorder of b2/b3 address adds + call-3 zero-reg
# r1->r5 fix. Proved undefeatable in C. Evidence: docs/match_notes_wave30_D.md).
$(BUILD)/w30d_0801c428.o: src/w30d_0801c428.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 tools/fix_0801c428.py $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 30-C: SpriteTileUpload_080046B0 @0x080046B0 (244 B, sanctioned asm
# transcription via dis2asm2.py; coordinator-verified 0-diff; CpuFastSet
# resolves from the BIOS veneer. Evidence: docs/match_notes_wave30_C.md).
$(BUILD)/w30c_080046b0.o: src/w30c_080046b0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 32-A: TileList_Upload @0x080096BC (272 B, sanctioned asm transcription).
$(BUILD)/w32a_080096bc.o: src/w32a_080096bc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-A: PatternRowsBlit @0x08006FE8 (264 B, sanctioned asm transcription).
$(BUILD)/w33a_08006fe8.o: src/w33a_08006fe8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-B: StateMachine_0800CD5C @0x0800CD5C (138 B true extent, pure C, main agbcc;
# 2-byte c046 tail pad accepted — mid-function pool forces 4-byte section alignment).
$(BUILD)/w33b_0800cd5c.o: src/w33b_0800cd5c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-B: DrawChipRects_08008B08 @0x08008B08 (176 B, sanctioned asm transcription).
$(BUILD)/w33b_08008b08.o: src/w33b_08008b08.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-C: ChipInit_080221CC @0x080221CC (196 B incl 24 B pool, old_agbcc + .s sed for pool-load reg).
$(BUILD)/w33c_080221cc.o: src/w33c_080221cc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/ldr\tr3, \.L4+8/ldr\tr1, .L4+8/; s/add\tr0, r0, r3/add\tr0, r0, r1/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-D: 12 bulk + blocked-revisit matches (coordinator-verified 0-diff).
$(BUILD)/w33d_0804c8a4.o: src/w33d_0804c8a4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-D: Sram_VerifyCompare @0x0804DC00 (46 B code + 2 B zero pad).
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tr1$$/\tbx\tr1\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w33d_080260d4.o: src/w33d_080260d4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-D: sub_08005268 @0x08005268 (10 B + 2 B zero pad).
$(BUILD)/w33d_08005268.o: src/w33d_08005268.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tr0$$/\tbx\tr0\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w33d_0800b3ec.o: src/w33d_0800b3ec.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-D: sub_08004E50 @0x08004E50 (14 B + 2 B zero pad).
$(BUILD)/w33d_08004e50.o: src/w33d_08004e50.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tr0$$/\tbx\tr0\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-D: sub_0804AD3C @0x0804AD3C (14 B + 2 B zero pad).
$(BUILD)/w33d_0804ad3c.o: src/w33d_0804ad3c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tr1$$/\tbx\tr1\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 33-D: sub_08024CC0 @0x08024CC0 (22 B + 2 B zero pad).
$(BUILD)/w33d_08024cc0.o: src/w33d_08024cc0.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tr1$$/\tbx\tr1\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w33d_08007f3c.o: src/w33d_08007f3c.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w33d_0800ea14.o: src/w33d_0800ea14.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w33d_0800ee70.o: src/w33d_0800ee70.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w33d_080111b4.o: src/w33d_080111b4.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 32-C: TblPairSwap_080249B8 @0x080249B8 (120 B, main agbcc; bx-r1 pad sed for ROM's 2 zero pad bytes).
$(BUILD)/w32c_080249b8.o: src/w32c_080249b8.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tr1$$/\tbx\tr1\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 32-C: Lookup_02D574 @0x0802D574 (52 B, old_agbcc; bx-lr pad sed for ROM's 2 zero pad bytes).
$(BUILD)/w32c_0802d574.o: src/w32c_0802d574.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -i 's/^\tbx\tlr$$/\tbx\tlr\n\t.short\t0x0000/' $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 32 (coordinator): ChipDispatch_08024A30 @0x08024A30 (268 B, sanctioned asm transcription; 28 C variants exhausted).
$(BUILD)/w32_08024a30.o: src/w32_08024a30.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 34-D: BoundsCheck_08042A64 @0x08042A64 (100 B incl 8-B pool, main agbcc
# + python post-process tools/fix_08042a64.py: prologue c/bb swap, push/pop r7,
# 2x adds operand order. 0 diffs coordinator-verified from clean-room build.
# Evidence: docs/match_notes_wave34_D.md).
$(BUILD)/w34d_08042a64.o: src/w34d_08042a64.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 tools/fix_08042a64.py $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 34-D: sub_08007678 @0x08007678 (176 B incl pools, main agbcc + python
# post-process tools/fix_08007678.py: rotate ldrb/lsl/ldr-r1. 0 diffs
# coordinator-verified from clean-room build.
# Evidence: docs/match_notes_wave34_D.md).
$(BUILD)/w34d_08007678.o: src/w34d_08007678.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 tools/fix_08007678.py $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 35-B: 0x0804B350 needs old_agbcc (s8 result kept in r0).
# Evidence: staging/wave35_B/w35b_results_note.md.
$(BUILD)/w35b_0804b350_MATCHED.o: src/w35b_0804b350_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 35-B: 0x0804C288 needs post-process tools/fix_0804c288.py (tst wall:
# agbcc never emits tst; patch replaces test+pool-chain in place, 4
# replacements, each asserted exactly once). Evidence:
# staging/wave35_B/w35b_results_note.md.
$(BUILD)/w35b_0804c288_MATCHED.o: src/w35b_0804c288_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(AGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 tools/fix_0804c288.py $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 35-A: ChipSlot_Tick @0x0800D9FC needs old_agbcc (correct compiler,
# Wave-34 breakthrough) + post-process tools/fix_0800d9fc.py (H-first
# load/key group reorder: gcc invariably sinks the variable load below
# the key computation; 32 C variants exhausted). Evidence:
# staging/wave35_A/w35a_results.md.
$(BUILD)/w35a_0800d9fc.o: src/w35a_0800d9fc.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 tools/fix_0800d9fc.py $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 36 (w36e_0802fbf0_MATCHED): old_agbcc (56 B @ 0x802fbf0).
$(BUILD)/w36e_0802fbf0_MATCHED.o: src/w36e_0802fbf0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36e_0802fbf0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36e_0802fbf0_MATCHED.s $(BUILD)/w36e_0802fbf0_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36e_0802fbf0_MATCHED.s

# Wave 36 (w36e_080272e0_MATCHED): old_agbcc (148 B @ 0x80272e0).
$(BUILD)/w36e_080272e0_MATCHED.o: src/w36e_080272e0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36e_080272e0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36e_080272e0_MATCHED.s $(BUILD)/w36e_080272e0_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36e_080272e0_MATCHED.s

# Wave 36 (w36c_0801e0d0_MATCHED): old_agbcc (124 B @ 0x801e0d0).
$(BUILD)/w36c_0801e0d0_MATCHED.o: src/w36c_0801e0d0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801e0d0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801e0d0_MATCHED.s $(BUILD)/w36c_0801e0d0_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801e0d0_MATCHED.s

# Wave 36 (w36c_08019f38_MATCHED): old_agbcc (128 B @ 0x8019f38).
$(BUILD)/w36c_08019f38_MATCHED.o: src/w36c_08019f38_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_08019f38_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_08019f38_MATCHED.s $(BUILD)/w36c_08019f38_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_08019f38_MATCHED.s

# Wave 36 (w36c_0801a81c_MATCHED): old_agbcc (128 B @ 0x801a81c).
$(BUILD)/w36c_0801a81c_MATCHED.o: src/w36c_0801a81c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801a81c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801a81c_MATCHED.s $(BUILD)/w36c_0801a81c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801a81c_MATCHED.s

# Wave 36 (w36c_0801cac4_MATCHED): old_agbcc (128 B @ 0x801cac4).
$(BUILD)/w36c_0801cac4_MATCHED.o: src/w36c_0801cac4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801cac4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801cac4_MATCHED.s $(BUILD)/w36c_0801cac4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801cac4_MATCHED.s

# Wave 36 (w36c_08021628_MATCHED): old_agbcc (128 B @ 0x8021628).
$(BUILD)/w36c_08021628_MATCHED.o: src/w36c_08021628_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_08021628_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_08021628_MATCHED.s $(BUILD)/w36c_08021628_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_08021628_MATCHED.s

# Wave 36 (w36c_08018f34_MATCHED): old_agbcc (132 B @ 0x8018f34).
$(BUILD)/w36c_08018f34_MATCHED.o: src/w36c_08018f34_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_08018f34_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_08018f34_MATCHED.s $(BUILD)/w36c_08018f34_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_08018f34_MATCHED.s

# Wave 36 (w36c_08019c94_MATCHED): old_agbcc (132 B @ 0x8019c94).
$(BUILD)/w36c_08019c94_MATCHED.o: src/w36c_08019c94_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_08019c94_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_08019c94_MATCHED.s $(BUILD)/w36c_08019c94_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_08019c94_MATCHED.s

# Wave 36 (w36c_0801a19c_MATCHED): old_agbcc (132 B @ 0x801a19c).
$(BUILD)/w36c_0801a19c_MATCHED.o: src/w36c_0801a19c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801a19c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801a19c_MATCHED.s $(BUILD)/w36c_0801a19c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801a19c_MATCHED.s

# Wave 36 (w36c_0801ae70_MATCHED): old_agbcc (132 B @ 0x801ae70).
$(BUILD)/w36c_0801ae70_MATCHED.o: src/w36c_0801ae70_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801ae70_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801ae70_MATCHED.s $(BUILD)/w36c_0801ae70_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801ae70_MATCHED.s

# Wave 36 (w36c_08011f88_MATCHED): old_agbcc (132 B @ 0x8011f88).
$(BUILD)/w36c_08011f88_MATCHED.o: src/w36c_08011f88_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_08011f88_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_08011f88_MATCHED.s $(BUILD)/w36c_08011f88_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_08011f88_MATCHED.s

# Wave 36 (w36c_0801a2bc_MATCHED): old_agbcc (136 B @ 0x801a2bc).
$(BUILD)/w36c_0801a2bc_MATCHED.o: src/w36c_0801a2bc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801a2bc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801a2bc_MATCHED.s $(BUILD)/w36c_0801a2bc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801a2bc_MATCHED.s

# Wave 36 (w36c_0801a568_MATCHED): old_agbcc (136 B @ 0x801a568).
$(BUILD)/w36c_0801a568_MATCHED.o: src/w36c_0801a568_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801a568_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801a568_MATCHED.s $(BUILD)/w36c_0801a568_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801a568_MATCHED.s

# Wave 36 (w36c_0801c108_MATCHED): old_agbcc (136 B @ 0x801c108).
$(BUILD)/w36c_0801c108_MATCHED.o: src/w36c_0801c108_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801c108_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801c108_MATCHED.s $(BUILD)/w36c_0801c108_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801c108_MATCHED.s

# Wave 36 (w36c_0801c628_MATCHED): old_agbcc (136 B @ 0x801c628).
$(BUILD)/w36c_0801c628_MATCHED.o: src/w36c_0801c628_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36c_0801c628_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36c_0801c628_MATCHED.s $(BUILD)/w36c_0801c628_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36c_0801c628_MATCHED.s

# Wave 36 (w36d_080054d0_MATCHED): old_agbcc (140 B @ 0x80054d0).
$(BUILD)/w36d_080054d0_MATCHED.o: src/w36d_080054d0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_080054d0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_080054d0_MATCHED.s $(BUILD)/w36d_080054d0_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_080054d0_MATCHED.s

# Wave 36 (w36d_080188f4_MATCHED): old_agbcc (140 B @ 0x80188f4).
$(BUILD)/w36d_080188f4_MATCHED.o: src/w36d_080188f4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_080188f4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_080188f4_MATCHED.s $(BUILD)/w36d_080188f4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_080188f4_MATCHED.s

# Wave 36 (w36d_08018c84_MATCHED): old_agbcc (148 B @ 0x8018c84).
$(BUILD)/w36d_08018c84_MATCHED.o: src/w36d_08018c84_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08018c84_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08018c84_MATCHED.s $(BUILD)/w36d_08018c84_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08018c84_MATCHED.s

# Wave 36 (w36d_08018ea4_MATCHED): old_agbcc (144 B @ 0x8018ea4).
$(BUILD)/w36d_08018ea4_MATCHED.o: src/w36d_08018ea4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08018ea4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08018ea4_MATCHED.s $(BUILD)/w36d_08018ea4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08018ea4_MATCHED.s

# Wave 36 (w36d_08019248_MATCHED): old_agbcc (148 B @ 0x8019248).
$(BUILD)/w36d_08019248_MATCHED.o: src/w36d_08019248_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08019248_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08019248_MATCHED.s $(BUILD)/w36d_08019248_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08019248_MATCHED.s

# Wave 36 (w36d_08019374_MATCHED): old_agbcc (140 B @ 0x8019374).
$(BUILD)/w36d_08019374_MATCHED.o: src/w36d_08019374_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08019374_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08019374_MATCHED.s $(BUILD)/w36d_08019374_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08019374_MATCHED.s

# Wave 36 (w36d_080194b4_MATCHED): old_agbcc (140 B @ 0x80194b4).
$(BUILD)/w36d_080194b4_MATCHED.o: src/w36d_080194b4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_080194b4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_080194b4_MATCHED.s $(BUILD)/w36d_080194b4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_080194b4_MATCHED.s

# Wave 36 (w36d_0801a3f0_MATCHED): old_agbcc (148 B @ 0x801a3f0).
$(BUILD)/w36d_0801a3f0_MATCHED.o: src/w36d_0801a3f0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801a3f0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801a3f0_MATCHED.s $(BUILD)/w36d_0801a3f0_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801a3f0_MATCHED.s

# Wave 36 (w36d_0801af58_MATCHED): old_agbcc + .s patch (140 B @ 0x801af58).
$(BUILD)/w36d_0801af58_MATCHED.o: src/w36d_0801af58_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801af58_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801af58_MATCHED.s $(BUILD)/w36d_0801af58_MATCHED.i
	python3 $(TOOLS)/fix_w36d_0801af58_patch.py $(BUILD)/w36d_0801af58_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801af58_MATCHED.s

# Wave 36 (w36d_0801b04c_MATCHED): old_agbcc + .s patch (144 B @ 0x801b04c).
$(BUILD)/w36d_0801b04c_MATCHED.o: src/w36d_0801b04c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801b04c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801b04c_MATCHED.s $(BUILD)/w36d_0801b04c_MATCHED.i
	python3 $(TOOLS)/fix_w36d_0801b04c_patch.py $(BUILD)/w36d_0801b04c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801b04c_MATCHED.s

# Wave 36 (w36d_0801b1b8_MATCHED): old_agbcc (140 B @ 0x801b1b8).
$(BUILD)/w36d_0801b1b8_MATCHED.o: src/w36d_0801b1b8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801b1b8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801b1b8_MATCHED.s $(BUILD)/w36d_0801b1b8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801b1b8_MATCHED.s

# Wave 36 (w36d_0801b244_MATCHED): old_agbcc (140 B @ 0x801b244).
$(BUILD)/w36d_0801b244_MATCHED.o: src/w36d_0801b244_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801b244_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801b244_MATCHED.s $(BUILD)/w36d_0801b244_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801b244_MATCHED.s

# Wave 36 (w36d_0801c254_MATCHED): old_agbcc (140 B @ 0x801c254).
$(BUILD)/w36d_0801c254_MATCHED.o: src/w36d_0801c254_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801c254_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801c254_MATCHED.s $(BUILD)/w36d_0801c254_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801c254_MATCHED.s

# Wave 36 (w36d_0801c774_MATCHED): old_agbcc (140 B @ 0x801c774).
$(BUILD)/w36d_0801c774_MATCHED.o: src/w36d_0801c774_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801c774_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801c774_MATCHED.s $(BUILD)/w36d_0801c774_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801c774_MATCHED.s

# Wave 36 (w36d_0801c91c_MATCHED): old_agbcc (140 B @ 0x801c91c).
$(BUILD)/w36d_0801c91c_MATCHED.o: src/w36d_0801c91c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0801c91c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0801c91c_MATCHED.s $(BUILD)/w36d_0801c91c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0801c91c_MATCHED.s

# Wave 36 (w36d_08022700_MATCHED): old_agbcc + .s patch (140 B @ 0x8022700).
$(BUILD)/w36d_08022700_MATCHED.o: src/w36d_08022700_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08022700_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08022700_MATCHED.s $(BUILD)/w36d_08022700_MATCHED.i
	python3 $(TOOLS)/fix_w36d_08022700_patch.py $(BUILD)/w36d_08022700_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08022700_MATCHED.s

# Wave 36 (w36d_080227dc_MATCHED): old_agbcc + .s patch (140 B @ 0x80227dc).
$(BUILD)/w36d_080227dc_MATCHED.o: src/w36d_080227dc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_080227dc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_080227dc_MATCHED.s $(BUILD)/w36d_080227dc_MATCHED.i
	python3 $(TOOLS)/fix_w36d_080227dc_patch.py $(BUILD)/w36d_080227dc_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_080227dc_MATCHED.s

# Wave 36 (w36d_08024b3c_MATCHED): old_agbcc (140 B @ 0x8024b3c).
$(BUILD)/w36d_08024b3c_MATCHED.o: src/w36d_08024b3c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08024b3c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08024b3c_MATCHED.s $(BUILD)/w36d_08024b3c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08024b3c_MATCHED.s

# Wave 36 (w36d_08024e2c_MATCHED): old_agbcc (140 B @ 0x8024e2c).
$(BUILD)/w36d_08024e2c_MATCHED.o: src/w36d_08024e2c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08024e2c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08024e2c_MATCHED.s $(BUILD)/w36d_08024e2c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08024e2c_MATCHED.s

# Wave 36 (w36d_08027374_MATCHED): old_agbcc + .s patch (140 B @ 0x8027374).
$(BUILD)/w36d_08027374_MATCHED.o: src/w36d_08027374_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08027374_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08027374_MATCHED.s $(BUILD)/w36d_08027374_MATCHED.i
	python3 $(TOOLS)/fix_w36d_08027374_patch.py $(BUILD)/w36d_08027374_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08027374_MATCHED.s

# Wave 36 (w36d_0802daf8_MATCHED): old_agbcc + .s patch (140 B @ 0x802daf8).
$(BUILD)/w36d_0802daf8_MATCHED.o: src/w36d_0802daf8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0802daf8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0802daf8_MATCHED.s $(BUILD)/w36d_0802daf8_MATCHED.i
	python3 $(TOOLS)/fix_w36d_0802daf8_patch.py $(BUILD)/w36d_0802daf8_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0802daf8_MATCHED.s

# Wave 36 (w36d_0802fc70_MATCHED): old_agbcc + .s patch (140 B @ 0x802fc70).
$(BUILD)/w36d_0802fc70_MATCHED.o: src/w36d_0802fc70_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0802fc70_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0802fc70_MATCHED.s $(BUILD)/w36d_0802fc70_MATCHED.i
	python3 $(TOOLS)/fix_w36d_0802fc70_patch.py $(BUILD)/w36d_0802fc70_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0802fc70_MATCHED.s

# Wave 36 (w36d_08046960_MATCHED): old_agbcc + .s patch (140 B @ 0x8046960).
$(BUILD)/w36d_08046960_MATCHED.o: src/w36d_08046960_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08046960_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08046960_MATCHED.s $(BUILD)/w36d_08046960_MATCHED.i
	python3 $(TOOLS)/fix_w36d_08046960_patch.py $(BUILD)/w36d_08046960_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08046960_MATCHED.s

# Wave 36 (w36d_080053a0_MATCHED): old_agbcc + .s patch (148 B @ 0x80053a0).
$(BUILD)/w36d_080053a0_MATCHED.o: src/w36d_080053a0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_080053a0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_080053a0_MATCHED.s $(BUILD)/w36d_080053a0_MATCHED.i
	python3 $(TOOLS)/fix_w36d_080053a0_patch.py $(BUILD)/w36d_080053a0_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_080053a0_MATCHED.s

# Wave 36 (w36d_0800cde8_MATCHED): old_agbcc + .s patch (148 B @ 0x800cde8).
$(BUILD)/w36d_0800cde8_MATCHED.o: src/w36d_0800cde8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0800cde8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0800cde8_MATCHED.s $(BUILD)/w36d_0800cde8_MATCHED.i
	python3 $(TOOLS)/fix_w36d_0800cde8_patch.py $(BUILD)/w36d_0800cde8_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0800cde8_MATCHED.s

# Wave 36 (w36d_0800ce7c_MATCHED): old_agbcc + .s patch (148 B @ 0x800ce7c).
$(BUILD)/w36d_0800ce7c_MATCHED.o: src/w36d_0800ce7c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_0800ce7c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_0800ce7c_MATCHED.s $(BUILD)/w36d_0800ce7c_MATCHED.i
	python3 $(TOOLS)/fix_w36d_0800ce7c_patch.py $(BUILD)/w36d_0800ce7c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_0800ce7c_MATCHED.s

# Wave 36 (w36d_08020f70_MATCHED): old_agbcc + .s patch (144 B @ 0x8020f70).
$(BUILD)/w36d_08020f70_MATCHED.o: src/w36d_08020f70_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08020f70_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08020f70_MATCHED.s $(BUILD)/w36d_08020f70_MATCHED.i
	python3 $(TOOLS)/fix_w36d_08020f70_patch.py $(BUILD)/w36d_08020f70_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08020f70_MATCHED.s

# Wave 36 (w36d_08022290_MATCHED): old_agbcc + .s patch (144 B @ 0x8022290).
$(BUILD)/w36d_08022290_MATCHED.o: src/w36d_08022290_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36d_08022290_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36d_08022290_MATCHED.s $(BUILD)/w36d_08022290_MATCHED.i
	python3 $(TOOLS)/fix_w36d_08022290_patch.py $(BUILD)/w36d_08022290_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36d_08022290_MATCHED.s

# Wave 36 (w36b_0801aacc_MATCHED): old_agbcc (104 B @ 0x801aacc).
$(BUILD)/w36b_0801aacc_MATCHED.o: src/w36b_0801aacc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0801aacc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0801aacc_MATCHED.s $(BUILD)/w36b_0801aacc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0801aacc_MATCHED.s

# Wave 36 (w36b_08021ed4_MATCHED): old_agbcc + .s patch (104 B @ 0x8021ed4).
$(BUILD)/w36b_08021ed4_MATCHED.o: src/w36b_08021ed4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08021ed4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08021ed4_MATCHED.s $(BUILD)/w36b_08021ed4_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08021ed4_patch.py $(BUILD)/w36b_08021ed4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08021ed4_MATCHED.s

# Wave 36 (w36b_0802329c_MATCHED): old_agbcc + .s patch (104 B @ 0x802329c).
$(BUILD)/w36b_0802329c_MATCHED.o: src/w36b_0802329c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0802329c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0802329c_MATCHED.s $(BUILD)/w36b_0802329c_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0802329c_patch.py $(BUILD)/w36b_0802329c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0802329c_MATCHED.s

# Wave 36 (w36b_0800419c_MATCHED): old_agbcc (108 B @ 0x800419c).
$(BUILD)/w36b_0800419c_MATCHED.o: src/w36b_0800419c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0800419c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0800419c_MATCHED.s $(BUILD)/w36b_0800419c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0800419c_MATCHED.s

# Wave 36 (w36b_0804b5cc_MATCHED): old_agbcc (104 B @ 0x804b5cc).
$(BUILD)/w36b_0804b5cc_MATCHED.o: src/w36b_0804b5cc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0804b5cc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0804b5cc_MATCHED.s $(BUILD)/w36b_0804b5cc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0804b5cc_MATCHED.s

# Wave 36 (w36b_080098c4_MATCHED): old_agbcc + .s patch (108 B @ 0x80098c4).
$(BUILD)/w36b_080098c4_MATCHED.o: src/w36b_080098c4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_080098c4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_080098c4_MATCHED.s $(BUILD)/w36b_080098c4_MATCHED.i
	python3 $(TOOLS)/fix_w36b_080098c4_patch.py $(BUILD)/w36b_080098c4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_080098c4_MATCHED.s

# Wave 36 (w36b_0800cc94_MATCHED): old_agbcc + .s patch (108 B @ 0x800cc94).
$(BUILD)/w36b_0800cc94_MATCHED.o: src/w36b_0800cc94_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0800cc94_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0800cc94_MATCHED.s $(BUILD)/w36b_0800cc94_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0800cc94_patch.py $(BUILD)/w36b_0800cc94_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0800cc94_MATCHED.s

# Wave 36 (w36b_0800ed44_MATCHED): old_agbcc + .s patch (108 B @ 0x800ed44).
$(BUILD)/w36b_0800ed44_MATCHED.o: src/w36b_0800ed44_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0800ed44_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0800ed44_MATCHED.s $(BUILD)/w36b_0800ed44_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0800ed44_patch.py $(BUILD)/w36b_0800ed44_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0800ed44_MATCHED.s

# Wave 36 (w36b_0800eed4_MATCHED): old_agbcc + .s patch (108 B @ 0x800eed4).
$(BUILD)/w36b_0800eed4_MATCHED.o: src/w36b_0800eed4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0800eed4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0800eed4_MATCHED.s $(BUILD)/w36b_0800eed4_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0800eed4_patch.py $(BUILD)/w36b_0800eed4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0800eed4_MATCHED.s

# Wave 36 (w36b_0802142c_MATCHED): old_agbcc + .s patch (108 B @ 0x802142c).
$(BUILD)/w36b_0802142c_MATCHED.o: src/w36b_0802142c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0802142c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0802142c_MATCHED.s $(BUILD)/w36b_0802142c_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0802142c_patch.py $(BUILD)/w36b_0802142c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0802142c_MATCHED.s

# Wave 36 (w36b_08025e5c_MATCHED): old_agbcc + .s patch (108 B @ 0x8025e5c).
$(BUILD)/w36b_08025e5c_MATCHED.o: src/w36b_08025e5c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08025e5c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08025e5c_MATCHED.s $(BUILD)/w36b_08025e5c_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08025e5c_patch.py $(BUILD)/w36b_08025e5c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08025e5c_MATCHED.s

# Wave 36 (w36b_080280e8_MATCHED): old_agbcc + .s patch (108 B @ 0x80280e8).
$(BUILD)/w36b_080280e8_MATCHED.o: src/w36b_080280e8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_080280e8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_080280e8_MATCHED.s $(BUILD)/w36b_080280e8_MATCHED.i
	python3 $(TOOLS)/fix_w36b_080280e8_patch.py $(BUILD)/w36b_080280e8_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_080280e8_MATCHED.s

# Wave 36 (w36b_0802e9f8_MATCHED): old_agbcc (108 B @ 0x802e9f8).
$(BUILD)/w36b_0802e9f8_MATCHED.o: src/w36b_0802e9f8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0802e9f8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0802e9f8_MATCHED.s $(BUILD)/w36b_0802e9f8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0802e9f8_MATCHED.s

# Wave 36 (w36b_08045fcc_MATCHED): old_agbcc (108 B @ 0x8045fcc).
$(BUILD)/w36b_08045fcc_MATCHED.o: src/w36b_08045fcc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08045fcc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08045fcc_MATCHED.s $(BUILD)/w36b_08045fcc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08045fcc_MATCHED.s

# Wave 36 (w36b_08007cf4_MATCHED): old_agbcc + .s patch (112 B @ 0x8007cf4).
$(BUILD)/w36b_08007cf4_MATCHED.o: src/w36b_08007cf4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08007cf4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08007cf4_MATCHED.s $(BUILD)/w36b_08007cf4_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08007cf4_patch.py $(BUILD)/w36b_08007cf4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08007cf4_MATCHED.s

# Wave 36 (w36b_0800c41c_MATCHED): old_agbcc + .s patch (112 B @ 0x800c41c).
$(BUILD)/w36b_0800c41c_MATCHED.o: src/w36b_0800c41c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0800c41c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0800c41c_MATCHED.s $(BUILD)/w36b_0800c41c_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0800c41c_patch.py $(BUILD)/w36b_0800c41c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0800c41c_MATCHED.s

# Wave 36 (w36b_08010b30_MATCHED): old_agbcc + .s patch (112 B @ 0x8010b30).
$(BUILD)/w36b_08010b30_MATCHED.o: src/w36b_08010b30_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08010b30_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08010b30_MATCHED.s $(BUILD)/w36b_08010b30_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08010b30_patch.py $(BUILD)/w36b_08010b30_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08010b30_MATCHED.s

# Wave 36 (w36b_0801b91c_MATCHED): old_agbcc + .s patch (80 B @ 0x801b91c).
$(BUILD)/w36b_0801b91c_MATCHED.o: src/w36b_0801b91c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0801b91c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0801b91c_MATCHED.s $(BUILD)/w36b_0801b91c_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0801b91c_patch.py $(BUILD)/w36b_0801b91c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0801b91c_MATCHED.s

# Wave 36 (w36b_0801cce0_MATCHED): old_agbcc + .s patch (80 B @ 0x801cce0).
$(BUILD)/w36b_0801cce0_MATCHED.o: src/w36b_0801cce0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0801cce0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0801cce0_MATCHED.s $(BUILD)/w36b_0801cce0_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0801cce0_patch.py $(BUILD)/w36b_0801cce0_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0801cce0_MATCHED.s

# Wave 36 (w36b_08023d68_MATCHED): old_agbcc (112 B @ 0x8023d68).
$(BUILD)/w36b_08023d68_MATCHED.o: src/w36b_08023d68_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08023d68_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08023d68_MATCHED.s $(BUILD)/w36b_08023d68_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08023d68_MATCHED.s

# Wave 36 (w36b_08028900_MATCHED): old_agbcc + .s patch (112 B @ 0x8028900).
$(BUILD)/w36b_08028900_MATCHED.o: src/w36b_08028900_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08028900_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08028900_MATCHED.s $(BUILD)/w36b_08028900_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08028900_patch.py $(BUILD)/w36b_08028900_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08028900_MATCHED.s

# Wave 36 (w36b_0802d670_MATCHED): old_agbcc + .s patch (112 B @ 0x802d670).
$(BUILD)/w36b_0802d670_MATCHED.o: src/w36b_0802d670_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0802d670_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0802d670_MATCHED.s $(BUILD)/w36b_0802d670_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0802d670_patch.py $(BUILD)/w36b_0802d670_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0802d670_MATCHED.s

# Wave 36 (w36b_0800e994_MATCHED): old_agbcc + .s patch (116 B @ 0x800e994).
$(BUILD)/w36b_0800e994_MATCHED.o: src/w36b_0800e994_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0800e994_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0800e994_MATCHED.s $(BUILD)/w36b_0800e994_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0800e994_patch.py $(BUILD)/w36b_0800e994_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0800e994_MATCHED.s

# Wave 36 (w36b_08011eb0_MATCHED): old_agbcc + .s patch (116 B @ 0x8011eb0).
$(BUILD)/w36b_08011eb0_MATCHED.o: src/w36b_08011eb0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08011eb0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08011eb0_MATCHED.s $(BUILD)/w36b_08011eb0_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08011eb0_patch.py $(BUILD)/w36b_08011eb0_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08011eb0_MATCHED.s

# Wave 36 (w36b_08023bc4_MATCHED): old_agbcc + .s patch (116 B @ 0x8023bc4).
$(BUILD)/w36b_08023bc4_MATCHED.o: src/w36b_08023bc4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08023bc4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08023bc4_MATCHED.s $(BUILD)/w36b_08023bc4_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08023bc4_patch.py $(BUILD)/w36b_08023bc4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08023bc4_MATCHED.s

# Wave 36 (w36b_08034eb8_MATCHED): old_agbcc + .s patch (116 B @ 0x8034eb8).
$(BUILD)/w36b_08034eb8_MATCHED.o: src/w36b_08034eb8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08034eb8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08034eb8_MATCHED.s $(BUILD)/w36b_08034eb8_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08034eb8_patch.py $(BUILD)/w36b_08034eb8_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08034eb8_MATCHED.s

# Wave 36 (w36b_0803ff0c_MATCHED): old_agbcc + .s patch (116 B @ 0x803ff0c).
$(BUILD)/w36b_0803ff0c_MATCHED.o: src/w36b_0803ff0c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0803ff0c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0803ff0c_MATCHED.s $(BUILD)/w36b_0803ff0c_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0803ff0c_patch.py $(BUILD)/w36b_0803ff0c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0803ff0c_MATCHED.s

# Wave 36 (w36b_08000e80_MATCHED): old_agbcc + .s patch (56 B @ 0x8000e80).
$(BUILD)/w36b_08000e80_MATCHED.o: src/w36b_08000e80_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08000e80_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08000e80_MATCHED.s $(BUILD)/w36b_08000e80_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08000e80_patch.py $(BUILD)/w36b_08000e80_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08000e80_MATCHED.s

# Wave 36 (w36b_080114e8_MATCHED): old_agbcc + .s patch (72 B @ 0x80114e8).
$(BUILD)/w36b_080114e8_MATCHED.o: src/w36b_080114e8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_080114e8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_080114e8_MATCHED.s $(BUILD)/w36b_080114e8_MATCHED.i
	python3 $(TOOLS)/fix_w36b_080114e8_patch.py $(BUILD)/w36b_080114e8_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_080114e8_MATCHED.s

# Wave 36 (w36b_0801a9f8_MATCHED): old_agbcc + .s patch (88 B @ 0x801a9f8).
$(BUILD)/w36b_0801a9f8_MATCHED.o: src/w36b_0801a9f8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0801a9f8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0801a9f8_MATCHED.s $(BUILD)/w36b_0801a9f8_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0801a9f8_patch.py $(BUILD)/w36b_0801a9f8_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0801a9f8_MATCHED.s

# Wave 36 (w36b_0804c630_MATCHED): old_agbcc + .s patch (120 B @ 0x804c630).
$(BUILD)/w36b_0804c630_MATCHED.o: src/w36b_0804c630_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0804c630_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0804c630_MATCHED.s $(BUILD)/w36b_0804c630_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0804c630_patch.py $(BUILD)/w36b_0804c630_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0804c630_MATCHED.s

# Wave 36 (w36b_0800a0d4_MATCHED): old_agbcc + .s patch (124 B @ 0x800a0d4).
$(BUILD)/w36b_0800a0d4_MATCHED.o: src/w36b_0800a0d4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0800a0d4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0800a0d4_MATCHED.s $(BUILD)/w36b_0800a0d4_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0800a0d4_patch.py $(BUILD)/w36b_0800a0d4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0800a0d4_MATCHED.s

# Wave 36 (w36b_08010750_MATCHED): old_agbcc + .s patch (124 B @ 0x8010750).
$(BUILD)/w36b_08010750_MATCHED.o: src/w36b_08010750_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_08010750_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_08010750_MATCHED.s $(BUILD)/w36b_08010750_MATCHED.i
	python3 $(TOOLS)/fix_w36b_08010750_patch.py $(BUILD)/w36b_08010750_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_08010750_MATCHED.s

# Wave 36 (w36b_0801bfb4_MATCHED): old_agbcc + .s patch (124 B @ 0x801bfb4).
$(BUILD)/w36b_0801bfb4_MATCHED.o: src/w36b_0801bfb4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36b_0801bfb4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36b_0801bfb4_MATCHED.s $(BUILD)/w36b_0801bfb4_MATCHED.i
	python3 $(TOOLS)/fix_w36b_0801bfb4_patch.py $(BUILD)/w36b_0801bfb4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36b_0801bfb4_MATCHED.s

# Wave 36 reconciliation (chat-spawned Wave 36 vs cron Wave 36 overlap;
# coordinator independently re-verified all 0-diff from clean-room builds).
# W36-chat B conflict (was W36-C BLOCKED): 0x08007798 (128 B, old).
$(BUILD)/w36bulk_08007798_MATCHED.o: src/w36bulk_08007798_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36bulk_08007798_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36bulk_08007798_MATCHED.s $(BUILD)/w36bulk_08007798_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36bulk_08007798_MATCHED.s
# W36-chat A upgrade (was W36-C BLOCKED): 0x0800cb70 (80 B, main + tools/fix_0800cb70.py).
$(BUILD)/w36a_0800cb70_MATCHED.o: src/w36a_0800cb70_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_0800cb70_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w36a_0800cb70_MATCHED.s $(BUILD)/w36a_0800cb70_MATCHED.i
	python3 tools/fix_0800cb70.py $(BUILD)/w36a_0800cb70_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_0800cb70_MATCHED.s
# W36-chat A upgrade (was W36-C BLOCKED): 0x08010d84 (88 B, old).
$(BUILD)/w36a_08010d84_MATCHED.o: src/w36a_08010d84_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_08010d84_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_08010d84_MATCHED.s $(BUILD)/w36a_08010d84_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_08010d84_MATCHED.s
# W36-chat A restore (W36 demoted): 0x0801b428 (84 B, old).
$(BUILD)/w36a_0801b428_MATCHED.o: src/w36a_0801b428_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_0801b428_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_0801b428_MATCHED.s $(BUILD)/w36a_0801b428_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_0801b428_MATCHED.s
# W36-chat A restore (W36 demoted): 0x0801b520 (84 B, old).
$(BUILD)/w36a_0801b520_MATCHED.o: src/w36a_0801b520_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_0801b520_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_0801b520_MATCHED.s $(BUILD)/w36a_0801b520_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_0801b520_MATCHED.s
# W36-chat A restore (W36 demoted): 0x0801b880 (80 B, old).
$(BUILD)/w36a_0801b880_MATCHED.o: src/w36a_0801b880_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_0801b880_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_0801b880_MATCHED.s $(BUILD)/w36a_0801b880_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_0801b880_MATCHED.s
# W36-chat B conflict (was W36-C BLOCKED): 0x0801dd48 (124 B, old).
$(BUILD)/w36bulk_0801dd48_MATCHED.o: src/w36bulk_0801dd48_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36bulk_0801dd48_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36bulk_0801dd48_MATCHED.s $(BUILD)/w36bulk_0801dd48_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36bulk_0801dd48_MATCHED.s
# W36-chat A restore (W36 demoted): 0x0801e93c (52 B, old + tools/fix_0801e93c.py).
$(BUILD)/w36a_0801e93c_MATCHED.o: src/w36a_0801e93c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_0801e93c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_0801e93c_MATCHED.s $(BUILD)/w36a_0801e93c_MATCHED.i
	python3 tools/fix_0801e93c.py $(BUILD)/w36a_0801e93c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_0801e93c_MATCHED.s
# W36-chat B conflict (was W36-C BLOCKED): 0x08021c2c (128 B, old).
$(BUILD)/w36bulk_08021c2c_MATCHED.o: src/w36bulk_08021c2c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36bulk_08021c2c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36bulk_08021c2c_MATCHED.s $(BUILD)/w36bulk_08021c2c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36bulk_08021c2c_MATCHED.s
# W36-chat A restore (W36 demoted): 0x080248c4 (84 B, old).
$(BUILD)/w36a_080248c4_MATCHED.o: src/w36a_080248c4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_080248c4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_080248c4_MATCHED.s $(BUILD)/w36a_080248c4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_080248c4_MATCHED.s
# W36-chat B conflict (was W36-C BLOCKED; TAIL2B c046 pad): 0x08024c40 (128 B, old).
$(BUILD)/w36bulk_08024c40_MATCHED.o: src/w36bulk_08024c40_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36bulk_08024c40_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36bulk_08024c40_MATCHED.s $(BUILD)/w36bulk_08024c40_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36bulk_08024c40_MATCHED.s
# W36-chat A upgrade (was W36-C BLOCKED): 0x08028970 (84 B, main + tools/fix_08028970.py).
$(BUILD)/w36a_08028970_MATCHED.o: src/w36a_08028970_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_08028970_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w36a_08028970_MATCHED.s $(BUILD)/w36a_08028970_MATCHED.i
	python3 tools/fix_08028970.py $(BUILD)/w36a_08028970_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_08028970_MATCHED.s
# W36-chat A restore (W36 demoted): 0x0803449c (84 B, old).
$(BUILD)/w36a_0803449c_MATCHED.o: src/w36a_0803449c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_0803449c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_0803449c_MATCHED.s $(BUILD)/w36a_0803449c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_0803449c_MATCHED.s
# W36-chat B conflict (was W36-C BLOCKED): 0x0804380c (132 B, old).
$(BUILD)/w36bulk_0804380c_MATCHED.o: src/w36bulk_0804380c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36bulk_0804380c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36bulk_0804380c_MATCHED.s $(BUILD)/w36bulk_0804380c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36bulk_0804380c_MATCHED.s
# W36-chat B conflict (was W36-C BLOCKED): 0x0804afd0 (128 B, old).
$(BUILD)/w36bulk_0804afd0_MATCHED.o: src/w36bulk_0804afd0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36bulk_0804afd0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36bulk_0804afd0_MATCHED.s $(BUILD)/w36bulk_0804afd0_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36bulk_0804afd0_MATCHED.s
# W36-chat A restore (W36 demoted): 0x0804c72c (84 B, old).
$(BUILD)/w36a_0804c72c_MATCHED.o: src/w36a_0804c72c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w36a_0804c72c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w36a_0804c72c_MATCHED.s $(BUILD)/w36a_0804c72c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w36a_0804c72c_MATCHED.s
# Wave 37-A: 0x08009238 (144 B, old; empty-asm barriers defeat const folding).
$(BUILD)/w37a_08009238_MATCHED.o: src/w37a_08009238_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37a_08009238_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37a_08009238_MATCHED.s $(BUILD)/w37a_08009238_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37a_08009238_MATCHED.s
# Wave 37-B Sub_08000EB8 (28 B, old).
$(BUILD)/w37b_08000eb8_MATCHED.o: src/w37b_08000eb8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_08000eb8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_08000eb8_MATCHED.s $(BUILD)/w37b_08000eb8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_08000eb8_MATCHED.s
# Wave 37-B Sub_08000ED4 (36 B, old).
$(BUILD)/w37b_08000ed4_MATCHED.o: src/w37b_08000ed4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_08000ed4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_08000ed4_MATCHED.s $(BUILD)/w37b_08000ed4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_08000ed4_MATCHED.s
# Wave 37-B Sub_08007C04 (136 B, old + patch, inline-asm ldrsb).
$(BUILD)/w37b_08007c04_MATCHED.o: src/w37b_08007c04_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_08007c04_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_08007c04_MATCHED.s $(BUILD)/w37b_08007c04_MATCHED.i
	python3 tools/fix_w37b_08007c04_patch.py $(BUILD)/w37b_08007c04_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_08007c04_MATCHED.s
# Wave 37-B Sub_08007F24 (24 B, old).
$(BUILD)/w37b_08007f24_MATCHED.o: src/w37b_08007f24_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_08007f24_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_08007f24_MATCHED.s $(BUILD)/w37b_08007f24_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_08007f24_MATCHED.s
# Wave 37-B Sub_08011530 (48 B, old + patch).
$(BUILD)/w37b_08011530_MATCHED.o: src/w37b_08011530_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_08011530_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_08011530_MATCHED.s $(BUILD)/w37b_08011530_MATCHED.i
	python3 tools/fix_w37b_08011530_patch.py $(BUILD)/w37b_08011530_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_08011530_MATCHED.s
# Wave 37-B Sub_080174F4 (136 B, old + patch).
$(BUILD)/w37b_080174f4_MATCHED.o: src/w37b_080174f4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_080174f4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_080174f4_MATCHED.s $(BUILD)/w37b_080174f4_MATCHED.i
	python3 tools/fix_w37b_080174f4_patch.py $(BUILD)/w37b_080174f4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_080174f4_MATCHED.s
# Wave 37-B Sub_0801AA50 (32 B, old + patch, Slot_FetchWord4 twin).
$(BUILD)/w37b_0801aa50_MATCHED.o: src/w37b_0801aa50_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_0801aa50_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_0801aa50_MATCHED.s $(BUILD)/w37b_0801aa50_MATCHED.i
	python3 tools/fix_w37b_0801aa50_patch.py $(BUILD)/w37b_0801aa50_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_0801aa50_MATCHED.s
# Wave 37-B Sub_0801B96C (32 B, old + patch, Slot_FetchWord4 twin).
$(BUILD)/w37b_0801b96c_MATCHED.o: src/w37b_0801b96c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_0801b96c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_0801b96c_MATCHED.s $(BUILD)/w37b_0801b96c_MATCHED.i
	python3 tools/fix_w37b_0801b96c_patch.py $(BUILD)/w37b_0801b96c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_0801b96c_MATCHED.s
# Wave 37-B Sub_0801CD30 (32 B, old + patch, Slot_FetchWord4 twin).
$(BUILD)/w37b_0801cd30_MATCHED.o: src/w37b_0801cd30_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_0801cd30_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_0801cd30_MATCHED.s $(BUILD)/w37b_0801cd30_MATCHED.i
	python3 tools/fix_w37b_0801cd30_patch.py $(BUILD)/w37b_0801cd30_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_0801cd30_MATCHED.s
# Wave 37-B Sub_0801E970 (32 B, old + patch, Slot_FetchWord4 twin).
$(BUILD)/w37b_0801e970_MATCHED.o: src/w37b_0801e970_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_0801e970_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_0801e970_MATCHED.s $(BUILD)/w37b_0801e970_MATCHED.i
	python3 tools/fix_w37b_0801e970_patch.py $(BUILD)/w37b_0801e970_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_0801e970_MATCHED.s
# Wave 37-B Sub_080402E0 (132 B, old + patch, inline-asm ldrsb).
$(BUILD)/w37b_080402e0_MATCHED.o: src/w37b_080402e0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_080402e0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_080402e0_MATCHED.s $(BUILD)/w37b_080402e0_MATCHED.i
	python3 tools/fix_w37b_080402e0_patch.py $(BUILD)/w37b_080402e0_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_080402e0_MATCHED.s
# Wave 37-B Sub_0804044C (132 B, old + patch).
$(BUILD)/w37b_0804044c_MATCHED.o: src/w37b_0804044c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37b_0804044c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37b_0804044c_MATCHED.s $(BUILD)/w37b_0804044c_MATCHED.i
	python3 tools/fix_w37b_0804044c_patch.py $(BUILD)/w37b_0804044c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37b_0804044c_MATCHED.s
# Wave 37-D F_0801ECE8 (268 B, sanctioned asm transcription, 7 C variants exhausted).
$(BUILD)/w37d_0801ece8_MATCHED.o: src/w37d_0801ece8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37d_0801ece8_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w37d_0801ece8_MATCHED.s $(BUILD)/w37d_0801ece8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37d_0801ece8_MATCHED.s
# Wave 37-D F_0801D6CC (348 B, sanctioned asm transcription, 6 C variants exhausted).
$(BUILD)/w37d_0801d6cc_MATCHED.o: src/w37d_0801d6cc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37d_0801d6cc_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w37d_0801d6cc_MATCHED.s $(BUILD)/w37d_0801d6cc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37d_0801d6cc_MATCHED.s
# Wave 37-D F_0801FFBC (304 B, sanctioned asm transcription, 3 C variants exhausted).
$(BUILD)/w37d_0801ffbc_MATCHED.o: src/w37d_0801ffbc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37d_0801ffbc_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w37d_0801ffbc_MATCHED.s $(BUILD)/w37d_0801ffbc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37d_0801ffbc_MATCHED.s
# Wave 37 coordinator: 0x0801edf4 (32 B, old + patch, Slot_FetchWord4 twin; gap inside 0x0801ece8 window).
$(BUILD)/w37coord_0801edf4_MATCHED.o: src/w37coord_0801edf4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37coord_0801edf4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37coord_0801edf4_MATCHED.s $(BUILD)/w37coord_0801edf4_MATCHED.i
	python3 tools/fix_w37coord_0801edf4_patch.py $(BUILD)/w37coord_0801edf4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37coord_0801edf4_MATCHED.s
# Wave 37-C Sub_08042D80 (148 B, old).
$(BUILD)/w37c_08042d80_MATCHED.o: src/w37c_08042d80_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08042d80_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08042d80_MATCHED.s $(BUILD)/w37c_08042d80_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08042d80_MATCHED.s
# Wave 37-C Sub_08016C94 (152 B, old).
$(BUILD)/w37c_08016c94_MATCHED.o: src/w37c_08016c94_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08016c94_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08016c94_MATCHED.s $(BUILD)/w37c_08016c94_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08016c94_MATCHED.s
# Wave 37-C Sub_080185A8 (152 B, old).
$(BUILD)/w37c_080185a8_MATCHED.o: src/w37c_080185a8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_080185a8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_080185a8_MATCHED.s $(BUILD)/w37c_080185a8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_080185a8_MATCHED.s
# Wave 37-C Sub_080192DC (152 B, old + patch).
$(BUILD)/w37c_080192dc_MATCHED.o: src/w37c_080192dc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_080192dc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_080192dc_MATCHED.s $(BUILD)/w37c_080192dc_MATCHED.i
	python3 tools/fix_w37c_080192dc_patch.py $(BUILD)/w37c_080192dc_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_080192dc_MATCHED.s
# Wave 37-C Sub_08018510 (152 B, old + patch).
$(BUILD)/w37c_08018510_MATCHED.o: src/w37c_08018510_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08018510_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08018510_MATCHED.s $(BUILD)/w37c_08018510_MATCHED.i
	python3 tools/fix_w37c_08018510_patch.py $(BUILD)/w37c_08018510_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08018510_MATCHED.s
# Wave 37-C Sub_0801986C (152 B, old).
$(BUILD)/w37c_0801986c_MATCHED.o: src/w37c_0801986c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801986c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801986c_MATCHED.s $(BUILD)/w37c_0801986c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801986c_MATCHED.s
# Wave 37-C Sub_08038488 (152 B, main).
$(BUILD)/w37c_08038488_MATCHED.o: src/w37c_08038488_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08038488_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w37c_08038488_MATCHED.s $(BUILD)/w37c_08038488_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08038488_MATCHED.s
# Wave 37-C Sub_0804CBCC (152 B, old).
$(BUILD)/w37c_0804cbcc_MATCHED.o: src/w37c_0804cbcc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0804cbcc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0804cbcc_MATCHED.s $(BUILD)/w37c_0804cbcc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0804cbcc_MATCHED.s
# Wave 37-C Sub_08005434 (156 B, old).
$(BUILD)/w37c_08005434_MATCHED.o: src/w37c_08005434_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08005434_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08005434_MATCHED.s $(BUILD)/w37c_08005434_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08005434_MATCHED.s
# Wave 37-C Sub_08009EDC (156 B, old).
$(BUILD)/w37c_08009edc_MATCHED.o: src/w37c_08009edc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08009edc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08009edc_MATCHED.s $(BUILD)/w37c_08009edc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08009edc_MATCHED.s
# Wave 37-C Sub_08018474 (156 B, old).
$(BUILD)/w37c_08018474_MATCHED.o: src/w37c_08018474_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08018474_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08018474_MATCHED.s $(BUILD)/w37c_08018474_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08018474_MATCHED.s
# Wave 37-C Sub_0801A220 (156 B, old).
$(BUILD)/w37c_0801a220_MATCHED.o: src/w37c_0801a220_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801a220_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801a220_MATCHED.s $(BUILD)/w37c_0801a220_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801a220_MATCHED.s
# Wave 37-C Sub_0801AC58 (156 B, old).
$(BUILD)/w37c_0801ac58_MATCHED.o: src/w37c_0801ac58_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801ac58_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801ac58_MATCHED.s $(BUILD)/w37c_0801ac58_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801ac58_MATCHED.s
# Wave 37-C Sub_0802D5D4 (156 B, old).
$(BUILD)/w37c_0802d5d4_MATCHED.o: src/w37c_0802d5d4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0802d5d4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0802d5d4_MATCHED.s $(BUILD)/w37c_0802d5d4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0802d5d4_MATCHED.s
# Wave 37-C Sub_0804713C (156 B, old).
$(BUILD)/w37c_0804713c_MATCHED.o: src/w37c_0804713c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0804713c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0804713c_MATCHED.s $(BUILD)/w37c_0804713c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0804713c_MATCHED.s
# Wave 37-C Sub_0801AD60 (160 B, old).
$(BUILD)/w37c_0801ad60_MATCHED.o: src/w37c_0801ad60_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801ad60_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801ad60_MATCHED.s $(BUILD)/w37c_0801ad60_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801ad60_MATCHED.s
# Wave 37-C Sub_0801757C (132 B TRUE, old; TSV 164 wrong).
$(BUILD)/w37c_0801757c_MATCHED.o: src/w37c_0801757c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801757c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801757c_MATCHED.s $(BUILD)/w37c_0801757c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801757c_MATCHED.s
# Wave 37-C Sub_0801EC44 (164 B, old).
$(BUILD)/w37c_0801ec44_MATCHED.o: src/w37c_0801ec44_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801ec44_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801ec44_MATCHED.s $(BUILD)/w37c_0801ec44_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801ec44_MATCHED.s
# Wave 37-C Sub_0804CB28 (164 B, old).
$(BUILD)/w37c_0804cb28_MATCHED.o: src/w37c_0804cb28_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0804cb28_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0804cb28_MATCHED.s $(BUILD)/w37c_0804cb28_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0804cb28_MATCHED.s
# Wave 37-C Sub_08017DC4 (168 B, old).
$(BUILD)/w37c_08017dc4_MATCHED.o: src/w37c_08017dc4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08017dc4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08017dc4_MATCHED.s $(BUILD)/w37c_08017dc4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08017dc4_MATCHED.s
# Wave 37-C Sub_0801E028 (168 B, old + patch).
$(BUILD)/w37c_0801e028_MATCHED.o: src/w37c_0801e028_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801e028_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801e028_MATCHED.s $(BUILD)/w37c_0801e028_MATCHED.i
	python3 tools/fix_w37c_0801e028_patch.py $(BUILD)/w37c_0801e028_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801e028_MATCHED.s
# Wave 37-C Sub_08021144 (168 B, old).
$(BUILD)/w37c_08021144_MATCHED.o: src/w37c_08021144_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_08021144_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_08021144_MATCHED.s $(BUILD)/w37c_08021144_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_08021144_MATCHED.s
# Wave 37-C Sub_080231D0 (148 B TRUE, old + patch; TSV 168 wrong).
$(BUILD)/w37c_080231d0_MATCHED.o: src/w37c_080231d0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_080231d0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_080231d0_MATCHED.s $(BUILD)/w37c_080231d0_MATCHED.i
	python3 tools/fix_w37c_080231d0_patch.py $(BUILD)/w37c_080231d0_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_080231d0_MATCHED.s
# Wave 37-C Sub_0801A344 (172 B, old).
$(BUILD)/w37c_0801a344_MATCHED.o: src/w37c_0801a344_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c_0801a344_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c_0801a344_MATCHED.s $(BUILD)/w37c_0801a344_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c_0801a344_MATCHED.s
# Wave 37-C2 Sub_08042E14 (172 B, old).
$(BUILD)/w37c2_08042e14_MATCHED.o: src/w37c2_08042e14_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08042e14_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08042e14_MATCHED.s $(BUILD)/w37c2_08042e14_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08042e14_MATCHED.s
# Wave 37-C2 Sub_0801969C (176 B, old).
$(BUILD)/w37c2_0801969c_MATCHED.o: src/w37c2_0801969c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_0801969c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_0801969c_MATCHED.s $(BUILD)/w37c2_0801969c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_0801969c_MATCHED.s
# Wave 37-C2 Sub_080197BC (176 B, old).
$(BUILD)/w37c2_080197bc_MATCHED.o: src/w37c2_080197bc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_080197bc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_080197bc_MATCHED.s $(BUILD)/w37c2_080197bc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_080197bc_MATCHED.s
# Wave 37-C2 Sub_08017ED8 (180 B, old).
$(BUILD)/w37c2_08017ed8_MATCHED.o: src/w37c2_08017ed8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08017ed8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08017ed8_MATCHED.s $(BUILD)/w37c2_08017ed8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08017ed8_MATCHED.s
# Wave 37-C2 Sub_08018640 (180 B, old).
$(BUILD)/w37c2_08018640_MATCHED.o: src/w37c2_08018640_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08018640_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08018640_MATCHED.s $(BUILD)/w37c2_08018640_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08018640_MATCHED.s
# Wave 37-C2 Sub_08019400 (180 B, old).
$(BUILD)/w37c2_08019400_MATCHED.o: src/w37c2_08019400_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08019400_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08019400_MATCHED.s $(BUILD)/w37c2_08019400_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08019400_MATCHED.s
# Wave 37-C2 Sub_08019AAC (184 B, old).
$(BUILD)/w37c2_08019aac_MATCHED.o: src/w37c2_08019aac_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08019aac_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08019aac_MATCHED.s $(BUILD)/w37c2_08019aac_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08019aac_MATCHED.s
# Wave 37-C2 Sub_08019BDC (184 B, old).
$(BUILD)/w37c2_08019bdc_MATCHED.o: src/w37c2_08019bdc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08019bdc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08019bdc_MATCHED.s $(BUILD)/w37c2_08019bdc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08019bdc_MATCHED.s
# Wave 37-C2 Sub_08019E7C (188 B, old).
$(BUILD)/w37c2_08019e7c_MATCHED.o: src/w37c2_08019e7c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08019e7c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08019e7c_MATCHED.s $(BUILD)/w37c2_08019e7c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08019e7c_MATCHED.s
# Wave 37-C2 Sub_0801A5F0 (188 B, old).
$(BUILD)/w37c2_0801a5f0_MATCHED.o: src/w37c2_0801a5f0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_0801a5f0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_0801a5f0_MATCHED.s $(BUILD)/w37c2_0801a5f0_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_0801a5f0_MATCHED.s
# Wave 37-C2 Sub_08017984 (160 B TRUE, old; TSV 192 wrong).
$(BUILD)/w37c2_08017984_MATCHED.o: src/w37c2_08017984_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08017984_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08017984_MATCHED.s $(BUILD)/w37c2_08017984_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08017984_MATCHED.s
# Wave 37-C2 Sub_08017A24 (32 B gap leaf, old).
$(BUILD)/w37c2_08017a24_MATCHED.o: src/w37c2_08017a24_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w37c2_08017a24_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w37c2_08017a24_MATCHED.s $(BUILD)/w37c2_08017a24_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w37c2_08017a24_MATCHED.s
# Wave 38-D F_08030AD4 (12,276 B, sanctioned asm transcription, full dispatcher unit).
$(BUILD)/w38d_08030ad4_MATCHED.o: src/w38d_08030ad4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38d_08030ad4_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w38d_08030ad4_MATCHED.s $(BUILD)/w38d_08030ad4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38d_08030ad4_MATCHED.s
# Wave 38-C Sub_08017600 (32 B, old, pure C; gap leaf).
$(BUILD)/w38c_08017600_MATCHED.o: src/w38c_08017600_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38c_08017600_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38c_08017600_MATCHED.s $(BUILD)/w38c_08017600_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38c_08017600_MATCHED.s
# Wave 38-C Sub_08023264 (20 B, old, pure C; gap leaf).
$(BUILD)/w38c_08023264_MATCHED.o: src/w38c_08023264_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38c_08023264_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38c_08023264_MATCHED.s $(BUILD)/w38c_08023264_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38c_08023264_MATCHED.s
# Wave 38-C Sub_08023A7C (112 B TRUE, old + patch; TSV 174 wrong).
$(BUILD)/w38c_08023a7c_MATCHED.o: src/w38c_08023a7c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38c_08023a7c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38c_08023a7c_MATCHED.s $(BUILD)/w38c_08023a7c_MATCHED.i
	python3 tools/fix_w38c_08023a7c_patch.py $(BUILD)/w38c_08023a7c_MATCHED.s $(BUILD)/w38c_08023a7c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38c_08023a7c_MATCHED.s
# Wave 38-C Sub_0801BDE4 (188 B, old + patch; r7-save).
$(BUILD)/w38c_0801bde4_MATCHED.o: src/w38c_0801bde4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38c_0801bde4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38c_0801bde4_MATCHED.s $(BUILD)/w38c_0801bde4_MATCHED.i
	python3 tools/fix_w38c_0801bde4_patch.py $(BUILD)/w38c_0801bde4_MATCHED.s $(BUILD)/w38c_0801bde4_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38c_0801bde4_MATCHED.s
# Wave 38-C Sub_0801C6B0 (196 B, old + patch; 2-register-field).
$(BUILD)/w38c_0801c6b0_MATCHED.o: src/w38c_0801c6b0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38c_0801c6b0_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38c_0801c6b0_MATCHED.s $(BUILD)/w38c_0801c6b0_MATCHED.i
	python3 tools/fix_w38c_0801c6b0_patch.py $(BUILD)/w38c_0801c6b0_MATCHED.s $(BUILD)/w38c_0801c6b0_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38c_0801c6b0_MATCHED.s
# Wave 38-C Sub_080234C8 (208 B, old + patch; clamp-copy insert).
$(BUILD)/w38c_080234c8_MATCHED.o: src/w38c_080234c8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38c_080234c8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38c_080234c8_MATCHED.s $(BUILD)/w38c_080234c8_MATCHED.i
	python3 tools/fix_w38c_080234c8_patch.py $(BUILD)/w38c_080234c8_MATCHED.s $(BUILD)/w38c_080234c8_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38c_080234c8_MATCHED.s
# Wave 38-C Sub_0800E144 (172 B, old + patch; 2-site).
$(BUILD)/w38c_0800e144_MATCHED.o: src/w38c_0800e144_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38c_0800e144_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38c_0800e144_MATCHED.s $(BUILD)/w38c_0800e144_MATCHED.i
	python3 tools/fix_w38c_0800e144_patch.py $(BUILD)/w38c_0800e144_MATCHED.s $(BUILD)/w38c_0800e144_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38c_0800e144_MATCHED.s
# Wave 38-B F_0800ADC8 (308 B, sanctioned asm transcription).
$(BUILD)/w38b_0800adc8_MATCHED.o: src/w38b_0800adc8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38b_0800adc8_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w38b_0800adc8_MATCHED.s $(BUILD)/w38b_0800adc8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38b_0800adc8_MATCHED.s
# Wave 38-B F_080361E8 (304 B, sanctioned asm transcription).
$(BUILD)/w38b_080361e8_MATCHED.o: src/w38b_080361e8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38b_080361e8_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w38b_080361e8_MATCHED.s $(BUILD)/w38b_080361e8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38b_080361e8_MATCHED.s
# Wave 38-B F_0800C268 (312 B, sanctioned asm transcription).
$(BUILD)/w38b_0800c268_MATCHED.o: src/w38b_0800c268_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38b_0800c268_MATCHED.i
	$(AGBCC) $(CFLAGS) -o $(BUILD)/w38b_0800c268_MATCHED.s $(BUILD)/w38b_0800c268_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38b_0800c268_MATCHED.s
# Wave 38-B Sub_08004E60 (128 B, old + patch).
$(BUILD)/w38b_08004e60_MATCHED.o: src/w38b_08004e60_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38b_08004e60_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38b_08004e60_MATCHED.s $(BUILD)/w38b_08004e60_MATCHED.i
	python3 tools/fix_w38b_08004e60_patch.py $(BUILD)/w38b_08004e60_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38b_08004e60_MATCHED.s
# Wave 38-B Sub_08034C1C (132 B, old + patch; callee 34BD4 via .set stub).
$(BUILD)/w38b_08034c1c_MATCHED.o: src/w38b_08034c1c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38b_08034c1c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38b_08034c1c_MATCHED.s $(BUILD)/w38b_08034c1c_MATCHED.i
	python3 tools/fix_w38b_08034c1c_patch.py $(BUILD)/w38b_08034c1c_MATCHED.s
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38b_08034c1c_MATCHED.s
# Wave 38-A bulk lines 347-450 (14 matched, all old_agbcc, pure C).
$(BUILD)/w38a_0801823c_MATCHED.o: src/w38a_0801823c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_0801823c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_0801823c_MATCHED.s $(BUILD)/w38a_0801823c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_0801823c_MATCHED.s
$(BUILD)/w38a_08005130_MATCHED.o: src/w38a_08005130_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08005130_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08005130_MATCHED.s $(BUILD)/w38a_08005130_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08005130_MATCHED.s
$(BUILD)/w38a_08012f4c_MATCHED.o: src/w38a_08012f4c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08012f4c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08012f4c_MATCHED.s $(BUILD)/w38a_08012f4c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08012f4c_MATCHED.s
$(BUILD)/w38a_08013528_MATCHED.o: src/w38a_08013528_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08013528_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08013528_MATCHED.s $(BUILD)/w38a_08013528_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08013528_MATCHED.s
$(BUILD)/w38a_080139fc_MATCHED.o: src/w38a_080139fc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_080139fc_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_080139fc_MATCHED.s $(BUILD)/w38a_080139fc_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_080139fc_MATCHED.s
$(BUILD)/w38a_08017a94_MATCHED.o: src/w38a_08017a94_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08017a94_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08017a94_MATCHED.s $(BUILD)/w38a_08017a94_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08017a94_MATCHED.s
$(BUILD)/w38a_08018fb8_MATCHED.o: src/w38a_08018fb8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08018fb8_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08018fb8_MATCHED.s $(BUILD)/w38a_08018fb8_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08018fb8_MATCHED.s
$(BUILD)/w38a_0802106c_MATCHED.o: src/w38a_0802106c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_0802106c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_0802106c_MATCHED.s $(BUILD)/w38a_0802106c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_0802106c_MATCHED.s
$(BUILD)/w38a_08035a24_MATCHED.o: src/w38a_08035a24_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08035a24_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08035a24_MATCHED.s $(BUILD)/w38a_08035a24_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08035a24_MATCHED.s
$(BUILD)/w38a_08013ad4_MATCHED.o: src/w38a_08013ad4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08013ad4_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08013ad4_MATCHED.s $(BUILD)/w38a_08013ad4_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08013ad4_MATCHED.s
$(BUILD)/w38a_08014078_MATCHED.o: src/w38a_08014078_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_08014078_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_08014078_MATCHED.s $(BUILD)/w38a_08014078_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_08014078_MATCHED.s
$(BUILD)/w38a_0801a484_MATCHED.o: src/w38a_0801a484_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_0801a484_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_0801a484_MATCHED.s $(BUILD)/w38a_0801a484_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_0801a484_MATCHED.s
$(BUILD)/w38a_0801572c_MATCHED.o: src/w38a_0801572c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_0801572c_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_0801572c_MATCHED.s $(BUILD)/w38a_0801572c_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_0801572c_MATCHED.s
$(BUILD)/w38a_0801b728_MATCHED.o: src/w38a_0801b728_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(BUILD)/w38a_0801b728_MATCHED.i
	$(OLDAGBCC) $(CFLAGS) -o $(BUILD)/w38a_0801b728_MATCHED.s $(BUILD)/w38a_0801b728_MATCHED.i
	$(AS) -mthumb $(ASFLAGS) -o $@ $(BUILD)/w38a_0801b728_MATCHED.s

# Wave 39: w39d_08009140_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39d_08009140_MATCHED.o: src/w39d_08009140_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39d_0803b898_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39d_0803b898_MATCHED.o: src/w39d_0803b898_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39a_080285c4_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39a_080285c4_MATCHED.o: src/w39a_080285c4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39a_08048084_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39a_08048084_MATCHED.o: src/w39a_08048084_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39a_0803895c_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39a_0803895c_MATCHED.o: src/w39a_0803895c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39b_0802f5ac_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39b_0802f5ac_MATCHED.o: src/w39b_0802f5ac_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39c_08015278_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w39c_08015278_MATCHED.o: src/w39c_08015278_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w39c_08015278_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 39: w39c_0801a72c_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w39c_0801a72c_MATCHED.o: src/w39c_0801a72c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w39c_0801a72c_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 39: w39c_08013708_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39c_08013708_MATCHED.o: src/w39c_08013708_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39c_0801519c_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39c_0801519c_MATCHED.o: src/w39c_0801519c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39c_08042b60_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39c_08042b60_MATCHED.o: src/w39c_08042b60_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39c_08023f28_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w39c_08023f28_MATCHED.o: src/w39c_08023f28_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 39: w39c_08037700_MATCHED.s (sanctioned asm transcription, coordinator-verified 0-diff).
$(BUILD)/w39c_08037700_MATCHED.o: src/w39c_08037700_MATCHED.s
	@mkdir -p $(BUILD)
	$(AS) -mthumb $(ASFLAGS) -o $@ $<

# Wave 39: w39c_0800c964_MATCHED.s (sanctioned asm transcription, coordinator-verified 0-diff).
$(BUILD)/w39c_0800c964_MATCHED.o: src/w39c_0800c964_MATCHED.s
	@mkdir -p $(BUILD)
	$(AS) -mthumb $(ASFLAGS) -o $@ $<

# Wave 40: w40a_080171c0_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w40a_080171c0_MATCHED.o: src/w40a_080171c0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w40a_080171c0_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 40: w40a_0801e890_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w40a_0801e890_MATCHED.o: src/w40a_0801e890_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w40a_0801e890_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 40: w40b_08003874_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w40b_08003874_MATCHED.o: src/w40b_08003874_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w40b_08003874_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 40: w40b_080118a4_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w40b_080118a4_MATCHED.o: src/w40b_080118a4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w40b_080118a4_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 40: w40b_08019904_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w40b_08019904_MATCHED.o: src/w40b_08019904_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 40: w40b_08035c5c_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w40b_08035c5c_MATCHED.o: src/w40b_08035c5c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 40: w40c_08017b6c_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w40c_08017b6c_MATCHED.o: src/w40c_08017b6c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w40c_08017b6c_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 40: w40c_0802129c_MATCHED.c (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w40c_0802129c_MATCHED.o: src/w40c_0802129c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w40c_0802129c_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 40: w40c_080173bc_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w40c_080173bc_MATCHED.o: src/w40c_080173bc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 40: w40c_08017ce0_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w40c_08017ce0_MATCHED.o: src/w40c_08017ce0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 40: w40d_0804b7f0_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w40d_0804b7f0_MATCHED.o: src/w40d_0804b7f0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 40: w40d_08049780_MATCHED.c (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w40d_08049780_MATCHED.o: src/w40d_08049780_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 41: w41a_08023c38_MATCHED (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w41a_08023c38_MATCHED.o: src/w41a_08023c38_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w41a_08023c38_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 41: w41b_08003b70_MATCHED (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w41b_08003b70_MATCHED.o: src/w41b_08003b70_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w41b_twins_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 41: w41b_08003e80_MATCHED (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w41b_08003e80_MATCHED.o: src/w41b_08003e80_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w41b_twins_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 41: w41c_08015ac4_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w41c_08015ac4_MATCHED.o: src/w41c_08015ac4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 41: w41c_0802d928_MATCHED (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w41c_0802d928_MATCHED.o: src/w41c_0802d928_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w41c_0802d928_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 41: w41d_08020870_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w41d_08020870_MATCHED.o: src/w41d_08020870_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 42: w42a_0801b9e8_MATCHED (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w42a_0801b9e8_MATCHED.o: src/w42a_0801b9e8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w42a_0801b9e8_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 42: w42c_0800e068_MATCHED (coordinator-verified 0-diff, old_agbcc + .s patch).
$(BUILD)/w42c_0800e068_MATCHED.o: src/w42c_0800e068_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w42c_0800e068_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 42: w42d_0804ca30_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w42d_0804ca30_MATCHED.o: src/w42d_0804ca30_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 42: w42d_08046cfc_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w42d_08046cfc_MATCHED.o: src/w42d_08046cfc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 43: w43b_08026430_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w43b_08026430_MATCHED.o: src/w43b_08026430_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 43: w43c_08018398_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w43c_08018398_MATCHED.o: src/w43c_08018398_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 43: w43c_0801b2d0_MATCHED (coordinator-verified 0-diff, old_agbcc + trailing .balign 4,0 zero pad).
$(BUILD)/w43c_0801b2d0_MATCHED.o: src/w43c_0801b2d0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 43: w43a_0803ff80_MATCHED (coordinator-verified 0-diff, old_agbcc + SANCTIONED order-swap .s patch).
$(BUILD)/w43a_0803ff80_MATCHED.o: src/w43a_0803ff80_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w43a_0803ff80_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 44: w44d_08018af4_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w44d_08018af4_MATCHED.o: src/w44d_08018af4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 45: w45c_0800bd20_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w45c_0800bd20_MATCHED.o: src/w45c_0800bd20_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 45: w45d_0801a89c_MATCHED (coordinator-verified 0-diff after SANCTIONED order-swap .s patch, old_agbcc).
$(BUILD)/w45d_0801a89c_MATCHED.o: src/w45d_0801a89c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w45d_0801a89c_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 46: w46a_08020660_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w46a_08020660_MATCHED.o: src/w46a_08020660_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 46: w46c_0801c800_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w46c_0801c800_MATCHED.o: src/w46c_0801c800_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 46: w46c_08001ae4_MATCHED (coordinator-verified 0-diff after SANCTIONED order-swap .s patch, old_agbcc).
$(BUILD)/w46c_08001ae4_MATCHED.o: src/w46c_08001ae4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w46c_08001ae4_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 46: w46d_0801c2e0_MATCHED (coordinator-verified 0-diff, old_agbcc; trailing .balign pad in-section per Wave 43 precedent).
$(BUILD)/w46d_0801c2e0_MATCHED.o: src/w46d_0801c2e0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 46: w46d_0801bb94_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w46d_0801bb94_MATCHED.o: src/w46d_0801bb94_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 46: w46d_0801ba94_MATCHED (coordinator-verified 0-diff after SANCTIONED register-field .s patch, old_agbcc).
$(BUILD)/w46d_0801ba94_MATCHED.o: src/w46d_0801ba94_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w46d_0801ba94_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 47: w47a_08001bf8_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w47a_08001bf8_MATCHED.o: src/w47a_08001bf8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 47: w47c_0801c9a8_MATCHED (coordinator-verified 0-diff, old_agbcc).
$(BUILD)/w47c_0801c9a8_MATCHED.o: src/w47c_0801c9a8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 47: w47d_08044630_MATCHED (coordinator-verified 0-diff after SANCTIONED order-swap + register-field .s patch, old_agbcc).
$(BUILD)/w47d_08044630_MATCHED.o: src/w47d_08044630_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w47d_08044630_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 47: w47d_0804472c_MATCHED (coordinator-verified 0-diff after SANCTIONED order-swap + register-field .s patch, old_agbcc).
$(BUILD)/w47d_0804472c_MATCHED.o: src/w47d_0804472c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w47d_0804472c_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 48: w48c_0804b634_MATCHED (coordinator-verified 0-diff after SANCTIONED 4-site register-field .s patch, old_agbcc).
$(BUILD)/w48c_0804b634_MATCHED.o: src/w48c_0804b634_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w48c_0804b634_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 49: w49c_08041fbc_MATCHED (coordinator-verified 0-diff after SANCTIONED 4-site .s patch: mode-1 reorder + 3 register-field renames, old_agbcc).
$(BUILD)/w49c_08041fbc_MATCHED.o: src/w49c_08041fbc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w49c_triple_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 49: w49c_080420d0_MATCHED (coordinator-verified 0-diff after SANCTIONED 4-site .s patch: mode-1 reorder + 3 register-field renames, old_agbcc).
$(BUILD)/w49c_080420d0_MATCHED.o: src/w49c_080420d0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w49c_triple_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 49: w49c_080421e4_MATCHED (coordinator-verified 0-diff after SANCTIONED 4-site .s patch: mode-1 reorder + 3 register-field renames, old_agbcc).
$(BUILD)/w49c_080421e4_MATCHED.o: src/w49c_080421e4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w49c_triple_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)
# Wave 49: w49d_0801d488_MATCHED (coordinator-verified 0-diff, pure C + inline-asm steering, old_agbcc).
$(BUILD)/w49d_0801d488_MATCHED.o: src/w49d_0801d488_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 49: w49d_080275f8_MATCHED (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w49d_080275f8_MATCHED.o: src/w49d_080275f8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50b_0801ebd0_MATCHED (coordinator-verified 0-diff, pure C + inline-asm barrier + r1 pin (no calls in leaf), old_agbcc).
$(BUILD)/w50b_0801ebd0_MATCHED.o: src/w50b_0801ebd0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50b_0800d278_MATCHED (coordinator-verified 0-diff, pure C + trailing .balign 4, 0 pad, old_agbcc).
$(BUILD)/w50b_0800d278_MATCHED.o: src/w50b_0800d278_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50c_08042878_MATCHED (coordinator-verified 0-diff, pure C + inline-asm steering (zero-byte asms), old_agbcc).
$(BUILD)/w50c_08042878_MATCHED.o: src/w50c_08042878_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50d_0801200c_MATCHED (coordinator-verified 0-diff with trailing .balign 4, 0 pad (v8 alone 228 B / 2 pad-only diffs), old_agbcc).
$(BUILD)/w50d_0801200c_MATCHED.o: src/w50d_0801200c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50d_08012190_MATCHED (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w50d_08012190_MATCHED.o: src/w50d_08012190_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50d_0800d59c_MATCHED (coordinator-verified 0-diff, pure C + inline-asm steering, old_agbcc).
$(BUILD)/w50d_0800d59c_MATCHED.o: src/w50d_0800d59c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50d_08013280_MATCHED (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w50d_08013280_MATCHED.o: src/w50d_08013280_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 50: w50d_08014fb4_MATCHED (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w50d_08014fb4_MATCHED.o: src/w50d_08014fb4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 51: w51a_08015644_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w51a_08015644_MATCHED.o: src/w51a_08015644_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 51: w51c_0800fee0_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w51c_0800fee0_MATCHED.o: src/w51c_0800fee0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 51: w51d_08000418_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w51d_08000418_MATCHED.o: src/w51d_08000418_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 51: w51c_0801eac4_MATCHED.c (coordinator-verified 0-diff after SANCTIONED 1-site register-field .s patch, old_agbcc).
$(BUILD)/w51c_0801eac4_MATCHED.o: src/w51c_0801eac4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w51c_0801eac4_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 52: w52a_0800fc64_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc).
$(BUILD)/w52a_0800fc64_MATCHED.o: src/w52a_0800fc64_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 52: w52b_080240cc_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (old-only: main gives 220 B / 167 diffs)).
$(BUILD)/w52b_080240cc_MATCHED.o: src/w52b_080240cc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 52: w52d_08011560_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (old-only: main gives 252 B / 12 diffs)).
$(BUILD)/w52d_08011560_MATCHED.o: src/w52d_08011560_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 53: w53a_0800bfd0_MATCHED.c (coordinator-verified 0-diff after SANCTIONED 2-site register-field .s patch, old_agbcc; raw C 232 B / 5 diffs).
$(BUILD)/w53a_0800bfd0_MATCHED.o: src/w53a_0800bfd0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	python3 $(TOOLS)/fix_w53a_0800bfd0_patch.py $(@:.o=.s) $(@:.o=.patched.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.patched.s)

# Wave 53: w53b_080170d4_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (old-only: main gives 35 diffs on base)).
$(BUILD)/w53b_080170d4_MATCHED.o: src/w53b_080170d4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 54: w54c_080059a8_MATCHED.c (coordinator-verified 0-diff, pure C + inline-asm add + block-scoped pins, old_agbcc (old-only: main gives 29 diffs).)
$(BUILD)/w54c_080059a8_MATCHED.o: src/w54c_080059a8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 54: w54d_08013434_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc.)
$(BUILD)/w54d_08013434_MATCHED.o: src/w54d_08013434_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 54: w54d_08014154_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (twin propagation).)
$(BUILD)/w54d_08014154_MATCHED.o: src/w54d_08014154_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 54: w54d_08014318_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (twin propagation).)
$(BUILD)/w54d_08014318_MATCHED.o: src/w54d_08014318_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 54: w54d_0801440c_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (twin propagation).)
$(BUILD)/w54d_0801440c_MATCHED.o: src/w54d_0801440c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 54: w54d_080145cc_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (twin propagation).)
$(BUILD)/w54d_080145cc_MATCHED.o: src/w54d_080145cc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 54: w54d_08019d18_MATCHED.c (coordinator-verified 0-diff, pure C + trailing .balign 4, 0, old_agbcc (old-only: main gives 8 diffs).)
$(BUILD)/w54d_08019d18_MATCHED.o: src/w54d_08019d18_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 55: w55d_0800695c_MATCHED.c (coordinator-verified 0-diff, pure C + trailing .balign 4, 0, old_agbcc (old-only).)
$(BUILD)/w55d_0800695c_MATCHED.o: src/w55d_0800695c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 55: w55d_08013904_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (old-only).)
$(BUILD)/w55d_08013904_MATCHED.o: src/w55d_08013904_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 55: w55d_08013bb0_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (old-only).)
$(BUILD)/w55d_08013bb0_MATCHED.o: src/w55d_08013bb0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 55: w55d_08014eb8_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (old-only).)
$(BUILD)/w55d_08014eb8_MATCHED.o: src/w55d_08014eb8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 55: w55d_08023fd0_MATCHED.c (coordinator-verified 0-diff, pure C, old_agbcc (old-only).)
$(BUILD)/w55d_08023fd0_MATCHED.o: src/w55d_08023fd0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 55: w55a_08027e8c_MATCHED.c (coordinator-verified 0-diff, pure C + extern-array tables + block-scoped tail pin, old_agbcc (old-only: main gives 7 diffs).)
$(BUILD)/w55a_08027e8c_MATCHED.o: src/w55a_08027e8c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 55: w55d_08028778_MATCHED.c (coordinator-verified 0-diff, pure C + inline-asm ldrsb + file-scope .balign 4, 0, old_agbcc (old-only).)
$(BUILD)/w55d_08028778_MATCHED.o: src/w55d_08028778_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 56: w56d_08014944_MATCHED.c (coordinator-verified 0-diff, pure C + unsigned-shift nibble + table-base barrier + shared inc block, old_agbcc (old-only: main gives 4 diffs).)
$(BUILD)/w56d_08014944_MATCHED.o: src/w56d_08014944_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 56: w56d_0801509c_MATCHED.c (coordinator-verified 0-diff, pure C, twin of 14944 with case1/case2 swapped, ChipInit 1, old_agbcc (old-only: main gives 4 diffs).)
$(BUILD)/w56d_0801509c_MATCHED.o: src/w56d_0801509c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 57: w57a_08010138_MATCHED.c (coordinator-verified 0-diff under old AND main agbcc, pure C + explicit-shift zero-extension + block-scoped r0 pins, old_agbcc.)
$(BUILD)/w57a_08010138_MATCHED.o: src/w57a_08010138_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 57: w57a_08025a64_MATCHED.c (coordinator-verified 0-diff under old AND main agbcc, pure C + tbh temp pin + pin-args, old_agbcc.)
$(BUILD)/w57a_08025a64_MATCHED.o: src/w57a_08025a64_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 57: w57c_0801d070_MATCHED.c (coordinator-verified 0-diff, old_agbcc only, pure C + struct-pair copy + w36b trailing pad.)
$(BUILD)/w57c_0801d070_MATCHED.o: src/w57c_0801d070_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 57: w57d_08018d18_MATCHED.c (coordinator-verified 0-diff, old_agbcc only, main gives 8 diffs, pure C + shared block after case 3 + empty-asm dead-load use.)
$(BUILD)/w57d_08018d18_MATCHED.o: src/w57d_08018d18_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 58: w58b_080067bc_MATCHED.c (coordinator-verified 0-diff under BOTH old and main agbcc, pure C + trailing-pad asm; second callee takes 7 args not 8 — corrects the Wave 57 frame-wall diagnosis.)
$(BUILD)/w58b_080067bc_MATCHED.o: src/w58b_080067bc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 59: w59d_08028fec_MATCHED.c (coordinator-verified 0-diff under old_agbcc ONLY, main gives 53 diffs; pure C switch dispatch + named -16 int temp + mode-4 zero temp.)
$(BUILD)/w59d_08028fec_MATCHED.o: src/w59d_08028fec_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60b_0802f364_MATCHED.c (coordinator-verified 0-diff under old_agbcc ONLY, main gives 425 diffs; minimal scoped copy-only inline asm (compiler emits lsl/lsr, asm emits adds) + pin-arg + per-branch dst+mask + trailing .balign 4, 0 (code 490 B, 2 mod 4).)
$(BUILD)/w60b_0802f364_MATCHED.o: src/w60b_0802f364_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60c_08013600_MATCHED.c (coordinator-verified 0-diff under old_agbcc; shared inc block inside switch between case 4 and case 5.)
$(BUILD)/w60c_08013600_MATCHED.o: src/w60c_08013600_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60c_08015378_MATCHED.c (coordinator-verified 0-diff under old_agbcc; case 2 falls through 174A4/178A8 block into inc, case 3 increments inline then falls into case 4; const 0xFFFFD300 = -11520.)
$(BUILD)/w60c_08015378_MATCHED.o: src/w60c_08015378_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60c_08015538_MATCHED.c (coordinator-verified 0-diff under old_agbcc; shared D9EC block via q/d9arg, case-4 bound <= 6 with no 17478 call, byte-pair via t++ pointer-increment form.)
$(BUILD)/w60c_08015538_MATCHED.o: src/w60c_08015538_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60d_08014a44_MATCHED.c (coordinator-verified 0-diff under old_agbcc; switch on s[14], jump table, shared s[14]++ tail + Tick epilogue.)
$(BUILD)/w60d_08014a44_MATCHED.o: src/w60d_08014a44_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60d_08013024_MATCHED.c (coordinator-verified 0-diff under old_agbcc; switch on s[14]; case 2 block-scoped r2-pinned nibble variable.)
$(BUILD)/w60d_08013024_MATCHED.o: src/w60d_08013024_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60d_08012274_MATCHED.c (coordinator-verified 0-diff under old_agbcc; switch on s[14] with bls+b dispatch; case 2 5-arg ChipInit via w39c idioms (r2-pinned table base + barrier, asm-add entry, lsl/asr trunc asm, register-offset ldrsh halves).)
$(BUILD)/w60d_08012274_MATCHED.o: src/w60d_08012274_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 60: w60d_080137e4_MATCHED.c (coordinator-verified 0-diff under old_agbcc; switch on s[14]; case 1 F_0801EBF0(36, -1, inline-nibble, -15360, 0), case 2 6-arg Sub_0801AA70 with r3-pinned base + asm-add entry + register-offset ldrsh halves.)
$(BUILD)/w60d_080137e4_MATCHED.o: src/w60d_080137e4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 61: w61c_08010bb4_MATCHED.c (coordinator-verified 0-diff under old_agbcc ONLY, main gives 12 diffs; pure C, no patch; c3 shift temp int pinned r3 + accumulator pinned r0; TRUE extent 260 B.)
$(BUILD)/w61c_08010bb4_MATCHED.o: src/w61c_08010bb4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 61: w61c_0801bc70_MATCHED.c (coordinator-verified 0-diff under old_agbcc ONLY, main gives 10 diffs; pure C, no r7 pin; t7 plain s32 + separate neg local + empty-asm +r(x) barrier; TRUE extent 268 B.)
$(BUILD)/w61c_0801bc70_MATCHED.o: src/w61c_0801bc70_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 63: w63c_0802cce4_MATCHED.c (coordinator-verified 488/2-pad-only, 0 code diffs under old_agbcc ONLY, main gives 93 diffs; int f + plain s16 reload; call-D extension via in-place lsl/asr stmt-expr asm + int a7 prototype — coordinator-sanctioned source-level asm, same class as landed ldrsb idiom; no empty asm, efm flag discharged; trailing .balign 4, 0 pad, code 486 B, 2 mod 4; TRUE extent 488 B.)
$(BUILD)/w63c_0802cce4_MATCHED.o: src/w63c_0802cce4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 64: w64a_080466ac_MATCHED.c (coordinator-verified 0-diff under old_agbcc + sed fixups, 02CB0 precedent; pure C gives 96 diffs; x-home permutation resisted all pure-C levers; sed performs register renames, side-effect-free load motion, ew exit fix with ROM-verified pool word 0x02004CE0; caller-local wider declarations are codegen-necessary — matched-prototype variant tested 348 B / 263 diffs; TRUE extent 304 B.)
$(BUILD)/w64a_080466ac_MATCHED.o: src/w64a_080466ac_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	sed -f $(TOOLS)/fix_w64a_080466ac.sed $(@:.o=.s) > $(@:.o=.s.fixed)
	mv $(@:.o=.s.fixed) $(@:.o=.s)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 65: w65b_0800cf10_MATCHED.c (coordinator-verified 316/0 under old_agbcc ONLY, main gives 31 diffs; s16 narrow toggle temps lo=(t^1)&1, hi=t&-2 break the r3-constant/bit-reuse coupling; pure C, no asm, toggle-region asm decision moot; TRUE extent 316 B.)
$(BUILD)/w65b_0800cf10_MATCHED.o: src/w65b_0800cf10_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 65: w65d_0804a0a4_MATCHED.c (coordinator-verified 332/0 under old_agbcc ONLY, main gives 4 diffs; 6 bl sites; TRUE extent 332 B = 302 code + 2 pad + 28 pool. LOAD-BEARING: CondRectFill y declared s8 in this file — matched source says u8 + internal cast — to reproduce caller-side lsl/asr; do not 'fix' to u8 without re-verifying 4A0A4. .set strips: Gfx_BlitRequest, CondRectFill_080062B4, ShiftPairCfg_4A1F0, exact-case T globals.)
$(BUILD)/w65d_0804a0a4_MATCHED.o: src/w65d_0804a0a4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 65: w65d_0801910c_MATCHED.c (coordinator-verified 316/0 under old_agbcc ONLY, main gives 4 diffs; u64 out-pair idiom + whole-u64 empty asm + trailing .balign pad; TRUE extent 316 B = 314 code + 2 pad, mid-function pools. .set strips: Memcpy_4DFA8, Vec2_AddMirrored, SetBit16, ChipSlot_IncUse, GetField17_U8, exact-case T globals; Vec2_CopyMirrored + sub_080178A8 kept, local absolutes/absent.)
$(BUILD)/w65d_0801910c_MATCHED.o: src/w65d_0801910c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 66: w66a_080147fc_MATCHED.c (coordinator-verified 328/0 under old_agbcc ONLY; switch sibling of 146C0, tiles into MATCHED 14944; TRUE extent 328 B. LOAD-BEARING: Check119_Minus3_Le1 declared u16 in this file (landed prototype unsigned int) to emit caller-side lsl#16/cmp/beq; do not 'fix' without re-verifying 147FC. .set strips: all 11, exact-case T globals.)
$(BUILD)/w66a_080147fc_MATCHED.o: src/w66a_080147fc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 66: w66a_08012a3c_MATCHED.c (coordinator-verified 324/0 under old_agbcc ONLY (main 4 diffs); nibble shift idiom; alternate 0-diff form staged at staging/w66d_1de84/12a3c_best_w66d.c (not landed); TRUE extent 324 B. LOAD-BEARING: Check119 declared u16 (landed unsigned int); ChipInit_0801EBF0 declared (u8,s32,u8,s32,u16) vs landed (u8,u8,u8,u16,u16); ChipInit_080178A8 d-param s32 vs landed u16; do not 'fix' without re-verifying 12A3C. .set strips: all 12, exact-case T globals.)
$(BUILD)/w66a_08012a3c_MATCHED.o: src/w66a_08012a3c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 66: w66a_08025b60_MATCHED.c (coordinator-verified 320/0 under old_agbcc ONLY; GetRomTableU16 direct-args idiom + 4*i+20+s pointer form; TRUE extent 320 B. LOAD-BEARING: GetRomTableU16_080266F0 declared returning int (and GetU16_10 as unsigned int) to avoid spurious post-call truncation; reconcile with landed prototypes only with re-verification. .set keeps: all 6, absent/local absolutes.)
$(BUILD)/w66a_08025b60_MATCHED.o: src/w66a_08025b60_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 67: w67a_080289c4_MATCHED.c (coordinator-verified 328/0 under old_agbcc ONLY (main 332/256); block-scoped r0 pin breaks the CSE cascade for the s[24]=0 store + address-variable form flips the zero-loop adds to ROM order; TRUE extent 328 B. Alternate 0-diff form w67a_080289c4_v27_apaddr.c staged (not landed). .set strips: sub_0800EA14, Sub_0802E9F8 (exact-case T globals at same addresses); keeps rest incl. gEwram data .set.)
$(BUILD)/w67a_080289c4_MATCHED.o: src/w67a_080289c4_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 67: w67d_08015f90_MATCHED.c (coordinator-verified 324/0 under old_agbcc (main also 0); fresh switch-dispatch ChipSlot state machine, jump-table targets all local — 147FC mould, NOT a dispatcher trap; TRUE extent 324 B = 322 code + 2 pad. LOAD-BEARING: Check119 declared u16 per landed 12A3C (landed prototype unsigned int); Check_08017494 is NEW, call-site-derived u8 decl; Vec2 constants bit-exact s32 of unknown semantic type; trailing 2 pad bytes via file-scope .balign (link-layout padding in full build). .set strips: ChipSlot_IncUse, ChipSlot_Tick, Vec2_SetMirrored, GetField17_U8, MaxAssign_17, DecIfNonZero_18, SetBytes_08011F68, SetBit16 (exact-case T globals at same addresses); keeps Check119, Check_08017494 (absent).)
$(BUILD)/w67d_08015f90_MATCHED.o: src/w67d_08015f90_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 68: w68c_080146c0_MATCHED.c (coordinator-verified 316/0 under old_agbcc; pure-C case-2 ordering m=15; b=gEntryMgr[0x11AF]; f=0xF0 breaks the W66/W67 6-diff floor; W67 asm proposal2 now SUPERSEDED (backup only). LOAD-BEARING: Check119_Minus3_Le1 declared u16 here (landed prototype unsigned int) -- landed-prototype variant tested 316/206 (breaks); only the narrow form emits caller-side lsl#16/cmp/beq in cases 1+3, same class as landed 147FC/12A3C. TRUE extent 316 B. .set strips: Check119_Minus3_Le1, ChipSlot_IncUse, ChipSlot_Tick, DecIfNonZero_18, GetField17_U8, MaxAssign_17, SetBit16, SetBytes_08011F68, TestBit16, Text_SelectBlobIdx, Vec2_SetMirrored (exact-case T globals at same addresses); keeps PalModeSet_4DFC (A only), sub_080178A8 (a only), gEntryMgr (absent).)
$(BUILD)/w68c_080146c0_MATCHED.o: src/w68c_080146c0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 68: w68a_08013138_MATCHED.c (coordinator-verified 328/0 under old_agbcc; fresh switch-dispatch ChipSlot state machine, cases 0-7, default -> Tick; jump-table pointer @0x08013154 = 0x08013158, table @0x08013158, 8 entries, all inside extent; TRUE extent 328 B = 324 code + 4 pool 0xFFFFC400. .set strips: ChipInit_0801AA70, ChipSlot_IncUse, ChipSlot_Tick, GetField17_U8, SetBytes_08011F68, Vec2_SetMirrored (exact-case T globals at same addresses); keeps Check119 (a only), Check_080174A4 (absent), F_08017464 (absent).)
$(BUILD)/w68a_08013138_MATCHED.o: src/w68a_08013138_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 68: w68a_08012504_MATCHED.c (coordinator-verified 328/0 under old_agbcc; fresh switch-dispatch ChipSlot state machine, cases 0-6, default -> Tick; jump table @0x08012524, 7 entries, inside extent; TRUE extent 328 B. LOAD-BEARING: ChipInit_0801BBB4 declared (u8,u8,s32,s32,u8*) here vs landed w17c (u8,u8,u16,u16,u8*) -- landed-prototype variant tested 324/156 (breaks catastrophically); the s32 form is codegen-necessary for the full-word pool constants 0xFFFFA600/0xFFFFCD00 (466ac precedent: tested, not assumed). .set strips: ChipInit_0801BBB4, ChipSlot_IncUse, ChipSlot_Tick, GetField17_U8, SetBytes_08011F68, Text_SelectBlobIdx, Vec2_SetMirrored (exact-case T globals at same addresses); keeps Check119 (a only), F_08017464 (absent).)
$(BUILD)/w68a_08012504_MATCHED.o: src/w68a_08012504_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 68: w68a_08026238_MATCHED.c (coordinator-verified 324/0 under old_agbcc; fresh find-or-append, sibling of landed 0x08026430; u16 sub_08026238(u8 *q, u8 *key); TRUE extent 324 B = 322 code + 2 pad via trailing .balign 4, 0. NOTE: caller w34c_08024fbc passes 3 args but arg2 is never read by this function (r2 first used as temp) -- landed prototype keeps 2 args, the true signature. .set keeps: all 7 (F_08023AEC, F_080263A4, F_080252D0, F_08025290, F_0802526C, F_0802637C, F_08026720 -- all absent from nm).)
$(BUILD)/w68a_08026238_MATCHED.o: src/w68a_08026238_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 69: w69a_08013cac_MATCHED.c (coordinator-verified 332/0 under old_agbcc; fresh switch-dispatch ChipSlot state machine, 7 cases on s[14], shared IncUse/s[14]++ tails, tail ChipSlot_Tick; struct-return Pair Vec2_CopyMirrored emits ROM's dead load of v.y. TRUE extent 332 B. .set strips: Vec2_SetMirrored, ChipSlot_IncUse, Check119_Minus3_Le1, Text_SelectBlobIdx, SetBit16, ChipInit_080178A8, GetField17_U8, MaxAssign_17, DecIfNonZero_18, SetBytes_08011F68, ChipSlot_Tick (exact-case T globals at same addresses); keeps Vec2_AddMirrored, Vec2_CopyMirrored (a only, no T).)
$(BUILD)/w69a_08013cac_MATCHED.o: src/w69a_08013cac_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 69: w69d_08018064_MATCHED.c (coordinator-verified 328/0 under old_agbcc; fresh ChipSlot state machine, switch s[13] under s[16]==2 and !=2, dead Pair from Sub_0800DD08; volatile Pair forces both stack loads incl. dead ldr r2,[sp,#8]; register s32 py r2 gives ROM-exact dead load; toggle temp variable at both toggle sites; goto ret0 moves shared return-0 block to end. TRUE extent 328 B = 326 code + 2 pad via trailing .balign 4, 0. Callee prototypes (DD4C/DD08/178A8) remain call-site-derived/unproven; the match proves call sequences, not callee signatures. .set strips: none; keeps Sub_0800DD4C, Sub_0800DD08, Sub_080178A8 (a only, no T).)
$(BUILD)/w69d_08018064_MATCHED.o: src/w69d_08018064_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 70: w70a_08012d28_MATCHED.c (coordinator-verified 340/0 under old_agbcc; fresh Vec2-family switch on s[14], cases 0..6, default -> Tick tail; shared SetMirrored+IncUse/s[14]++ tails; TRUE extent 340 B = 336 code through bx @0x12E76 + 4 trailing pool @0x12E78 = 0xFFFFC400. Main agbcc gives 2 diffs, so OLDAGBCC rule. .set strips (10, exact-case T globals): Vec2_SetMirrored, ChipSlot_IncUse, Check119_Minus3_Le1, Text_SelectBlobIdx, SetBit16, ChipInit_080178A8, MaxAssign_17, DecIfNonZero_18, SetBytes_08011F68, ChipSlot_Tick; keeps: none (whole __asm__ block removed).)
$(BUILD)/w70a_08012d28_MATCHED.o: src/w70a_08012d28_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 70: w70a_08013f24_MATCHED.c (coordinator-verified 340/0 under old_agbcc; fresh Vec2-family switch on s[14], cases 0..7, default -> Tick tail; case-3 6-arg callee 0x0801AA70 is a NEW caller-TU prototype (u8,u8,u8,s32,u32,u8*) -- real signature unknown, only call shape verified; case-4 gate is GetField17>6 (NOT 5 as in 13CAC/1CB44, NOT Check119-gated). TRUE extent 340 B = 336 code through bx @0x14072 + 4 trailing pool @0x14074 = 0xFFFFC400. Main agbcc gives 2 diffs, so OLDAGBCC rule. .set strips (9, exact-case T globals): Vec2_SetMirrored, ChipSlot_IncUse, Check119_Minus3_Le1, Text_SelectBlobIdx, SetBit16, GetField17_U8, DecIfNonZero_18, SetBytes_08011F68, ChipSlot_Tick; keeps Call_0801AA70 (no baseline symbol).)
$(BUILD)/w70a_08013f24_MATCHED.o: src/w70a_08013f24_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
# Wave 70: w70a_08024cd8_MATCHED.c (coordinator-verified 340/0 under old_agbcc; fresh u16 F(u8*,u8,u8), element expression recomputed at EVERY call site, outer condition flipped F1==0 branch first; F1/F2/F3 return u8, F4/F5/F6 declared u32 so the u16 caller truncates; F5 emitted once (shared tail), F6 twice; 432 hoisted to r7 except the F1!=0 branch first F2 site rematerialization. TRUE extent 340 B = 340 code through bx @0x24E2A, no pool, no pad. Main agbcc gives 49 diffs, so OLDAGBCC rule. .set strips: none; keeps all 6 Call_08025xxx (no baseline symbols -- including Call_08025B60, the Wave-66-landed function, whose baseline symbol is under a different name, so the stub is load-bearing).)
$(BUILD)/w70a_08024cd8_MATCHED.o: src/w70a_08024cd8_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 72: w72a_080493ec_MATCHED.c (coordinator-verified 372/0 under old_agbcc; fresh u8 F(u8*s), Teardown first / Setup tail, case-0 falls through into case 1 shared ending, case-3 TABLE-load-after-call split + shift interleave, case-0 ands block as int t with u32 0xFFFFFC3F mask variable. TRUE extent 372 B = 364 code through bx @0x49556 + pools 0x46A4 @0x49558, 0x46A5 @0x4955C. Main agbcc gives 376 B / 189 diffs, so OLDAGBCC rule. .set strips: none; keeps all Call_ stubs (no baseline symbols -- including Call_0804A40C (BLOCKED) and Call_08049560 (next fn), both load-bearing stubs).)
$(BUILD)/w72a_080493ec_MATCHED.o: src/w72a_080493ec_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 73: sub_08041E58 / sub_0801264C need old_agbcc.
$(BUILD)/w73a_08041e58_MATCHED.o: src/w73a_08041e58_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
$(BUILD)/w73a_0801264c_MATCHED.o: src/w73a_0801264c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 74: sub_0801238C / sub_08012880 need old_agbcc (coordinator-verified 376/0 each, pure C, no flags).
$(BUILD)/w74a_0801238c_MATCHED.o: src/w74a_0801238c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
$(BUILD)/w74a_08012880_MATCHED.o: src/w74a_08012880_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 78: sub_08037F38 needs old_agbcc (coordinator-verified 384/0, pure C, no flags).
$(BUILD)/w78d_08037f38_MATCHED.o: src/w78d_08037f38_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 83: sub_08014B54 needs old_agbcc (coordinator-verified 412/0, pure C, no flags).
$(BUILD)/w83a_08014b54_MATCHED.o: src/w83a_08014b54_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 83: sub_0802FDA0 needs old_agbcc (coordinator-verified 416/0, pure C + explicit same-section zero pad object, no flags).
$(BUILD)/w83a_0802fda0_MATCHED.o: src/w83a_0802fda0_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

# Wave 83: sub_08039CFC needs old_agbcc (coordinator-verified 416/0, pure C, no flags).
$(BUILD)/w83a_08039cfc_MATCHED.o: src/w83a_08039cfc_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)

$(BUILD)/w84d_0804367c_MATCHED.o: src/w84d_0804367c_MATCHED.c
	@mkdir -p $(BUILD)
	$(CPP) $(CPPFLAGS) $< -o $(@:.o=.i)
	$(OLDAGBCC) $(CFLAGS) -o $(@:.o=.s) $(@:.o=.i)
	$(AS) -mthumb $(ASFLAGS) -o $@ $(@:.o=.s)
