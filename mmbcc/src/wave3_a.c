/* MMBCCDecomp — Wave 3 batch1 staged matches (worker A).
 * MATCHED 2026-10-20. 10/15 functions byte-identical (main agbcc -O2
 * -mthumb-interwork unless noted). 5 BLOCKED (see docs/match_notes_wave3_a.md).
 *
 * Functions (all names tentative — inferred from behavior only):
 *  0x08017474 GetField17_U8      (4 B)  u8 s[17] getter; 49 callers
 *  0x080265F4 GetField22_U16     (4 B)  u16 *(s+22) getter
 *  0x0802654C GetField24_U8      (4 B)  u8 s[24] getter
 *  0x0800EDE4 SetEwram5130_12    (12 B) *(u16*)(0x02005130+12) = v
 *  0x0804A3F0 GetEwramBD20_130   (12 B) return *(u8*)(0x0200BD20+130)
 *  0x080174C4 SetField120_U16Pair (8 B) *(u16*)(s+120)=b; *(u16*)(s+122)=c
 *  0x080258F8 GetIndexedU8       (10 B) return *(u8*)(a+((u16)b<<2)+21)
 *  0x08002EE0 CopyMosaicReg      (20 B) *(u16*)0x0400004C = *(u16*)0x02003240
 *  0x080266F0 GetRomTableU16     (16 B) return *(u16*)(0x0822740C+(idx<<4)+6)
 *  0x0800440C InitLinkedNode     (16 B) *0x0200081C=s; *(s+12)=s+20
 *
 * Absolute symbols (.set) are at the END of this file: GAS 2.42
 * mis-binds R_ARM_THM_CALL when the .set precedes the code (see
 * docs/match_notes_wave2.md). Remove each .set when that symbol gets
 * a real definition (duplicate-symbol otherwise).
 *
 * Landing notes:
 * - GetIndexedU8 (0x080258F8): compiled section is 12 B (10 code + 2 pad);
 *   ROM has 10 B (next function immediately after). Strip the 2-byte pad.
 * - All other sections are exact size (pools included where present).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 gEwram_02005130[];
extern u8 gEwram_0200BD20[];
extern u16 gRegMosaic[];
extern u16 gEwram_02003240[];
extern u8 gRom_0822740C[];
extern u8 *gEwram_0200081C;

/* 0x08017474: u8 getter at offset 17. Tentative. */
__attribute__((section(".text.w3a_getfield17_u8")))
u8 GetField17_U8(u8 *s)
{
    return s[17];
}

/* 0x080265F4: u16 getter at offset 22. Tentative. */
__attribute__((section(".text.w3a_getfield22_u16")))
u16 GetField22_U16(u8 *s)
{
    return *(u16 *)(s + 22);
}

/* 0x0802654C: u8 getter at offset 24. Tentative. */
__attribute__((section(".text.w3a_getfield24_u8")))
u8 GetField24_U8(u8 *s)
{
    return s[24];
}

/* 0x0800EDE4: *(u16*)(0x02005130+12) = v. Tentative. */
__attribute__((section(".text.w3a_setewram5130_12")))
void SetEwram5130_12(u16 v)
{
    u8 *base = gEwram_02005130;
    *(u16 *)(base + 12) = v;
}

/* 0x0804A3F0: return *(u8*)(0x0200BD20+130). Tentative. */
__attribute__((section(".text.w3a_getewrambd20_130")))
u8 GetEwramBD20_130(void)
{
    u8 *base = gEwram_0200BD20;
    return *(base + 130);
}

/* 0x080174C4: *(u16*)(s+120)=b; *(u16*)(s+122)=c. Tentative.
 * The `s += 120` is required: agbcc otherwise keeps the base in r3. */
__attribute__((section(".text.w3a_setfield120_u16pair")))
void SetField120_U16Pair(u8 *s, u16 b, u16 c)
{
    s += 120;
    *(u16 *)s = b;
    *(u16 *)(s + 2) = c;
}

/* 0x080258F8: return *(u8*)(a + ((u16)b<<2) + 21). Tentative.
 * The ((u16)b)<<2 with u32 accumulator is required for the exact
 * `lsls #16; lsrs #14; adds r1,r1,r0` sequence (see match notes). */
__attribute__((section(".text.w3a_getindexedu8")))
u8 GetIndexedU8(u8 *a, u16 b)
{
    u32 off = ((u16)b) << 2;
    off += (u32)a;
    return *(u8 *)(off + 21);
}

/* 2-byte zero pad: ROM has 0000 at 0x08025902 (next function at
 * 0x08025904); GAS would otherwise end the section with c046. */
__attribute__((section(".text.w3a_getindexedu8")))
static const u8 sPad_GetIndexedU8[2] = { 0, 0 };

/* 0x08002EE0: *(u16*)REG_MOSAIC(0x0400004C) = *(u16*)0x02003240. Tentative. */
__attribute__((section(".text.w3a_copymosaicreg")))
void CopyMosaicReg(void)
{
    u16 *dst = gRegMosaic;
    u16 *src = gEwram_02003240;
    *dst = *src;
}

/* 0x080266F0: return *(u16*)(0x0822740C + (idx<<4) + 6). Tentative.
 * 16-byte stride table in ROM; sibling accessor at 0x08026700 (batch2)
 * reads u8 at +11. */
__attribute__((section(".text.w3a_getromtableu16")))
u16 GetRomTableU16(u8 idx)
{
    u8 *base = gRom_0822740C;
    return *(u16 *)(base + ((u16)idx << 4) + 6);
}

/* 0x0800440C: *0x0200081C = s; *(s+12) = s+20. Tentative.
 * The separate `t = s; t += 20` is required for the exact
 * `adds r1,r0,#0; adds r1,#20` sequence. */
__attribute__((section(".text.w3a_initlinkednode")))
void InitLinkedNode(u8 *s)
{
    u8 *t;
    gEwram_0200081C = s;
    t = s;
    t += 20;
    *(u8 **)(s + 12) = t;
}

__asm__(
    ".globl gEwram_02005130\n.set gEwram_02005130, 0x02005130\n"
    ".globl gEwram_0200BD20\n.set gEwram_0200BD20, 0x0200BD20\n"
    ".globl gRegMosaic\n.set gRegMosaic, 0x0400004C\n"
    ".globl gEwram_02003240\n.set gEwram_02003240, 0x02003240\n"
    ".globl gRom_0822740C\n.set gRom_0822740C, 0x0822740C\n"
    ".globl gEwram_0200081C\n.set gEwram_0200081C, 0x0200081C\n"
);
