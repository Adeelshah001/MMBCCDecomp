/* w50b 0x0801EAC4 v9 — duplicated-branch structure + real tail lookup.
 * ROM decode (fresh, 2026-10-26; pools raw LE):
 *   push {r4,r5,lr}; r4=s; r5=*(s+40) cur; bl Sub_D9FC(s) (0x0800d9fc).
 *   bit1 = (cur[0]>>1)&1 (lsrs/movs/ands/cmp/beq). If bit1:
 *     if ((u8)(s[119]-3) > 1) return;
 *     countdown A: if (s[18]!=0) { s[18]--; if (s[18]!=0) return; }
 *     if (cur[0]&1) { table block A (pool 0x0801EB0C = 0x082243D8); return; }
 *   else:
 *     countdown B (identical bytes, separate block);
 *     if (cur[0]&1) { table block B (pool 0x0801EB40 = 0x082243D8); return; }
 *   table block (join 0x0801EB30): s[12]=2; s[20]=*(Tbl[s[9]]+8) [u32 deref
 *     of entry, then +8 u32 deref]; return.
 *   advance: old1=cur[1]; old0h=cur[0]>>4; cur+=4; s[40]=cur;
 *     if (old1!=cur[1] || old0h!=((cur[0]>>4)&15)) mismatch else match.
 *   match: ChipSlot_IncUse(s, cur[2]); goto s18-store.
 *   mismatch: Sub_D6E0(s, cur[1]|0x200, cur[0]>>4);
 *     ChipSlot_IncUse(s, cur[2]);
 *     hv=*(u16*)0x081705B0 (pool 0x0801EBC8, raw b0051708);
 *     b=*(u8*)(0x020031E4 + ((hv>>4)<<1)) (pool 0x0801EBCC, raw e4310002);
 *     cl=b&3; if (cl>3) cl=3; s[69]=(s[69]&~12)|(cl<<2) [ROM movs#13/negs];
 *     s[34]=s[17]+14; then s18-store.
 *   s18-store: s[18]=cur[3]; pop {r4,r5}; pop {r0}; bx r0; pad; pools.
 *   Extent 268 B (0xEAC4-0xEBD0). v1: 184 B / 127 diffs (shared countdown,
 *   constant cl, table block unconditional).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_0800D9FC(u8 *s);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern void Sub_0800D6E0(u8 *s, u32 a, u32 b);

__attribute__((section(".text.w51c_0801eac4")))
void Func_0801EAC4(u8 *s) {
    u8 *cur = *(u8 **)(s + 40);
    u8 old1;
    u8 old0h;
    Sub_0800D9FC(s);
    if (((cur[0] >> 1) & 1) != 0) {
        if ((u8)(s[119] - 3) > 1)
            return;
        if (s[18] != 0) {
            s[18]--;
            if (s[18] != 0)
                return;
        }
        if ((cur[0] & 1) != 0) {
            u32 **base = (u32 **)0x082243D8;
            register u32 sh __asm__("r0");
            u32 *slot;
            __asm__ volatile("" : "+r"(base));
            sh = (u32)(s[9] << 2);
            sh += (u32)base;
            slot = (u32 *)sh;
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*slot + 8);
            return;
        }
    } else {
        if (s[18] != 0) {
            s[18]--;
            if (s[18] != 0)
                return;
        }
        if ((cur[0] & 1) != 0) {
            u32 **base = (u32 **)0x082243D8;
            register u32 sh __asm__("r0");
            u32 *slot;
            __asm__ volatile("" : "+r"(base));
            sh = (u32)(s[9] << 2);
            sh += (u32)base;
            slot = (u32 *)sh;
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*slot + 8);
            return;
        }
    }
    old1 = cur[1];
    {
        register u32 mm __asm__("r1") = 15;
        old0h = (u8)(cur[0] >> 4);
        cur += 4;
        *(u8 **)(s + 40) = cur;
        if (old1 == cur[1] && old0h == (u8)((cur[0] >> 4) & mm)) {
            ChipSlot_IncUse(s, cur[2]);
        } else {
        u16 hv;
        u8 b;
        u8 cl;
        {
            u32 v = 0x200;
            register u32 cp __asm__("r0") = v;
            __asm__ volatile("" : "+r"(v));
            Sub_0800D6E0(s, cur[1] | cp, (u32)(cur[0] >> 4));
        }
        ChipSlot_IncUse(s, cur[2]);
        hv = *(u16 *)0x081705B0;
        b = *(u8 *)(0x020031E4 + ((hv >> 4) << 1));
        cl = (u8)(b & 3);
        {
            int cl2 = cl;
            int mk;
            u32 sh;
            u8 *p69;
            __asm__ volatile("" : "+r"(cl2));
            if (cl2 > 3)
                cl = 3;
            p69 = s + 69;
            sh = (u32)(cl << 2);
            mk = 13;
            __asm__ volatile("" : "+r"(mk));
            mk = -mk;
            *p69 = (u8)((*p69 & mk) | sh);
        }
        {
            u8 tv = (u8)(s[17] + 14);
            s[34] = tv;
        }
        }
    }
    s[18] = cur[3];
}

__asm__(
    ".globl Sub_0800D9FC\n.set Sub_0800D9FC, 0x0800d9fc\n"
    ".globl Sub_0800D6E0\n.set Sub_0800D6E0, 0x0800d6e0\n"
);
