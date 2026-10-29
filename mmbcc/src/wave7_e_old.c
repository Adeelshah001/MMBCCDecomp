/* Wave 7 batch E (coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave7_e.md. */
typedef signed char s8;

/* 0x08047538: Rank_FromValue (coordinator-verified, 154B + 2B 00 pad).
   old_agbcc omits push {lr} for true-leaf switch functions. */
__attribute__((section(".text.w7e_08047538")))
int Rank_FromValue(s8 x)
{
    int r = 0;
    switch (x) {
    case 0: r = 0; break;
    case 5: r = 1; break;
    case 10: r = 2; break;
    case 15: r = 3; break;
    case 20: r = 4; break;
    case 25: r = 5; break;
    }
    return r;
}
__attribute__((section(".text.w7e_08047538")))
static const unsigned short w7e_08047538_gap = 0;
