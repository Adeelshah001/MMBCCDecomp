	.text
	.arm
	.global Start

@ GBA ROM header for Mega Man Battle Chip Challenge (USA).
@ Values from ANALYSIS.md §1.1 (user's own dump, read in place).
@ The Nintendo logo (0x04-0x9F) is NOT stored here — gbafix injects it
@ at build time. Total header size must be exactly 0xC0 bytes so that
@ Init (in crt0.s) lands at 0x080000C0.
Start:
	b Init                  @ 0x00: entry branch -> 0xC0
	.fill 156, 1, 0         @ 0x04: Nintendo logo (gbafix fills this)
	.ascii "BATTLECHIPGP"   @ 0xA0: game title (12 bytes)
	.ascii "A89E"           @ 0xAC: game code
	.ascii "08"             @ 0xB0: maker code (Capcom)
	.byte 0x96              @ 0xB2: fixed value
	.byte 0x00              @ 0xB3: main unit code
	.byte 0x00              @ 0xB4: device type
	.fill 7, 1, 0           @ 0xB5: reserved
	.byte 0x00              @ 0xBC: mask ROM version
	.byte 0x00              @ 0xBD: header checksum (gbafix writes the
	                        @      computed value; the build then applies
	                        @      the 0x7B quirk — see tools/finish_rom.py
	                        @      and ANALYSIS.md §1.1)
	.fill 2, 1, 0           @ 0xBE: reserved
	@ end of header = 0xC0
