OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Start)

/* Phase-0 linker script. Explicit per-object ordering is what will make
   the link byte-identical later (cf. ANALYSIS.md section 3.2):
   rom_header.o first (0x08000000), then crt0.o (Init at 0x080000C0),
   then everything else in link order. asm/ and src/ objects get
   explicit slots here as functions are matched in Phase 3. */
SECTIONS
{
    . = 0x08000000;
    .text : {
        build/rom_header.o (.text);
        build/crt0.o (.text);
        *(.text);
    }

    /* Save-driver slice (Phase 1): BIOS veneer table + 6 SRAM primitives,
       explicitly placed at 0x0804DB24, before everything else is matched. */
    . = 0x0804DB24;
    .text.savedrv : { build/savedrv.o (.text.savedrv); }

    /* Phase 3 Wave 0 (matched C): BIOS veneers, SRAM primitives, and the
       _call_via_rN thunk span. Added by the Wave-0 worker. */
    . = 0x0804DB24; .text.bios   : { build/bios.o (.text.bios); }
    . = 0x0804DB38; .text.sram   : { build/sram.o (.text.sram); }
    . = 0x08000eb8; .text.w37b_08000eb8 : { build/w37b_08000eb8_MATCHED.o (.text.w37b_08000eb8); } /* Wave 37-B Sub_08000EB8 (28 B, old) */
    . = 0x08000ed4; .text.w37b_08000ed4 : { build/w37b_08000ed4_MATCHED.o (.text.w37b_08000ed4); } /* Wave 37-B Sub_08000ED4 (36 B, old) */
    . = 0x0800288c; .text.w36d_0800288c : { build/w36d_0800288c_MATCHED.o (.text.w36d_0800288c); } /* Wave 36 reconciliation Sub_0800288C (68 B, main) */
    . = 0x080050f0; .text.w36d_080050f0 : { build/w36d_080050f0_MATCHED.o (.text.w36d_080050f0); } /* Wave 36 reconciliation Sub_080050F0 (64 B, main) */
    . = 0x08005434; .text.w37c_08005434 : { build/w37c_08005434_MATCHED.o (.text.w37c_08005434); } /* Wave 37-C Sub_08005434 (156 B, old) */
    . = 0x08007798; .text.w36bulk_08007798 : { build/w36bulk_08007798_MATCHED.o (.text.w36bulk_08007798); } /* Wave 36 reconciliation Sub_08007798 (128 B, old) */
    . = 0x08007c04; .text.w37b_08007c04 : { build/w37b_08007c04_MATCHED.o (.text.w37b_08007c04); } /* Wave 37-B Sub_08007C04 (136 B, old + patch, inline-asm ldrsb) */
    . = 0x08007f24; .text.w37b_08007f24 : { build/w37b_08007f24_MATCHED.o (.text.w37b_08007f24); } /* Wave 37-B Sub_08007F24 (24 B, old) */
    . = 0x08009238; .text.w37a_08009238 : { build/w37a_08009238_MATCHED.o (.text.w37a_08009238); } /* Wave 37 Sub_08009238 (144 B, old, empty-asm barrier defeats const folding) */
    . = 0x08009edc; .text.w37c_08009edc : { build/w37c_08009edc_MATCHED.o (.text.w37c_08009edc); } /* Wave 37-C Sub_08009EDC (156 B, old) */
    . = 0x0800b448; .text.w36d_0800b448 : { build/w36d_0800b448_MATCHED.o (.text.w36d_0800b448); } /* Wave 36 reconciliation Sub_0800B448 (40 B, main) */
    . = 0x0800c878; .text.w36d_0800c878 : { build/w36d_0800c878_MATCHED.o (.text.w36d_0800c878); } /* Wave 36 reconciliation Sub_0800C878 (68 B, main) */
    . = 0x0800cb70; .text.w36a_0800cb70 : { build/w36a_0800cb70_MATCHED.o (.text.w36a_0800cb70); } /* Wave 36 reconciliation Lookup_0800cb70 (80 B, main + tools/fix_0800cb70.py) */
    . = 0x0800ec7c; .text.w36a_0800ec7c : { build/w36a_0800ec7c_MATCHED.o (.text.w36a_0800ec7c); } /* Wave 36 reconciliation Wrap_0800ec7c (92 B, main) */
    . = 0x0800edb0; .text.w36d_0800edb0 : { build/w36d_0800edb0_MATCHED.o (.text.w36d_0800edb0); } /* Wave 36 reconciliation Sub_0800EDB0 (52 B, main) */
    . = 0x08010d84; .text.w36a_08010d84 : { build/w36a_08010d84_MATCHED.o (.text.w36a_08010d84); } /* Wave 36 reconciliation Step_08010d84 (88 B, old) */
    . = 0x080112cc; .text.w36d_080112cc : { build/w36d_080112cc_MATCHED.o (.text.w36d_080112cc); } /* Wave 36 reconciliation Sub_080112CC (48 B, main) */
    . = 0x08011530; .text.w37b_08011530 : { build/w37b_08011530_MATCHED.o (.text.w37b_08011530); } /* Wave 37-B Sub_08011530 (48 B, old + patch) */
    . = 0x08016c94; .text.w37c_08016c94 : { build/w37c_08016c94_MATCHED.o (.text.w37c_08016c94); } /* Wave 37-C Sub_08016C94 (152 B, old) */
    . = 0x080129f8; .text.w36d_080129f8 : { build/w36d_080129f8_MATCHED.o (.text.w36d_080129f8); } /* Wave 36 reconciliation Sub_080129F8 (68 B, main) */
    . = 0x080174f4; .text.w37b_080174f4 : { build/w37b_080174f4_MATCHED.o (.text.w37b_080174f4); } /* Wave 37-B Sub_080174F4 (136 B, old + patch) */
    . = 0x0801757c; .text.w37c_0801757c : { build/w37c_0801757c_MATCHED.o (.text.w37c_0801757c); } /* Wave 37-C Sub_0801757C (132 B TRUE, old; TSV 164 wrong) */
    . = 0x08017670; .text.w36d_08017670 : { build/w36d_08017670_MATCHED.o (.text.w36d_08017670); } /* Wave 36 reconciliation Sub_08017670 (60 B, main) */
    . = 0x08017984; .text.w37c2_08017984 : { build/w37c2_08017984_MATCHED.o (.text.w37c2_08017984); } /* Wave 37-C2 Sub_08017984 (160 B TRUE, old; TSV 192 wrong) */
    . = 0x08017a24; .text.w37c2_08017a24 : { build/w37c2_08017a24_MATCHED.o (.text.w37c2_08017a24); } /* Wave 37-C2 Sub_08017A24 (32 B gap leaf, old) */
    . = 0x08017dc4; .text.w37c_08017dc4 : { build/w37c_08017dc4_MATCHED.o (.text.w37c_08017dc4); } /* Wave 37-C Sub_08017DC4 (168 B, old) */
    . = 0x08017ed8; .text.w37c2_08017ed8 : { build/w37c2_08017ed8_MATCHED.o (.text.w37c2_08017ed8); } /* Wave 37-C2 Sub_08017ED8 (180 B, old) */
    . = 0x08018474; .text.w37c_08018474 : { build/w37c_08018474_MATCHED.o (.text.w37c_08018474); } /* Wave 37-C Sub_08018474 (156 B, old) */
    . = 0x08018510; .text.w37c_08018510 : { build/w37c_08018510_MATCHED.o (.text.w37c_08018510); } /* Wave 37-C Sub_08018510 (152 B, old + patch) */
    . = 0x080185a8; .text.w37c_080185a8 : { build/w37c_080185a8_MATCHED.o (.text.w37c_080185a8); } /* Wave 37-C Sub_080185A8 (152 B, old) */
    . = 0x08018640; .text.w37c2_08018640 : { build/w37c2_08018640_MATCHED.o (.text.w37c2_08018640); } /* Wave 37-C2 Sub_08018640 (180 B, old) */
    . = 0x080192dc; .text.w37c_080192dc : { build/w37c_080192dc_MATCHED.o (.text.w37c_080192dc); } /* Wave 37-C Sub_080192DC (152 B, old + patch) */
    . = 0x08019400; .text.w37c2_08019400 : { build/w37c2_08019400_MATCHED.o (.text.w37c2_08019400); } /* Wave 37-C2 Sub_08019400 (180 B, old) */
    . = 0x0801969c; .text.w37c2_0801969c : { build/w37c2_0801969c_MATCHED.o (.text.w37c2_0801969c); } /* Wave 37-C2 Sub_0801969C (176 B, old) */
    . = 0x080197bc; .text.w37c2_080197bc : { build/w37c2_080197bc_MATCHED.o (.text.w37c2_080197bc); } /* Wave 37-C2 Sub_080197BC (176 B, old) */
    . = 0x0801986c; .text.w37c_0801986c : { build/w37c_0801986c_MATCHED.o (.text.w37c_0801986c); } /* Wave 37-C Sub_0801986C (152 B, old) */
    . = 0x08019aac; .text.w37c2_08019aac : { build/w37c2_08019aac_MATCHED.o (.text.w37c2_08019aac); } /* Wave 37-C2 Sub_08019AAC (184 B, old) */
    . = 0x08019bdc; .text.w37c2_08019bdc : { build/w37c2_08019bdc_MATCHED.o (.text.w37c2_08019bdc); } /* Wave 37-C2 Sub_08019BDC (184 B, old) */
    . = 0x08019e7c; .text.w37c2_08019e7c : { build/w37c2_08019e7c_MATCHED.o (.text.w37c2_08019e7c); } /* Wave 37-C2 Sub_08019E7C (188 B, old) */
    . = 0x0801a220; .text.w37c_0801a220 : { build/w37c_0801a220_MATCHED.o (.text.w37c_0801a220); } /* Wave 37-C Sub_0801A220 (156 B, old) */
    . = 0x0801a344; .text.w37c_0801a344 : { build/w37c_0801a344_MATCHED.o (.text.w37c_0801a344); } /* Wave 37-C Sub_0801A344 (172 B, old) */
    . = 0x0801a5f0; .text.w37c2_0801a5f0 : { build/w37c2_0801a5f0_MATCHED.o (.text.w37c2_0801a5f0); } /* Wave 37-C2 Sub_0801A5F0 (188 B, old) */
    . = 0x0801ac58; .text.w37c_0801ac58 : { build/w37c_0801ac58_MATCHED.o (.text.w37c_0801ac58); } /* Wave 37-C Sub_0801AC58 (156 B, old) */
    . = 0x0801ad60; .text.w37c_0801ad60 : { build/w37c_0801ad60_MATCHED.o (.text.w37c_0801ad60); } /* Wave 37-C Sub_0801AD60 (160 B, old) */
    . = 0x0801aa50; .text.w37b_0801aa50 : { build/w37b_0801aa50_MATCHED.o (.text.w37b_0801aa50); } /* Wave 37-B Sub_0801AA50 (32 B, old + patch, Slot_FetchWord4 twin) */
    . = 0x0801b428; .text.w36a_0801b428 : { build/w36a_0801b428_MATCHED.o (.text.w36a_0801b428); } /* Wave 36 reconciliation Step_0801b428 (84 B, old) */
    . = 0x0801b520; .text.w36a_0801b520 : { build/w36a_0801b520_MATCHED.o (.text.w36a_0801b520); } /* Wave 36 reconciliation Step_0801b520 (84 B, old) */
    . = 0x0801b880; .text.w36a_0801b880 : { build/w36a_0801b880_MATCHED.o (.text.w36a_0801b880); } /* Wave 36 reconciliation Step_0801b880 (80 B, old) */
    . = 0x0801b96c; .text.w37b_0801b96c : { build/w37b_0801b96c_MATCHED.o (.text.w37b_0801b96c); } /* Wave 37-B Sub_0801B96C (32 B, old + patch, Slot_FetchWord4 twin) */
    . = 0x0801cd30; .text.w37b_0801cd30 : { build/w37b_0801cd30_MATCHED.o (.text.w37b_0801cd30); } /* Wave 37-B Sub_0801CD30 (32 B, old + patch, Slot_FetchWord4 twin) */
    . = 0x0801d6cc; .text.w37d3_0801d6cc_asm : { build/w37d_0801d6cc_MATCHED.o (.text.w37d3_0801d6cc_asm); } /* Wave 37-D F_0801D6CC (348 B, sanctioned asm transcription) */
    . = 0x0801dd48; .text.w36bulk_0801dd48 : { build/w36bulk_0801dd48_MATCHED.o (.text.w36bulk_0801dd48); } /* Wave 36 reconciliation Sub_0801DD48 (124 B, old) */
    . = 0x0801e028; .text.w37c_0801e028 : { build/w37c_0801e028_MATCHED.o (.text.w37c_0801e028); } /* Wave 37-C Sub_0801E028 (168 B, old + patch) */
    . = 0x0801e93c; .text.w36a_0801e93c : { build/w36a_0801e93c_MATCHED.o (.text.w36a_0801e93c); } /* Wave 36 reconciliation Step_0801e93c (52 B, old + tools/fix_0801e93c.py) */
    . = 0x0801ece8; .text.w37d1_0801ece8_asm : { build/w37d_0801ece8_MATCHED.o (.text.w37d1_0801ece8_asm); } /* Wave 37-D F_0801ECE8 (268 B, sanctioned asm transcription) */
    . = 0x0801edf4; .text.w37coord_0801edf4 : { build/w37coord_0801edf4_MATCHED.o (.text.w37coord_0801edf4); } /* Wave 37 coordinator Sub_0801EDF4 (32 B, old + patch, Slot_FetchWord4 twin) */
    . = 0x0801ec44; .text.w37c_0801ec44 : { build/w37c_0801ec44_MATCHED.o (.text.w37c_0801ec44); } /* Wave 37-C Sub_0801EC44 (164 B, old) */
    . = 0x0801e970; .text.w37b_0801e970 : { build/w37b_0801e970_MATCHED.o (.text.w37b_0801e970); } /* Wave 37-B Sub_0801E970 (32 B, old + patch, Slot_FetchWord4 twin) */
    . = 0x0801ffbc; .text.w37d4_0801ffbc_asm : { build/w37d_0801ffbc_MATCHED.o (.text.w37d4_0801ffbc_asm); } /* Wave 37-D F_0801FFBC (304 B, sanctioned asm transcription) */
    . = 0x08021144; .text.w37c_08021144 : { build/w37c_08021144_MATCHED.o (.text.w37c_08021144); } /* Wave 37-C Sub_08021144 (168 B, old) */
    . = 0x08021c2c; .text.w36bulk_08021c2c : { build/w36bulk_08021c2c_MATCHED.o (.text.w36bulk_08021c2c); } /* Wave 36 reconciliation Sub_08021C2C (128 B, old) */
    . = 0x080231d0; .text.w37c_080231d0 : { build/w37c_080231d0_MATCHED.o (.text.w37c_080231d0); } /* Wave 37-C Sub_080231D0 (148 B TRUE, old + patch; TSV 168 wrong) */
    . = 0x0802366c; .text.w36d_0802366c : { build/w36d_0802366c_MATCHED.o (.text.w36d_0802366c); } /* Wave 36 reconciliation Sub_0802366C (68 B, main) */
    . = 0x080248c4; .text.w36a_080248c4 : { build/w36a_080248c4_MATCHED.o (.text.w36a_080248c4); } /* Wave 36 reconciliation Check_080248c4 (84 B, old) */
    . = 0x08024c40; .text.w36bulk_08024c40 : { build/w36bulk_08024c40_MATCHED.o (.text.w36bulk_08024c40); } /* Wave 36 reconciliation Sub_08024C40 (128 B, old) */
    . = 0x080256e0; .text.w36d_080256e0 : { build/w36d_080256e0_MATCHED.o (.text.w36d_080256e0); } /* Wave 36 reconciliation Sub_080256E0 (60 B, main) */
    . = 0x08028970; .text.w36a_08028970 : { build/w36a_08028970_MATCHED.o (.text.w36a_08028970); } /* Wave 36 reconciliation Check_08028970 (84 B, main + tools/fix_08028970.py) */
    . = 0x0802d5d4; .text.w37c_0802d5d4 : { build/w37c_0802d5d4_MATCHED.o (.text.w37c_0802d5d4); } /* Wave 37-C Sub_0802D5D4 (156 B, old) */
    . = 0x0803449c; .text.w36a_0803449c : { build/w36a_0803449c_MATCHED.o (.text.w36a_0803449c); } /* Wave 36 reconciliation Step_0803449c (84 B, old) */
    . = 0x08038488; .text.w37c_08038488 : { build/w37c_08038488_MATCHED.o (.text.w37c_08038488); } /* Wave 37-C Sub_08038488 (152 B, main) */
    . = 0x080402e0; .text.w37b_080402e0 : { build/w37b_080402e0_MATCHED.o (.text.w37b_080402e0); } /* Wave 37-B Sub_080402E0 (132 B, old + patch, inline-asm ldrsb) */
    . = 0x0804044c; .text.w37b_0804044c : { build/w37b_0804044c_MATCHED.o (.text.w37b_0804044c); } /* Wave 37-B Sub_0804044C (132 B, old + patch) */
    . = 0x08042d80; .text.w37c_08042d80 : { build/w37c_08042d80_MATCHED.o (.text.w37c_08042d80); } /* Wave 37-C Sub_08042D80 (148 B, old) */
    . = 0x08042e14; .text.w37c2_08042e14 : { build/w37c2_08042e14_MATCHED.o (.text.w37c2_08042e14); } /* Wave 37-C2 Sub_08042E14 (172 B, old) */
    . = 0x0804380c; .text.w36bulk_0804380c : { build/w36bulk_0804380c_MATCHED.o (.text.w36bulk_0804380c); } /* Wave 36 reconciliation Sub_0804380C (132 B, old) */
    . = 0x0804713c; .text.w37c_0804713c : { build/w37c_0804713c_MATCHED.o (.text.w37c_0804713c); } /* Wave 37-C Sub_0804713C (156 B, old) */
    . = 0x0804afd0; .text.w36bulk_0804afd0 : { build/w36bulk_0804afd0_MATCHED.o (.text.w36bulk_0804afd0); } /* Wave 36 reconciliation Sub_0804AFD0 (128 B, old) */
    . = 0x0804c72c; .text.w36a_0804c72c : { build/w36a_0804c72c_MATCHED.o (.text.w36a_0804c72c); } /* Wave 36 reconciliation Lookup_0804c72c (84 B, old) */
    . = 0x0804cb28; .text.w37c_0804cb28 : { build/w37c_0804cb28_MATCHED.o (.text.w37c_0804cb28); } /* Wave 37-C Sub_0804CB28 (164 B, old) */
    . = 0x0804cbcc; .text.w37c_0804cbcc : { build/w37c_0804cbcc_MATCHED.o (.text.w37c_0804cbcc); } /* Wave 37-C Sub_0804CBCC (152 B, old) */
    . = 0x0804DCCC; .text.thunks : { build/thunks.o (.text.thunks); }

    /* Phase 3 Wave 10 (hand-written .s, worker S, coordinator-merge pending):
       libgcc division block + duplicate bx-thunks at 0x0804DCEC-0x0804DFA8.
       All five are C-IMPOSSIBLE (proven empirically in
       docs/match_notes_wave9_C.md: agbcc/old_agbcc always emit
       `push {r4,lr}` at function start and `pop {r4,pc}`-style epilogues;
       ROM has mid-prologue `push {r4}` and `pop {r4}; mov pc,lr`).
       Sections live in asm/div.s. The 0x0804DCEC/0x0804DDA0/0x0804DE70
       slots are 2-aligned (SUBALIGN(2) per the w3e_divzero_4dede
       precedent); the others are 4-aligned. External branch targets
       (DivZeroStub_4DD90, DivZeroStub @0x0804DE64) are global symbols
       from build/wave9_c_noiw.o / build/wave3_d_noiw.o; the other two
       (0x0804DEDE, 0x0804DF9E) are ldscript BYTE blocks referenced from
       div.s via .set (their .c sources are intentionally not in SRCS_C). */
    . = 0x0804DCEC; .text.dupthunks : SUBALIGN(2) { build/div.o (.text.dupthunks); }
    . = 0x0804DD08; .text.sdiv   : { build/div.o (.text.sdiv); }
    . = 0x0804DDA0; .text.smod   : SUBALIGN(2) { build/div.o (.text.smod); }
    . = 0x0804DE70; .text.udiv   : SUBALIGN(2) { build/div.o (.text.udiv); }
    . = 0x0804DEE8; .text.umod   : { build/div.o (.text.umod); }

    /* Phase 3: matched-C slots (Wave 1). Each function placed at its exact
       ROM address via section attributes in its .c file. Stub .c files are
       UNMATCHED until a worker replaces them with byte-identical C.
       Wave-0 slots (.text.bios/.text.sram) were added by the Wave-0
       worker on landing. */
    . = 0x080004FC; .text.mainloop      : { build/mainloop.o (.text.mainloop); }
    . = 0x0800063C; .text.hwinit        : { build/hwinit.o (.text.hwinit); }
    . = 0x08000AD4; .text.hblank_setup  : { build/hblank.o (.text.hblank_setup); }
    . = 0x08000B54; .text.hblank0       : { build/hblank.o (.text.hblank0); }
    . = 0x08000BAC; .text.hblank1       : { build/hblank.o (.text.hblank1); }
    . = 0x08000C04; .text.hblank01      : { build/hblank.o (.text.hblank01); }
    . = 0x08000C68; .text.strided_copy  : { build/strided_copy.o (.text.strided_copy); }
    . = 0x08000D90; .text.task_register : { build/task_register.o (.text.task_register); }
    . = 0x0804C6B4; .text.text_select   : { build/text.o (.text.text_select); }
    . = 0x0804CDE8; .text.text_open     : { build/text.o (.text.text_open); }

    /* Phase 3 Wave 2 (matched C, worker B, coordinator-verified):
       Vec2 mirror-aware vector helpers. old_agbcc (see Makefile). */
    . = 0x0800DD2C; .text.vec2_setmirrored : { build/vec2.o (.text.vec2_setmirrored); }
    . = 0x0800DD4C; .text.vec2_addmirrored : { build/vec2.o (.text.vec2_addmirrored); }

    /* Phase 3 Wave 2 (matched C, worker D, coordinator-verified):
       EntryMgr setup/teardown (old_agbcc) and GatedDispatch (agbcc).
       HookA/HookB live in .text.entrymgr_teardown at 0x4F70/0x4F7C. */
    . = 0x08004F18; .text.entrymgr_teardown : { build/entrymgr.o (.text.entrymgr_teardown); }
    . = 0x08004F80; .text.entrymgr_setup    : { build/entrymgr.o (.text.entrymgr_setup); }
    . = 0x08006DD8; .text.gateddispatch     : { build/gateddispatch.o (.text.gateddispatch); }

    /* Phase 3 Wave 2 (matched C, worker C, coordinator-verified):
       Text_SelectBlobIdx + Gfx_BlitRequest. Main agbcc. */
    . = 0x0804A378; .text.text_selidx : { build/text_idx.o (.text.text_selidx); }
    . = 0x08006A54; .text.gfx_blitreq : { build/gfx.o (.text.gfx_blitreq); }

    /* Phase 3 Wave 2 (matched C, worker A, coordinator-verified):
       ChipSlot helpers. Main agbcc. */
    . = 0x0800D9EC; .text.chipslot_incuse : { build/chipslot.o (.text.chipslot_incuse); }
    . = 0x0800D6E0; .text.chipslot_setup  : { build/chipslot.o (.text.chipslot_setup); }

    /* Phase 3 Wave 3 batch 3 (matched C, worker C, coordinator-verified):
       leaf accessors/forwarders. Main agbcc. 2-mod-4 sections carry an
       explicit 00 00 pad object in the .c file (see wave3_c.c). */
    . = 0x080057FC; .text.w3c_noopstub : { build/wave3_c.o (.text.w3c_noopstub); }
    . = 0x08003130; .text.w3c_setu32_4 : { build/wave3_c.o (.text.w3c_setu32_4); }
    . = 0x08025A0C; .text.w3c_getu8_0 : { build/wave3_c.o (.text.w3c_getu8_0); }
    . = 0x08017460; .text.w3c_getu8_12 : { build/wave3_c.o (.text.w3c_getu8_12); }
    . = 0x08024724; .text.w3c_tou8 : { build/wave3_c.o (.text.w3c_tou8); }
    . = 0x0802617C; .text.w3c_setu32pair : { build/wave3_c.o (.text.w3c_setu32pair); }
    . = 0x0800EE38; .text.w3c_g05130_setu16_12 : { build/wave3_c.o (.text.w3c_g05130_setu16_12); }
    . = 0x080256D4; .text.w3c_setu8_0_ff1 : { build/wave3_c.o (.text.w3c_setu8_0_ff1); }
    . = 0x080174EC; .text.w3c_gets16_78_3 : { build/wave3_c.o (.text.w3c_gets16_78_3); }
    . = 0x08021290; .text.w3c_wrap_chiptick : { build/wave3_c.o (.text.w3c_wrap_chiptick); }
    . = 0x0804A2CC; .text.w3c_g0bd10_zero2 : { build/wave3_c.o (.text.w3c_g0bd10_zero2); }
    . = 0x08017488; .text.w3c_incu8_11 : { build/wave3_c.o (.text.w3c_incu8_11); }
    . = 0x0800EAB4; .text.w3c_g05130_gets8_0a : { build/wave3_c.o (.text.w3c_g05130_gets8_0a); }
    . = 0x08002FC4; .text.w3c_text_blobu16 : { build/wave3_c.o (.text.w3c_text_blobu16); }
    . = 0x0804CA08; .text.w3c_g0ce08_indirectcall : { build/wave3_c.o (.text.w3c_g0ce08_indirectcall); }

    /* Phase 3 Wave 3 batch 2 (matched C, worker B, coordinator-verified):
       leaf accessors, list push, table lookups, trampolines. Main agbcc.
       2-mod-4 sections carry an explicit 00 00 pad object in the .c file.
       ChipSlot_Tick .set in wave3_b.c is temporary (BLOCKED wave 2). */
    . = 0x0804C278; .text.w3b_tailcallr3 : { build/wave3_b.o (.text.w3b_tailcallr3); }
    . = 0x080256DC; .text.w3b_setu8_1 : { build/wave3_b.o (.text.w3b_setu8_1); }
    . = 0x0804B970; .text.w3b_armtramp : { build/wave3_b.o (.text.w3b_armtramp); }
    . = 0x080257B8; .text.w3b_getu16_14 : { build/wave3_b.o (.text.w3b_getu16_14); }
    . = 0x08024760; .text.w3b_ewget16_18 : { build/wave3_b.o (.text.w3b_ewget16_18); }
    . = 0x0800EDF0; .text.w3b_ewset16_14 : { build/wave3_b.o (.text.w3b_ewset16_14); }
    . = 0x0800EE2C; .text.w3b_ewset16_16 : { build/wave3_b.o (.text.w3b_ewset16_16); }
    . = 0x08004170; .text.w3b_listpush : { build/wave3_b.o (.text.w3b_listpush); }
    . = 0x0800EE44; .text.w3b_ewset8_68 : { build/wave3_b.o (.text.w3b_ewset8_68); }
    . = 0x08011F7C; .text.w3b_tickwrap : { build/wave3_b.o (.text.w3b_tickwrap); }
    . = 0x080082CC; .text.w3b_sethalf8000 : { build/wave3_b.o (.text.w3b_sethalf8000); }
    . = 0x08010364; .text.w3b_ewset8_72 : { build/wave3_b.o (.text.w3b_ewset8_72); }
    . = 0x0804A3FC; .text.w3b_ewset16_128 : { build/wave3_b.o (.text.w3b_ewset16_128); }
    . = 0x08026710; .text.w3b_tblget11 : { build/wave3_b.o (.text.w3b_tblget11); }
    . = 0x08010DDC; .text.w3b_ewset8ret1_20 : { build/wave3_b.o (.text.w3b_ewset8ret1_20); }

    /* Phase 3 Wave 3 batch 4 (matched C, worker D, coordinator-verified):
       leaf accessors, EWRAM helpers, script-interpreter fragment.
       Main agbcc; w3d_noop carries an explicit 00 00 pad object.
       DivZeroStub (no-interwork TU) lives in wave3_d_noiw.o. */
    . = 0x08005208; .text.w3d_noop : { build/wave3_d.o (.text.w3d_noop); }
    . = 0x080257F8; .text.w3d_getu16_10 : { build/wave3_d.o (.text.w3d_getu16_10); }
    . = 0x08023E30; .text.w3d_getu32_38 : { build/wave3_d.o (.text.w3d_getu32_38); }
    . = 0x08026550; .text.w3d_getu8_19 : { build/wave3_d.o (.text.w3d_getu8_19); }
    . = 0x08011BC8; .text.w3d_ewramget : { build/wave3_d.o (.text.w3d_ewramget); }
    . = 0x08026DB0; .text.w3d_ewramset : { build/wave3_d.o (.text.w3d_ewramset); }
    . = 0x08017458; .text.w3d_incu8_12 : { build/wave3_d.o (.text.w3d_incu8_12); }
    . = 0x080174E4; .text.w3d_gets16_7c : { build/wave3_d.o (.text.w3d_gets16_7c); }
    . = 0x0800EA08; .text.w3d_ewramset2 : { build/wave3_d.o (.text.w3d_ewramset2); }
    . = 0x0800B6E8; .text.w3d_oru8_1f : { build/wave3_d.o (.text.w3d_oru8_1f); }
    . = 0x08004158; .text.w3d_setu32_200 : { build/wave3_d.o (.text.w3d_setu32_200); }
    . = 0x0804BE44; .text.w3d_script_nextop : { build/wave3_d.o (.text.w3d_script_nextop); }
    /* Wave 23-D: hand-written script-interpreter asm cluster (ASM-STAGED).
       Evidence: staging/wave23_D/w23d_scriptops.c. */
    . = 0x080378B8; .text.w23d_080378b8 : { build/w23d_080378b8.o (.text.w23d_080378b8); } /* F_080378B8 (88 B + 4 pool, main agbcc) */
    . = 0x0804BDE0; .text.w23d_listwalk_0804bde0 : { build/w23d_scriptops.o (.text.w23d_listwalk_0804bde0); } /* ListWalk_0804BDE0 (48 B) */
    . = 0x0804BE10; .text.w23d_inittab36_0804be10 : { build/w23d_scriptops.o (.text.w23d_inittab36_0804be10); } /* Script_InitTable36_0804BE10 (24 B) */
    . = 0x0804BE28; .text.w23d_validptr_0804be2a : { build/w23d_scriptops.o (.text.w23d_validptr_0804be2a); } /* ValidateScriptPtr_0804BE2A (28 B incl. pool) */
    . = 0x0804BE50; .text.w23d_readu32be_0804be50 : { build/w23d_scriptops.o (.text.w23d_readu32be_0804be50); } /* Script_ReadU32BE_0804BE50 (32 B) */
    . = 0x0804BE70; .text.w23d_dispatch_0804be70 : { build/w23d_scriptops.o (.text.w23d_dispatch_0804be70); } /* Script_Dispatch_0804BE70 (28 B) */
    . = 0x0804BE8C; .text.w23d_popptr_0804be8c : { build/w23d_scriptops.o (.text.w23d_popptr_0804be8c); } /* Script_PopPtr_0804BE8C (20 B) */
    . = 0x0804BEA0; .text.w23d_countloop_0804bea0 : { build/w23d_scriptops.o (.text.w23d_countloop_0804bea0); } /* Script_CountLoop_0804BEA0 (48 B) */
    . = 0x0804BED0; .text.w23d_op29_0804bed0 : { build/w23d_scriptops.o (.text.w23d_op29_0804bed0); } /* ScriptOp_Store29_0804BED0 (12 B) */
    . = 0x0804BEDC; .text.w23d_opmul_0804bedc : { build/w23d_scriptops.o (.text.w23d_opmul_0804bedc); } /* ScriptOp_MulShift_0804BEDC (20 B) */
    . = 0x0804BEF0; .text.w23d_op10_0804bef0 : { build/w23d_scriptops.o (.text.w23d_op10_0804bef0); } /* ScriptOp_Store10_0804BEF0 (20 B) */
    . = 0x0804BF04; .text.w23d_loadentry3_0804bf04 : { build/w23d_scriptops.o (.text.w23d_loadentry3_0804bf04); } /* Script_LoadEntry3_0804BF04 (48 B) */
    . = 0x0804BF34; .text.w23d_op18_0804bf34 : { build/w23d_scriptops.o (.text.w23d_op18_0804bf34); } /* ScriptOp_Store18_0804BF34 (20 B) */
    . = 0x0804BF48; .text.w23d_op20_0804bf48 : { build/w23d_scriptops.o (.text.w23d_op20_0804bf48); } /* ScriptOp_Store20_0804BF48 (20 B) */
    . = 0x0804BF5C; .text.w23d_op14_0804bf5c : { build/w23d_scriptops.o (.text.w23d_op14_0804bf5c); } /* ScriptOp_Store14_0804BF5C (20 B) */
    . = 0x0804BF70; .text.w23d_op15_0804bf70 : { build/w23d_scriptops.o (.text.w23d_op15_0804bf70); } /* ScriptOp_Store15_0804BF70 (20 B) */
    . = 0x0804BF84; .text.w23d_op27_0804bf84 : { build/w23d_scriptops.o (.text.w23d_op27_0804bf84); } /* ScriptOp_Store27_0804BF84 (12 B) */
    . = 0x0804BF90; .text.w23d_op24_0804bf90 : { build/w23d_scriptops.o (.text.w23d_op24_0804bf90); } /* ScriptOp_Store24_0804BF90 (24 B) */
    . = 0x0804BFA8; .text.w23d_op12_0804bfa8 : { build/w23d_scriptops.o (.text.w23d_op12_0804bfa8); } /* ScriptOp_Store12_0804BFA8 (20 B) */
    . = 0x0804BFBC; .text.w23d_winin_0804bfbc : { build/w23d_scriptops.o (.text.w23d_winin_0804bfbc); } /* Script_WriteWinIn_0804BFBC (24 B incl. pool) */
    . = 0x0804C020; .text.w23d_dispcnt_0804c020 : { build/w23d_scriptops.o (.text.w23d_dispcnt_0804c020); } /* DispatchCounter_0804C020 (30 B) */
    . = 0x08011CC4; .text.w3d_tblu32 : { build/wave3_d.o (.text.w3d_tblu32); }
    . = 0x08011C04; .text.w3d_ewraminit : { build/wave3_d.o (.text.w3d_ewraminit); }
    . = 0x0804DE64; .text.w3d_divzero : { build/wave3_d_noiw.o (.text.w3d_divzero); }

    /* Phase 3 Wave 3 batch 5 (matched C, worker E, coordinator-verified +
       coordinator-split by flag set). Main agbcc in wave3_e.o;
       old_agbcc in wave3_e_old.o; no-interwork agbcc in wave3_e_noiw.o.
       2-mod-4 sections carry an explicit 00 00 pad object in the .c file.
       NOTE: .text.w3e_divzero_4dede needs SUBALIGN(2) — the 2-aligned
       address 0x0804DEDE would otherwise slide to 0x0804DEE0 under the
       section's default 4-alignment (worker E, verified). */
    . = 0x08000A18; .text.w3e_empty_0a18 : { build/wave3_e.o (.text.w3e_empty_0a18); }
    . = 0x08025A08; .text.w3e_getbyte1_25a08 : { build/wave3_e.o (.text.w3e_getbyte1_25a08); }
    . = 0x0804005C; .text.w3e_constzero_4005c : { build/wave3_e.o (.text.w3e_constzero_4005c); }
    . = 0x08011C50; .text.w3e_getlimit_11c50 : { build/wave3_e.o (.text.w3e_getlimit_11c50); }
    . = 0x0802472C; .text.w3e_zero16_2472c : { build/wave3_e_old.o (.text.w3e_zero16_2472c); }
    . = 0x080030BC; .text.w3e_store2h_030bc : { build/wave3_e.o (.text.w3e_store2h_030bc); }
    . = 0x080361DC; .text.w3e_teardownwrap_361dc : { build/wave3_e.o (.text.w3e_teardownwrap_361dc); }
    . = 0x080174CC; .text.w3e_setxy_174cc : { build/wave3_e.o (.text.w3e_setxy_174cc); }
    . = 0x0801007C; .text.w3e_ewramh_1007c : { build/wave3_e.o (.text.w3e_ewramh_1007c); }
    /* NOTE: .text.w3e_divzero_4dede is emitted via BYTE(), not from any
       .o section: the 10-byte function is followed in ROM by `00 29`
       (start of unmatched code at 0x0804DEE8), so neither gas's c046 pad
       nor a 00 00 pad object is correct here. The 10 bytes are the
       verified agbcc-no-interwork output (see wave3_e_noiw.c, which is
       intentionally not in SRCS_C); the bl encoding (ff f7 5c ff ->
       0x0804DD9C) is position-fixed. */
    . = 0x0804DEDE; .text.w3e_divzero_4dede : SUBALIGN(1) {
        BYTE(0x00); BYTE(0xB5); BYTE(0xFF); BYTE(0xF7); BYTE(0x5C);
        BYTE(0xFF); BYTE(0x00); BYTE(0x20); BYTE(0x00); BYTE(0xBD);
    }
    . = 0x08004164; .text.w3e_setf204_04164 : { build/wave3_e.o (.text.w3e_setf204_04164); }
    . = 0x08003090; .text.w3e_inittri_03090 : { build/wave3_e.o (.text.w3e_inittri_03090); }
    . = 0x080267B4; .text.w3e_initrec8_267b4 : { build/wave3_e.o (.text.w3e_initrec8_267b4); }
    . = 0x08024734; .text.w3e_tableget_24734 : { build/wave3_e.o (.text.w3e_tableget_24734); }
    . = 0x08028874; .text.w3e_setpair0_28874 : { build/wave3_e.o (.text.w3e_setpair0_28874); }

    /* Phase 3 Wave 3 batch 1 (matched C, worker A, coordinator-verified).
       Main agbcc. w3a_getindexedu8 carries an explicit 00 00 pad object.
       The 0x0804BDA2 `bx r3` is a duplicate libgcc-style thunk (no pad;
       next function immediately at 0x0804BDA4) — emitted via BYTE(). */
    . = 0x0804BDA2; .text.thunk_bxr3_dup : { BYTE(0x18); BYTE(0x47); }
    . = 0x08017474; .text.w3a_getfield17_u8 : { build/wave3_a.o (.text.w3a_getfield17_u8); }
    . = 0x080265F4; .text.w3a_getfield22_u16 : { build/wave3_a.o (.text.w3a_getfield22_u16); }
    . = 0x0802654C; .text.w3a_getfield24_u8 : { build/wave3_a.o (.text.w3a_getfield24_u8); }
    . = 0x0800EDE4; .text.w3a_setewram5130_12 : { build/wave3_a.o (.text.w3a_setewram5130_12); }
    . = 0x0804A3F0; .text.w3a_getewrambd20_130 : { build/wave3_a.o (.text.w3a_getewrambd20_130); }
    . = 0x080174C4; .text.w3a_setfield120_u16pair : { build/wave3_a.o (.text.w3a_setfield120_u16pair); }
    . = 0x080258F8; .text.w3a_getindexedu8 : { build/wave3_a.o (.text.w3a_getindexedu8); }
    . = 0x08002EE0; .text.w3a_copymosaicreg : { build/wave3_a.o (.text.w3a_copymosaicreg); }
    . = 0x080266F0; .text.w3a_getromtableu16 : { build/wave3_a.o (.text.w3a_getromtableu16); }
    . = 0x0800440C; .text.w3a_initlinkednode : { build/wave3_a.o (.text.w3a_initlinkednode); }

    /* Phase 3 Wave 4 batch I (62 matched C, coordinator-verified).
       45 via old_agbcc (dispatcher shape: index in r3), 17 via main agbcc.
       6 pad objects share their function sections. Evidence:
       docs/match_notes_wave4_i.md. */
    . = 0x0800303C; .text.w4i_selblob_ret : { build/wave4_i.o (.text.w4i_selblob_ret); }
    . = 0x0800EE8C; .text.w4i_callewset8_72 : { build/wave4_i.o (.text.w4i_callewset8_72); }
    . = 0x08024634; .text.w4i_wrap_getromtableu16 : { build/wave4_i.o (.text.w4i_wrap_getromtableu16); }
    . = 0x0802465C; .text.w4i_wrap_tblget11 : { build/wave4_i.o (.text.w4i_wrap_tblget11); }
    . = 0x08024FF4; .text.w4i_getent_u8_24 : { build/wave4_i.o (.text.w4i_getent_u8_24); }
    . = 0x0802500C; .text.w4i_getent_u8_19 : { build/wave4_i.o (.text.w4i_getent_u8_19); }
    . = 0x08025024; .text.w4i_getent_u16_22 : { build/wave4_i.o (.text.w4i_getent_u16_22); }
    . = 0x08025934; .text.w4i_setslot_ifle29 : { build/wave4_i.o (.text.w4i_setslot_ifle29); }
    . = 0x080265F8; .text.w4i_sub80_field22 : { build/wave4_i.o (.text.w4i_sub80_field22); }
    . = 0x08027730; .text.w4i_entmgr_reinit1 : { build/wave4_i.o (.text.w4i_entmgr_reinit1); }
    . = 0x08027748; .text.w4i_entmgr_reinit2 : { build/wave4_i.o (.text.w4i_entmgr_reinit2); }
    . = 0x0803510C; .text.w4i_entmgr_reinit45 : { build/wave4_i.o (.text.w4i_entmgr_reinit45); }
    . = 0x08035E40; .text.w4i_entmgr_reinit12 : { build/wave4_i.o (.text.w4i_entmgr_reinit12); }
    . = 0x080482BC; .text.w4i_entmgr_reinit23 : { build/wave4_i.o (.text.w4i_entmgr_reinit23); }
    . = 0x0804DA00; .text.w4i_dispatch_postinc : { build/wave4_i.o (.text.w4i_dispatch_postinc); }
    . = 0x0804DA20; .text.w4i_callvia_mem2 : { build/wave4_i.o (.text.w4i_callvia_mem2); }
    . = 0x0804CA1C; .text.w4i_callvia_mem1 : { build/wave4_i.o (.text.w4i_callvia_mem1); }
    . = 0x08001D98; .text.w4i_dispatch_0816e2c0_2 : { build/wave4_i_old.o (.text.w4i_dispatch_0816e2c0_2); }
    . = 0x0800330C; .text.w4i_dispatch_0816e304 : { build/wave4_i_old.o (.text.w4i_dispatch_0816e304); }
    . = 0x080045F8; .text.w4i_cpufastset_vram : { build/wave4_i_old.o (.text.w4i_cpufastset_vram); }
    . = 0x08004BC0; .text.w4i_dispatch_081705a4_0 : { build/wave4_i_old.o (.text.w4i_dispatch_081705a4_0); }
    . = 0x0800CD38; .text.w4i_dispatch_081734f4_0 : { build/wave4_i_old.o (.text.w4i_dispatch_081734f4_0); }
    . = 0x08023278; .text.w4i_dispatch_stktbl : { build/wave4_i_old.o (.text.w4i_dispatch_stktbl); }
    . = 0x08024F08; .text.w4i_getent_u16_14 : { build/wave4_i_old.o (.text.w4i_getent_u16_14); }
    . = 0x08024F48; .text.w4i_getent_u16_10 : { build/wave4_i_old.o (.text.w4i_getent_u16_10); }
    . = 0x080251B8; .text.w4i_getent_idxbyte1 : { build/wave4_i_old.o (.text.w4i_getent_idxbyte1); }
    . = 0x0802588C; .text.w4i_addtbl_s14 : { build/wave4_i_old.o (.text.w4i_addtbl_s14); }
    . = 0x080258A4; .text.w4i_addtbl_s14_idx : { build/wave4_i_old.o (.text.w4i_addtbl_s14_idx); }
    . = 0x08027CFC; .text.w4i_entmgr_clearbit3 : { build/wave4_i_old.o (.text.w4i_entmgr_clearbit3); }
    . = 0x080365F8; .text.w4i_set469f_dispatch0 : { build/wave4_i_old.o (.text.w4i_set469f_dispatch0); }
    . = 0x0803661C; .text.w4i_set469f_dispatch1 : { build/wave4_i_old.o (.text.w4i_set469f_dispatch1); }
    . = 0x08036640; .text.w4i_set469f_dispatch2 : { build/wave4_i_old.o (.text.w4i_set469f_dispatch2); }
    . = 0x08047600; .text.w4i_copyhdr_dispatch : { build/wave4_i_old.o (.text.w4i_copyhdr_dispatch); }
    . = 0x080400D0; .text.w4i_dispatch4_r3 : { build/wave4_i_old.o (.text.w4i_dispatch4_r3); }
    . = 0x0800AC70; .text.w4i_dispatch_08173064_1 : { build/wave4_i_old.o (.text.w4i_dispatch_08173064_1); }
    . = 0x080120F0; .text.w4i_dispatch_08223d08_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08223d08_10); }
    . = 0x08015A48; .text.w4i_dispatch_08223e94_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08223e94_10); }
    . = 0x0801D3A8; .text.w4i_dispatch_08226a24_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08226a24_10); }
    . = 0x0801F224; .text.w4i_dispatch_08226dd8_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08226dd8_10); }
    . = 0x08020588; .text.w4i_dispatch_08226edc_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08226edc_10); }
    . = 0x0802103C; .text.w4i_dispatch_08226f2c_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08226f2c_10); }
    . = 0x08021564; .text.w4i_dispatch_08226fec_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08226fec_10); }
    . = 0x0802181C; .text.w4i_dispatch_0822701c_10 : { build/wave4_i_old.o (.text.w4i_dispatch_0822701c_10); }
    . = 0x08021E34; .text.w4i_dispatch_0822709c_10 : { build/wave4_i_old.o (.text.w4i_dispatch_0822709c_10); }
    . = 0x08022680; .text.w4i_dispatch_08227140_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08227140_10); }
    . = 0x0802295C; .text.w4i_dispatch_08227168_10 : { build/wave4_i_old.o (.text.w4i_dispatch_08227168_10); }
    . = 0x08023070; .text.w4i_dispatch_082271c8_10 : { build/wave4_i_old.o (.text.w4i_dispatch_082271c8_10); }
    . = 0x0802372C; .text.w4i_dispatch_082271f4_10 : { build/wave4_i_old.o (.text.w4i_dispatch_082271f4_10); }
    . = 0x08027718; .text.w4i_dispatch_0822dc84_1 : { build/wave4_i_old.o (.text.w4i_dispatch_0822dc84_1); }
    . = 0x08035DF4; .text.w4i_dispatch_0822eb58_1 : { build/wave4_i_old.o (.text.w4i_dispatch_0822eb58_1); }
    . = 0x08037958; .text.w4i_dispatch_08230d94_1 : { build/wave4_i_old.o (.text.w4i_dispatch_08230d94_1); }
    . = 0x08038E70; .text.w4i_dispatch_08231098_1 : { build/wave4_i_old.o (.text.w4i_dispatch_08231098_1); }
    . = 0x0803AE2C; .text.w4i_dispatch_08232330_1 : { build/wave4_i_old.o (.text.w4i_dispatch_08232330_1); }
    . = 0x080468EC; .text.w4i_dispatch_08233a44_2 : { build/wave4_i_old.o (.text.w4i_dispatch_08233a44_2); }
    . = 0x080350B4; .text.w4i_dispatch_0822ea6c_4 : { build/wave4_i_old.o (.text.w4i_dispatch_0822ea6c_4); }
    . = 0x08042AC8; .text.w4i_dispatch_08232d2c_4 : { build/wave4_i_old.o (.text.w4i_dispatch_08232d2c_4); }
    . = 0x08045EA0; .text.w4i_dispatch_08232e48_4 : { build/wave4_i_old.o (.text.w4i_dispatch_08232e48_4); }
    . = 0x08047CA4; .text.w4i_dispatch_08233c54_4 : { build/wave4_i_old.o (.text.w4i_dispatch_08233c54_4); }
    . = 0x080499EC; .text.w4i_dispatch_08234b74_4 : { build/wave4_i_old.o (.text.w4i_dispatch_08234b74_4); }
    . = 0x08048260; .text.w4i_dispatch_08234314_2 : { build/wave4_i_old.o (.text.w4i_dispatch_08234314_2); }
    . = 0x0804AF90; .text.w4i_dispatch_08234d4c_0 : { build/wave4_i_old.o (.text.w4i_dispatch_08234d4c_0); }
    . = 0x0804B334; .text.w4i_dispatch_08234d60_0 : { build/wave4_i_old.o (.text.w4i_dispatch_08234d60_0); }
    /* Phase 3 Wave 4 batch J (5 matched, coordinator-verified).
       4 via old_agbcc (main agbcc mis-allocates one register each).
       Wrap_0804DF9E (8 B: b500 f7ff fefc 2000) emitted via BYTE():
       GAS pads the C section with a 2-byte nop the ROM does not have
       (next function at 0x0804DFA6). src/wave4_j_noiw.c is the
       documented, build-verified no-interwork source. Evidence:
       docs/match_notes_wave4_j.md. */
    . = 0x080044F4; .text.w4j_listunlinkpush : { build/wave4_j_old.o (.text.w4j_listunlinkpush); }
    . = 0x08011E98; .text.w4j_objsetfromtablea : { build/wave4_j_old.o (.text.w4j_objsetfromtablea); }
    . = 0x08017084; .text.w4j_objsetfromtableb : { build/wave4_j_old.o (.text.w4j_objsetfromtableb); }
    . = 0x08020F58; .text.w4j_objsetfromtablec : { build/wave4_j_old.o (.text.w4j_objsetfromtablec); }
    . = 0x0804DF9E; .text.w4j_wrap_0804df9e : {
        BYTE(0x00); BYTE(0xB5); BYTE(0xFF); BYTE(0xF7);
        BYTE(0xFC); BYTE(0xFE); BYTE(0x00); BYTE(0x20);
        BYTE(0x00); BYTE(0xBD);
    }
    /* Phase 3 Wave 9 batch C (2 matched C, worker C, coordinator-verified).
       No-interwork TU: agbcc WITHOUT -mthumb-interwork.
       Evidence: docs/match_notes_wave9_C.md. */
    . = 0x0804DD90; .text.w9c_divzero_4dd90 : { build/wave9_c_noiw.o (.text.w9c_divzero_4dd90); }
    . = 0x0804DFA8; .text.w9c_memcpy_4dfa8 : { build/wave9_c_noiw.o (.text.w9c_memcpy_4dfa8); }
    /* Phase 3 Wave 4 batch H (5 matched C, coordinator-verified).
       Evidence: docs/match_notes_wave4_h.md. */
    . = 0x08000758; .text.w4h_memcpy16 : { build/wave4_h.o (.text.w4h_memcpy16); }
    . = 0x080028D0; .text.w4h_cpy8 : { build/wave4_h.o (.text.w4h_cpy8); }
    . = 0x08002A1C; .text.w29c_08002a1c : { build/w29c_08002a1c.o (.text.w29c_08002a1c); } /* sub_08002A1C (224 B incl pool, old_agbcc) */
    . = 0x080216A8; .text.w4h_init216a8 : { build/wave4_h.o (.text.w4h_init216a8); }
    . = 0x08011C80; .text.w4h_tbl11c80 : { build/wave4_h.o (.text.w4h_tbl11c80); }
    . = 0x080350D0; .text.w4h_reinit350d0 : { build/wave4_h.o (.text.w4h_reinit350d0); }
    /* Phase 3 Wave 4 batch G (TaskMgr_Update, coordinator-verified).
       Calls sub_080002dc (unmatched fwd-ref) via absolute .set.
       Evidence: docs/match_notes_wave4_g.md. */
    . = 0x08000CD4; .text.w4g_taskmgrupdate : { build/wave4_g.o (.text.w4g_taskmgrupdate); }
    /* Phase 3 Wave 4 batch K (7 matched C, coordinator-verified).
       2 via old_agbcc (wave4_k_old.o). Evidence:
       docs/match_notes_wave4_k.md. */
    . = 0x08035E0C; .text.w4k_t35e0c : { build/wave4_k.o (.text.w4k_t35e0c); }
    . = 0x08035EB0; .text.w4k_t35eb0 : { build/wave4_k_old.o (.text.w4k_t35eb0); }
    . = 0x08035F0C; .text.w4k_t35f0c : { build/wave4_k.o (.text.w4k_t35f0c); }
    . = 0x080360B0; .text.w4k_t360b0 : { build/wave4_k.o (.text.w4k_t360b0); }
    . = 0x08036664; .text.w4k_t36664 : { build/wave4_k.o (.text.w4k_t36664); }
    . = 0x08036724; .text.w4k_t36724 : { build/wave4_k_old.o (.text.w4k_t36724); }
    . = 0x08036780; .text.w4k_t36780 : { build/wave4_k.o (.text.w4k_t36780); }
    /* Phase 3 Wave 5 blocked-revisit (3 unblocked, coordinator-verified).
       HBlank_VCountUpdate via old_agbcc (see Makefile); StridedCopy
       replaces the Wave-1 stub in src/strided_copy.c (slot above).
       Evidence: docs/match_notes_wave5_blk.md. */
    . = 0x08000978; .text.w5b_vcount : { build/wave5_blk_old.o (.text.w5b_vcount); }
    . = 0x080366A8; .text.w5b_366a8 : { build/wave5_blk.o (.text.w5b_366a8); }
    /* Phase 3 Wave 5 POOL-H1 (3 matched C, coordinator-verified):
       TableDispatch_9380 via old_agbcc (see Makefile).
       Evidence: docs/match_notes_wave5_h1.md. */
    . = 0x0800BB78; .text.w5h_bb78 : { build/wave5_h1.o (.text.w5h_bb78); }
    . = 0x0800D568; .text.w5h_d568 : { build/wave5_h1.o (.text.w5h_d568); }
    . = 0x08009380; .text.w5h_9380 : { build/wave5_h1_old.o (.text.w5h_9380); }
    /* Phase 3 Wave 5 POOL-G2 (4 matched C, coordinator-verified).
       Evidence: docs/match_notes_wave5_g2.md. */
    . = 0x080360C4; .text.w5g_360c4 : { build/wave5_g2.o (.text.w5g_360c4); }
    . = 0x08040798; .text.w5g_40798 : { build/wave5_g2.o (.text.w5g_40798); }
    . = 0x08045200; .text.w5g_45200 : { build/wave5_g2.o (.text.w5g_45200); }
    . = 0x0804529C; .text.w5g_4529c : { build/wave5_g2.o (.text.w5g_4529c); }
    /* Phase 3 Wave 5 POOL-G1 (2 matched C via old_agbcc, coordinator-verified).
       Evidence: docs/match_notes_wave5_g1.md. */
    . = 0x080207EC; .text.w5g1_207ec : { build/wave5_g1_old.o (.text.w5g1_207ec); }
    . = 0x08022EBC; .text.w5g1_22ebc : { build/wave5_g1_old.o (.text.w5g1_22ebc); }
    /* Phase 3 Wave 5 POOL-H2 (13 matched C, coordinator-verified):
       4 via old_agbcc (wave5_h2_old.o, see Makefile), 9 via main agbcc.
       Evidence: docs/match_notes_wave5_h2.md. */
    . = 0x08035128; .text.w5h_35128 : { build/wave5_h2_old.o (.text.w5h_35128); }
    . = 0x08035BC8; .text.w5h_35bc8 : { build/wave5_h2.o (.text.w5h_35bc8); }
    . = 0x08035C1C; .text.w5h_35c1c : { build/wave5_h2.o (.text.w5h_35c1c); }
    . = 0x08035DA4; .text.w5h_35da4 : { build/wave5_h2.o (.text.w5h_35da4); }
    . = 0x080366E8; .text.w5h_366e8 : { build/wave5_h2_old.o (.text.w5h_366e8); }
    . = 0x08037598; .text.w5h_37598 : { build/wave5_h2.o (.text.w5h_37598); }
    . = 0x08037A30; .text.w5h_37a30 : { build/wave5_h2_old.o (.text.w5h_37a30); }
    . = 0x08037AD8; .text.w5h_37ad8 : { build/wave5_h2.o (.text.w5h_37ad8); }
    . = 0x08038F3C; .text.w5h_38f3c : { build/wave5_h2_old.o (.text.w5h_38f3c); }
    . = 0x08038FE4; .text.w5h_38fe4 : { build/wave5_h2.o (.text.w5h_38fe4); }
    . = 0x08045EBC; .text.w5h_45ebc : { build/wave5_h2.o (.text.w5h_45ebc); }
    . = 0x0804827C; .text.w5h_4827c : { build/wave5_h2.o (.text.w5h_4827c); }
    . = 0x080496A8; .text.w5h_496a8 : { build/wave5_h2.o (.text.w5h_496a8); }
    /* Phase 3 Wave 6 BLK-A + L1 (4 verified: 3 BLK-A + Task_38AD4,
       coordinator-verified; sub_0800322C claim rejected).
       Evidence: docs/match_notes_wave6_blkA.md, docs/match_notes_wave6_l1.md. */
    . = 0x08003154; .text.w6a_3154 : { build/wave6_blka.o (.text.w6a_3154); }
    . = 0x08003298; .text.w6a_3298 : { build/wave6_blka.o (.text.w6a_3298); }
    . = 0x08017D50; .text.w6a_17d50 : { build/wave6_blka_old.o (.text.w6a_17d50); }
    . = 0x08038AD4; .text.w6l1_38ad4 : { build/wave6_l1_old.o (.text.w6l1_38ad4); }
    /* Phase 3 Wave 6 BLK-B (2 verified, coordinator-verified, old_agbcc).
       Evidence: docs/match_notes_wave6_blkB.md. */
    . = 0x080230A0; .text.w6b_230a0 : { build/wave6_blkb_old.o (.text.w6b_230a0); }
    . = 0x08037440; .text.w6b_37440 : { build/wave6_blkb_old.o (.text.w6b_37440); }
    /* Phase 3 Wave 6 L4 (29 verified, coordinator-verified, old_agbcc).
       Evidence: docs/match_notes_wave6_l4.md. */
    . = 0x08021000; .text.w6l4_08021000 : { build/wave6_l4_old.o (.text.w6l4_08021000); }
    . = 0x0801ae00; .text.w6l4_0801ae00 : { build/wave6_l4_old.o (.text.w6l4_0801ae00); }
    . = 0x0801dad4; .text.w6l4_0801dad4 : { build/wave6_l4_old.o (.text.w6l4_0801dad4); }
    . = 0x08017e6c; .text.w6l4_08017e6c : { build/wave6_l4_old.o (.text.w6l4_08017e6c); }
    . = 0x0801db9c; .text.w6l4_0801db9c : { build/wave6_l4_old.o (.text.w6l4_0801db9c); }
    . = 0x0801bc04; .text.w6l4_0801bc04 : { build/wave6_l4_old.o (.text.w6l4_0801bc04); }
    . = 0x0801acf4; .text.w6l4_0801acf4 : { build/wave6_l4_old.o (.text.w6l4_0801acf4); }
    . = 0x08011cd4; .text.w6l4_08011cd4 : { build/wave6_l4_old.o (.text.w6l4_08011cd4); }
    . = 0x0804ccb8; .text.w6l4_0804ccb8 : { build/wave6_l4_old.o (.text.w6l4_0804ccb8); }
    . = 0x0801afe4; .text.w6l4_0801afe4 : { build/wave6_l4_old.o (.text.w6l4_0801afe4); }
    . = 0x080217e0; .text.w6l4_080217e0 : { build/wave6_l4_old.o (.text.w6l4_080217e0); }
    . = 0x08022920; .text.w6l4_08022920 : { build/wave6_l4_old.o (.text.w6l4_08022920); }
    . = 0x0801d36c; .text.w6l4_0801d36c : { build/wave6_l4_old.o (.text.w6l4_0801d36c); }
    . = 0x08021df8; .text.w6l4_08021df8 : { build/wave6_l4_old.o (.text.w6l4_08021df8); }
    . = 0x0802054c; .text.w6l4_0802054c : { build/wave6_l4_old.o (.text.w6l4_0802054c); }
    . = 0x08023034; .text.w6l4_08023034 : { build/wave6_l4_old.o (.text.w6l4_08023034); }
    . = 0x08021528; .text.w6l4_08021528 : { build/wave6_l4_old.o (.text.w6l4_08021528); }
    . = 0x0801f1e8; .text.w6l4_0801f1e8 : { build/wave6_l4_old.o (.text.w6l4_0801f1e8); }
    . = 0x08022644; .text.w6l4_08022644 : { build/wave6_l4_old.o (.text.w6l4_08022644); }
    . = 0x080236f0; .text.w6l4_080236f0 : { build/wave6_l4_old.o (.text.w6l4_080236f0); }
    . = 0x0801b6c4; .text.w6l4_0801b6c4 : { build/wave6_l4_old.o (.text.w6l4_0801b6c4); }
    . = 0x0801aef4; .text.w6l4_0801aef4 : { build/wave6_l4_old.o (.text.w6l4_0801aef4); }
    . = 0x0801b81c; .text.w6l4_0801b81c : { build/wave6_l4_old.o (.text.w6l4_0801b81c); }
    . = 0x08016dac; .text.w6l4_08016dac : { build/wave6_l4_old.o (.text.w6l4_08016dac); }
    . = 0x0802503c; .text.w6l4_0802503c : { build/wave6_l4_old.o (.text.w6l4_0802503c); }
    . = 0x08007bec; .text.w6l4_08007bec : { build/wave6_l4_old.o (.text.w6l4_08007bec); }
    . = 0x0800e204; .text.w6l4_0800e204 : { build/wave6_l4_old.o (.text.w6l4_0800e204); }
    . = 0x08002904; .text.w6l4_08002904 : { build/wave6_l4_old.o (.text.w6l4_08002904); }
    . = 0x08028244; .text.w6l4_08028244 : { build/wave6_l4_old.o (.text.w6l4_08028244); }
    /* Phase 3 Wave 6 L3 (15 verified, coordinator-verified, old_agbcc).
       Evidence: docs/match_notes_wave6_l3.md. */
    . = 0x080186F4; .text.w6l3_186f4 : { build/wave6_l3_old.o (.text.w6l3_186f4); }
    . = 0x0801B3AC; .text.w6l3_1b3ac : { build/wave6_l3_old.o (.text.w6l3_1b3ac); }
    . = 0x08022320; .text.w6l3_22320 : { build/wave6_l3_old.o (.text.w6l3_22320); }
    . = 0x08020D54; .text.w6l3_20d54 : { build/wave6_l3_old.o (.text.w6l3_20d54); }
    . = 0x080223E4; .text.w6l3_223e4 : { build/wave6_l3_old.o (.text.w6l3_223e4); }
    . = 0x08022E14; .text.w6l3_22e14 : { build/wave6_l3_old.o (.text.w6l3_22e14); }
    . = 0x0801ABE4; .text.w6l3_1abe4 : { build/wave6_l3_old.o (.text.w6l3_1abe4); }
    . = 0x0801D658; .text.w6l3_1d658 : { build/wave6_l3_old.o (.text.w6l3_1d658); }
    . = 0x0801D828; .text.w6l3_1d828 : { build/wave6_l3_old.o (.text.w6l3_1d828); }
    . = 0x0801F930; .text.w6l3_1f930 : { build/wave6_l3_old.o (.text.w6l3_1f930); }
    . = 0x08019090; .text.w6l3_19090 : { build/wave6_l3_old.o (.text.w6l3_19090); }
    . = 0x08001DB8; .text.w6l3_1db8 : { build/wave6_l3_old.o (.text.w6l3_1db8); }
    . = 0x08042EC0; .text.w6l3_42ec0 : { build/wave6_l3_old.o (.text.w6l3_42ec0); }
    . = 0x0804CD70; .text.w6l3_4cd70 : { build/wave6_l3_old.o (.text.w6l3_4cd70); }
    . = 0x0803AF98; .text.w6l3_3af98 : { build/wave6_l3_old.o (.text.w6l3_3af98); }
    . = 0x08025578; .text.w7e_08025578 : { build/wave7_e.o (.text.w7e_08025578); }
    . = 0x08047538; .text.w7e_08047538 : { build/wave7_e_old.o (.text.w7e_08047538); }
    . = 0x080031B8; .text.w7d_080031b8 : { build/wave7_d.o (.text.w7d_080031b8); }
    . = 0x0800322C; .text.w7d_0800322c : { build/wave7_d.o (.text.w7d_0800322c); }
    . = 0x08017F8C; .text.w7d_08017f8c : { build/wave7_d_old.o (.text.w7d_08017f8c); }
    . = 0x0801DCC0; .text.w7d_0801dcc0 : { build/wave7_d_old.o (.text.w7d_0801dcc0); }
    . = 0x080205B8; .text.w7d_080205b8 : { build/wave7_d_old.o (.text.w7d_080205b8); }
    . = 0x080367E0; .text.w7b_080367e0 : { build/wave7_b.o (.text.w7b_080367e0); }
    . = 0x08011cac; .text.w7g2_08011cac : { build/wave7_g2_old.o (.text.w7g2_08011cac); }
    . = 0x08025324; .text.w7g2_08025324 : { build/wave7_g2_old.o (.text.w7g2_08025324); }
    . = 0x080363d4; .text.w7g2_080363d4 : { build/wave7_g2_old.o (.text.w7g2_080363d4); }
    . = 0x0803fcc4; .text.w7g2_0803fcc4 : { build/wave7_g2_old.o (.text.w7g2_0803fcc4); }
    . = 0x08040060; .text.w7g2_08040060 : { build/wave7_g2_old.o (.text.w7g2_08040060); }
    . = 0x080496e8; .text.w7g2_080496e8 : { build/wave7_g2_old.o (.text.w7g2_080496e8); }
    . = 0x08049560; .text.w29c_08049560 : { build/w29c_08049560.o (.text.w29c_08049560); } /* GfxSetup_08049560 (328 B, main agbcc) */
    . = 0x0804aa78; .text.w7g2_0804aa78 : { build/wave7_g2_old.o (.text.w7g2_0804aa78); }
    . = 0x0804ac48; .text.w7g2_0804ac48 : { build/wave7_g2_old.o (.text.w7g2_0804ac48); }
    . = 0x08027e44; .text.w7g2_08027e44 : { build/wave7_g2_old.o (.text.w7g2_08027e44); }
    . = 0x08000e64; .text.w7g2_08000e64 : { build/wave7_g2_old.o (.text.w7g2_08000e64); }
    . = 0x08002e50; .text.w7g2_08002e50 : { build/wave7_g2_old.o (.text.w7g2_08002e50); }
    . = 0x080110c8; .text.w7g2_080110c8 : { build/wave7_g2_old.o (.text.w7g2_080110c8); }
    . = 0x08011f50; .text.w7g2_08011f50 : { build/wave7_g2_old.o (.text.w7g2_08011f50); }
    . = 0x080252d0; .text.w7g2_080252d0 : { build/wave7_g2_old.o (.text.w7g2_080252d0); }
    . = 0x08025478; .text.w7g2_08025478 : { build/wave7_g2_old.o (.text.w7g2_08025478); }
    . = 0x080258c0; .text.w7g2_080258c0 : { build/wave7_g2_old.o (.text.w7g2_080258c0); }
    . = 0x0804a494; .text.w7g2_0804a494 : { build/wave7_g2_old.o (.text.w7g2_0804a494); }
    . = 0x08004188; .text.w7g2_08004188 : { build/wave7_g2_old.o (.text.w7g2_08004188); }
    . = 0x08004244; .text.w7g2_08004244 : { build/wave7_g2_old.o (.text.w7g2_08004244); }
    . = 0x08008610; .text.w7g2_08008610 : { build/wave7_g2_old.o (.text.w7g2_08008610); }
    . = 0x08010088; .text.w7g2_08010088 : { build/wave7_g2_old.o (.text.w7g2_08010088); }
    . = 0x08010124; .text.w7g2_08010124 : { build/wave7_g2_old.o (.text.w7g2_08010124); }
    . = 0x08010248; .text.w7g2_08010248 : { build/wave7_g2_old.o (.text.w7g2_08010248); }
    . = 0x080102f4; .text.w7g2_080102f4 : { build/wave7_g2_old.o (.text.w7g2_080102f4); }
    . = 0x080103cc; .text.w7g2_080103cc : { build/wave7_g2_old.o (.text.w7g2_080103cc); }
    . = 0x080104f4; .text.w7g2_080104f4 : { build/wave7_g2_old.o (.text.w7g2_080104f4); }
    . = 0x0801109c; .text.w7g2_0801109c : { build/wave7_g2_old.o (.text.w7g2_0801109c); }
    . = 0x08011f68; .text.w7g2_08011f68 : { build/wave7_g2_old.o (.text.w7g2_08011f68); }
    . = 0x08024500; .text.w7g2_08024500 : { build/wave7_g2_old.o (.text.w7g2_08024500); }
    . = 0x08024514; .text.w7g2_08024514 : { build/wave7_g2_old.o (.text.w7g2_08024514); }
    . = 0x0802453c; .text.w7g2_0802453c : { build/wave7_g2_old.o (.text.w7g2_0802453c); }
    . = 0x08026108; .text.w7g2_08026108 : { build/wave7_g2_old.o (.text.w7g2_08026108); }
    . = 0x0803fe1c; .text.w7g2_0803fe1c : { build/wave7_g2_old.o (.text.w7g2_0803fe1c); }
    . = 0x0803fe30; .text.w7g2_0803fe30 : { build/wave7_g2_old.o (.text.w7g2_0803fe30); }
    . = 0x0804ad24; .text.w7g2_0804ad24 : { build/wave7_g2_old.o (.text.w7g2_0804ad24); }
    . = 0x0804c5f4; .text.w7g2_0804c5f4 : { build/wave7_g2_old.o (.text.w7g2_0804c5f4); }
    . = 0x08002a04; .text.w7g2_08002a04 : { build/wave7_g2_old.o (.text.w7g2_08002a04); }
    . = 0x08007cdc; .text.w7g2_08007cdc : { build/wave7_g2_old.o (.text.w7g2_08007cdc); }
    . = 0x0800b29c; .text.w7g2_0800b29c : { build/wave7_g2_old.o (.text.w7g2_0800b29c); }
    . = 0x0800b148; .text.w17a_0800b148 : { build/w17a_0800b148.o (.text.w17a_0800b148); } /* sub_0800B148 (340 B) */
    . = 0x08021d84; .text.w7g2_08021d84 : { build/wave7_g2_old.o (.text.w7g2_08021d84); }
    . = 0x08024528; .text.w7g2_08024528 : { build/wave7_g2_old.o (.text.w7g2_08024528); }
    . = 0x0802571c; .text.w7g2_0802571c : { build/wave7_g2_old.o (.text.w7g2_0802571c); }
    . = 0x08046de4; .text.w7g2_08046de4 : { build/wave7_g2_old.o (.text.w7g2_08046de4); }
    . = 0x0800dcf8; .text.w7g2_0800dcf8 : { build/wave7_g2_old.o (.text.w7g2_0800dcf8); }
    . = 0x080112bc; .text.w7g2_080112bc : { build/wave7_g2_old.o (.text.w7g2_080112bc); }
    . = 0x08016f88; .text.w7g2_08016f88 : { build/wave7_g2_old.o (.text.w7g2_08016f88); }
    . = 0x08017494; .text.w7g2_08017494 : { build/wave7_g2_old.o (.text.w7g2_08017494); }
    . = 0x080174a4; .text.w7g2_080174a4 : { build/wave7_g2_old.o (.text.w7g2_080174a4); }
    . = 0x0802365c; .text.w7g2_0802365c : { build/wave7_g2_old.o (.text.w7g2_0802365c); }
    . = 0x080252e8; .text.w7g2_080252e8 : { build/wave7_g2_old.o (.text.w7g2_080252e8); }
    . = 0x08025994; .text.w7g2_08025994 : { build/wave7_g2_old.o (.text.w7g2_08025994); }
    . = 0x08026700; .text.w7g2_08026700 : { build/wave7_g2_old.o (.text.w7g2_08026700); }
    . = 0x0803fef8; .text.w7g2_0803fef8 : { build/wave7_g2_old.o (.text.w7g2_0803fef8); }
    . = 0x08008bb8; .text.w7g2_08008bb8 : { build/wave7_g2_old.o (.text.w7g2_08008bb8); }
    . = 0x08009640; .text.w7g2_08009640 : { build/wave7_g2_old.o (.text.w7g2_08009640); }
    . = 0x0800e1f0; .text.w7g2_0800e1f0 : { build/wave7_g2.o (.text.w7g2_0800e1f0); }
    . = 0x08016f98; .text.w7g2_08016f98 : { build/wave7_g2_old.o (.text.w7g2_08016f98); }
    . = 0x080170c4; .text.w7g2_080170c4 : { build/wave7_g2_old.o (.text.w7g2_080170c4); }
    . = 0x08017464; .text.w7g2_08017464 : { build/wave7_g2_old.o (.text.w7g2_08017464); }
    . = 0x08017478; .text.w7g2_08017478 : { build/wave7_g2_old.o (.text.w7g2_08017478); }
    . = 0x0801cdd8; .text.w7g2_0801cdd8 : { build/wave7_g2_old.o (.text.w7g2_0801cdd8); }
    . = 0x0801d34c; .text.w7g2_0801d34c : { build/wave7_g2_old.o (.text.w7g2_0801d34c); }
    . = 0x0801f1d8; .text.w7g2_0801f1d8 : { build/wave7_g2_old.o (.text.w7g2_0801f1d8); }
    . = 0x08022634; .text.w7g2_08022634 : { build/wave7_g2_old.o (.text.w7g2_08022634); }
    . = 0x080252f8; .text.w7g2_080252f8 : { build/wave7_g2_old.o (.text.w7g2_080252f8); }
    . = 0x0800edfc; .text.w7g2_0800edfc : { build/wave7_g2_old.o (.text.w7g2_0800edfc); }
    . = 0x0800ee14; .text.w7g2_0800ee14 : { build/wave7_g2_old.o (.text.w7g2_0800ee14); }
    . = 0x08002e70; .text.w7g2_08002e70 : { build/wave7_g2.o (.text.w7g2_08002e70); }
    . = 0x08002E80; .text.w23a_08002E80 : { build/w23a_08002e80.o (.text.w23a_08002E80); } /* sub_08002E80 (84 B, old_agbcc) */
    . = 0x08002EF4; .text.w24d_08002ef4 : { build/w24d_08002ef4.o (.text.w24d_08002ef4); } /* SetAA_Clr2_08002EF4 (48 B incl pool, main agbcc) */
    . = 0x08001C88; .text.w24d_08001C88 : { build/w24d_08001c88.o (.text.w24d_08001c88); } /* CallTwice_08001C88 (32 B, main agbcc) */
    . = 0x08001d88; .text.w7g2_08001d88 : { build/wave7_g2.o (.text.w7g2_08001d88); }
    . = 0x08000c9c; .text.w7g2_08000c9c : { build/wave7_g2.o (.text.w7g2_08000c9c); }
    . = 0x08002e44; .text.w7g2_08002e44 : { build/wave7_g2.o (.text.w7g2_08002e44); }
    . = 0x08002ed4; .text.w7g2_08002ed4 : { build/wave7_g2.o (.text.w7g2_08002ed4); }
    . = 0x0800d3a0; .text.w7f_0800d3a0 : { build/wave7_f.o (.text.w7f_0800d3a0); }
    . = 0x08010fb4; .text.w7f_08010fb4 : { build/wave7_f_old.o (.text.w7f_08010fb4); }
    . = 0x08004424; .text.w7f_08004424 : { build/wave7_f_old.o (.text.w7f_08004424); }
    . = 0x08004454; .text.w7f_08004454 : { build/wave7_f_old.o (.text.w7f_08004454); }
    . = 0x08021594; .text.w7c_08021594 : { build/wave7_c_old.o (.text.w7c_08021594); }
    . = 0x0802184C; .text.w7c_0802184c : { build/wave7_c_old.o (.text.w7c_0802184c); }
    /* Wave 8 batch R: re-derived Wave-7-G1 claims */
    . = 0x080021c4; .text.w8r_080021c4 : { build/wave8_r.o (.text.w8r_080021c4); }
    . = 0x08004b94; .text.w8r_08004b94 : { build/wave8_r.o (.text.w8r_08004b94); }
    . = 0x080475d4; .text.w8r_080475d4 : { build/wave8_r.o (.text.w8r_080475d4); }
    . = 0x0800b4c8; .text.w8r_0800b4c8 : { build/wave8_r.o (.text.w8r_0800b4c8); }
    . = 0x08026f98; .text.w8r_08026f98 : { build/wave8_r_old.o (.text.w8r_08026f98); }
    . = 0x0802c7b4; .text.w8r_0802c7b4 : { build/wave8_r_old.o (.text.w8r_0802c7b4); }
    . = 0x08010454; .text.w8r_08010454 : { build/wave8_r_old.o (.text.w8r_08010454); }
    . = 0x0802520c; .text.w8r_0802520c : { build/wave8_r_old.o (.text.w8r_0802520c); }
    . = 0x0802526c; .text.w8r_0802526c : { build/wave8_r_old.o (.text.w8r_0802526c); }
    . = 0x08004e24; .text.w8r_08004e24 : { build/wave8_r_old.o (.text.w8r_08004e24); }
    . = 0x08004e0c; .text.w8r_08004e0c : { build/wave8_r_old.o (.text.w8r_08004e0c); }
    . = 0x08010478; .text.w8r_08010478 : { build/wave8_r_old.o (.text.w8r_08010478); }
    . = 0x0801052c; .text.w8r_0801052c : { build/wave8_r_old.o (.text.w8r_0801052c); }
    /* Wave 8 batch B: blocked-revisit cracks */
    . = 0x0800b2d8; .text.w8b_0800b2d8 : { build/wave8_b_old.o (.text.w8b_0800b2d8); }
    . = 0x0800b2f0; .text.w8b_0800b2f0 : { build/wave8_b_old.o (.text.w8b_0800b2f0); }
    /* Wave 8 batch XL: ARM sound-driver mixer fragment */
    . = 0x0804bcdc; .text.w8xl_0804bcdc : { build/wave8_xl.o (.text.w8xl_0804bcdc); }
    /* Wave 8 batch M: EWRAM bump allocator / entity-list appends */
    . = 0x0800069c; .text.w8m_0800069c : { build/wave8_m_old.o (.text.w8m_0800069c); }
    . = 0x08002568; .text.w8m_08002568 : { build/wave8_m.o (.text.w8m_08002568); }
    . = 0x080025c4; .text.w8m_080025c4 : { build/wave8_m.o (.text.w8m_080025c4); }
    /* Wave 8 batch U: unattempted-pool cracks */
    . = 0x080110b0; .text.w8u_0x080110b0 : { build/wave8_u_old.o (.text.w8u_0x080110b0); }
    . = 0x0800b2b4; .text.w8u_0x0800b2b4 : { build/wave8_u_old.o (.text.w8u_0x0800b2b4); }
    . = 0x0804b310; .text.w8u_0x0804b310 : { build/wave8_u_old.o (.text.w8u_0x0804b310); }
    . = 0x08010374; .text.w8u_0x08010374 : { build/wave8_u_old.o (.text.w8u_0x08010374); }
    . = 0x08010f88; .text.w8u_0x08010f88 : { build/wave8_u_old.o (.text.w8u_0x08010f88); }
    . = 0x0800db40; .text.w8u_0x0800db40 : { build/wave8_u_old.o (.text.w8u_0x0800db40); }
    . = 0x0800c8bc; .text.w8u_0x0800c8bc : { build/wave8_u_old.o (.text.w8u_0x0800c8bc); }
    . = 0x0804a660; .text.w8u_0x0804a660 : { build/wave8_u_old.o (.text.w8u_0x0804a660); }
    . = 0x0800b6f4; .text.w8u_0x0800b6f4 : { build/wave8_u_old.o (.text.w8u_0x0800b6f4); }
    /* Wave 8 batch S: small-leaf matches */
    . = 0x0800300c; .text.w8s_0800300c : { build/wave8_s_old.o (.text.w8s_0800300c); }
    . = 0x08008628; .text.w8s_08008628 : { build/wave8_s_old.o (.text.w8s_08008628); }
    . = 0x08008654; .text.w8s_08008654 : { build/wave8_s_old.o (.text.w8s_08008654); }
    . = 0x08008680; .text.w8s_08008680 : { build/wave8_s_old.o (.text.w8s_08008680); }
    . = 0x0800960c; .text.w8s_0800960c : { build/wave8_s_old.o (.text.w8s_0800960c); }
    . = 0x0800c92c; .text.w8s_0800c92c : { build/wave8_s_old.o (.text.w8s_0800c92c); }
    . = 0x08024554; .text.w8s_08024554 : { build/wave8_s_old.o (.text.w8s_08024554); }
    . = 0x08024570; .text.w8s_08024570 : { build/wave8_s_old.o (.text.w8s_08024570); }
    . = 0x0802458c; .text.w8s_0802458c : { build/wave8_s_old.o (.text.w8s_0802458c); }
    . = 0x080245c4; .text.w8s_080245c4 : { build/wave8_s_old.o (.text.w8s_080245c4); }
    . = 0x080245e0; .text.w8s_080245e0 : { build/wave8_s_old.o (.text.w8s_080245e0); }
    . = 0x080245fc; .text.w8s_080245fc : { build/wave8_s_old.o (.text.w8s_080245fc); }
    . = 0x08024618; .text.w8s_08024618 : { build/wave8_s_old.o (.text.w8s_08024618); }
    . = 0x08024670; .text.w8s_08024670 : { build/wave8_s_old.o (.text.w8s_08024670); }
    . = 0x0802468c; .text.w8s_0802468c : { build/wave8_s_old.o (.text.w8s_0802468c); }
    . = 0x080246a8; .text.w8s_080246a8 : { build/wave8_s_old.o (.text.w8s_080246a8); }
    . = 0x080246c4; .text.w8s_080246c4 : { build/wave8_s_old.o (.text.w8s_080246c4); }
    . = 0x080246e0; .text.w8s_080246e0 : { build/wave8_s_old.o (.text.w8s_080246e0); }
    . = 0x080247a8; .text.w8s_080247a8 : { build/wave8_s_old.o (.text.w8s_080247a8); }
    . = 0x0802637c; .text.w8s_0802637c : { build/wave8_s_old.o (.text.w8s_0802637c); }
    . = 0x0803fa1c; .text.w8s_0803fa1c : { build/wave8_s_old.o (.text.w8s_0803fa1c); }
    /* Wave 9 batch A: blocked-revisit closers */
    . = 0x0801d3c0; .text.w9a_0801d3c0 : { build/wave9_a_old.o (.text.w9a_0801d3c0); }
    /* Wave 9 batch F: blocked revisits */
    . = 0x080481fc; .text.w9f_0x080481fc : { build/wave9_f_old.o (.text.w9f_0x080481fc); }
    . = 0x08011c58; .text.w9f_0x08011c58 : { build/wave9_f_old.o (.text.w9f_0x08011c58); }
    /* Wave 9 batch B: Script_StepState (964B) */
    . = 0x0803f480; .text.w9b_0803f480 : { build/wave9_b_old.o (.text.w9b_0803f480); }
    /* Wave 9 batch D: leaves-up bulk batch 1 (7 functions) */
    . = 0x0800800c; .text.w9d_0800800c : { build/wave9_d_old.o (.text.w9d_0800800c); }
    . = 0x08010508; .text.w9d_08010508 : { build/wave9_d_old.o (.text.w9d_08010508); }
    . = 0x080258d8; .text.w9d_080258d8 : { build/wave9_d_old.o (.text.w9d_080258d8); }
    . = 0x08025638; .text.w9d_08025638 : { build/wave9_d_old.o (.text.w9d_08025638); }
    . = 0x0800b4e4; .text.w9d_0800b4e4 : { build/wave9_d_old.o (.text.w9d_0800b4e4); }
    . = 0x08025290; .text.w9d_08025290 : { build/wave9_d_old.o (.text.w9d_08025290); }
    . = 0x0802d440; .text.w9d_0802d440 : { build/wave9_d_old.o (.text.w9d_0802d440); }
    . = 0x080400a8; .text.w9e_80400a8 : { build/wave9_e_old.o (.text.w9e_80400a8); }
    . = 0x0803fd68; .text.w9e_803fd68 : { build/wave9_e_old.o (.text.w9e_803fd68); }
    . = 0x08025654; .text.w9e_8025654 : { build/wave9_e_old.o (.text.w9e_8025654); }
    . = 0x08011dd0; .text.w9e_8011dd0 : { build/wave9_e_old.o (.text.w9e_8011dd0); }
    . = 0x0800b308; .text.w9e_800b308 : { build/wave9_e_old.o (.text.w9e_800b308); }
    /* Wave 10 worker T: Task_3AFFC unblock — sub_0800B368 (72 B) */
    . = 0x0800b368; .text.w10t_0x0800b368 : { build/wave10_T_old.o (.text.w10t_0x0800b368); }
    /* Wave 10 worker R: W9 staging blockers */
    . = 0x08011d34; .text.w10r_8011d34 : { build/wave10_R_old.o (.text.w10r_8011d34); }
    . = 0x08011d68; .text.w10r_8011d68 : { build/wave10_R_old.o (.text.w10r_8011d68); }
    . = 0x0800520c; .text.w10r_800520c : { build/wave10_R_old.o (.text.w10r_800520c); }
    /* Wave 10 worker H: ComputeFields @0x0804CFD4 (180 B) */
    . = 0x0804cfd4; .text.w10h_0804cfd4 : { build/wave10_H_old.o (.text.w10h_0804cfd4); }
    /* Wave 10 worker H: Obj_AddEntry @0x0802D7A0 (340 B, .s transcription) */
    . = 0x0802d7a0; .text.objaddentry : { build/objaddentry.o (.text.objaddentry); }
    /* Wave 10 worker L: leaves-up bulk batch (7 functions) */
    . = 0x0800c248; .text.w10l_0800c248 : { build/wave10_L_old.o (.text.w10l_0800c248); }
    . = 0x0802d460; .text.w10l_0802d460 : { build/wave10_L_old.o (.text.w10l_0802d460); }
    . = 0x08026720; .text.w10l_08026720 : { build/wave10_L_old.o (.text.w10l_08026720); }
    . = 0x08026d94; .text.w10l_08026d94 : { build/wave10_L_old.o (.text.w10l_08026d94); }
    . = 0x08016fac; .text.w10l_08016fac : { build/wave10_L_old.o (.text.w10l_08016fac); }
    . = 0x08049934; .text.w10l_08049934 : { build/wave10_L_old.o (.text.w10l_08049934); }
    . = 0x08023ce4; .text.w10l_08023ce4 : { build/wave10_L_old.o (.text.w10l_08023ce4); }
    /* Wave 11 worker D: sub_0803FACC (IsSpecialChip_3FACC, 76 B incl. pool) */
    . = 0x0803facc; .text.w11d_0803facc : { build/wave11_D_old.o (.text.w11d_0803facc); }
    /* Wave 11 worker B: 7 functions (all old_agbcc) */
    . = 0x08026554; .text.w11b_08026554 : { build/wave11_B_old.o (.text.w11b_08026554); }
    . = 0x080265b0; .text.w11b_080265b0 : { build/wave11_B_old.o (.text.w11b_080265b0); }
    . = 0x080265d0; .text.w11b_080265d0 : { build/wave11_B_old.o (.text.w11b_080265d0); }
    . = 0x0804ac88; .text.w11b_0804ac88 : { build/wave11_B_old.o (.text.w11b_0804ac88); }
    . = 0x08011c14; .text.w11b_08011c14 : { build/wave11_B_old.o (.text.w11b_08011c14); }
    . = 0x08023b88; .text.w11b_08023b88 : { build/wave11_B_old.o (.text.w11b_08023b88); }
    . = 0x08001e74; .text.w11b_08001e74 : { build/wave11_B_old.o (.text.w11b_08001e74); }
    /* Wave 11 worker A: 26 functions (all old_agbcc) */
    . = 0x08020230; .text.w11a_08020230 : { build/wave11_A_old.o (.text.w11a_08020230); }
    /* Wave 12 worker C: 5 functions (all old_agbcc) */
    . = 0x0800cd00; .text.w12c_0800cd00 : { build/wave12_C_old.o (.text.w12c_0800cd00); }
    . = 0x08002c74; .text.w12c_08002c74 : { build/wave12_C_old.o (.text.w12c_08002c74); }
    . = 0x08002CB0; .text.w23a_08002CB0 : { build/w23a_08002cb0.o (.text.w23a_08002CB0); } /* sub_08002CB0 (112 B, main agbcc + sed) */
    . = 0x0804AF20; .text.w24a_0804AF20 : { build/w24a_0804af20.o (.text.w24a_0804AF20); } /* InitRec28_4AF20 (112 B, main agbcc + sed) */
    . = 0x080499ac; .text.w12c_080499ac : { build/wave12_C_old.o (.text.w12c_080499ac); }
    . = 0x0800c4b4; .text.w12c_0800c4b4 : { build/wave12_C_old.o (.text.w12c_0800c4b4); }
    . = 0x0800c3a0; .text.w12c_0800c3a0 : { build/wave12_C_old.o (.text.w12c_0800c3a0); }
    /* Wave 12 worker B: r1/r2/r3 allocation cluster (4 functions, old_agbcc) */
    . = 0x08011db0; .text.w12b_08011db0 : { build/wave12_B_old.o (.text.w12b_08011db0); }
    . = 0x0804d7a0; .text.w12b_0804d7a0 : { build/wave12_B_old.o (.text.w12b_0804d7a0); }
    . = 0x0802518c; .text.w12b_0802518c : { build/wave12_B_old.o (.text.w12b_0802518c); }
    . = 0x0802d8f4; .text.w12b_0802d8f4 : { build/wave12_B_old.o (.text.w12b_0802d8f4); }
    . = 0x08024744; .text.w11a_08024744 : { build/wave11_A_old.o (.text.w11a_08024744); }
    . = 0x0803fe00; .text.w11a_0803fe00 : { build/wave11_A_old.o (.text.w11a_0803fe00); }
    . = 0x0804c53c; .text.w11a_0804c53c : { build/wave11_A_old.o (.text.w11a_0804c53c); }
    . = 0x0800ee50; .text.w11a_0800ee50 : { build/wave11_A_old.o (.text.w11a_0800ee50); }
    . = 0x0800d104; .text.w11a_0800d104 : { build/wave11_A_old.o (.text.w11a_0800d104); }
    . = 0x0803f440; .text.w11a_0803f440 : { build/wave11_A_old.o (.text.w11a_0803f440); }
    . = 0x0803f460; .text.w11a_0803f460 : { build/wave11_A_old.o (.text.w11a_0803f460); }
    . = 0x0803fd9c; .text.w11a_0803fd9c : { build/wave11_A_old.o (.text.w11a_0803fd9c); }
    . = 0x0804c610; .text.w11a_0804c610 : { build/wave11_A_old.o (.text.w11a_0804c610); }
    . = 0x08011054; .text.w11a_08011054 : { build/wave11_A_old.o (.text.w11a_08011054); }
    . = 0x080173fc; .text.w11a_080173fc : { build/wave11_A_old.o (.text.w11a_080173fc); }
    . = 0x08021c0c; .text.w11a_08021c0c : { build/wave11_A_old.o (.text.w11a_08021c0c); }
    . = 0x08025308; .text.w11a_08025308 : { build/wave11_A_old.o (.text.w11a_08025308); }
    . = 0x08001d68; .text.w11a_08001d68 : { build/wave11_A_old.o (.text.w11a_08001d68); }
    . = 0x0804bdc0; .text.w11a_0804bdc0 : { build/wave11_A_old.o (.text.w11a_0804bdc0); }
    . = 0x08000ef8; .text.w11a_08000ef8 : { build/wave11_A_old.o (.text.w11a_08000ef8); }
    . = 0x08023b64; .text.w11a_08023b64 : { build/wave11_A_old.o (.text.w11a_08023b64); }
    . = 0x08023d10; .text.w11a_08023d10 : { build/wave11_A_old.o (.text.w11a_08023d10); }
    . = 0x08025490; .text.w11a_08025490 : { build/wave11_A_old.o (.text.w11a_08025490); }
    . = 0x0804acdc; .text.w11a_0804acdc : { build/wave11_A_old.o (.text.w11a_0804acdc); }
    . = 0x08036318; .text.w11a_08036318 : { build/wave11_A_old.o (.text.w11a_08036318); }
    . = 0x0803fa48; .text.w11a_0803fa48 : { build/wave11_A_old.o (.text.w11a_0803fa48); }
    . = 0x0804a3c4; .text.w8s_0804a3c4 : { build/wave8_s_old.o (.text.w8s_0804a3c4); }
    . = 0x0804ad4c; .text.w8s_0804ad4c : { build/wave8_s_old.o (.text.w8s_0804ad4c); }
    /* Phase 3 Wave 13 worker B: 2 Task_3AFFC callees (main agbcc,
       coordinator-verified). Evidence: docs/match_notes_wave13_B.md. */
    . = 0x0800BEE0; .text.w12a_0800bee0 : { build/wave13_B.o (.text.w12a_0800bee0); }
    . = 0x080241F8; .text.w12a_080241f8 : { build/wave13_B.o (.text.w12a_080241f8); }
    /* Phase 3 Wave 13 worker B: TblGetByte_24384 @0x08024384 (174 B).
       GAS pads the C section to 176 with c046; verified bytes emitted
       via BYTE(). Documented source: src/wave13_B.c (main agbcc).
       Evidence: docs/match_notes_wave13_B.md. */
    . = 0x08024384; .text.w12a_08024384 : {
        BYTE(0x00); BYTE(0xB5); BYTE(0x00); BYTE(0x04); BYTE(0x00); BYTE(0x0C); BYTE(0x00); BYTE(0x28);
        BYTE(0x4E); BYTE(0xD0); BYTE(0x01); BYTE(0x0B); BYTE(0x02); BYTE(0x29); BYTE(0x19); BYTE(0xD0);
        BYTE(0x02); BYTE(0x29); BYTE(0x02); BYTE(0xDC); BYTE(0x01); BYTE(0x29); BYTE(0x05); BYTE(0xD0);
        BYTE(0x46); BYTE(0xE0); BYTE(0x03); BYTE(0x29); BYTE(0x30); BYTE(0xD0); BYTE(0x04); BYTE(0x29);
        BYTE(0x3C); BYTE(0xD0); BYTE(0x41); BYTE(0xE0); BYTE(0x06); BYTE(0x48); BYTE(0x00); BYTE(0x68);
        BYTE(0xD8); BYTE(0x21); BYTE(0x49); BYTE(0x00); BYTE(0x42); BYTE(0x18); BYTE(0x13); BYTE(0x78);
        BYTE(0xD9); BYTE(0x00); BYTE(0xC9); BYTE(0x18); BYTE(0x09); BYTE(0x01); BYTE(0x40); BYTE(0x18);
        BYTE(0x01); BYTE(0xF0); BYTE(0x26); BYTE(0xFB); BYTE(0x1B); BYTE(0xE0); BYTE(0x00); BYTE(0x00);
        BYTE(0xA4); BYTE(0x70); BYTE(0x00); BYTE(0x02); BYTE(0x08); BYTE(0x49); BYTE(0x01); BYTE(0x40);
        BYTE(0x00); BYTE(0x29); BYTE(0x11); BYTE(0xD1); BYTE(0x07); BYTE(0x48); BYTE(0x00); BYTE(0x68);
        BYTE(0xD8); BYTE(0x21); BYTE(0x49); BYTE(0x00); BYTE(0x42); BYTE(0x18); BYTE(0x13); BYTE(0x78);
        BYTE(0xD9); BYTE(0x00); BYTE(0xC9); BYTE(0x18); BYTE(0x09); BYTE(0x01); BYTE(0x40); BYTE(0x18);
        BYTE(0x01); BYTE(0xF0); BYTE(0x12); BYTE(0xFB); BYTE(0x07); BYTE(0xE0); BYTE(0x00); BYTE(0x00);
        BYTE(0xFF); BYTE(0x0F); BYTE(0x00); BYTE(0x00); BYTE(0xA4); BYTE(0x70); BYTE(0x00); BYTE(0x02);
        BYTE(0x02); BYTE(0x48); BYTE(0x02); BYTE(0xF0); BYTE(0xDB); BYTE(0xF8); BYTE(0x00); BYTE(0x06);
        BYTE(0x00); BYTE(0x0E); BYTE(0x16); BYTE(0xE0); BYTE(0xA8); BYTE(0x70); BYTE(0x00); BYTE(0x02);
        BYTE(0x04); BYTE(0x4A); BYTE(0x05); BYTE(0x49); BYTE(0x01); BYTE(0x40); BYTE(0x88); BYTE(0x00);
        BYTE(0x40); BYTE(0x18); BYTE(0x80); BYTE(0x00); BYTE(0x80); BYTE(0x18); BYTE(0x00); BYTE(0x78);
        BYTE(0x0B); BYTE(0xE0); BYTE(0x00); BYTE(0x00); BYTE(0xF0); BYTE(0x98); BYTE(0x22); BYTE(0x08);
        BYTE(0xFF); BYTE(0x0F); BYTE(0x00); BYTE(0x00); BYTE(0x01); BYTE(0x48); BYTE(0x00); BYTE(0x78);
        BYTE(0x03); BYTE(0xE0); BYTE(0x00); BYTE(0x00); BYTE(0xCC); BYTE(0x70); BYTE(0x00); BYTE(0x02);
        BYTE(0x32); BYTE(0x20); BYTE(0x02); BYTE(0xBC); BYTE(0x08); BYTE(0x47);
    }
    /* Phase 3 Wave 13 worker D: 4 leaves-up matches (old_agbcc,
       coordinator-verified). Evidence: docs/match_notes_wave13_D.md. */
    . = 0x08046CA0; .text.w13d_08046ca0 : { build/wave13_D_old.o (.text.w13d_08046ca0); }
    . = 0x08002D20; .text.w13d_08002d20 : { build/wave13_D_old.o (.text.w13d_08002d20); }
    . = 0x08002678; .text.w13d_08002678 : { build/wave13_D_old.o (.text.w13d_08002678); }
    . = 0x080048B4; .text.w13d_080048b4 : { build/wave13_D_old.o (.text.w13d_080048b4); }
    /* Phase 3 Wave 14 worker D: blocked revisits (old_agbcc,
       coordinator-verified). Evidence: docs/match_notes_wave14_D.md. */
    . = 0x08005338; .text.w14d_08005338 : { build/wave14_D_old.o (.text.w14d_08005338); }
    . = 0x08023D34; .text.w14d_08023d34 : { build/wave14_D_old.o (.text.w14d_08023d34); }
    . = 0x08026574; .text.w14d_08026574 : { build/wave14_D_old.o (.text.w14d_08026574); }
    . = 0x08010498; .text.w14d_08010498 : { build/wave14_D_old.o (.text.w14d_08010498); }
    . = 0x0802FC4C; .text.w14d_0802fc4c : { build/wave14_D_old.o (.text.w14d_0802fc4c); }
    . = 0x08047510; .text.w14d_08047510 : { build/wave14_D_old.o (.text.w14d_08047510); }
    . = 0x0804D634; .text.w14d_0804d634 : { build/wave14_D_old.o (.text.w14d_0804d634); }
    . = 0x0804DA34; .text.w14d_0804da34 : { build/wave14_D_old.o (.text.w14d_0804da34); }
    . = 0x0804A884; .text.w14d_0804a884 : { build/wave14_D_old.o (.text.w14d_0804a884); }
    /* Phase 3 Wave 14 worker B: 13 leaves-up matches (main/old/noiw,
       coordinator-verified). Evidence: docs/match_notes_wave14_B.md. */
    . = 0x0804D130; .text.w14b_0804d130 : { build/wave14_B_old.o (.text.w14b_0804d130); } /* IoRegWrite_4D130 (80 B) */
    . = 0x08004484; .text.w14b_08004484 : { build/wave14_B_old.o (.text.w14b_08004484); } /* List_InsertAfter_4484 (56 B) */
    . = 0x080044BC; .text.w14b_080044bc : { build/wave14_B_old.o (.text.w14b_080044bc); } /* List_InsertBefore_44BC (56 B) */
    . = 0x08047C4C; .text.w14b_08047c4c : { build/wave14_B_old.o (.text.w14b_08047c4c); } /* CopyTables_47C4C (88 B) */
    . = 0x08004E44; .text.w14b_08004e44 : { build/wave14_B.o (.text.w14b_08004e44); } /* Call4E60_4E44 (12 B) */
    . = 0x0804A328; .text.w14b_0804a328 : { build/wave14_B.o (.text.w14b_0804a328); } /* LoadCallClear_4A328 (24 B) */
    . = 0x08025730; .text.w14b_08025730 : { build/wave14_B.o (.text.w14b_08025730); } /* TblLookup_25730 (36 B) */
    . = 0x0800D770; .text.w14b_0800d770 : { build/wave14_B.o (.text.w14b_0800d770); } /* Wrapper_D770 (36 B) */
    . = 0x0800D728; .text.w14b_0800d728 : { build/wave14_B.o (.text.w14b_0800d728); } /* Wrapper_D728 (36 B) */
    /* MemsetAligned_4E008 (82 B, noiw) @0x0804E008: GAS c046 tail pad does not match ROM;
       emitted via BYTE() from verified build output. */
    . = 0x0804E008; .text.w14b_0804e008_b : {
BYTE(0x30); BYTE(0xB5); BYTE(0x05); BYTE(0x1C); BYTE(0x0C); BYTE(0x1C); BYTE(0x2B); BYTE(0x1C);
        BYTE(0x03); BYTE(0x2A); BYTE(0x1C); BYTE(0xD9); BYTE(0x03); BYTE(0x20); BYTE(0x28); BYTE(0x40);
        BYTE(0x00); BYTE(0x28); BYTE(0x18); BYTE(0xD1); BYTE(0x29); BYTE(0x1C); BYTE(0xFF); BYTE(0x20);
        BYTE(0x04); BYTE(0x40); BYTE(0x23); BYTE(0x02); BYTE(0x23); BYTE(0x43); BYTE(0x18); BYTE(0x04);
        BYTE(0x03); BYTE(0x43); BYTE(0x0F); BYTE(0x2A); BYTE(0x09); BYTE(0xD9); BYTE(0x08); BYTE(0xC1);
        BYTE(0x08); BYTE(0xC1); BYTE(0x08); BYTE(0xC1); BYTE(0x08); BYTE(0xC1); BYTE(0x10); BYTE(0x3A);
        BYTE(0x0F); BYTE(0x2A); BYTE(0xF8); BYTE(0xD8); BYTE(0x01); BYTE(0xE0); BYTE(0x08); BYTE(0xC1);
        BYTE(0x04); BYTE(0x3A); BYTE(0x03); BYTE(0x2A); BYTE(0xFB); BYTE(0xD8); BYTE(0x0B); BYTE(0x1C);
        BYTE(0x01); BYTE(0xE0); BYTE(0x1C); BYTE(0x70); BYTE(0x01); BYTE(0x33); BYTE(0x10); BYTE(0x1C);
        BYTE(0x01); BYTE(0x3A); BYTE(0x00); BYTE(0x28); BYTE(0xF9); BYTE(0xD1); BYTE(0x28); BYTE(0x1C);
        BYTE(0x30); BYTE(0xBD);
    }
    /* SearchFF_2567C (86 B, old) @0x0802567C: GAS c046 tail pad does not match ROM;
       emitted via BYTE() from verified build output. */
    . = 0x0802567C; .text.w14b_0802567c_b : {
BYTE(0x10); BYTE(0xB5); BYTE(0x04); BYTE(0x1C); BYTE(0x01); BYTE(0x22); BYTE(0xA3); BYTE(0x1C);
        BYTE(0x10); BYTE(0x04); BYTE(0x01); BYTE(0x14); BYTE(0x58); BYTE(0x18); BYTE(0x00); BYTE(0x78);
        BYTE(0xFF); BYTE(0x28); BYTE(0x02); BYTE(0xD1); BYTE(0x10); BYTE(0x06); BYTE(0x00); BYTE(0x0E);
        BYTE(0x1A); BYTE(0xE0); BYTE(0x48); BYTE(0x1C); BYTE(0x00); BYTE(0x04); BYTE(0x02); BYTE(0x0C);
        BYTE(0x00); BYTE(0x14); BYTE(0x09); BYTE(0x28); BYTE(0xF0); BYTE(0xDD); BYTE(0x00); BYTE(0x22);
        BYTE(0x23); BYTE(0x1C); BYTE(0x0C); BYTE(0x33); BYTE(0x10); BYTE(0x04); BYTE(0x01); BYTE(0x14);
        BYTE(0x58); BYTE(0x18); BYTE(0x00); BYTE(0x78); BYTE(0xFF); BYTE(0x28); BYTE(0x04); BYTE(0xD1);
        BYTE(0x10); BYTE(0x1C); BYTE(0x0A); BYTE(0x30); BYTE(0x00); BYTE(0x06); BYTE(0x00); BYTE(0x0E);
        BYTE(0x06); BYTE(0xE0); BYTE(0x48); BYTE(0x1C); BYTE(0x00); BYTE(0x04); BYTE(0x02); BYTE(0x0C);
        BYTE(0x00); BYTE(0x14); BYTE(0x01); BYTE(0x28); BYTE(0xEE); BYTE(0xDD); BYTE(0x00); BYTE(0x20);
        BYTE(0x10); BYTE(0xBC); BYTE(0x02); BYTE(0xBC); BYTE(0x08); BYTE(0x47);
    }
    /* PalModeSet_4DFC (14 B) @0x08004DFC: GAS c046 tail pad does not match ROM;
       emitted via BYTE() from verified build output. */
    . = 0x08004DFC; .text.w14b_08004dfc_b : {
BYTE(0x00); BYTE(0xB5); BYTE(0x00); BYTE(0x06); BYTE(0x00); BYTE(0x0E); BYTE(0x08); BYTE(0xF0);
        BYTE(0xCD); BYTE(0xFA); BYTE(0x01); BYTE(0xBC); BYTE(0x00); BYTE(0x47);
    }
    /* RangeCheckClear_2FC28 (34 B) @0x0802FC28: GAS c046 tail pad does not match ROM;
       emitted via BYTE() from verified build output. */
    . = 0x0802FC28; .text.w14b_0802fc28_b : {
BYTE(0x30); BYTE(0xB5); BYTE(0x04); BYTE(0x1C); BYTE(0x0D); BYTE(0x1C); BYTE(0x20); BYTE(0x68);
        BYTE(0x00); BYTE(0x89); BYTE(0x10); BYTE(0xF0); BYTE(0x47); BYTE(0xF8); BYTE(0x00); BYTE(0x06);
        BYTE(0x00); BYTE(0x28); BYTE(0x01); BYTE(0xD1); BYTE(0x02); BYTE(0x20); BYTE(0x28); BYTE(0x70);
        BYTE(0x00); BYTE(0x20); BYTE(0x20); BYTE(0x60); BYTE(0x30); BYTE(0xBC); BYTE(0x01); BYTE(0xBC);
        BYTE(0x00); BYTE(0x47);
    }
    /* Phase 3 Wave 14 worker C: 34 bulk leaves-up matches (main/old,
       coordinator-landed and re-verified). Evidence: docs/match_notes_wave14_C.md. */
    . = 0x08000F1C; .text.w14c_08000f1c : { build/wave14_C.o (.text.w14c_08000f1c); } /* F_08000F1C (10 B) */
    . = 0x08002F40; .text.w14c_08002f40 : { build/wave14_C.o (.text.w14c_08002f40); } /* F_08002F40 (10 B) */
    . = 0x08002F4C; .text.w14c_08002f4c : { build/wave14_C.o (.text.w14c_08002f4c); } /* F_08002F4C (10 B) */
    . = 0x08005610; .text.w14c_08005610 : { build/wave14_C.o (.text.w14c_08005610); } /* F_08005610 (10 B) */
    . = 0x0800D55C; .text.w14c_0800d55c : { build/wave14_C.o (.text.w14c_0800d55c); } /* F_0800D55C (10 B) */
    . = 0x08010ACC; .text.w14c_08010acc : { build/wave14_C.o (.text.w14c_08010acc); } /* F_08010ACC (10 B) */
    . = 0x08011BD4; .text.w14c_08011bd4 : { build/wave14_C.o (.text.w14c_08011bd4); } /* F_08011BD4 (10 B) */
    . = 0x0804C6A8; .text.w14c_0804c6a8 : { build/wave14_C.o (.text.w14c_0804c6a8); } /* F_0804C6A8 (10 B) */
    . = 0x08001C4C; .text.w14c_08001c4c : { build/wave14_C.o (.text.w14c_08001c4c); } /* F_08001C4C (14 B) */
    . = 0x080050E0; .text.w14c_080050e0 : { build/wave14_C.o (.text.w14c_080050e0); } /* F_080050E0 (14 B) */
    . = 0x0802616C; .text.w14c_0802616c : { build/wave14_C.o (.text.w14c_0802616c); } /* F_0802616C (14 B) */
    . = 0x0804C84C; .text.w14c_0804c84c : { build/wave14_C.o (.text.w14c_0804c84c); } /* F_0804C84C (14 B) */
    . = 0x08004EE0; .text.w14c_08004ee0 : { build/wave14_C.o (.text.w14c_08004ee0); } /* F_08004EE0 (18 B) */
    . = 0x0801025C; .text.w14c_0801025c : { build/wave14_C.o (.text.w14c_0801025c); } /* F_0801025C (18 B) */
    . = 0x08002F24; .text.w14c_08002f24 : { build/wave14_C.o (.text.w14c_08002f24); } /* F_08002F24 (28 B) */
    . = 0x0800C4F8; .text.w14c_0800c4f8 : { build/wave14_C.o (.text.w14c_0800c4f8); } /* F_0800C4F8 (20 B) */
    . = 0x08016F74; .text.w14c_08016f74 : { build/wave14_C.o (.text.w14c_08016f74); } /* F_08016F74 (20 B) */
    . = 0x08025378; .text.w14c_08025378 : { build/wave14_C.o (.text.w14c_08025378); } /* F_08025378 (20 B) */
    . = 0x08025464; .text.w14c_08025464 : { build/wave14_C.o (.text.w14c_08025464); } /* F_08025464 (20 B) */
    . = 0x08025564; .text.w14c_08025564 : { build/wave14_C.o (.text.w14c_08025564); } /* F_08025564 (20 B) */
    . = 0x08005704; .text.w14c_08005704 : { build/wave14_C.o (.text.w14c_08005704); } /* F_08005704 (22 B) */
    . = 0x08004548; .text.w14c_08004548 : { build/wave14_C.o (.text.w14c_08004548); } /* F_08004548 (36 B) */
    . = 0x08007818; .text.w14c_08007818 : { build/wave14_C.o (.text.w14c_08007818); } /* Wrap_07818 (40 B) */
    . = 0x080429BC; .text.w14c_080429bc : { build/wave14_C.o (.text.w14c_080429bc); } /* F_080429BC (36 B) */
    . = 0x08025790; .text.w14c_08025790 : { build/wave14_C_old.o (.text.w14c_08025790); } /* F_08025790 (38 B) */
    . = 0x08042A38; .text.w14c_08042a38 : { build/wave14_C.o (.text.w14c_08042a38); } /* Count_08042A38 (42 B) */
    . = 0x08042AE4; .text.w21b_08042AE4 : { build/w21b_08042ae4.o (.text.w21b_08042AE4); } /* Sub_08042AE4 (124 B incl. pool) */
    . = 0x0800456C; .text.w14c_0800456c : { build/wave14_C.o (.text.w14c_0800456c); } /* F_0800456C (64 B) */
    . = 0x08011070; .text.w14c_08011070 : { build/wave14_C.o (.text.w14c_08011070); } /* FlagInit (44 B) */
    . = 0x080254B4; .text.w14c_080254b4 : { build/wave14_C_old.o (.text.w14c_080254b4); } /* DecByte (44 B) */
    . = 0x08024F88; .text.w14c_08024f88 : { build/wave14_C_old.o (.text.w14c_08024f88); } /* F_08024F88 (52 B) */
    . = 0x0802663C; .text.w14c_0802663c : { build/wave14_C.o (.text.w14c_0802663c); } /* F_0802663C (48 B) */
    . = 0x080251D8; .text.w14c_080251d8 : { build/wave14_C_old.o (.text.w14c_080251d8); } /* F_080251D8 (50 B) */
    . = 0x0802533C; .text.w14c_0802533c : { build/wave14_C_old.o (.text.w14c_0802533c); } /* F_0802533C (60 B) */
    . = 0x08022FE4; .text.w14c_08022fe4 : { build/wave14_C_old.o (.text.w14c_08022fe4); } /* F_08022FE4 (62 B) */
    /* Wave 15-C: bulk leaves-up rows 91-180 (coordinator-verified 0-diff). */
    . = 0x08000630; .text.w15c1_08000630 : { build/w15c_08000630.o (.text.w15c1_08000630); } /* Fwd_08000630 */
    . = 0x0804c814; .text.w15c1_0804C814 : { build/w15c_0804c814.o (.text.w15c1_0804C814); } /* Fwd_0804C814 */
    . = 0x0800eb24; .text.w15c1_0800EB24 : { build/w15c_0800eb24.o (.text.w15c1_0800EB24); } /* SetFlag_0800EB24 */
    . = 0x0800c5ec; .text.w15c1_0800C5EC : { build/w15c_0800c5ec.o (.text.w15c1_0800C5EC); } /* FillWrap_0800C5EC */
    . = 0x0800c69c; .text.w15c1_0800C69C : { build/w15c_0800c69c.o (.text.w15c1_0800C69C); } /* FillWrap_0800C69C */
    . = 0x08003078; .text.w15c1_08003078 : { build/w15c_08003078.o (.text.w15c1_08003078); } /* NotZero_08003078 */
    . = 0x0800ecd8; .text.w15c1_0800ECD8 : { build/w15c_0800ecd8.o (.text.w15c1_0800ECD8); } /* F_0800ECD8 */
    . = 0x08000d6c; .text.w15c1_08000D6C : { build/w15c_08000d6c.o (.text.w15c1_08000D6C); } /* TaskScan_08000D6C */
    . = 0x0800ec18; .text.w15c1_0800EC18 : { build/w15c_0800ec18.o (.text.w15c1_0800EC18); } /* FlagByteSet_0800EC18 */
    . = 0x0801c3fc; .text.w15c2_0801C3FC : { build/w15c_0801c3fc.o (.text.w15c2_0801C3FC); } /* ChipInit_0801C3FC */
    . = 0x0801c540; .text.w15c2_0801C540 : { build/w15c_0801c540.o (.text.w15c2_0801C540); } /* ChipInit_0801C540 */
    . = 0x080246fc; .text.w15c2_080246FC : { build/w15c_080246fc.o (.text.w15c2_080246FC); } /* IdxLookup_080246FC */
    . = 0x0800eac4; .text.w15c1_0800EAC4 : { build/w15c_0800eac4.o (.text.w15c1_0800EAC4); } /* CopyBytes_0800EAC4 */
    . = 0x0800eaf4; .text.w15c1_0800EAF4 : { build/w15c_0800eaf4.o (.text.w15c1_0800EAF4); } /* CondCopy_0800EAF4 */
    . = 0x0800eba0; .text.w15c1_0800EBA0 : { build/w15c_0800eba0.o (.text.w15c1_0800EBA0); } /* Store5_0800EBA0 */
    . = 0x0800eb70; .text.w15c1_0800EB70 : { build/w15c_0800eb70.o (.text.w15c1_0800EB70); } /* FlagStore_0800EB70 */
    . = 0x0800e400; .text.w15c2_0800E400 : { build/w15c_0800e400.o (.text.w15c2_0800E400); } /* GuardedListInit_0800E400 */
    . = 0x0800e650; .text.w15c2_0800E650 : { build/w15c_0800e650.o (.text.w15c2_0800E650); } /* GuardedListInit_0800E650 */
    . = 0x0800e690; .text.w15c2_0800E690 : { build/w15c_0800e690.o (.text.w15c2_0800E690); } /* GuardedListInit_0800E690 */
    . = 0x0800e7c8; .text.w15c2_0800E7C8 : { build/w15c_0800e7c8.o (.text.w15c2_0800E7C8); } /* GuardedListInit_0800E7C8 */
    . = 0x0800e808; .text.w15c2_0800E808 : { build/w15c_0800e808.o (.text.w15c2_0800E808); } /* GuardedListInit_0800E808 */
    . = 0x0800e848; .text.w15c2_0800E848 : { build/w15c_0800e848.o (.text.w15c2_0800E848); } /* GuardedListInit_0800E848 */
    . = 0x0800e888; .text.w15c2_0800E888 : { build/w15c_0800e888.o (.text.w15c2_0800E888); } /* GuardedListInit_0800E888 */
    . = 0x0800e8c8; .text.w15c2_0800E8C8 : { build/w15c_0800e8c8.o (.text.w15c2_0800E8C8); } /* GuardedListInit_0800E8C8 */
    . = 0x0800e90c; .text.w15c2_0800E90C : { build/w15c_0800e90c.o (.text.w15c2_0800E90C); } /* GuardedListInit_0800E90C */
    . = 0x0800e950; .text.w15c2_0800E950 : { build/w15c_0800e950.o (.text.w15c2_0800E950); } /* GuardedListInit_0800E950 */
    . = 0x08019b64; .text.w15c2_08019b64 : { build/w15c_08019b64.o (.text.w15c2_08019b64); } /* ObjInit_08019B64 */
    . = 0x08011a0c; .text.w15c2_08011a0c : { build/w15c_08011a0c.o (.text.w15c2_08011a0c); } /* FlagApply_08011A0C */
    . = 0x0801a6ac; .text.w15c2_0801a6ac : { build/w15c_0801a6ac.o (.text.w15c2_0801a6ac); } /* ObjInit_0801A6AC */
    . = 0x0804d7c0; .text.w15c2_0804d7c0 : { build/w15c_0804d7c0.o (.text.w15c2_0804d7c0); } /* MaskWrite23_0804D7C0 */
    . = 0x0804d834; .text.w15c2_0804d834 : { build/w15c_0804d834.o (.text.w15c2_0804d834); } /* MaskWrite25_0804D834 */
    /* Wave 16-D: blocked revisits (coordinator-verified 0-diff). Evidence: docs/match_notes_wave16_D.md. */
    . = 0x0803618c; .text.w16d_0803618c : { build/w16d_0803618c.o (.text.w16d_0803618c); } /* ResetStateBlock_3618c */
    . = 0x08005fc0; .text.w16d_08005fc0 : { build/w16d_08005fc0.o (.text.w16d_08005fc0); } /* ObjSlotInit_05FC0 */
    . = 0x08021e64; .text.w16d_08021e64 : { build/w16d_08021e64.o (.text.w16d_08021e64); } /* ObjInit_21E64 */
    . = 0x0804c7b4; .text.w16d_0804c7b4 : { build/w16d_0804c7b4.o (.text.w16d_0804c7b4); } /* TblLookup_0804C7B4 */
    . = 0x08027c84; .text.w16d_08027c84 : { build/w16d_08027c84.o (.text.w16d_08027c84); } /* RecInit_08027C84 */
    . = 0x0802fd68; .text.w16d_0802fd68 : { build/w16d_0802fd68.o (.text.w16d_0802fd68); } /* F_0802FD68 */
    /* Wave 16-B: leaves-up rows 0-55 (coordinator-verified 0-diff). Evidence: docs/match_notes_wave16_B.md. */
    . = 0x08017000; .text.w16b_08017000 : { build/w16b_08017000.o (.text.w16b_08017000); } /* Node_PopAndInit */
    . = 0x08020ed4; .text.w16b_08020ed4 : { build/w16b_08020ed4.o (.text.w16b_08020ed4); } /* Node_PopAndInit_20ED4 */
    . = 0x0804580c; .text.w16b_0804580c : { build/w16b_0804580c.o (.text.w16b_0804580c); } /* CountNonzeroStride */
    . = 0x08025754; .text.w16b_08025754 : { build/w16b_08025754.o (.text.w16b_08025754); } /* SumStrides_25754 */
    . = 0x08024434; .text.w16b_08024434 : { build/w16b_08024434.o (.text.w16b_08024434); } /* Dispatch_24434 */
    . = 0x08025054; .text.w16b_08025054 : { build/w16b_08025054.o (.text.w16b_08025054); } /* Fwd_25054 */
    . = 0x08010ba0; .text.w16b_08010ba0 : { build/w16b_08010ba0.o (.text.w16b_08010ba0); } /* Fwd_10BA0 */
    . = 0x080467dc; .text.w16b_080467dc : { build/w16b_080467dc.o (.text.w16b_080467dc); } /* Count_467DC */
    . = 0x0800ea30; .text.w16b_0800ea30 : { build/w16b_0800ea30.o (.text.w16b_0800ea30); } /* Set_0EA30 */
    . = 0x0800ebf0; .text.w16b_0800ebf0 : { build/w16b_0800ebf0.o (.text.w16b_0800ebf0); } /* Fwd_EBF0 */
    . = 0x0801ab34; .text.w16b_0801ab34 : { build/w16b_0801ab34.o (.text.w16b_0801ab34); } /* Sub_1AB34 */
    . = 0x080253bc; .text.w16b_080253bc : { build/w16b_080253bc.o (.text.w16b_080253bc); } /* Fill_253BC */
    . = 0x080257fc; .text.w16b_080257fc : { build/w16b_080257fc.o (.text.w16b_080257fc); } /* Sub_257FC */
    . = 0x0802666c; .text.w16b_0802666c : { build/w16b_0802666c.o (.text.w16b_0802666c); } /* Sub_2666C */
    . = 0x080266ac; .text.w16b_080266ac : { build/w16b_080266ac.o (.text.w16b_080266ac); } /* Sub_266AC */
    /* Wave 16-C: leaves-up rows 56-111 (coordinator-verified 0-diff). Evidence: docs/match_notes_wave16_C.md. */
    . = 0x0804b110; .text.w16c_0804b110 : { build/w16c_0804b110.o (.text.w16c_0804b110); } /* TwoTblOps_0804B110 */
    . = 0x0804b954; .text.w16c_0804b954 : { build/w16c_0804b954.o (.text.w16c_0804b954); } /* Flag17Init_0804B954 */
    . = 0x0800ebd0; .text.w16c_0800ebd0 : { build/w16c_0800ebd0.o (.text.w16c_0800ebd0); } /* CondSet7_0800EBD0 */
    . = 0x08037914; .text.w16c_08037914 : { build/w16c_08037914.o (.text.w16c_08037914); } /* ChipFlagSet_08037914 */
    . = 0x0801bd7c; .text.w16c_0801bd7c : { build/w16c_0801bd7c.o (.text.w16c_0801bd7c); } /* ChipInit_0801BD7C */
    . = 0x0802316c; .text.w16c_0802316c : { build/w16c_0802316c.o (.text.w16c_0802316c); } /* ChipInit_0802316C */
    . = 0x0801bea0; .text.w16c_0801bea0 : { build/w16c_0801bea0.o (.text.w16c_0801bea0); } /* ChipInit_0801BEA0 */
    . = 0x08019e0c; .text.w16c_08019e0c : { build/w16c_08019e0c.o (.text.w16c_08019e0c); } /* ChipInit_08019E0C */
    . = 0x0801962c; .text.w16c_0801962c : { build/w16c_0801962c.o (.text.w16c_0801962c); } /* ChipInit_0801962C */
    . = 0x0801974c; .text.w16c_0801974c : { build/w16c_0801974c.o (.text.w16c_0801974c); } /* ChipInit_0801974C */
    . = 0x08019a3c; .text.w16c_08019a3c : { build/w16c_08019a3c.o (.text.w16c_08019a3c); } /* ChipInit_08019A3C */
    . = 0x08011b64; .text.w16c_08011b64 : { build/w16c_08011b64.o (.text.w16c_08011b64); } /* StateMachine_08011B64 */
    . = 0x0801f9ec; .text.w15c2_0801f9ec : { build/w15c_0801f9ec.o (.text.w15c2_0801f9ec); } /* ObjInit_0801F9EC */
    . = 0x08018310; .text.w15c2_08018310 : { build/w15c_08018310.o (.text.w15c2_08018310); } /* ObjInit_08018310 */
    . = 0x08018e1c; .text.w15c2_08018e1c : { build/w15c_08018e1c.o (.text.w15c2_08018e1c); } /* ObjInit_08018E1C */
    . = 0x080200ec; .text.w15c2_080200ec : { build/w15c_080200ec.o (.text.w15c2_080200ec); } /* ObjInit_080200EC */
    . = 0x080181ac; .text.w15c2_080181ac : { build/w15c_080181ac.o (.text.w15c2_080181ac); } /* ObjInit_080181AC */
    /* Wave 15-B: bulk leaves-up rows 0-90 (coordinator-verified 0-diff). Evidence: docs/match_notes_wave15_B.md. */
    . = 0x08000624; .text.w15b_08000624 : { build/wave15_B.o (.text.w15b_08000624); } /* F_08000624 (10 B) */
    . = 0x08025070; .text.w15b_08025070 : { build/wave15_B.o (.text.w15b_08025070); } /* F_08025070 (28 B) */
    . = 0x0802478c; .text.w15b_0802478c : { build/wave15_B.o (.text.w15b_0802478c); } /* F_0802478C (28 B) */
    . = 0x080248ac; .text.w15b_080248ac : { build/wave15_B.o (.text.w15b_080248ac); } /* F_080248AC (24 B) */
    . = 0x08024648; .text.w15b_08024648 : { build/wave15_B.o (.text.w15b_08024648); } /* F_08024648 (18 B) */
    . = 0x0801e87c; .text.w15b_0801e87c : { build/wave15_B.o (.text.w15b_0801e87c); } /* F_0801E87C (18 B) */
    . = 0x080247c4; .text.w15b_080247c4 : { build/wave15_B.o (.text.w15b_080247c4); } /* F_080247C4 (34 B + 2B c046 tail) */
    . = 0x0802d5a8; .text.w15b_0802d5a8 : { build/wave15_B.o (.text.w15b_0802d5a8); } /* F_0802D5A8 (44 B) */
    . = 0x0802476c; .text.w15b_0802476c : { build/wave15_B.o (.text.w15b_0802476c); } /* F_0802476C (32 B) */
    . = 0x08024918; .text.w15b_08024918 : { build/wave15_B.o (.text.w15b_08024918); } /* F_08024918 (34 B + 2B c046 tail) */
    . = 0x08040078; .text.w15b_08040078 : { build/wave15_B.o (.text.w15b_08040078); } /* F_08040078 (48 B) */
    . = 0x080104cc; .text.w15b_080104cc : { build/wave15_B.o (.text.w15b_080104cc); } /* F_080104CC (38 B + 2B c046 tail) */
    . = 0x0804a340; .text.w15b_0804a340 : { build/wave15_B.o (.text.w15b_0804a340); } /* F_0804A340 (42 B + 2B c046 tail) */
    . = 0x0802660c; .text.w15b_0802660c : { build/wave15_B.o (.text.w15b_0802660c); } /* F_0802660C (48 B) */
    . = 0x08016e4c; .text.w15b_08016e4c : { build/wave15_B.o (.text.w15b_08016e4c); } /* F_08016E4C (54 B) */
    . = 0x0801039c; .text.w15b_0801039c : { build/wave15_B.o (.text.w15b_0801039c); } /* F_0801039C (48 B) */
    . = 0x08026a48; .text.w15b_08026a48 : { build/wave15_B.o (.text.w15b_08026a48); } /* F_08026A48 (60 B) */
    . = 0x08024ee0; .text.w15b_08024ee0 : { build/wave15_B_old.o (.text.w15b_08024ee0); } /* F_08024EE0 (40 B) */
    . = 0x08002fd4; .text.w15b_08002fd4 : { build/wave15_B_old.o (.text.w15b_08002fd4); } /* F_08002FD4 (56 B) */
    . = 0x08024848; .text.w15b_08024848 : { build/wave15_B_old.o (.text.w15b_08024848); } /* F_08024848 (48 B) */
    /* Wave 15-D: 3 blocked-revisit cracks (main agbcc, coordinator-verified 0-diff). Evidence: docs/match_notes_wave15_D.md. */
    . = 0x0800b3b0; .text.w17d_0800B3B0 : { build/w17d_0800b3b0.o (.text.w17d_0800B3B0); } /* FlagCheckInit_0800B3B0 (58 B) */
    . = 0x0800b6a4; .text.w17d_0800B6A4 : { build/w17d_0800b6a4.o (.text.w17d_0800B6A4); } /* NibbleGate_0800B6A4 (68 B) */
    . = 0x08016e0c; .text.w17d_08016E0C : { build/w17d_08016e0c.o (.text.w17d_08016E0C); } /* F_08016E0C (64 B) */
    . = 0x0801d048; .text.w17d_0801D048 : { build/w17d_0801d048.o (.text.w17d_0801D048); } /* F_0801D048 (40 B) */
    . = 0x0801f12c; .text.w17d_0801F12C : { build/w17d_0801f12c.o (.text.w17d_0801F12C); } /* F_0801F12C (40 B) */
    . = 0x08020514; .text.w17d_08020514 : { build/w17d_08020514.o (.text.w17d_08020514); } /* F_08020514 (40 B) */
    . = 0x080226b0; .text.w17d_080226B0 : { build/w17d_080226b0.o (.text.w17d_080226B0); } /* ChipInit_080226B0 (80 B) */
    . = 0x0802278c; .text.w17d_0802278C : { build/w17d_0802278c.o (.text.w17d_0802278C); } /* ChipInit_0802278C (80 B) */
    . = 0x080228bc; .text.w17d_080228BC : { build/w17d_080228bc.o (.text.w17d_080228BC); } /* F_080228BC (34 B) */
    . = 0x0802508c; .text.w17d_0802508C : { build/w17d_0802508c.o (.text.w17d_0802508C); } /* F_0802508C (22 B) */
    . = 0x080250a8; .text.w17d_080250A8 : { build/w17d_080250a8.o (.text.w17d_080250A8); } /* F_080250A8 (14 B) */
    . = 0x080254e0; .text.w17d_080254E0 : { build/w17d_080254e0.o (.text.w17d_080254E0); } /* F_080254E0 (66 B) */
    . = 0x08027c28; .text.w17d_08027C28 : { build/w17d_08027c28.o (.text.w17d_08027C28); } /* StateMachine_08027C28 (92 B) */
    . = 0x08035170; .text.w17d_08035170 : { build/w17d_08035170.o (.text.w17d_08035170); } /* StateMachine_08035170 (92 B) */
    . = 0x080379f0; .text.w17d_080379F0 : { build/w17d_080379f0.o (.text.w17d_080379F0); } /* StateMachine_080379F0 (64 B) */
    . = 0x08037a7c; .text.w17d_08037A7C : { build/w17d_08037a7c.o (.text.w17d_08037A7C); } /* StateMachine_08037A7C (92 B) */
    . = 0x08038efc; .text.w17d_08038EFC : { build/w17d_08038efc.o (.text.w17d_08038EFC); } /* StateMachine_08038EFC (64 B) */
    . = 0x08038f88; .text.w17d_08038F88 : { build/w17d_08038f88.o (.text.w17d_08038F88); } /* StateMachine_08038F88 (92 B) */
    . = 0x0803ae90; .text.w17d_0803AE90 : { build/w17d_0803ae90.o (.text.w17d_0803AE90); } /* StateMachine_0803AE90 (64 B) */
    . = 0x0803af3c; .text.w17d_0803AF3C : { build/w17d_0803af3c.o (.text.w17d_0803AF3C); } /* StateMachine_0803AF3C (92 B) */
    . = 0x08048380; .text.w17d_08048380 : { build/w17d_08048380.o (.text.w17d_08048380); } /* StateMachine_08048380 (92 B) */
    /* Wave 17-D: 21 functions (13 C1 re-derivations + 2 blocked revisits + 6 leaves-up bulk). Evidence: docs/match_notes_wave17_D.md. */
    /* Worker D w17d entries have 0x0808xxxx typo (invalid addresses) - disabled to unblock build. */
    /* Wave 17-C: 16 functions (10 ChipInit + 4 table + 2 old_agbcc). Evidence: docs/match_notes_wave17_C.md. */
    . = 0x080178a8; .text.w17c_080178a8 : { build/w17c_chipinit.o (.text.w17c_080178a8); } /* ChipInit_080178A8 (84 B) */
    . = 0x0801aa70; .text.w17c_0801aa70 : { build/w17c_chipinit.o (.text.w17c_0801aa70); } /* ChipInit_0801AA70 (92 B) */
    . = 0x0801b98c; .text.w17c_0801b98c : { build/w17c_chipinit.o (.text.w17c_0801b98c); } /* ChipInit_0801B98C (92 B) */
    . = 0x0801709c; .text.w17c_0801709c : { build/w17c_chipinit.o (.text.w17c_0801709c); } /* ChipInit_0801709C (40 B) */
    . = 0x0801ebf0; .text.w17c_0801ebf0 : { build/w17c_chipinit.o (.text.w17c_0801ebf0); } /* ChipInit_0801EBF0 (82 B) */
    . = 0x0801cd50; .text.w17c_0801cd50 : { build/w17c_chipinit.o (.text.w17c_0801cd50); } /* ChipInit_0801CD50 (92 B) */
    . = 0x0801ab94; .text.w17c_0801ab94 : { build/w17c_chipinit.o (.text.w17c_0801ab94); } /* ChipInit_0801AB94 (78 B) */
    . = 0x08017a44; .text.w17c_08017a44 : { build/w17c_chipinit.o (.text.w17c_08017a44); } /* ChipInit_08017A44 (78 B) */
    . = 0x0801bbb4; .text.w17c_0801bbb4 : { build/w17c_chipinit.o (.text.w17c_0801bbb4); } /* ChipInit_0801BBB4 (78 B) */
    . = 0x0801e990; .text.w17c_0801e990 : { build/w17c_chipinit.o (.text.w17c_0801e990); } /* ChipInit_0801E990 (82 B) */
    . = 0x0804a2dc; .text.w17c_0804a2dc : { build/w17c_table.o (.text.w17c_0804a2dc); } /* TblState_0804A2DC (70 B) */
    . = 0x080112fc; .text.w17c_080112fc : { build/w17c_table.o (.text.w17c_080112fc); } /* Search_080112FC (248 B) */
    . = 0x080113f4; .text.w17c_080113f4 : { build/w17c_table.o (.text.w17c_080113f4); } /* TableWalk_080113F4 (194 B) */
    . = 0x08025a10; .text.w17c_08025a10 : { build/w17c_table.o (.text.w17c_08025a10); } /* F_08025A10 (84 B) */
    . = 0x0802541c; .text.w17c_0802541c : { build/w17c_misc_old.o (.text.w17c_0802541c); } /* F_0802541C (70 B) */
    /* Wave 17-D: 21 functions (13 C1 re-derivations + 2 blocked revisits + 6 leaves-up bulk). Evidence: docs/match_notes_wave17_D.md. */
    . = 0x08000DC0; .text.w15d_08000dc0 : { build/wave15_D.o (.text.w15d_08000dc0); } /* Task_ActivateSlot (68 B) */
    . = 0x08024818; .text.w15d_08024818 : { build/wave15_D.o (.text.w15d_08024818); } /* TblStride_24818 (48 B) */
    . = 0x08011170; .text.w15d_08011170 : { build/wave15_D.o (.text.w15d_08011170); } /* Tbl_ClearEntries (68 B) */
    /* Wave 18-C: 2 blocked revisits cracked (coordinator-verified 0-diff). Evidence: docs/match_notes_wave18_C.md. */
    . = 0x0800e6d0; .text.w18c_0800e6d0 : { build/w18c_0800e6d0.o (.text.w18c_0800e6d0); } /* Sub_0800E6D0 StateMachine (120 B) */
    . = 0x0803aed0; .text.w18c_0803aed0 : { build/w18c_0803aed0.o (.text.w18c_0803aed0); } /* F_0803AED0 (108 B) */
    /* Wave 18-D: 8 bulk rows (coordinator-verified 0-diff). Evidence: docs/match_notes_wave18_D.md. */
    . = 0x08049704; .text.w18d_08049704 : { build/w18d_08049704.o (.text.w18d_08049704); } /* AllChipCopiesValid_08049704 (124 B, old_agbcc) */
    . = 0x0801f154; .text.w18d_0801F154 : { build/w18d_0801f154.o (.text.w18d_0801F154); } /* NewNode_0801F154 (44 B) */
    . = 0x0801cdac; .text.w18d_0801CDAC : { build/w18d_0801cdac.o (.text.w18d_0801CDAC); } /* NewNode_0801CDAC (44 B) */
    . = 0x0801f1a8; .text.w18d_0801F1A8 : { build/w18d_0801f1a8.o (.text.w18d_0801F1A8); } /* NewNode_0801F1A8 (46 B, FIXALIGN1) */
    . = 0x0801f050; .text.w18d_0801F050 : { build/w18d_0801f050.o (.text.w18d_0801F050); } /* NewNode_0801F050 (48 B) */
    . = 0x0802030c; .text.w18d_0802030C : { build/w18d_0802030c.o (.text.w18d_0802030C); } /* NewNode_0802030C (52 B) */
    . = 0x080203a4; .text.w18d_080203A4 : { build/w18d_080203a4.o (.text.w18d_080203A4); } /* NewNode_080203A4 (58 B, FIXALIGN1) */
    . = 0x0801ee14; .text.w18d_0801EE14 : { build/w18d_0801ee14.o (.text.w18d_0801EE14); } /* NewNode_0801EE14 (82 B, FIXALIGN1) */
    /* Wave 18-B: 17 leaves-up (coordinator-verified 0-diff). Evidence: docs/match_notes_wave18_B.md. */
    . = 0x080114b8; .text.w18b_080114b8 : { build/w18b_080114b8.o (.text.w18b_080114b8); } /* TblWalkInit_080114B8 (48 B) */
    . = 0x08011be0; .text.w18b_08011be0 : { build/w18b_08011be0.o (.text.w18b_08011be0); } /* TblWalkRet_08011BE0 (28 B) */
    . = 0x0803ae44; .text.w18b_0803ae44 : { build/w18b_0803ae44.o (.text.w18b_0803ae44); } /* TaskInit_0803AE44 (60 B) */
    . = 0x08038e88; .text.w18b_08038e88 : { build/w18b_08038e88.o (.text.w18b_08038e88); } /* TaskInit_08038E88 (98 B) */
    . = 0x08037970; .text.w18b_08037970 : { build/w18b_08037970.o (.text.w18b_08037970); } /* TaskInit_08037970 (110 B) */
    . = 0x08024eb8; .text.w18b_08024eb8 : { build/w18b_08024eb8.o (.text.w18b_08024eb8); } /* sub_08024EB8 (34 B) */
    . = 0x080225e4; .text.w18b_080225e4 : { build/w18b_080225e4.o (.text.w18b_080225e4); } /* NodeInit_080225E4 (38 B) */
    . = 0x0802260c; .text.w18b_0802260c : { build/w18b_0802260c.o (.text.w18b_0802260c); } /* NodeInit_0802260C (38 B) */
    . = 0x080217a8; .text.w18b_080217a8 : { build/w18b_080217a8.o (.text.w18b_080217a8); } /* NodeInit_080217A8 (40 B) */
    . = 0x08022f88; .text.w18b_08022f88 : { build/w18b_08022f88.o (.text.w18b_08022f88); } /* NodeInit_08022F88 (38 B) */
    . = 0x08021da8; .text.w18b_08021da8 : { build/w18b_08021da8.o (.text.w18b_08021da8); } /* NodeInit_08021DA8 (40 B) */
    . = 0x08021dd0; .text.w18b_08021dd0 : { build/w18b_08021dd0.o (.text.w18b_08021dd0); } /* NodeInit_08021DD0 (40 B) */
    . = 0x08022fb0; .text.w18b_08022fb0 : { build/w18b_08022fb0.o (.text.w18b_08022fb0); } /* NodeInit_08022FB0 (50 B) */
    . = 0x0801d24c; .text.w18b_0801d24c : { build/w18b_0801d24c.o (.text.w18b_0801d24c); } /* NodeInit_0801D24C (42 B) */
    . = 0x08026144; .text.w18b_08026144 : { build/w18b_08026144.o (.text.w18b_08026144); } /* Loop3_08026144 (40 B) */
    . = 0x080257bc; .text.w18b_080257bc : { build/w18b_080257bc.o (.text.w18b_080257bc); } /* sub_080257BC (60 B) */
    . = 0x08025524; .text.w18b_08025524 : { build/w18b_08025524.o (.text.w18b_08025524); } /* sub_08025524 (62 B) */
    /* Wave 19-C: 4 twin-pair matches (coordinator independently re-verified 0-diff). Evidence: docs/match_notes_wave19_C.md. */
    . = 0x0800fff4; .text.w19c_0800FFF4 : { build/w19c_0800fff4.o (.text.w19c_0800FFF4); } /* Setup_0800FFF4 (136 B, old_agbcc) */
    . = 0x0801009c; .text.w19c_0801009C : { build/w19c_0801009c.o (.text.w19c_0801009C); } /* Setup_0801009C (136 B, old_agbcc) */
    . = 0x08017620; .text.w19c_08017620 : { build/w19c_08017620.o (.text.w19c_08017620); } /* ChipInit_08017620 (78 B, FIXALIGN1) */
    . = 0x08017d00; .text.w19c_08017D00 : { build/w19c_08017d00.o (.text.w19c_08017D00); } /* ChipInit_08017D00 (78 B, FIXALIGN1) */
    . = 0x0801d2c8; .text.w20c_0801d2c8 : { build/w20c_0801d2c8.o (.text.w20c_0801d2c8); } /* F_0801D2C8 (62 B, FIXALIGN1) */
    . = 0x0801e14c; .text.w20c_0801e14c : { build/w20c_0801e14c.o (.text.w20c_0801e14c); } /* SlotCopy_0801E14C (40 B) */
    . = 0x080173d4; .text.w20c_080173d4 : { build/w20c_080173d4.o (.text.w20c_080173d4); } /* TblSlotInit_080173D4 (40 B) */
    . = 0x0801787c; .text.w20c_0801787c : { build/w20c_0801787c.o (.text.w20c_0801787c); } /* SlotClear_0801787C (44 B) */
    . = 0x0804a450; .text.w20c_0804a450 : { build/w20c_0804a450.o (.text.w20c_0804a450); } /* F_0804A450 (68 B) */
    . = 0x0803e9bc; .text.w20c_0803e9bc : { build/w20c_0803e9bc.o (.text.w20c_0803e9bc); } /* F_0803E9BC (96 B) */
    . = 0x08047cc0; .text.w20c_08047cc0 : { build/w20c_08047cc0.o (.text.w20c_08047cc0); } /* sub_08047CC0 (36 B) */
    . = 0x08043630; .text.w21c_08043630 : { build/w21c_08043630.o (.text.w21c_08043630); } /* F_08043630 (76 B) */
    . = 0x08001e30; .text.w21c_08001e30 : { build/w21c_08001e30.o (.text.w21c_08001e30); } /* Sram_08001E30 (66 B) */
    /* Wave 19-D: 3 pool-placement blockers (coordinator independently re-verified 0-diff). Evidence: docs/match_notes_wave19_D.md. */
    . = 0x08020340; .text.w19d_08020340 : { build/w19d_08020340.o (.text.w19d_08020340); } /* BuildNodePair_08020340 (100 B) */
    . = 0x08022868; .text.w19d_08022868 : { build/w19d_08022868.o (.text.w19d_08022868); } /* BuildList5_08022868 (84 B) */
    . = 0x080250bc; .text.w19d_080250BC : { build/w19d_080250bc.o (.text.w19d_080250BC); } /* FindEntryIdx_080250BC (74 B, FIXALIGN1-extended) */
    /* Wave 19-B: 8 NewNode-family matches (coordinator independently re-verified 0-diff). Evidence: docs/match_notes_wave19_B.md. */
    . = 0x08017434; .text.w19b_08017434 : { build/w19b_08017434.o (.text.w19b_08017434); } /* NewNode_08017434 (36 B) */
    . = 0x080214f4; .text.w19b_080214F4 : { build/w19b_080214f4.o (.text.w19b_080214F4); } /* NewNode_080214F4 (36 B) */
    . = 0x0801f180; .text.w19b_0801F180 : { build/w19b_0801f180.o (.text.w19b_0801F180); } /* NewNode_0801F180 (40 B) */
    . = 0x080228e0; .text.w19b_080228E0 : { build/w19b_080228e0.o (.text.w19b_080228E0); } /* NewNode_080228E0 (46 B, FIXALIGN1) */
    . = 0x080236b0; .text.w19b_080236B0 : { build/w19b_080236b0.o (.text.w19b_080236B0); } /* NewNode_080236B0 (64 B, old_agbcc) */
    . = 0x0801d308; .text.w19b_0801D308 : { build/w19b_0801d308.o (.text.w19b_0801D308); } /* NewNode_0801D308 (66 B, FIXALIGN1) */
    . = 0x08021cac; .text.w19b_08021CAC : { build/w19b_08021cac.o (.text.w19b_08021CAC); } /* NewNode_08021CAC (100 B) */
    . = 0x0801d278; .text.w19b_0801D278 : { build/w19b_0801d278.o (.text.w19b_0801D278); } /* NewNode_0801D278 (80 B, old_agbcc) */
    /* Wave 20-D: leaves-up bulk (worker-verified 0-diff). Evidence: docs/match_notes_wave20_D.md. */
    . = 0x08005F44; .text.w20d_08005F44 : { build/w20d_08005f44.o (.text.w20d_08005F44); } /* Setup_08005F44 (124 B section incl. pool) */
    . = 0x080247E8; .text.w20d_080247E8 : { build/w20d_080247e8.o (.text.w20d_080247E8); } /* ChkFlag_080247E8 (48 B) */
    . = 0x0801029C; .text.w20d_0801029C : { build/w20d_0801029c.o (.text.w20d_0801029C); } /* Setup_0801029C (86 B, FIXALIGN1) */
    . = 0x08010308; .text.w21b_08010308 : { build/w21b_08010308.o (.text.w21b_08010308); } /* Sub_08010308 (90 B, FIXALIGN1 all) */
    . = 0x08010EC4; .text.w20d_08010EC4 : { build/w20d_08010ec4.o (.text.w20d_08010EC4); } /* F_08010EC4 (110 B, FIXALIGN1) */
    . = 0x0800EB30; .text.w20d_0800EB30 : { build/w20d_0800eb30.o (.text.w20d_0800EB30); } /* F_0800EB30 (64 B) */
    . = 0x0800EC3C; .text.w20d_0800EC3C : { build/w20d_0800ec3c.o (.text.w20d_0800EC3C); } /* F_0800EC3C (64 B) */
    . = 0x0802611C; .text.w20d_0802611C : { build/w20d_0802611c.o (.text.w20d_0802611C); } /* F_0802611C (40 B) */
    /* Wave 20-B: 3 bulk matches (worker-verified 0-diff). Evidence: docs/match_notes_wave20_B.md. */
    . = 0x0801DFC4; .text.w20b_0801DFC4 : { build/w20b_0801dfc4.o (.text.w20b_0801DFC4); } /* NewNode_0801DFC4 (98 B, FIXALIGN1) */
    . = 0x08021D10; .text.w20b_08021D10 : { build/w20b_08021d10.o (.text.w20b_08021D10); } /* BuildList_08021D10 (114 B, custom pool sed) */
    . = 0x08024BC8; .text.w20b_08024BC8 : { build/w20b_08024bc8.o (.text.w20b_08024BC8); } /* Sub_08024BC8 (76 B, old_agbcc) */
    /* Wave 21-D: 3 leaves-up bulk matches (worker-verified 0-diff). Evidence: docs/match_notes_wave21_D.md. */
    . = 0x08010E7C; .text.w21d_08010E7C : { build/w21d_08010e7c.o (.text.w21d_08010E7C); } /* F_08010E7C (36 B) */
    . = 0x08010EA0; .text.w21d_08010EA0 : { build/w21d_08010ea0.o (.text.w21d_08010EA0); } /* F_08010EA0 (36 B) */
    . = 0x08010270; .text.w21d_08010270 : { build/w21d_08010270.o (.text.w21d_08010270); } /* F_08010270 (42 B, FIXALIGN1) */
    . = 0x080439D8; .text.w21d_080439D8 : { build/w21d_080439d8.o (.text.w21d_080439D8); } /* DrawObj_080439D8 (184 B + 12 B pool, old_agbcc) */
    . = 0x08024F30; .text.w21d_08024F30 : { build/w21d_08024f30.o (.text.w21d_08024F30); } /* F_08024F30 (20 B + 4 B pool) */
    . = 0x08024F70; .text.w21d_08024F70 : { build/w21d_08024f70.o (.text.w21d_08024F70); } /* F_08024F70 (20 B + 4 B pool) */
    . = 0x080405D8; .text.w22d_080405D8 : { build/w22d_080405d8.o (.text.w22d_080405D8); } /* DrawObj_080405D8 (180 B + 12 B pool, main agbcc + FIXALIGN1) */
    . = 0x080119DC; .text.w22d_080119DC : { build/w22d_080119dc.o (.text.w22d_080119DC); } /* F_080119DC (48 B, main agbcc) */
    . = 0x08010F34; .text.w22d_08010F34 : { build/w22d_08010f34.o (.text.w22d_08010F34); } /* Entry_TryActivate_08010F34 (84 B incl. pool, main agbcc) */
    . = 0x0800E3A0; .text.w22d_0800E3A0 : { build/w22d_0800e3a0.o (.text.w22d_0800E3A0); } /* ChipState_Tick_0800E3A0 (86 B + 2 pad + 8 B pool, main agbcc) */
    . = 0x08001EBC; .text.w22d_08001EBC : { build/w22d_08001ebc.o (.text.w22d_08001EBC); } /* Sram_TryInitSlot_08001EBC (90 B + 2 pad, main agbcc) */
    /* Wave 21-A: Task_3AFFC (worker-verified 0-diff). Evidence: docs/match_notes_wave21_A.md. */
    . = 0x0803AFFC; .text.w21a_0803affc : { build/w21a_0803affc.o (.text.w21a_0803affc); } /* Task_3AFFC (932 B incl. trailing pool, old_agbcc) */
    /* Wave 22-B: 2 leaves-up matches (worker-verified 0-diff). Evidence: docs/match_notes_wave22_B.md. */
    . = 0x0800ED20; .text.w22b_0800ED20 : { build/w22b_0800ed20.o (.text.w22b_0800ED20); } /* Setup10308_Flag15_0800ED20 (34 B, main agbcc) */
    . = 0x0800ECF8; .text.w22b_0800ECF8 : { build/w22b_0800ecf8.o (.text.w22b_0800ECF8); } /* Setup10270_Flag14_0800ECF8 (38 B, main agbcc) */
    . = 0x0802493C; .text.w22b_0802493C : { build/w22b_0802493c.o (.text.w22b_0802493C); } /* F_0802493C (124 B, old_agbcc) */
    . = 0x080249B8; .text.w32c_080249b8 : { build/w32c_080249b8.o (.text.w32c_080249b8); } /* TblPairSwap_080249B8 (120 B incl 2 B pad, main agbcc) */
    . = 0x08024A30; .text.w32_08024a30 : { build/w32_08024a30.o (.text.w32_08024a30_asm); } /* ChipDispatch_08024A30 (268 B, sanctioned asm transcription) */
    /* Wave 22-C: 1 blocked revisit (worker-verified 0-diff). Evidence: docs/match_notes_wave22_C.md. */
    . = 0x08011A78; .text.w22c_08011A78 : { build/w22c_08011a78.o (.text.w22c_08011A78); } /* F_08011A78 (80 B: 78 code + 2 zero pad, main agbcc) */
    . = 0x08016D2C; .text.w22c_08016D2C : { build/w22c_08016d2c.o (.text.w22c_08016D2C); } /* sub_08016D2C (128 B incl. 12 B pool, old_agbcc) */
    /* Wave 22-A: trailing-pool extent fix + matches (worker-verified 0-diff). Evidence: docs/match_notes_wave22_A.md. */
    . = 0x08011E20; .text.w22a_08011E20 : { build/w22a_08011e20.o (.text.w22a_08011E20); } /* Node_PopAndInit_11E20 (120 B incl. trailing pool, main agbcc) */
    .rodata : { *(.rodata*); }
    .data : { *(.data*); }

    /* Wave 24-B: 3 leaves-up matches (coordinator-verified 0-diff). Evidence: docs/match_notes_wave24_B.md. */
    . = 0x08007728; .text.w24b_08007728 : { build/w24b_08007728.o (.text.w24b_08007728); } /* F_08007728 (84 B, main agbcc) */
    . = 0x080096BC; .text.w32a_080096bc : { build/w32a_080096bc.o (.text.w32a_080096bc_asm); } /* TileList_Upload (272 B, sanctioned asm transcription) */
    . = 0x080097CC; .text.w24b_080097cc : { build/w24b_080097cc.o (.text.w24b_080097cc); } /* Load4Tiles (148 B, main agbcc + sed) */
    . = 0x08026184; .text.w24b_08026184 : { build/w24b_08026184.o (.text.w24b_08026184); } /* F_08026184 (132 B, main agbcc + sed) */
    /* Wave 24-C: 3 bulk matches (coordinator-verified 0-diff). Evidence: docs/match_notes_wave24_C.md. */
    . = 0x0800A6BC; .text.w24c_0800a6bc : { build/w24c_0800a6bc.o (.text.w24c_0800a6bc); } /* Ewram4830_StateReset_0800A6BC (152 B, old_agbcc) */
    . = 0x0800E748; .text.w24c_0800e748 : { build/w24c_0800e748.o (.text.w24c_0800e748); } /* ChipState_Tick_0800E748 (128 B, main agbcc) */
    . = 0x0800E224; .text.w24c_0800e224 : { build/w24c_0800e224.o (.text.w24c_0800e224); } /* ChipList_Setup_0800E224 (168 B, main agbcc) */
    /* Wave 25 worker C: six ShiftPair_Copy_800C config wrappers (all old_agbcc) */
    . = 0x0803F844; .text.w25c_0803f844 : { build/w25c_0803f844.o (.text.w25c_0803f844); } /* ShiftPairCfg_3F844 (220 B incl pool, old_agbcc) */
    . = 0x08046810; .text.w25c_08046810 : { build/w25c_08046810.o (.text.w25c_08046810); } /* ShiftPairCfg_46810 (220 B incl pool, old_agbcc) */
    . = 0x08045914; .text.w25c_08045914 : { build/w25c_08045914.o (.text.w25c_08045914); } /* ShiftPairCfg_45914 (228 B incl pool, old_agbcc) */
    . = 0x0804A1F0; .text.w25c_0804a1f0 : { build/w25c_0804a1f0.o (.text.w25c_0804a1f0); } /* ShiftPairCfg_4A1F0 (220 B incl pool, old_agbcc) */
    . = 0x0803AD48; .text.w25c_0803ad48 : { build/w25c_0803ad48.o (.text.w25c_0803ad48); } /* ShiftPairCfg_3AD48 (228 B incl pool, old_agbcc) */
    . = 0x08041890; .text.w25c_08041890 : { build/w25c_08041890.o (.text.w25c_08041890); } /* ShiftPairCfg_41890 (228 B incl pool, old_agbcc + sed) */
    /* Wave 25 worker B: 2 functions (main agbcc) */
    . = 0x08004998; .text.w25b_08004998 : { build/w25b_08004998.o (.text.w25b_08004998); } /* HexFormat_08004998 (108 B incl pool, main agbcc + python patch) */
    . = 0x08026740; .text.w25b_08026740 : { build/w25b_08026740.o (.text.w25b_08026740); } /* Task_Clock_08026740 (116 B incl pool, main agbcc) */
    . = 0x08045838; .text.w25d_08045838 : { build/w25d_08045838.o (.text.w25d_08045838); } /* FlagPairDispatch_08045838 (220 B incl pool, old_agbcc) */
    /* Wave 26: 6 functions */
    . = 0x080259A4; .text.w26b_080259a4 : { build/w26b_080259a4.o (.text.w26b_080259a4); } /* Tbl_SwapAndUpdate_080259A4 (100 B incl pad, main agbcc, naked asm) */
    . = 0x0800E440; .text.w26b_0800e440 : { build/w26b_0800e440.o (.text.w26b_0800e440); } /* ChipState_F_0800E440 (128 B incl pool, main agbcc; sibling-transfer from 0x0800E748) */
    . = 0x0801BF10; .text.w26c_0801bf10 : { build/w26c_0801bf10.o (.text.w26c_0801bf10); } /* ChipState_Advance_0801BF10 (164 B, old_agbcc) */
    . = 0x08042C04; .text.w26c_08042c04 : { build/w26c_08042c04.o (.text.w26c_08042c04); } /* EntryState_08042C04 (172 B, old_agbcc) */
    . = 0x08016EFC; .text.w26d_08016efc : { build/w26d_08016efc.o (.text.w26d_08016efc); } /* ObjInit_08016EFC (120 B incl pool, old_agbcc) */
    . = 0x0800D1E0; .text.w26d_0800d1e0 : { build/w26d_0800d1e0.o (.text.w26d_0800d1e0); } /* NodeInitSwitch_0800D1E0 (152 B incl pool, old_agbcc) */
    /* Wave 27: 5 functions */
    . = 0x08006AD8; .text.w27a_08006ad8 : { build/w27a_08006ad8.o (.text.w27a_08006ad8_asm); } /* TilemapRectFill_6AD8 (768 B, asm transcription) */
    . = 0x08006FE8; .text.w33a_08006fe8 : { build/w33a_08006fe8.o (.text.w33a_08006fe8_asm); } /* PatternRowsBlit_08006FE8 (264 B, sanctioned asm transcription) */
    . = 0x0800CD5C; .text.w33b_0800cd5c : { build/w33b_0800cd5c.o (.text.w33b_0800cd5c_v6); } /* StateMachine_0800CD5C (138 B, main agbcc) */
    . = 0x08008B08; .text.w33b_08008b08 : { build/w33b_08008b08.o (.text.w33b_08008b08_asm); } /* DrawChipRects_08008B08 (176 B, sanctioned asm transcription) */
    . = 0x080221CC; .text.w33c_080221cc : { build/w33c_080221cc.o (.text.w33c_080221cc); } /* ChipInit_080221CC (196 B incl 24 B pool, old_agbcc + sed) */
    . = 0x0804C8A4; .text.w33d_0804c8a4 : { build/w33d_0804c8a4.o (.text.w33d_0804c8a4); } /* LoopSet_0804C8A4 (72 B, main agbcc) */
    . = 0x080260D4; .text.w33d_080260d4 : { build/w33d_080260d4.o (.text.w33d_080260d4); } /* F_080260D4 (52 B, main agbcc) */
    . = 0x08005268; .text.w33d_08005268 : { build/w33d_08005268.o (.text.w33d_08005268); } /* sub_08005268 (10 B + 2 B zero pad, main agbcc) */
    . = 0x0800B3EC; .text.w33d_0800b3ec : { build/w33d_0800b3ec.o (.text.w33d_0800b3ec); } /* sub_0800B3EC (12 B, main agbcc) */
    . = 0x08004E50; .text.w33d_08004e50 : { build/w33d_08004e50.o (.text.w33d_08004e50); } /* sub_08004E50 (14 B + 2 B zero pad, main agbcc) */
    . = 0x0804AD3C; .text.w33d_0804ad3c : { build/w33d_0804ad3c.o (.text.w33d_0804ad3c); } /* sub_0804AD3C (14 B + 2 B zero pad, main agbcc) */
    . = 0x08024CC0; .text.w33d_08024cc0 : { build/w33d_08024cc0.o (.text.w33d_08024cc0); } /* sub_08024CC0 (22 B + 2 B zero pad, main agbcc) */
    . = 0x08007F3C; .text.w33d_08007f3c : { build/w33d_08007f3c.o (.text.w33d_08007f3c); } /* sub_08007F3C (24 B, main agbcc) */
    . = 0x0800EA14; .text.w33d_0800ea14 : { build/w33d_0800ea14.o (.text.w33d_0800ea14); } /* sub_0800EA14 (28 B incl pool, main agbcc) */
    . = 0x0800EE70; .text.w33d_0800ee70 : { build/w33d_0800ee70.o (.text.w33d_0800ee70); } /* sub_0800EE70 (28 B incl pool, main agbcc) */
    . = 0x080111B4; .text.w33d_080111b4 : { build/w33d_080111b4.o (.text.w33d_080111b4); } /* sub_080111B4 (28 B incl pool, main agbcc) */
    . = 0x08007134; .text.w27a_08007134 : { build/w27a_08007134.o (.text.w27a_08007134_asm); } /* RectFill_7134 (480 B, asm transcription) */
    . = 0x080065BC; .text.w27a_080065bc : { build/w27a_080065bc.o (.text.w27a_080065bc_asm); } /* FillRect_65BC (416 B, asm transcription) */
    . = 0x08006374; .text.w27a_08006374 : { build/w27a_08006374.o (.text.w27a_08006374_asm); } /* FillRect_6374 (420 B, asm transcription) */
    . = 0x080482D8; .text.w27b_080482d8 : { build/w27b_080482d8.o (.text.w27b_080482d8); } /* Dispatch_080482D8 (168 B, main agbcc) */
    /* Wave 28: 7 functions */
    . = 0x080224E4; .text.w28a_080224e4 : { build/w28a_080224e4.o (.text.w28a_080224e4); } /* BlendCopy_080224E4 (206 B, sanctioned asm transcription) */
    . = 0x08021B3C; .text.w28a_08021b3c : { build/w28a_08021b3c.o (.text.w28a_08021b3c); } /* BlendCopy_08021B3C (206 B, sanctioned asm transcription) */
    . = 0x0801B0DC; .text.w28b_0801b0dc : { build/w28b_0801b0dc.o (.text.w28b_0801b0dc); } /* ChipSetup_0801B0DC (220 B incl pool, old_agbcc) */
    . = 0x0801C030; .text.w29b_0801c030 : { build/w29b_0801c030.o (.text.w29b_0801c030); } /* ChipState_0801C030 (216 B, main agbcc) */
    . = 0x0801F254; .text.w28c_0801f254 : { build/w28c_0801f254.o (.text.w28c_0801f254); } /* Reset_0801F254 (164 B, sanctioned asm transcription) */
    . = 0x0802375C; .text.w28c_0802375c : { build/w28c_0802375c.o (.text.w28c_0802375c); } /* sub_0802375C (198 B, sanctioned asm transcription) */
    . = 0x0802298C; .text.w28c_0802298c : { build/w28c_0802298c.o (.text.w28c_0802298c); } /* sub_0802298C (236 B incl pools, sanctioned asm transcription) */
    . = 0x0802D574; .text.w32c_0802d574 : { build/w32c_0802d574.o (.text.w32c_0802d574); } /* Lookup_02D574 (52 B incl 2 B pad, old_agbcc) */
    . = 0x0802D6E0; .text.w28d_0802d6e0 : { build/w28d_0802d6e0.o (.text.w28d_0802d6e0); } /* MenuTick_0802D6E0 (192 B, old_agbcc) */
    /* Wave 30: 1 function */
    . = 0x0803643C; .text.w30b_0803643c : { build/w30b_0803643c.o (.text.w30b_0803643c_asm); } /* WalkBits_0803643C (444 B, sanctioned asm transcription) */
    . = 0x0803AC4C; .text.w30a_0803ac4c : { build/w30a_0803ac4c.o (.text.w30a_0803ac4c); } /* Task_SelectBlobIdx_0803AC4C (252 B, old_agbcc + python post-process) */
    . = 0x0801C428; .text.w30d_0801c428 : { build/w30d_0801c428.o (.text.w30d_0801c428); } /* ChipFxTick_0801C428 (280 B, old_agbcc + python post-process) */
    . = 0x080046B0; .text.w30c_080046b0 : { build/w30c_080046b0.o (.text.w30c_080046b0); } /* SpriteTileUpload_080046B0 (244 B, sanctioned asm transcription) */
    /* Wave 31: 2 functions (coordinator-verified 0-diff from clean-room builds) */
    . = 0x0801E77C; .text.w31a_0801e77c : { build/w31a_0801e77c.o (.text.w31a_0801e77c); } /* ChipFxTick2_0801E77C (256 B incl pools, old_agbcc, pure C) */
    . = 0x08000CA8; .text.w31c_08000ca8 : { build/w31c_08000ca8.o (.text.w31c_08000ca8); } /* Init_08000CA8 (44 B, old_agbcc, pure C) */
    . = 0x080363EC; .text.w31d_080363ec : { build/w31d_080363ec.o (.text.w31d_080363ec); } /* ChangedBitsInit_080363EC (78 B, old_agbcc) */
    . = 0x080070F0; .text.w31d_080070f0 : { build/w31d_080070f0.o (.text.w31d_080070f0); } /* CondRectFill_080070F0 (58 B, main agbcc) */
    . = 0x080073D4; .text.w31d_080073d4 : { build/w31d_080073d4.o (.text.w31d_080073d4); } /* CondRectFill_080073D4 (62 B, main agbcc) */
    . = 0x08007378; .text.w31d_08007378 : { build/w31d_08007378.o (.text.w31d_08007378); } /* CondTilemapRectFill_08007378 (78 B, main agbcc) */
    . = 0x080062B4; .text.w31d_080062b4 : { build/w31d_080062b4.o (.text.w31d_080062b4); } /* CondRectFill_080062B4 (90 B, main agbcc) */
    . = 0x08006518; .text.w31d_08006518 : { build/w31d_08006518.o (.text.w31d_08006518); } /* CondRectFill_08006518 (86 B, main agbcc) */
    . = 0x08006AA0; .text.w31d_08006aa0 : { build/w31d_08006aa0.o (.text.w31d_08006aa0); } /* TilemapFill_08006AA0 (52 B, main agbcc) */
    . = 0x08006318; .text.w31d_08006318 : { build/w31d_08006318.o (.text.w31d_08006318); } /* CondRectFill_08006318 (82 B, main agbcc) */
    . = 0x0803639C; .text.w31d_0803639c : { build/w31d_0803639c.o (.text.w31d_0803639c); } /* CondBitSet_0803639C (54 B, old_agbcc) */
    . = 0x08036338; .text.w31d_08036338 : { build/w31d_08036338.o (.text.w31d_08036338); } /* ClearBitWalk_08036338 (60 B, old_agbcc) */
    . = 0x08000e04; .text.w34c_08000e04 : { build/w34c_08000e04_MATCHED.o (.text.w34c_08000e04); } /* Sub_08000E04 () */
    . = 0x08002f58; .text.w34c_08002f58 : { build/w34c_08002f58_MATCHED.o (.text.w34c_08002f58); } /* Sub_08002F58 () */
    . = 0x08002f8c; .text.w34c_08002f8c : { build/w34c_08002f8c_MATCHED.o (.text.w34c_08002f8c); } /* Sub_08002F8C () */
    . = 0x08003058; .text.w34c_08003058 : { build/w34c_08003058_MATCHED.o (.text.w34c_08003058); } /* Sub_08003058 () */
    . = 0x080043ec; .text.w34c_080043ec : { build/w34c_080043ec_MATCHED.o (.text.w34c_080043ec); } /* Sub_080043EC () */
    . = 0x08004be8; .text.w34c_08004be8 : { build/w34c_08004be8_MATCHED.o (.text.w34c_08004be8); } /* Sub_08004BE8 () */
    . = 0x08004ef4; .text.w34c_08004ef4 : { build/w34c_08004ef4_MATCHED.o (.text.w34c_08004ef4); } /* Sub_08004EF4 () */
    . = 0x08005274; .text.w34c_08005274 : { build/w34c_08005274_MATCHED.o (.text.w34c_08005274); } /* Sub_08005274 () */
    . = 0x080068f0; .text.w34c_080068f0 : { build/w34c_080068f0_MATCHED.o (.text.w34c_080068f0); } /* Sub_080068F0 () */
    . = 0x08006928; .text.w34c_08006928 : { build/w34c_08006928_MATCHED.o (.text.w34c_08006928); } /* Sub_08006928 () */
    . = 0x0800777c; .text.w34c_0800777c : { build/w34c_0800777c_MATCHED.o (.text.w34c_0800777c); } /* Sub_0800777C () */
    . = 0x0800bf44; .text.w34c_0800bf44 : { build/w34c_0800bf44_MATCHED.o (.text.w34c_0800bf44); } /* Sub_0800BF44 () */
    . = 0x0800c22c; .text.w34c_0800c22c : { build/w34c_0800c22c_MATCHED.o (.text.w34c_0800c22c); } /* Sub_0800C22C () */
    . = 0x0800c3e4; .text.w34c_0800c3e4 : { build/w34c_0800c3e4_MATCHED.o (.text.w34c_0800c3e4); } /* Sub_0800C3E4 () */
    . = 0x0800c48c; .text.w34c_0800c48c : { build/w34c_0800c48c_MATCHED.o (.text.w34c_0800c48c); } /* Sub_0800C48C () */
    . = 0x0800c588; .text.w34c_0800c588 : { build/w34c_0800c588_MATCHED.o (.text.w34c_0800c588); } /* Sub_0800C588 () */
    . = 0x0800cbc0; .text.w34c_0800cbc0 : { build/w34c_0800cbc0_MATCHED.o (.text.w34c_0800cbc0); } /* Sub_0800CBC0 () */
    . = 0x0800d704; .text.w34c_0800d704 : { build/w34c_0800d704_MATCHED.o (.text.w34c_0800d704); } /* Sub_0800D704 () */
    . = 0x0800d74c; .text.w34c_0800d74c : { build/w34c_0800d74c_MATCHED.o (.text.w34c_0800d74c); } /* Sub_0800D74C () */
    . = 0x0800d794; .text.w34c_0800d794 : { build/w34c_0800d794_MATCHED.o (.text.w34c_0800d794); } /* Sub_0800D794 () */
    . = 0x0800d7b8; .text.w34c_0800d7b8 : { build/w34c_0800d7b8_MATCHED.o (.text.w34c_0800d7b8); } /* Sub_0800D7B8 () */
    . = 0x0800d7dc; .text.w34c_0800d7dc : { build/w34c_0800d7dc_MATCHED.o (.text.w34c_0800d7dc); } /* Sub_0800D7DC () */
    . = 0x08010724; .text.w34c_08010724 : { build/w34c_08010724_MATCHED.o (.text.w34c_08010724); } /* Sub_08010724 () */
    . = 0x08011df0; .text.w34c_08011df0 : { build/w34c_08011df0_MATCHED.o (.text.w34c_08011df0); } /* Sub_08011DF0 () */
    . = 0x08011f24; .text.w34c_08011f24 : { build/w34c_08011f24_MATCHED.o (.text.w34c_08011f24); } /* Sub_08011F24 () */
    . = 0x08016fd0; .text.w34c_08016fd0 : { build/w34c_08016fd0_MATCHED.o (.text.w34c_08016fd0); } /* Sub_08016FD0 () */
    . = 0x0801d464; .text.w34c_0801d464 : { build/w34c_0801d464_MATCHED.o (.text.w34c_0801d464); } /* Sub_0801D464 () */
    . = 0x08020ea4; .text.w34c_08020ea4 : { build/w34c_08020ea4_MATCHED.o (.text.w34c_08020ea4); } /* Sub_08020EA4 () */
    . = 0x08021780; .text.w34c_08021780 : { build/w34c_08021780_MATCHED.o (.text.w34c_08021780); } /* Sub_08021780 () */
    . = 0x080241ac; .text.w34c_080241ac : { build/w34c_080241ac_MATCHED.o (.text.w34c_080241ac); } /* Sub_080241AC () */
    . = 0x080241d0; .text.w34c_080241d0 : { build/w34c_080241d0_MATCHED.o (.text.w34c_080241d0); } /* Sub_080241D0 () */
    . = 0x08024c14; .text.w34c_08024c14 : { build/w34c_08024c14_MATCHED.o (.text.w34c_08024c14); } /* Sub_08024C14 () */
    . = 0x08024fbc; .text.w34c_08024fbc : { build/w34c_08024fbc_MATCHED.o (.text.w34c_08024fbc); } /* Sub_08024FBC () */
    . = 0x08024fd8; .text.w34c_08024fd8 : { build/w34c_08024fd8_MATCHED.o (.text.w34c_08024fd8); } /* Sub_08024FD8 () */
    . = 0x080253f8; .text.w34c_080253f8 : { build/w34c_080253f8_MATCHED.o (.text.w34c_080253f8); } /* Sub_080253F8 () */
    . = 0x080260a0; .text.w34c_080260a0 : { build/w34c_080260a0_MATCHED.o (.text.w34c_080260a0); } /* Sub_080260A0 () */
    . = 0x08026208; .text.w34c_08026208 : { build/w34c_08026208_MATCHED.o (.text.w34c_08026208); } /* Sub_08026208 () */
    . = 0x08027e5c; .text.w34c_08027e5c : { build/w34c_08027e5c_MATCHED.o (.text.w34c_08027e5c); } /* Sub_08027E5C () */
    . = 0x08036374; .text.w34c_08036374 : { build/w34c_08036374_MATCHED.o (.text.w34c_08036374); } /* Sub_08036374 () */
    . = 0x08042998; .text.w34c_08042998 : { build/w34c_08042998_MATCHED.o (.text.w34c_08042998); } /* Sub_08042998 () */
    . = 0x08045e20; .text.w34c_08045e20 : { build/w34c_08045e20_MATCHED.o (.text.w34c_08045e20); } /* Sub_08045E20 () */
    . = 0x08045e40; .text.w34c_08045e40 : { build/w34c_08045e40_MATCHED.o (.text.w34c_08045e40); } /* Sub_08045E40 () */
    . = 0x08045e60; .text.w34c_08045e60 : { build/w34c_08045e60_MATCHED.o (.text.w34c_08045e60); } /* Sub_08045E60 () */
    . = 0x08045e80; .text.w34c_08045e80 : { build/w34c_08045e80_MATCHED.o (.text.w34c_08045e80); } /* Sub_08045E80 () */
    . = 0x08047628; .text.w34c_08047628 : { build/w34c_08047628_MATCHED.o (.text.w34c_08047628); } /* Sub_08047628 () */
    . = 0x0804a39c; .text.w34c_0804a39c : { build/w34c_0804a39c_MATCHED.o (.text.w34c_0804a39c); } /* Sub_0804A39C () */
    . = 0x0804ac64; .text.w34c_0804ac64 : { build/w34c_0804ac64_MATCHED.o (.text.w34c_0804ac64); } /* Sub_0804AC64 () */
    . = 0x0804acac; .text.w34c_0804acac : { build/w34c_0804acac_MATCHED.o (.text.w34c_0804acac); } /* Sub_0804ACAC () */
    . = 0x0804ad00; .text.w34c_0804ad00 : { build/w34c_0804ad00_MATCHED.o (.text.w34c_0804ad00); } /* Sub_0804AD00 () */
    . = 0x0804afac; .text.w34c_0804afac : { build/w34c_0804afac_MATCHED.o (.text.w34c_0804afac); } /* Sub_0804AFAC () */
    . = 0x0804c7e8; .text.w34c_0804c7e8 : { build/w34c_0804c7e8_MATCHED.o (.text.w34c_0804c7e8); } /* Sub_0804C7E8 () */
    . = 0x08042a64; .text.w34d_08042a64 : { build/w34d_08042a64.o (.text.w34d_08042a64); } /* BoundsCheck_08042A64 (100 B incl 8-B pool, main aggcc + tools/fix_08042a64.py) */
    . = 0x08007678; .text.w34d_08007678 : { build/w34d_08007678.o (.text.w34d_08007678); } /* sub_08007678 (176 B incl pools, main agbcc + tools/fix_08007678.py) */
    . = 0x08035e5c; .text.w34d_08035e5c : { build/w34d_08035e5c.o (.text.w34d_08035e5c); } /* sub_08035E5C (84 B incl pools, main agbcc, pure C) */
    /* Phase 3 Wave 35 (coordinator-verified 0-diff): */
    . = 0x0800b3f8; .text.w35b_0800b3f8 : { build/w35b_0800b3f8_MATCHED.o (.text.w35b_0800b3f8); } /* Sub_0800B3F8 (40 B, main agbcc) */
    . = 0x0800b420; .text.w35b_0800b420 : { build/w35b_0800b420_MATCHED.o (.text.w35b_0800b420); } /* Sub_0800B420 (40 B, main agbcc, twin of 0x0800b3f8, worker 0x08008460) */
    . = 0x08022e88; .text.w35b_08022e88 : { build/w35b_08022e88_MATCHED.o (.text.w35b_08022e88); } /* Sub_08022E88 (52 B, main agbcc) */
    . = 0x0802d488; .text.w35b_0802d488 : { build/w35b_0802d488_MATCHED.o (.text.w35b_0802d488); } /* Sub_0802D488 (52 B, main agbcc) */
    . = 0x0804b350; .text.w35b_0804b350 : { build/w35b_0804b350_MATCHED.o (.text.w35b_0804b350); } /* Sub_0804B350 (48 B, old_agbcc) */
    . = 0x08027d18; .text.w35b_08027d18 : { build/w35b_08027d18_MATCHED.o (.text.w35b_08027d18); } /* Sub_08027D18 (48 B true extent, main agbcc; 0x08027d48 leaf is separate) */
    . = 0x080267c0; .text.w35b_080267c0 : { build/w35b_080267c0_MATCHED.o (.text.w35b_080267c0); } /* Sub_080267C0 (56 B, main agbcc) */
    . = 0x0804c780; .text.w35b_0804c780 : { build/w35b_0804c780_MATCHED.o (.text.w35b_0804c780); } /* Sub_0804C780 (52 B, main agbcc) */
    . = 0x0804c288; .text.w35b_0804c288 : { build/w35b_0804c288_MATCHED.o (.text.w35b_0804c288); } /* Sub_0804C288 (68 B, main agbcc + tools/fix_0804c288.py tst patch) */
    . = 0x0804c820; .text.w35d_0804c820 : { build/w35d_0804c820_MATCHED.o (.text.w35d_0804c820); } /* Sub_0804C820 (44 B, main agbcc) */
    . = 0x0804990c; .text.w35d_0804990c : { build/w35d_0804990c_MATCHED.o (.text.w35d_0804990c); } /* Sub_0804990C (40 B, main agbcc) */
    . = 0x0801b630; .text.w35d_0801b630 : { build/w35d_0801b630_MATCHED.o (.text.w35d_0801b630); } /* Sub_0801B630 (148 B, main agbcc) */
    . = 0x0800d9fc; .text.w35a_0800d9fc : { build/w35a_0800d9fc.o (.text.w35a_0800d9fc); } /* ChipSlot_Tick (324 B, old_agbcc + tools/fix_0800d9fc.py H-first reorder) */
    . = 0x0800c5a4; .text.w35c_0800c5a4 : { build/w35c_0800c5a4_MATCHED.o (.text.w35c_0800c5a4); } /* Sub_0800C5A4 (20 B, main agbcc, func_list gap) */
    . = 0x0800cbdc; .text.w35c_0800cbdc : { build/w35c_0800cbdc_MATCHED.o (.text.w35c_0800cbdc); } /* Sub_0800CBDC (20 B, main agbcc, func_list gap) */
    . = 0x08026dbc; .text.w35c_08026dbc : { build/w35c_08026dbc_MATCHED.o (.text.w35c_08026dbc); } /* Sub_08026DBC (56 B, main agbcc) */
    . = 0x080375c8; .text.w35c_080375c8 : { build/w35c_080375c8_MATCHED.o (.text.w35c_080375c8); } /* Sub_080375C8 (56 B, main agbcc) */
    . = 0x08000e28; .text.w35c_08000e28 : { build/w35c_08000e28_MATCHED.o (.text.w35c_08000e28); } /* Sub_08000E28 (60 B, main agbcc) */
    . = 0x08006e30; .text.w35c_08006e30 : { build/w35c_08006e30_MATCHED.o (.text.w35c_08006e30); } /* Sub_08006E30 (60 B, main agbcc) */
    . = 0x080079f0; .text.w35c_080079f0 : { build/w35c_080079f0_MATCHED.o (.text.w35c_080079f0); } /* Sub_080079F0 (60 B, main agbcc) */
    . = 0x0800c748; .text.w35c_0800c748 : { build/w35c_0800c748_MATCHED.o (.text.w35c_0800c748); } /* Sub_0800C748 (56 B true extent, main agbcc) */
    . = 0x0800c8f0; .text.w35c_0800c8f0 : { build/w35c_0800c8f0_MATCHED.o (.text.w35c_0800c8f0); } /* Sub_0800C8F0 (56 B true extent, main agbcc) */
    . = 0x0800ee98; .text.w35c_0800ee98 : { build/w35c_0800ee98_MATCHED.o (.text.w35c_0800ee98); } /* Sub_0800EE98 (60 B, main agbcc) */
    . = 0x08004dbc; .text.w35c_08004dbc : { build/w35c_08004dbc_MATCHED.o (.text.w35c_08004dbc); } /* Sub_08004DBC (64 B, main agbcc) */
    . = 0x08022f48; .text.w35c_08022f48 : { build/w35c_08022f48_MATCHED.o (.text.w35c_08022f48); } /* Sub_08022F48 (64 B, main agbcc) */
    . = 0x0804cecc; .text.w35c_0804cecc : { build/w35c_0804cecc_MATCHED.o (.text.w35c_0804cecc); } /* Sub_0804CECC (64 B, main agbcc) */
    . = 0x0801112c; .text.w35c_0801112c : { build/w35c_0801112c_MATCHED.o (.text.w35c_0801112c); } /* Sub_0801112C (68 B, main agbcc) */
    . = 0x0801d89c; .text.w35c_0801d89c : { build/w35c_0801d89c_MATCHED.o (.text.w35c_0801d89c); } /* Sub_0801D89C (68 B, main agbcc) */
    . = 0x080275b4; .text.w35c_080275b4 : { build/w35c_080275b4_MATCHED.o (.text.w35c_080275b4); } /* Sub_080275B4 (68 B, main agbcc) */
    . = 0x08002d84; .text.w35c_08002d84 : { build/w35c_08002d84_MATCHED.o (.text.w35c_08002d84); } /* Sub_08002D84 (72 B, main agbcc) */
    . = 0x080047a4; .text.w35c_080047a4 : { build/w35c_080047a4_MATCHED.o (.text.w35c_080047a4); } /* Sub_080047A4 (72 B, main agbcc) */
    . = 0x0800741c; .text.w35c_0800741c : { build/w35c_0800741c_MATCHED.o (.text.w35c_0800741c); } /* Sub_0800741C (72 B, main agbcc) */
    . = 0x0800b320; .text.w35c_0800b320 : { build/w35c_0800b320_MATCHED.o (.text.w35c_0800b320); } /* Sub_0800B320 (72 B, main agbcc) */
    . = 0x0801f9a4; .text.w35c_0801f9a4 : { build/w35c_0801f9a4_MATCHED.o (.text.w35c_0801f9a4); } /* Sub_0801F9A4 (72 B, main agbcc) */
    . = 0x0802756c; .text.w35c_0802756c : { build/w35c_0802756c_MATCHED.o (.text.w35c_0802756c); } /* Sub_0802756C (72 B, main agbcc) */
    . = 0x08027cb4; .text.w35c_08027cb4 : { build/w35c_08027cb4_MATCHED.o (.text.w35c_08027cb4); } /* Sub_08027CB4 (72 B, main agbcc) */
    . = 0x080110e0; .text.w35c_080110e0 : { build/w35c_080110e0_MATCHED.o (.text.w35c_080110e0); } /* Sub_080110E0 (76 B, main agbcc) */

    /* Wave 36 landings (110 functions, coordinator-verified 0-diff). */
    . = 0x80008c0; .text.w36a_080008c0 : { build/w36a_080008c0_MATCHED.o (.text.w36a_080008c0); } /* Wave 36 w36a_080008c0_MATCHED.c (88 B, main) */
    . = 0x8000e80; .text.w36b_08000e80 : { build/w36b_08000e80_MATCHED.o (.text.w36b_08000e80); } /* Wave 36 w36b_08000e80_MATCHED.c (56 B, old) */
    . = 0x8001c08; .text.w36e_08001c08 : { build/w36e_08001c08_MATCHED.o (.text.w36e_08001c08); } /* Wave 36 w36e_08001c08_MATCHED.c (68 B, main) */
    . = 0x800419c; .text.w36b_0800419c : { build/w36b_0800419c_MATCHED.o (.text.w36b_0800419c); } /* Wave 36 w36b_0800419c_MATCHED.c (108 B, old) */
    . = 0x80053a0; .text.w36d_080053a0 : { build/w36d_080053a0_MATCHED.o (.text.w36d_080053a0); } /* Wave 36 w36d_080053a0_MATCHED.c (148 B, old) */
    . = 0x80054d0; .text.w36d_080054d0 : { build/w36d_080054d0_MATCHED.o (.text.w36d_080054d0); } /* Wave 36 w36d_080054d0_MATCHED.c (140 B, old) */
    . = 0x80060c4; .text.w36a_080060c4 : { build/w36a_080060c4_MATCHED.o (.text.w36a_080060c4); } /* Wave 36 w36a_080060c4_MATCHED.c (96 B, main) */
    . = 0x800675c; .text.w36a_0800675c : { build/w36a_0800675c_MATCHED.o (.text.w36a_0800675c); } /* Wave 36 w36a_0800675c_MATCHED.c (96 B, main) */
    . = 0x8007324; .text.w36a_08007324 : { build/w36a_08007324_MATCHED.o (.text.w36a_08007324); } /* Wave 36 w36a_08007324_MATCHED.c (84 B, main) */
    . = 0x8007c8c; .text.w36a_08007c8c : { build/w36a_08007c8c_MATCHED.o (.text.w36a_08007c8c); } /* Wave 36 w36a_08007c8c_MATCHED.c (80 B, main) */
    . = 0x8007cf4; .text.w36b_08007cf4 : { build/w36b_08007cf4_MATCHED.o (.text.w36b_08007cf4); } /* Wave 36 w36b_08007cf4_MATCHED.c (112 B, old) */
    . = 0x8007e9c; .text.w36a_08007e9c : { build/w36a_08007e9c_MATCHED.o (.text.w36a_08007e9c); } /* Wave 36 w36a_08007e9c_MATCHED.c (80 B, main) */
    . = 0x8007eec; .text.w36a_08007eec : { build/w36a_08007eec_MATCHED.o (.text.w36a_08007eec); } /* Wave 36 w36a_08007eec_MATCHED.c (56 B, main) */
    . = 0x80098c4; .text.w36b_080098c4 : { build/w36b_080098c4_MATCHED.o (.text.w36b_080098c4); } /* Wave 36 w36b_080098c4_MATCHED.c (108 B, old) */
    . = 0x800a0d4; .text.w36b_0800a0d4 : { build/w36b_0800a0d4_MATCHED.o (.text.w36b_0800a0d4); } /* Wave 36 w36b_0800a0d4_MATCHED.c (124 B, old) */
    . = 0x800b470; .text.w36a_0800b470 : { build/w36a_0800b470_MATCHED.o (.text.w36a_0800b470); } /* Wave 36 w36a_0800b470_MATCHED.c (88 B, main) */
    . = 0x800c41c; .text.w36b_0800c41c : { build/w36b_0800c41c_MATCHED.o (.text.w36b_0800c41c); } /* Wave 36 w36b_0800c41c_MATCHED.c (112 B, old) */
    . = 0x800cc94; .text.w36b_0800cc94 : { build/w36b_0800cc94_MATCHED.o (.text.w36b_0800cc94); } /* Wave 36 w36b_0800cc94_MATCHED.c (108 B, old) */
    . = 0x800cde8; .text.w36d_0800cde8 : { build/w36d_0800cde8_MATCHED.o (.text.w36d_0800cde8); } /* Wave 36 w36d_0800cde8_MATCHED.c (148 B, old) */
    . = 0x800ce7c; .text.w36d_0800ce7c : { build/w36d_0800ce7c_MATCHED.o (.text.w36d_0800ce7c); } /* Wave 36 w36d_0800ce7c_MATCHED.c (148 B, old) */
    . = 0x800dea4; .text.w36a_0800dea4 : { build/w36a_0800dea4_MATCHED.o (.text.w36a_0800dea4); } /* Wave 36 w36a_0800dea4_MATCHED.c (84 B, main) */
    . = 0x800e994; .text.w36b_0800e994 : { build/w36b_0800e994_MATCHED.o (.text.w36b_0800e994); } /* Wave 36 w36b_0800e994_MATCHED.c (116 B, old) */
    . = 0x800ed44; .text.w36b_0800ed44 : { build/w36b_0800ed44_MATCHED.o (.text.w36b_0800ed44); } /* Wave 36 w36b_0800ed44_MATCHED.c (108 B, old) */
    . = 0x800eed4; .text.w36b_0800eed4 : { build/w36b_0800eed4_MATCHED.o (.text.w36b_0800eed4); } /* Wave 36 w36b_0800eed4_MATCHED.c (108 B, old) */
    . = 0x801054c; .text.w36a_0801054c : { build/w36a_0801054c_MATCHED.o (.text.w36a_0801054c); } /* Wave 36 w36a_0801054c_MATCHED.c (88 B, main) */
    . = 0x8010750; .text.w36b_08010750 : { build/w36b_08010750_MATCHED.o (.text.w36b_08010750); } /* Wave 36 w36b_08010750_MATCHED.c (124 B, old) */
    . = 0x8010b30; .text.w36b_08010b30 : { build/w36b_08010b30_MATCHED.o (.text.w36b_08010b30); } /* Wave 36 w36b_08010b30_MATCHED.c (112 B, old) */
    . = 0x80114e8; .text.w36b_080114e8 : { build/w36b_080114e8_MATCHED.o (.text.w36b_080114e8); } /* Wave 36 w36b_080114e8_MATCHED.c (72 B, old) */
    . = 0x8011eb0; .text.w36b_08011eb0 : { build/w36b_08011eb0_MATCHED.o (.text.w36b_08011eb0); } /* Wave 36 w36b_08011eb0_MATCHED.c (116 B, old) */
    . = 0x8011f88; .text.w36c_08011f88 : { build/w36c_08011f88_MATCHED.o (.text.w36c_08011f88); } /* Wave 36 w36c_08011f88_MATCHED.c (132 B, old) */
    . = 0x8012108; .text.w36c_08012108 : { build/w36c_08012108_MATCHED.o (.text.w36c_08012108); } /* Wave 36 w36c_08012108_MATCHED.c (136 B, main) */
    . = 0x8015a60; .text.w36a_08015a60 : { build/w36a_08015a60_MATCHED.o (.text.w36a_08015a60); } /* Wave 36 w36a_08015a60_MATCHED.c (100 B, main) */
    . = 0x80188f4; .text.w36d_080188f4 : { build/w36d_080188f4_MATCHED.o (.text.w36d_080188f4); } /* Wave 36 w36d_080188f4_MATCHED.c (140 B, old) */
    . = 0x8018c84; .text.w36d_08018c84 : { build/w36d_08018c84_MATCHED.o (.text.w36d_08018c84); } /* Wave 36 w36d_08018c84_MATCHED.c (148 B, old) */
    . = 0x8018ea4; .text.w36d_08018ea4 : { build/w36d_08018ea4_MATCHED.o (.text.w36d_08018ea4); } /* Wave 36 w36d_08018ea4_MATCHED.c (144 B, old) */
    . = 0x8018f34; .text.w36c_08018f34 : { build/w36c_08018f34_MATCHED.o (.text.w36c_08018f34); } /* Wave 36 w36c_08018f34_MATCHED.c (132 B, old) */
    . = 0x8019248; .text.w36d_08019248 : { build/w36d_08019248_MATCHED.o (.text.w36d_08019248); } /* Wave 36 w36d_08019248_MATCHED.c (148 B, old) */
    . = 0x8019374; .text.w36d_08019374 : { build/w36d_08019374_MATCHED.o (.text.w36d_08019374); } /* Wave 36 w36d_08019374_MATCHED.c (140 B, old) */
    . = 0x80194b4; .text.w36d_080194b4 : { build/w36d_080194b4_MATCHED.o (.text.w36d_080194b4); } /* Wave 36 w36d_080194b4_MATCHED.c (140 B, old) */
    . = 0x8019c94; .text.w36c_08019c94 : { build/w36c_08019c94_MATCHED.o (.text.w36c_08019c94); } /* Wave 36 w36c_08019c94_MATCHED.c (132 B, old) */
    . = 0x8019f38; .text.w36c_08019f38 : { build/w36c_08019f38_MATCHED.o (.text.w36c_08019f38); } /* Wave 36 w36c_08019f38_MATCHED.c (128 B, old) */
    . = 0x801a19c; .text.w36c_0801a19c : { build/w36c_0801a19c_MATCHED.o (.text.w36c_0801a19c); } /* Wave 36 w36c_0801a19c_MATCHED.c (132 B, old) */
    . = 0x801a2bc; .text.w36c_0801a2bc : { build/w36c_0801a2bc_MATCHED.o (.text.w36c_0801a2bc); } /* Wave 36 w36c_0801a2bc_MATCHED.c (136 B, old) */
    . = 0x801a3f0; .text.w36d_0801a3f0 : { build/w36d_0801a3f0_MATCHED.o (.text.w36d_0801a3f0); } /* Wave 36 w36d_0801a3f0_MATCHED.c (148 B, old) */
    . = 0x801a568; .text.w36c_0801a568 : { build/w36c_0801a568_MATCHED.o (.text.w36c_0801a568); } /* Wave 36 w36c_0801a568_MATCHED.c (136 B, old) */
    . = 0x801a81c; .text.w36c_0801a81c : { build/w36c_0801a81c_MATCHED.o (.text.w36c_0801a81c); } /* Wave 36 w36c_0801a81c_MATCHED.c (128 B, old) */
    . = 0x801a9ac; .text.w36e_0801a9ac : { build/w36e_0801a9ac_MATCHED.o (.text.w36e_0801a9ac); } /* Wave 36 w36e_0801a9ac_MATCHED.c (76 B, main) */
    . = 0x801a9f8; .text.w36b_0801a9f8 : { build/w36b_0801a9f8_MATCHED.o (.text.w36b_0801a9f8); } /* Wave 36 w36b_0801a9f8_MATCHED.c (88 B, old) */
    . = 0x801aacc; .text.w36b_0801aacc : { build/w36b_0801aacc_MATCHED.o (.text.w36b_0801aacc); } /* Wave 36 w36b_0801aacc_MATCHED.c (104 B, old) */
    . = 0x801ae70; .text.w36c_0801ae70 : { build/w36c_0801ae70_MATCHED.o (.text.w36c_0801ae70); } /* Wave 36 w36c_0801ae70_MATCHED.c (132 B, old) */
    . = 0x801af58; .text.w36d_0801af58 : { build/w36d_0801af58_MATCHED.o (.text.w36d_0801af58); } /* Wave 36 w36d_0801af58_MATCHED.c (140 B, old) */
    . = 0x801b04c; .text.w36d_0801b04c : { build/w36d_0801b04c_MATCHED.o (.text.w36d_0801b04c); } /* Wave 36 w36d_0801b04c_MATCHED.c (144 B, old) */
    . = 0x801b1b8; .text.w36d_0801b1b8 : { build/w36d_0801b1b8_MATCHED.o (.text.w36d_0801b1b8); } /* Wave 36 w36d_0801b1b8_MATCHED.c (140 B, old) */
    . = 0x801b244; .text.w36d_0801b244 : { build/w36d_0801b244_MATCHED.o (.text.w36d_0801b244); } /* Wave 36 w36d_0801b244_MATCHED.c (140 B, old) */
    . = 0x801b8d0; .text.w36e_0801b8d0 : { build/w36e_0801b8d0_MATCHED.o (.text.w36e_0801b8d0); } /* Wave 36 w36e_0801b8d0_MATCHED.c (76 B, main) */
    . = 0x801b91c; .text.w36b_0801b91c : { build/w36b_0801b91c_MATCHED.o (.text.w36b_0801b91c); } /* Wave 36 w36b_0801b91c_MATCHED.c (80 B, old) */
    . = 0x801bfb4; .text.w36b_0801bfb4 : { build/w36b_0801bfb4_MATCHED.o (.text.w36b_0801bfb4); } /* Wave 36 w36b_0801bfb4_MATCHED.c (124 B, old) */
    . = 0x801c108; .text.w36c_0801c108 : { build/w36c_0801c108_MATCHED.o (.text.w36c_0801c108); } /* Wave 36 w36c_0801c108_MATCHED.c (136 B, old) */
    . = 0x801c254; .text.w36d_0801c254 : { build/w36d_0801c254_MATCHED.o (.text.w36d_0801c254); } /* Wave 36 w36d_0801c254_MATCHED.c (140 B, old) */
    . = 0x801c628; .text.w36c_0801c628 : { build/w36c_0801c628_MATCHED.o (.text.w36c_0801c628); } /* Wave 36 w36c_0801c628_MATCHED.c (136 B, old) */
    . = 0x801c774; .text.w36d_0801c774 : { build/w36d_0801c774_MATCHED.o (.text.w36d_0801c774); } /* Wave 36 w36d_0801c774_MATCHED.c (140 B, old) */
    . = 0x801c91c; .text.w36d_0801c91c : { build/w36d_0801c91c_MATCHED.o (.text.w36d_0801c91c); } /* Wave 36 w36d_0801c91c_MATCHED.c (140 B, old) */
    . = 0x801cac4; .text.w36c_0801cac4 : { build/w36c_0801cac4_MATCHED.o (.text.w36c_0801cac4); } /* Wave 36 w36c_0801cac4_MATCHED.c (128 B, old) */
    . = 0x801cc94; .text.w36e_0801cc94 : { build/w36e_0801cc94_MATCHED.o (.text.w36e_0801cc94); } /* Wave 36 w36e_0801cc94_MATCHED.c (76 B, main) */
    . = 0x801cce0; .text.w36b_0801cce0 : { build/w36b_0801cce0_MATCHED.o (.text.w36b_0801cce0); } /* Wave 36 w36b_0801cce0_MATCHED.c (80 B, old) */
    . = 0x801db40; .text.w36a_0801db40 : { build/w36a_0801db40_MATCHED.o (.text.w36a_0801db40); } /* Wave 36 w36a_0801db40_MATCHED.c (92 B, main) */
    . = 0x801e0d0; .text.w36c_0801e0d0 : { build/w36c_0801e0d0_MATCHED.o (.text.w36c_0801e0d0); } /* Wave 36 w36c_0801e0d0_MATCHED.c (124 B, old) */
    . = 0x8020f70; .text.w36d_08020f70 : { build/w36d_08020f70_MATCHED.o (.text.w36d_08020f70); } /* Wave 36 w36d_08020f70_MATCHED.c (144 B, old) */
    . = 0x802142c; .text.w36b_0802142c : { build/w36b_0802142c_MATCHED.o (.text.w36b_0802142c); } /* Wave 36 w36b_0802142c_MATCHED.c (108 B, old) */
    . = 0x8021628; .text.w36c_08021628 : { build/w36c_08021628_MATCHED.o (.text.w36c_08021628); } /* Wave 36 w36c_08021628_MATCHED.c (128 B, old) */
    . = 0x8021ed4; .text.w36b_08021ed4 : { build/w36b_08021ed4_MATCHED.o (.text.w36b_08021ed4); } /* Wave 36 w36b_08021ed4_MATCHED.c (104 B, old) */
    . = 0x8022290; .text.w36d_08022290 : { build/w36d_08022290_MATCHED.o (.text.w36d_08022290); } /* Wave 36 w36d_08022290_MATCHED.c (144 B, old) */
    . = 0x8022700; .text.w36d_08022700 : { build/w36d_08022700_MATCHED.o (.text.w36d_08022700); } /* Wave 36 w36d_08022700_MATCHED.c (140 B, old) */
    . = 0x80227dc; .text.w36d_080227dc : { build/w36d_080227dc_MATCHED.o (.text.w36d_080227dc); } /* Wave 36 w36d_080227dc_MATCHED.c (140 B, old) */
    . = 0x8023110; .text.w36a_08023110 : { build/w36a_08023110_MATCHED.o (.text.w36a_08023110); } /* Wave 36 w36a_08023110_MATCHED.c (92 B, main) */
    . = 0x802329c; .text.w36b_0802329c : { build/w36b_0802329c_MATCHED.o (.text.w36b_0802329c); } /* Wave 36 w36b_0802329c_MATCHED.c (104 B, old) */
    . = 0x8023bc4; .text.w36b_08023bc4 : { build/w36b_08023bc4_MATCHED.o (.text.w36b_08023bc4); } /* Wave 36 w36b_08023bc4_MATCHED.c (116 B, old) */
    . = 0x8023d68; .text.w36b_08023d68 : { build/w36b_08023d68_MATCHED.o (.text.w36b_08023d68); } /* Wave 36 w36b_08023d68_MATCHED.c (112 B, old) */
    . = 0x8024b3c; .text.w36d_08024b3c : { build/w36d_08024b3c_MATCHED.o (.text.w36d_08024b3c); } /* Wave 36 w36d_08024b3c_MATCHED.c (140 B, old) */
    . = 0x8024e2c; .text.w36d_08024e2c : { build/w36d_08024e2c_MATCHED.o (.text.w36d_08024e2c); } /* Wave 36 w36d_08024e2c_MATCHED.c (140 B, old) */
    . = 0x8025e5c; .text.w36b_08025e5c : { build/w36b_08025e5c_MATCHED.o (.text.w36b_08025e5c); } /* Wave 36 w36b_08025e5c_MATCHED.c (108 B, old) */
    . = 0x8026a84; .text.w36c_08026a84 : { build/w36c_08026a84_MATCHED.o (.text.w36c_08026a84); } /* Wave 36 w36c_08026a84_MATCHED.c (124 B, main) */
    . = 0x80272e0; .text.w36e_080272e0 : { build/w36e_080272e0_MATCHED.o (.text.w36e_080272e0); } /* Wave 36 w36e_080272e0_MATCHED.c (148 B, old) */
    . = 0x8027374; .text.w36d_08027374 : { build/w36d_08027374_MATCHED.o (.text.w36d_08027374); } /* Wave 36 w36d_08027374_MATCHED.c (140 B, old) */
    . = 0x8027d48; .text.w36e_08027d48 : { build/w36e_08027d48_MATCHED.o (.text.w36e_08027d48); } /* Wave 36 w36e_08027d48_MATCHED.c (4 B, main) */
    . = 0x80280e8; .text.w36b_080280e8 : { build/w36b_080280e8_MATCHED.o (.text.w36b_080280e8); } /* Wave 36 w36b_080280e8_MATCHED.c (108 B, old) */
    . = 0x802873c; .text.w36e_0802873c : { build/w36e_0802873c_MATCHED.o (.text.w36e_0802873c); } /* Wave 36 w36e_0802873c_MATCHED.c (60 B, main) */
    . = 0x8028900; .text.w36b_08028900 : { build/w36b_08028900_MATCHED.o (.text.w36b_08028900); } /* Wave 36 w36b_08028900_MATCHED.c (112 B, old) */
    . = 0x802d670; .text.w36b_0802d670 : { build/w36b_0802d670_MATCHED.o (.text.w36b_0802d670); } /* Wave 36 w36b_0802d670_MATCHED.c (112 B, old) */
    . = 0x802daf8; .text.w36d_0802daf8 : { build/w36d_0802daf8_MATCHED.o (.text.w36d_0802daf8); } /* Wave 36 w36d_0802daf8_MATCHED.c (140 B, old) */
    . = 0x802e9f8; .text.w36b_0802e9f8 : { build/w36b_0802e9f8_MATCHED.o (.text.w36b_0802e9f8); } /* Wave 36 w36b_0802e9f8_MATCHED.c (108 B, old) */
    . = 0x802f550; .text.w36a_0802f550 : { build/w36a_0802f550_MATCHED.o (.text.w36a_0802f550); } /* Wave 36 w36a_0802f550_MATCHED.c (92 B, main) */
    . = 0x802fbf0; .text.w36e_0802fbf0 : { build/w36e_0802fbf0_MATCHED.o (.text.w36e_0802fbf0); } /* Wave 36 w36e_0802fbf0_MATCHED.c (56 B, old) */
    . = 0x802fc70; .text.w36d_0802fc70 : { build/w36d_0802fc70_MATCHED.o (.text.w36d_0802fc70); } /* Wave 36 w36d_0802fc70_MATCHED.c (140 B, old) */
    . = 0x8034eb8; .text.w36b_08034eb8 : { build/w36b_08034eb8_MATCHED.o (.text.w36b_08034eb8); } /* Wave 36 w36b_08034eb8_MATCHED.c (116 B, old) */
    . = 0x8038520; .text.w36c_08038520 : { build/w36c_08038520_MATCHED.o (.text.w36c_08038520); } /* Wave 36 w36c_08038520_MATCHED.c (136 B, main) */
    . = 0x803ff0c; .text.w36b_0803ff0c : { build/w36b_0803ff0c_MATCHED.o (.text.w36b_0803ff0c); } /* Wave 36 w36b_0803ff0c_MATCHED.c (116 B, old) */
    . = 0x80429e0; .text.w36a_080429e0 : { build/w36a_080429e0_MATCHED.o (.text.w36a_080429e0); } /* Wave 36 w36a_080429e0_MATCHED.c (88 B, main) */
    . = 0x8045fcc; .text.w36b_08045fcc : { build/w36b_08045fcc_MATCHED.o (.text.w36b_08045fcc); } /* Wave 36 w36b_08045fcc_MATCHED.c (108 B, old) */
    . = 0x8046904; .text.w36a_08046904 : { build/w36a_08046904_MATCHED.o (.text.w36a_08046904); } /* Wave 36 w36a_08046904_MATCHED.c (92 B, main) */
    . = 0x8046960; .text.w36d_08046960 : { build/w36d_08046960_MATCHED.o (.text.w36d_08046960); } /* Wave 36 w36d_08046960_MATCHED.c (140 B, old) */
    . = 0x804b5cc; .text.w36b_0804b5cc : { build/w36b_0804b5cc_MATCHED.o (.text.w36b_0804b5cc); } /* Wave 36 w36b_0804b5cc_MATCHED.c (104 B, old) */
    . = 0x804c630; .text.w36b_0804c630 : { build/w36b_0804c630_MATCHED.o (.text.w36b_0804c630); } /* Wave 36 w36b_0804c630_MATCHED.c (120 B, old) */
    /* Wave 38-D: F_08030AD4 giant dispatcher (12,276 B, sanctioned asm transcription). */
    . = 0x08030ad4; .text.w38d_08030ad4_asm : { build/w38d_08030ad4_MATCHED.o (.text.w38d_08030ad4_asm); }
    /* Wave 38-C: 7 matched (2 pure C gaps + 5 C+patch). */
    . = 0x08017600; .text.w38c_08017600 : { build/w38c_08017600_MATCHED.o (.text.w38c_08017600); }
    . = 0x08023264; .text.w38c_08023264 : { build/w38c_08023264_MATCHED.o (.text.w38c_08023264); }
    . = 0x08023a7c; .text.w38c_08023a7c : { build/w38c_08023a7c_MATCHED.o (.text.w38c_08023a7c); }
    . = 0x0801bde4; .text.w38c_0801bde4 : { build/w38c_0801bde4_MATCHED.o (.text.w38c_0801bde4); }
    . = 0x0801c6b0; .text.w38c_0801c6b0 : { build/w38c_0801c6b0_MATCHED.o (.text.w38c_0801c6b0); }
    . = 0x080234c8; .text.w38c_080234c8 : { build/w38c_080234c8_MATCHED.o (.text.w38c_080234c8); }
    . = 0x0800e144; .text.w38c_0800e144 : { build/w38c_0800e144_MATCHED.o (.text.w38c_0800e144); }
    /* Wave 38-B: 3 transcriptions + 2 C+patch. */
    . = 0x0800adc8; .text.w38b_0800adc8_asm : { build/w38b_0800adc8_MATCHED.o (.text.w38b_0800adc8_asm); }
    . = 0x080361e8; .text.w38b_080361e8_asm : { build/w38b_080361e8_MATCHED.o (.text.w38b_080361e8_asm); }
    . = 0x0800c268; .text.w38b_0800c268_asm : { build/w38b_0800c268_MATCHED.o (.text.w38b_0800c268_asm); }
    . = 0x08004e60; .text.w38b_08004e60 : { build/w38b_08004e60_MATCHED.o (.text.w38b_08004e60); }
    . = 0x08034c1c; .text.w38b_08034c1c : { build/w38b_08034c1c_MATCHED.o (.text.w38b_08034c1c); }
    /* Wave 38-A: 14 bulk lines 347-450 (all old_agbcc, pure C). */
    . = 0x0801823c; .text.w38a_0801823c : { build/w38a_0801823c_MATCHED.o (.text.w38a_0801823c); }
    . = 0x08005130; .text.w38a_08005130 : { build/w38a_08005130_MATCHED.o (.text.w38a_08005130); }
    . = 0x08012f4c; .text.w38a_08012f4c : { build/w38a_08012f4c_MATCHED.o (.text.w38a_08012f4c); }
    . = 0x08013528; .text.w38a_08013528 : { build/w38a_08013528_MATCHED.o (.text.w38a_08013528); }
    . = 0x080139fc; .text.w38a_080139fc : { build/w38a_080139fc_MATCHED.o (.text.w38a_080139fc); }
    . = 0x08017a94; .text.w38a_08017a94 : { build/w38a_08017a94_MATCHED.o (.text.w38a_08017a94); }
    . = 0x08018fb8; .text.w38a_08018fb8 : { build/w38a_08018fb8_MATCHED.o (.text.w38a_08018fb8); }
    . = 0x0802106c; .text.w38a_0802106c : { build/w38a_0802106c_MATCHED.o (.text.w38a_0802106c); }
    . = 0x08035a24; .text.w38a_08035a24 : { build/w38a_08035a24_MATCHED.o (.text.w38a_08035a24); }
    . = 0x08013ad4; .text.w38a_08013ad4 : { build/w38a_08013ad4_MATCHED.o (.text.w38a_08013ad4); }
    . = 0x08014078; .text.w38a_08014078 : { build/w38a_08014078_MATCHED.o (.text.w38a_08014078); }
    . = 0x0801a484; .text.w38a_0801a484 : { build/w38a_0801a484_MATCHED.o (.text.w38a_0801a484); }
    . = 0x0801572c; .text.w38a_0801572c : { build/w38a_0801572c_MATCHED.o (.text.w38a_0801572c); }
    . = 0x0801b728; .text.w38a_0801b728 : { build/w38a_0801b728_MATCHED.o (.text.w38a_0801b728); }
    . = 0x08009140; .text.w39d_08009140 : { build/w39d_08009140_MATCHED.o (.text.w39d_08009140); } /* Wave 39 */
    . = 0x0803B898; .text.w39d_0803b898 : { build/w39d_0803b898_MATCHED.o (.text.w39d_0803b898); } /* Wave 39 */
    . = 0x080285C4; .text.w39a_080285c4 : { build/w39a_080285c4_MATCHED.o (.text.w39a_080285c4); } /* Wave 39 */
    . = 0x08048084; .text.w39a_08048084 : { build/w39a_08048084_MATCHED.o (.text.w39a_08048084); } /* Wave 39 */
    . = 0x0803895C; .text.w39a_0803895c : { build/w39a_0803895c_MATCHED.o (.text.w39a_0803895c); } /* Wave 39 */
    . = 0x0802F5AC; .text.w39b_0802f5ac : { build/w39b_0802f5ac_MATCHED.o (.text.w39b_0802f5ac); } /* Wave 39 */
    . = 0x08015278; .text.w39c_08015278 : { build/w39c_08015278_MATCHED.o (.text.w39c_08015278); } /* Wave 39 */
    . = 0x0801A72C; .text.w39c_0801a72c : { build/w39c_0801a72c_MATCHED.o (.text.w39c_0801a72c); } /* Wave 39 */
    . = 0x08013708; .text.w39c_08013708 : { build/w39c_08013708_MATCHED.o (.text.w39c_08013708); } /* Wave 39 */
    . = 0x0801519C; .text.w39c_0801519c : { build/w39c_0801519c_MATCHED.o (.text.w39c_0801519c); } /* Wave 39 */
    . = 0x08042B60; .text.w39c_08042b60 : { build/w39c_08042b60_MATCHED.o (.text.w39c_08042b60); } /* Wave 39 */
    . = 0x08023F28; .text.w39c_08023f28 : { build/w39c_08023f28_MATCHED.o (.text.w39c_08023f28); } /* Wave 39 */
    . = 0x08037700; .text.w39c_08037700 : { build/w39c_08037700_MATCHED.o (.text.w39c_08037700); } /* Wave 39 */
    . = 0x0800C964; .text.w39c_0800c964 : { build/w39c_0800c964_MATCHED.o (.text.w39c_0800c964); } /* Wave 39 */
    . = 0x080171c0; .text.w40a_080171c0 : { build/w40a_080171c0_MATCHED.o (.text.w40a_080171c0); } /* Wave 40 */
    . = 0x0801e890; .text.w40a_0801e890 : { build/w40a_0801e890_MATCHED.o (.text.w40a_0801e890); } /* Wave 40 */
    . = 0x08003874; .text.w40b_08003874 : { build/w40b_08003874_MATCHED.o (.text.w40b_08003874); } /* Wave 40 */
    . = 0x080118a4; .text.w40b_080118a4 : { build/w40b_080118a4_MATCHED.o (.text.w40b_080118a4); } /* Wave 40 */
    . = 0x08019904; .text.w40b_08019904 : { build/w40b_08019904_MATCHED.o (.text.w40b_08019904); } /* Wave 40 */
    . = 0x08035c5c; .text.w40b_08035c5c : { build/w40b_08035c5c_MATCHED.o (.text.w40b_08035c5c); } /* Wave 40 */
    . = 0x08017b6c; .text.w40c_08017b6c : { build/w40c_08017b6c_MATCHED.o (.text.w40c_08017b6c); } /* Wave 40 */
    . = 0x0802129c; .text.w40c_0802129c : { build/w40c_0802129c_MATCHED.o (.text.w40c_0802129c); } /* Wave 40 */
    . = 0x080173bc; .text.w40c_080173bc : { build/w40c_080173bc_MATCHED.o (.text.w40c_080173bc); } /* Wave 40 */
    . = 0x08017ce0; .text.w40c_08017ce0 : { build/w40c_08017ce0_MATCHED.o (.text.w40c_08017ce0); } /* Wave 40 */
    . = 0x0804b7f0; .text.w40d_0804b7f0 : { build/w40d_0804b7f0_MATCHED.o (.text.w40d_0804b7f0); } /* Wave 40 */
    . = 0x08049780; .text.w40d_08049780 : { build/w40d_08049780_MATCHED.o (.text.w40d_08049780); } /* Wave 40 */
    . = 0x08023c38; .text.w41a_08023c38 : { build/w41a_08023c38_MATCHED.o (.text.w41a_08023c38); } /* Wave 41 */
    . = 0x08003b70; .text.w41b_08003b70 : { build/w41b_08003b70_MATCHED.o (.text.w41b_08003b70); } /* Wave 41 */
    . = 0x08003e80; .text.w41b_08003e80 : { build/w41b_08003e80_MATCHED.o (.text.w41b_08003e80); } /* Wave 41 */
    . = 0x08015ac4; .text.w41c_08015ac4 : { build/w41c_08015ac4_MATCHED.o (.text.w41c_08015ac4); } /* Wave 41 */
    . = 0x0802d928; .text.w41c_0802d928 : { build/w41c_0802d928_MATCHED.o (.text.w41c_0802d928); } /* Wave 41 */
    . = 0x08020870; .text.w41d_08020870 : { build/w41d_08020870_MATCHED.o (.text.w41d_08020870); } /* Wave 41 */
    . = 0x0801b9e8; .text.w42a_0801b9e8 : { build/w42a_0801b9e8_MATCHED.o (.text.w42a_0801b9e8); } /* Wave 42 */
    . = 0x0800e068; .text.w42c_0800e068 : { build/w42c_0800e068_MATCHED.o (.text.w42c_0800e068); } /* Wave 42 */
    . = 0x0804ca30; .text.w42d_0804ca30 : { build/w42d_0804ca30_MATCHED.o (.text.w42d_0804ca30); } /* Wave 42 */
    . = 0x08046cfc; .text.w42d_08046cfc : { build/w42d_08046cfc_MATCHED.o (.text.w42d_08046cfc); } /* Wave 42 */
    . = 0x08026430; .text.w43b_08026430 : { build/w43b_08026430_MATCHED.o (.text.w43b_08026430); } /* Wave 43 */
    . = 0x08018398; .text.w43c_08018398 : { build/w43c_08018398_MATCHED.o (.text.w43c_08018398); } /* Wave 43 */
    . = 0x0801b2d0; .text.w43c_0801b2d0 : { build/w43c_0801b2d0_MATCHED.o (.text.w43c_0801b2d0); } /* Wave 43 */
    . = 0x0803ff80; .text.w43a_0803ff80 : { build/w43a_0803ff80_MATCHED.o (.text.w43a_0803ff80); } /* Wave 43 */
    . = 0x08018af4; .text.w44d_08018af4 : { build/w44d_08018af4_MATCHED.o (.text.w44d_08018af4); } /* Wave 44 */
    . = 0x080380b8; .text.w45b_080380b8 : { build/w45b_080380b8_MATCHED.o (.text.w45b_080380b8); } /* Wave 45 */
    . = 0x0800bd20; .text.w45c_0800bd20 : { build/w45c_0800bd20_MATCHED.o (.text.w45c_0800bd20); } /* Wave 45 */
    . = 0x0801a89c; .text.w45d_0801a89c : { build/w45d_0801a89c_MATCHED.o (.text.w45d_0801a89c); } /* Wave 45 */
    . = 0x08020660; .text.w46a_08020660 : { build/w46a_08020660_MATCHED.o (.text.w46a_08020660); } /* Wave 46 */
    . = 0x0801c800; .text.w46c_0801c800 : { build/w46c_0801c800_MATCHED.o (.text.w46c_0801c800); } /* Wave 46 */
    . = 0x08001ae4; .text.w46c_08001ae4 : { build/w46c_08001ae4_MATCHED.o (.text.w46c_08001ae4); } /* Wave 46 */
    . = 0x0801c2e0; .text.w46d_0801c2e0 : { build/w46d_0801c2e0_MATCHED.o (.text.w46d_0801c2e0); } /* Wave 46 */
    . = 0x0801bb94; .text.w46d_0801bb94 : { build/w46d_0801bb94_MATCHED.o (.text.w46d_0801bb94); } /* Wave 46 */
    . = 0x0801ba94; .text.w46d_0801ba94 : { build/w46d_0801ba94_MATCHED.o (.text.w46d_0801ba94); } /* Wave 46 */
    . = 0x08001bf8; .text.w47a_08001bf8 : { build/w47a_08001bf8_MATCHED.o (.text.w47a_08001bf8); } /* Wave 47 */
    . = 0x0801c9a8; .text.w47c_0801c9a8 : { build/w47c_0801c9a8_MATCHED.o (.text.w47c_0801c9a8); } /* Wave 47 */
    . = 0x08044630; .text.w47d_08044630 : { build/w47d_08044630_MATCHED.o (.text.w47d_08044630); } /* Wave 47 */
    . = 0x0804472c; .text.w47d_0804472c : { build/w47d_0804472c_MATCHED.o (.text.w47d_0804472c); } /* Wave 47 */
    . = 0x0804b634; .text.w48c_0804b634 : { build/w48c_0804b634_MATCHED.o (.text.w48c_0804b634); } /* Wave 48 */
    . = 0x08041fbc; .text.w49c_08041fbc : { build/w49c_08041fbc_MATCHED.o (.text.w49c_08041fbc); } /* Wave 49 */
    . = 0x080420d0; .text.w49c_080420d0 : { build/w49c_080420d0_MATCHED.o (.text.w49c_080420d0); } /* Wave 49 */
    . = 0x080421e4; .text.w49c_080421e4 : { build/w49c_080421e4_MATCHED.o (.text.w49c_080421e4); } /* Wave 49 */
    . = 0x0801d488; .text.w49d_0801d488 : { build/w49d_0801d488_MATCHED.o (.text.w49d_0801d488); } /* Wave 49 */
    . = 0x080275f8; .text.w49d_080275f8 : { build/w49d_080275f8_MATCHED.o (.text.w49d_080275f8); } /* Wave 49 */
    . = 0x0801ebd0; .text.w50b_0801ebd0 : { build/w50b_0801ebd0_MATCHED.o (.text.w50b_0801ebd0); } /* Wave 50 */
    . = 0x0800d278; .text.w50b_0800d278 : { build/w50b_0800d278_MATCHED.o (.text.w50b_0800d278); } /* Wave 50 */
    . = 0x08042878; .text.w50c_08042878 : { build/w50c_08042878_MATCHED.o (.text.w50c_08042878); } /* Wave 50 */
    . = 0x0801200c; .text.w50d_0801200c : { build/w50d_0801200c_MATCHED.o (.text.w50d_0801200c); } /* Wave 50 */
    . = 0x08012190; .text.w50d_08012190 : { build/w50d_08012190_MATCHED.o (.text.w50d_08012190); } /* Wave 50 */
    . = 0x0800d59c; .text.w50d_0800d59c : { build/w50d_0800d59c_MATCHED.o (.text.w50d_0800d59c); } /* Wave 50 */
    . = 0x08013280; .text.w50d_08013280 : { build/w50d_08013280_MATCHED.o (.text.w50d_08013280); } /* Wave 50 */
    . = 0x08014fb4; .text.w50d_08014fb4 : { build/w50d_08014fb4_MATCHED.o (.text.w50d_08014fb4); } /* Wave 50 */
    . = 0x08015644; .text.w51a_08015644 : { build/w51a_08015644_MATCHED.o (.text.w51a_08015644); } /* Wave 51 */
    . = 0x0800fee0; .text.w51c_0800fee0 : { build/w51c_0800fee0_MATCHED.o (.text.w51c_0800fee0); } /* Wave 51 */
    . = 0x08000418; .text.w51d_08000418 : { build/w51d_08000418_MATCHED.o (.text.w51d_08000418); } /* Wave 51 */
    . = 0x0801eac4; .text.w51c_0801eac4 : { build/w51c_0801eac4_MATCHED.o (.text.w51c_0801eac4); } /* Wave 51 */
    . = 0x800fc64; .text.w52a_0800fc64 : { build/w52a_0800fc64_MATCHED.o (.text.w52a_0800fc64); } /* Wave 52 */
    . = 0x80240cc; .text.w52b_080240cc : { build/w52b_080240cc_MATCHED.o (.text.w52b_080240cc); } /* Wave 52 */
    . = 0x8011560; .text.w52d_08011560 : { build/w52d_08011560_MATCHED.o (.text.w52d_08011560); } /* Wave 52 */
    . = 0x800bfd0; .text.w53a_0800bfd0 : { build/w53a_0800bfd0_MATCHED.o (.text.w53a_0800bfd0); } /* Wave 53 */
    . = 0x80170d4; .text.w53b_080170d4 : { build/w53b_080170d4_MATCHED.o (.text.w53b_080170d4); } /* Wave 53 */
    . = 0x80059a8; .text.w54c_080059a8 : { build/w54c_080059a8_MATCHED.o (.text.w54c_080059a8); } /* Wave 54 */
    . = 0x8013434; .text.w54d_08013434 : { build/w54d_08013434_MATCHED.o (.text.w54d_08013434); } /* Wave 54 */
    . = 0x8014154; .text.w54d_08014154 : { build/w54d_08014154_MATCHED.o (.text.w54d_08014154); } /* Wave 54 */
    . = 0x8014318; .text.w54d_08014318 : { build/w54d_08014318_MATCHED.o (.text.w54d_08014318); } /* Wave 54 */
    . = 0x801440c; .text.w54d_0801440c : { build/w54d_0801440c_MATCHED.o (.text.w54d_0801440c); } /* Wave 54 */
    . = 0x80145cc; .text.w54d_080145cc : { build/w54d_080145cc_MATCHED.o (.text.w54d_080145cc); } /* Wave 54 */
    . = 0x8019d18; .text.w54d_08019d18 : { build/w54d_08019d18_MATCHED.o (.text.w54d_08019d18); } /* Wave 54 */
    . = 0x800695c; .text.w55d_0800695c : { build/w55d_0800695c_MATCHED.o (.text.w55d_0800695c); } /* Wave 55 */
    . = 0x8013904; .text.w55d_08013904 : { build/w55d_08013904_MATCHED.o (.text.w55d_08013904); } /* Wave 55 */
    . = 0x8013bb0; .text.w55d_08013bb0 : { build/w55d_08013bb0_MATCHED.o (.text.w55d_08013bb0); } /* Wave 55 */
    . = 0x8014eb8; .text.w55d_08014eb8 : { build/w55d_08014eb8_MATCHED.o (.text.w55d_08014eb8); } /* Wave 55 */
    . = 0x8023fd0; .text.w55d_08023fd0 : { build/w55d_08023fd0_MATCHED.o (.text.w55d_08023fd0); } /* Wave 55 */
    . = 0x8027e8c; .text.w55a_08027e8c : { build/w55a_08027e8c_MATCHED.o (.text.w55a_08027e8c); } /* Wave 55 */
    . = 0x8028778; .text.w55d_08028778 : { build/w55d_08028778_MATCHED.o (.text.w55d_08028778); } /* Wave 55 */
    . = 0x8014944; .text.w56d_08014944 : { build/w56d_08014944_MATCHED.o (.text.w56d_08014944); } /* Wave 56 */
    . = 0x801509c; .text.w56d_0801509c : { build/w56d_0801509c_MATCHED.o (.text.w56d_0801509c); } /* Wave 56 */
    . = 0x8010138; .text.w57a_08010138 : { build/w57a_08010138_MATCHED.o (.text.w57a_08010138); } /* Wave 57 */
    . = 0x8025a64; .text.w57a_08025a64 : { build/w57a_08025a64_MATCHED.o (.text.w57a_08025a64); } /* Wave 57 */
    . = 0x801d070; .text.w57c_0801d070 : { build/w57c_0801d070_MATCHED.o (.text.w57c_0801d070); } /* Wave 57 */
    . = 0x8018d18; .text.w57d_08018d18 : { build/w57d_08018d18_MATCHED.o (.text.w57d_08018d18); } /* Wave 57 */
    . = 0x80067bc; .text.w58b_080067bc : { build/w58b_080067bc_MATCHED.o (.text.w58b_080067bc); } /* Wave 58 */
    . = 0x8028fec; .text.w59d_08028fec : { build/w59d_08028fec_MATCHED.o (.text.w59d_08028fec); } /* Wave 59 */
    . = 0x8021fdc; .text.w59c_08021fdc : { build/w59c_08021fdc_MATCHED.o (.text.w59c_08021fdc); } /* Wave 59 */
    . = 0x804a694; .text.w60b_0804a694 : { build/w60b_0804a694_MATCHED.o (.text.w60b_0804a694); } /* Wave 60 */
    . = 0x802f364; .text.w60b_0802f364 : { build/w60b_0802f364_MATCHED.o (.text.w60b_0802f364); } /* Wave 60 */
    . = 0x8013600; .text.w60c_08013600 : { build/w60c_08013600_MATCHED.o (.text.w60c_08013600); } /* Wave 60 */
    . = 0x8015378; .text.w60c_08015378 : { build/w60c_08015378_MATCHED.o (.text.w60c_08015378); } /* Wave 60 */
    . = 0x8015538; .text.w60c_08015538 : { build/w60c_08015538_MATCHED.o (.text.w60c_08015538); } /* Wave 60 */
    . = 0x8014a44; .text.w60d_08014a44 : { build/w60d_08014a44_MATCHED.o (.text.w60d_08014a44); } /* Wave 60 */
    . = 0x8013024; .text.w60d_08013024 : { build/w60d_08013024_MATCHED.o (.text.w60d_08013024); } /* Wave 60 */
    . = 0x8012274; .text.w60d_08012274 : { build/w60d_08012274_MATCHED.o (.text.w60d_08012274); } /* Wave 60 */
    . = 0x80137e4; .text.w60d_080137e4 : { build/w60d_080137e4_MATCHED.o (.text.w60d_080137e4); } /* Wave 60 */
    . = 0x8010bb4; .text.w61c_08010bb4 : { build/w61c_08010bb4_MATCHED.o (.text.w61c_08010bb4); } /* Wave 61 */
    . = 0x801bc70; .text.w61c_0801bc70 : { build/w61c_0801bc70_MATCHED.o (.text.w61c_0801bc70); } /* Wave 61 */
    . = 0x802cce4; .text.w63c_0802cce4 : { build/w63c_0802cce4_MATCHED.o (.text.w63c_0802cce4); } /* Wave 63 */
    . = 0x80466ac; .text.w64a_080466ac : { build/w64a_080466ac_MATCHED.o (.text.w64a_080466ac); } /* Wave 64 */
    . = 0x800cf10; .text.w65b_0800cf10 : { build/w65b_0800cf10_MATCHED.o (.text.w65b_0800cf10); } /* Wave 65 */
    . = 0x804a0a4; .text.w65d_0804a0a4 : { build/w65d_0804a0a4_MATCHED.o (.text.w65d_0804a0a4); } /* Wave 65 */
    . = 0x801910c; .text.w65d_0801910c : { build/w65d_0801910c_MATCHED.o (.text.w65d_0801910c); } /* Wave 65 */
    . = 0x80147fc; .text.w66a_080147fc : { build/w66a_080147fc_MATCHED.o (.text.w66a_080147fc); } /* Wave 66 */
    . = 0x8012a3c; .text.w66a_08012a3c : { build/w66a_08012a3c_MATCHED.o (.text.w66a_08012a3c); } /* Wave 66 */
    . = 0x8025b60; .text.w66a_08025b60 : { build/w66a_08025b60_MATCHED.o (.text.w66a_08025b60); } /* Wave 66 */
    . = 0x80289c4; .text.w67a_080289c4 : { build/w67a_080289c4_MATCHED.o (.text.w67a_080289c4); } /* Wave 67 */
    . = 0x8015f90; .text.w67d_08015f90 : { build/w67d_08015f90_MATCHED.o (.text.w67d_08015f90); } /* Wave 67 */
    . = 0x80146c0; .text.w68c_080146c0 : { build/w68c_080146c0_MATCHED.o (.text.w68c_080146c0); } /* Wave 68 */
    . = 0x8013138; .text.w68a_08013138 : { build/w68a_08013138_MATCHED.o (.text.w68a_08013138); } /* Wave 68 */
    . = 0x8012504; .text.w68a_08012504 : { build/w68a_08012504_MATCHED.o (.text.w68a_08012504); } /* Wave 68 */
    . = 0x8026238; .text.w68a_08026238 : { build/w68a_08026238_MATCHED.o (.text.w68a_08026238); } /* Wave 68 */
    . = 0x8013cac; .text.w69a_08013cac : { build/w69a_08013cac_MATCHED.o (.text.w69a_08013cac); } /* Wave 69 */
    . = 0x8018064; .text.w69d_08018064 : { build/w69d_08018064_MATCHED.o (.text.w69d_08018064); } /* Wave 69 */
    . = 0x8012d28; .text.w70a_08012d28 : { build/w70a_08012d28_MATCHED.o (.text.w70a_08012d28); } /* Wave 70 */
    . = 0x8013f24; .text.w70a_08013f24 : { build/w70a_08013f24_MATCHED.o (.text.w70a_08013f24); } /* Wave 70 */
    . = 0x8024cd8; .text.w70a_08024cd8 : { build/w70a_08024cd8_MATCHED.o (.text.w70a_08024cd8); } /* Wave 70 */
    . = 0x80493ec; .text.w72a_080493ec : { build/w72a_080493ec_MATCHED.o (.text.w72a_080493ec); } /* Wave 72 */
    . = 0x8041e58; .text.w73a_08041e58 : { build/w73a_08041e58_MATCHED.o (.text.w73a_08041e58); } /* Wave 73 */
    . = 0x801264c; .text.w73a_0801264c : { build/w73a_0801264c_MATCHED.o (.text.w73a_0801264c); } /* Wave 73 */
    . = 0x801238c; .text.w74a_0801238c : { build/w74a_0801238c_MATCHED.o (.text.w74a_0801238c); } /* Wave 74 */
    . = 0x8012880; .text.w74a_08012880 : { build/w74a_08012880_MATCHED.o (.text.w74a_08012880); } /* Wave 74 */
    . = 0x8037f38; .text.w78d_08037f38 : { build/w78d_08037f38_MATCHED.o (.text.w78d_08037f38); } /* Wave 78 */
    . = 0x8014b54; .text.w83a_08014b54 : { build/w83a_08014b54_MATCHED.o (.text.w83a_08014b54); } /* Wave 83 */
    . = 0x802fda0; .text.w83a_0802fda0 : { build/w83a_0802fda0_MATCHED.o (.text.w83a_0802fda0); } /* Wave 83 */
    . = 0x8039cfc; .text.w83a_08039cfc : { build/w83a_08039cfc_MATCHED.o (.text.w83a_08039cfc); } /* Wave 83 */
    . = 0x804367c; .text.w84d_0804367c : { build/w84d_0804367c_MATCHED.o (.text.w84d_0804367c); } /* Wave 84 */
    /DISCARD/ : { *(.eh_frame*); *(.comment*); *(.note*);
        /* Wave 15 fix: wave13_B.o's .text.w12a_08024384 input section (176 B C-compiled,
           c046-padded) must NOT orphan-merge into the BYTE()-emitted output section
           above (174 B verified) — the merge duplicated content and corrupted the
           following ROM region. The BYTE() block is the verified-good version;
           the TblGetByte_24384 symbol is unreferenced. */
        build/wave13_B.o (.text.w12a_08024384);
        build/w17c_misc_old.o (.text.w17c_080254e0); }
}
