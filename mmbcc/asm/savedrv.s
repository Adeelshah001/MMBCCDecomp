	@ MMBCCDecomp — save-driver slice (Wave 0).
	@ All 11 symbols migrated to matched C:
	@   BIOS veneers  -> src/bios.c  (.text.bios,  0x0804DB24)
	@   SRAM prims    -> src/sram.c  (.text.sram,  0x0804DB38)
	@   _call_via_rN  -> asm/thunks.s (.text.thunks, 0x0804DCCC)
	@ This stub keeps the .text.savedrv section (now empty) so the
	@ ldscript slot still resolves.
	.section .text.savedrv,"ax",%progbits
