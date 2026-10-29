/* W40-C v7: 0x08017b6c, TRUE extent 372 B (0x08017b6c..0x08017ce0).
 * v6 + CORRECTION (from the 2-byte patched diff): ROM's beq after each
 * compare skips the bitfield block too, so the bitfield runs ONLY when
 * the compare is true -- it lives INSIDE the if body in both cases.
 * Semantics: chip-slot state machine on s[13] (switch decision tree):
 *   ent = (u8 *)0x082263A8 + s[16] * 16; obj = *(u8 **)(s + 44);
 *   case 0: if ((u8)(s[0x77]-3) > 1 && GetField17(obj) == 0) break;
 *     if (ent[0] != ent[6]) { ChipSlot_Setup(s, ent[1] | 768, ent[6]);
 *       bitfield block; }
 *     ChipSlot_IncUse(s, ent[3]); s[18] = 25; s[13]++;
 *   case 1: if ((s[18] -= 1) == 0) s[13]++;
 *   case 2: if (GetField17(obj) <= 6) break;
 *     if (ent[6] != ent[7]) { ChipSlot_Setup(s, ent[1] | 768, ent[7]);
 *       bitfield block; }
 *     ChipSlot_IncUse(s, ent[4]); s[13]++;
 *   case 3: if ((u8)(s[0x77]-3) > 1) break; DecIfNonZero_18(obj);
 *     *(u32 *)(s + 44) = 0; s[12] = 2; s[20] = *(u32 *)(tbl[s[9]] + 8);
 *   all paths: ChipSlot_Tick(s).
 * Bitfield block: ctr = *(u16 *)0x081705B0;
 *   bits = RAM[(ctr >> 4) * 2] & 3, signed-clamped to 3;
 *   s[69] = (bits << 2) | (s[69] & -13); s[34] = 14.
 * Base compiler: old_agbcc -O2 -mthumb-interwork + w40c_08017b6c_patch.py
 * (register-allocation / scheduling fixups only; see the patch header).
 * Callees via .set at END (GAS idiom).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u8 GetField17_U8(u8 *s);
void DecIfNonZero_18(u8 *s);
void ChipSlot_Setup(u8 *s, u16 b, u8 c);
void ChipSlot_IncUse(u8 *s, u8 idx);
void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w40c_08017b6c")))
void Sub_08017B6C(u8 *s)
{
    u32 i0 = s[16];
    u32 sh0 = i0 << 4;
    u8 *ent = (u8 *)(sh0 + 0x082263A8);
    u8 *obj = *(u8 **)(s + 44);
    switch (s[13]) {
    case 0: {
        u8 v = (u8)(s[0x77] - 3);
        if (v > 1 && GetField17_U8(obj) == 0)
            break;
        if (ent[0] != ent[6]) {
            u16 a = 768;
            u16 ctr;
            u8 bits;
            int vv;
            int m;
            a |= ent[1];
            ChipSlot_Setup(s, a, ent[6]);
            ctr = *(u16 *)0x081705B0;
            bits = ((u8 *)0x020031E4)[(ctr >> 4) * 2] & 3;
            vv = bits;
            m = -13;
            __asm__ volatile("" : "+r" (vv));
            if (vv > 3)
                bits = 3;
            __asm__ volatile("" : "+r" (m));
            s[69] = (bits << 2) | (s[69] & m);
            s[34] = 14;
        }
        ChipSlot_IncUse(s, ent[3]);
        s[18] = 25;
        s[13]++;
        break;
    }
    case 1:
        if ((s[18] -= 1) == 0)
            s[13]++;
        break;
    case 2: {
        if (GetField17_U8(obj) <= 6)
            break;
        if (ent[6] != ent[7]) {
            u16 a = 768;
            u16 ctr;
            u8 bits;
            int vv;
            int m;
            a |= ent[1];
            ChipSlot_Setup(s, a, ent[7]);
            ctr = *(u16 *)0x081705B0;
            bits = ((u8 *)0x020031E4)[(ctr >> 4) * 2] & 3;
            vv = bits;
            m = -13;
            __asm__ volatile("" : "+r" (vv));
            if (vv > 3)
                bits = 3;
            __asm__ volatile("" : "+r" (m));
            s[69] = (bits << 2) | (s[69] & m);
            s[34] = 14;
        }
        ChipSlot_IncUse(s, ent[4]);
        s[13]++;
        break;
    }
    case 3: {
        u8 v = (u8)(s[0x77] - 3);
        if (v > 1)
            break;
        DecIfNonZero_18(obj);
        *(u32 *)(s + 44) = 0;
        {
            register u32 *tblp __asm__("r1") = (u32 *)0x082243D8;
            u32 *e = tblp + s[9];
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)(*e + 8);
        }
        break;
    }
    default:
        break;
    }
    ChipSlot_Tick(s);
}

