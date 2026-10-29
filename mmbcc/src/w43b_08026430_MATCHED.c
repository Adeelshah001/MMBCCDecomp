/* Wave 43 coordinator landing: coordinator-verified 0-diff
 * (standalone rebuild + in-built-ROM check).
 * See staging/w43coord_verify/ for coordinator verification artifacts.
 */
/* Wave 43 Worker B: 0x08026430, TRUE extent 284 B. MATCHED-claim
 * (standalone 0-diff vs baserom, old_agbcc -O2 -mthumb-interwork;
 * main agbcc also 0-diff). Built on W42-C v7 (46 diffs).
 * Semantics (re-read from disassembly): find-or-append a 28-byte record.
 *   s[24]=s[25]=0; if (Validate_263A4(src)) { s[24]=3; return 0; }
 *   for (i = 0; i < *(u16 *)(s+22); i++):
 *     idx = GetIdx_252D0(s+16, i); ent = *(u8 **)(s+4) + idx*28;
 *     if (ent[24] != src[13]) continue;
 *     if (Cmp_2637C(b, ent+14)) continue;
 *     if (idx == 0) { s[24]=1; s[25]=0; } else { s[24]=2; s[25]=(u8)i; }
 *     return 0;
 *   if (*(u16 *)(s+22) > 127) { s[24]=4; return 0; }
 *   idx = BufRemove_25290(s+8, *(u16 *)(s+14)-1); Append_2526C(s+16, idx);
 *   ent = *(u8 **)(s+4) + idx*28;
 *   ent[0]=src[0]; ent[1]=Clamp_26720(src[0]);
 *   ent[2..13]=src[1..12]; ent u16[14,16,18,20]=b u16[0,2,4,6];
 *   *(u16 *)(ent+22)=0x8000; ent[24]=src[13]; ent[25]=1;
 *   return idx | 0x2000;
 * Techniques that closed the last 46 diffs (all plain C, no asm):
 *   (a) two-statement loop add: ent=(u8 *)(idx*28); ent+=(u32)base
 *       -> ROM's adds r0,r0,r1 (offset in r0, base in r1);
 *   (b) plain u16 variable hv=0x8000 for the tail store -> ROM's
 *       movs r0,#128; lsls r0,#8; strh (and the return temp then
 *       lands in r2, matching ROM, instead of r1);
 *   (c) trailing __asm__(".balign 4, 0") -> the ROM's 00 00
 *       inter-function padding (GAS otherwise emits a 0x46c0 nop;
 *       code itself is 282 B, extent 284 B incl. padding).
 * Callees via .set at END (GAS idiom). Registry status re-checked
 * this wave (W42-C's notes were stale): GetIdx_252D0 (0x080252d0),
 * Cmp_2637C (0x0802637c), BufRemove_25290, Append_2526C and
 * Clamp_26720 are all MATCHED; only Validate_263A4 (0x080263a4,
 * registry BLOCKED) needs .set adjudication at landing.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u8 Validate_263A4(u8 *src);
u8 GetIdx_252D0(u8 *list, u16 i);
u8 Cmp_2637C(u8 *b, u8 *ent14);
u8 BufRemove_25290(u8 *list, u16 idx);
void Append_2526C(u8 *list, u8 idx);
u8 Clamp_26720(u8 v);

__attribute__((section(".text.w43b_08026430")))
u16 F_08026430(u8 *s, u8 *b, u8 *src)
{
    u16 i;
    u8 idx;
    s[24] = 0;
    s[25] = 0;
    if (Validate_263A4(src)) {
        s[24] = 3;
        return 0;
    }
    for (i = 0; i < *(u16 *)(s + 22); i++) {
        register u8 *ent __asm__("r0");
        u8 *base;
        idx = GetIdx_252D0(s + 16, i);
        base = *(u8 **)(s + 4);
        ent = (u8 *)(idx * 28);
        ent += (u32)base;
        if (ent[24] != src[13])
            continue;
        if (Cmp_2637C(b, ent + 14))
            continue;
        if (idx == 0) {
            s[24] = 1;
            s[25] = 0;
        } else {
            s[24] = 2;
            s[25] = (u8)i;
        }
        return 0;
    }
    if (*(u16 *)(s + 22) > 127) {
        s[24] = 4;
        return 0;
    }
    idx = BufRemove_25290(s + 8, *(u16 *)(s + 14) - 1);
    Append_2526C(s + 16, idx);
    {
        u8 *ent = *(u8 **)(s + 4) + idx * 28;
        u16 hv;
    ent[0] = src[0];
    ent[1] = Clamp_26720(src[0]);
    ent[2] = src[1];
    ent[3] = src[2];
    ent[4] = src[3];
    ent[5] = src[4];
    ent[6] = src[5];
    ent[7] = src[6];
    ent[8] = src[7];
    ent[9] = src[8];
    ent[10] = src[9];
    ent[11] = src[10];
    ent[12] = src[11];
    ent[13] = src[12];
    *(u16 *)(ent + 14) = *(u16 *)(b + 0);
    *(u16 *)(ent + 16) = *(u16 *)(b + 2);
    *(u16 *)(ent + 18) = *(u16 *)(b + 4);
    *(u16 *)(ent + 20) = *(u16 *)(b + 6);
    hv = 0x8000;
    *(u16 *)(ent + 22) = hv;
    ent[24] = src[13];
    ent[25] = 1;
    }
    return idx | 0x2000;
}

/* Pad to 4-byte alignment with zeros (ROM inter-function padding is 00 00,
 * whereas GAS would otherwise emit a 0x46c0 Thumb nop here). */
__asm__(".balign 4, 0");

__asm__(".set Validate_263A4, 0x080263a4");
__asm__(".set GetIdx_252D0, 0x080252d0");
__asm__(".set Cmp_2637C, 0x0802637c");
__asm__(".set BufRemove_25290, 0x08025290");
__asm__(".set Append_2526C, 0x0802526c");
