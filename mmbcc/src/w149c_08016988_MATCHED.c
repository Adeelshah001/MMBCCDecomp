/* Wave 149-C LANDED (Wave 149 coordinator): 0x08016988 v8, manual method.
 * Landed 0-diff (780/780 B, old_agbcc -O2). Three .set stubs DROPPED at landing
 * (already .globl-defined elsewhere, linked to the real definitions):
 * Sub_0800D9FC (w51c line 126), Sub_0804A378 (w126a line 147),
 * G_02003670 (w84d line 118). Other 9 .set stubs kept (no .globl definition).
 * CLEAN 0-DIFF (780/780 B, oldO2) -- closing lever: case-1 if-branch
 * block-scoped zero (int z = 0; s[0x13] = z;) breaks the zero liveness
 * that flipped the pair-store homes: pair store now pointer r1 /
 * value r0 as in ROM, and the s13 tail reloads movs r0,#0 instead of
 * reusing the s25 zero. Parent of v7 (10/10); A3 (block zero for the
 * pair store itself) regressed to 13/13 and was rejected.
 * TRUE extent 780 B (next fn 0x08016C94).
 */
/* Wave 142-C (STAGED ONLY, NOT LANDED): 0x08016988 v1, manual method.
 * Hand-read from the disassembly (rdis_16988.txt, 312 insns, 1 switch).
 * void Sub_08016988(u8 *s): state machine on s[0xe] (0..11, default
 * epilogue). q = s + 0x7c (sub-struct pointer, kept in r6); ptr =
 * *(u32 *)(s + 0x2c) (a pointer stored in the struct).
 * Shared epilogue: Sub_0800D9FC(s); return. Shared advance block:
 * s[0xe]++; epilogue. Shared increment block: s[0x12]++; epilogue.
 * Case 0: if (q[7]==0) 174A4(ptr,0);  [twin delta vs 16690: arg 0, not 1] DD2C(s,0xffffc400,0); D9EC(s,0);
 *   s[0x12]=0; if (q[7]!=0) s[0xe]=5; else s[0xe]++; epilogue.
 * Case 1: s[0x24]|=1; s[0x24]=((s[0x24]|1)&~0x1e)|((s[0x12]&0xf)<<1);
 *   s[0x25]=0; *(u16*)(s+0x26)=0x4210;  [twin delta vs 16690: (0,0x4210), not (1,0)] if (s[0x12]==0xf) { s[0x13]=0;
 *   s[0xe]++; } else s[0x12]++; epilogue.
 * Case 2: if ((u8)17474(ptr)>6) s[0xe]++; else s[0x13]++; epilogue.
 * Case 3: s[0x24] pattern (as case 1); s[0x25]=0; *(u16*)(s+0x26)=0x4210;  [twin delta vs 16690: (0,0x4210), not (1,0)]
 *   if (s[0x12]==0) s[0xe]++; else s[0x12]--; epilogue.
 * Case 4: 17478(ptr,8); 17464(ptr); ptr=0; DD2C(s,0xffffc400,0);
 *   D9EC(s,0); q[4]=0; 1F68(s,0); epilogue.
 * Case 5: if ((u8)17474(ptr)==0) { s[0x24] pattern; s[0x25]=1;
 *   *(u16*)(s+0x26)=0; if (s[0x12]<=0xe) s[0x12]++; }
 *   else { s[0x24]=(s[0x24]|1)&~0x1e; s[0x25]=0; *(u16*)(s+0x26)=0x4210;  [twin delta vs 16690: (0,0x4210), not (1,0)]
 *   if ((u8)17474(ptr)>6) s[0xe]=5; else { *(0x0200481f)=
 *   (*(0x0200481f)&0xf)|0x40; s[0x21]=6; D9EC(s,3); s[0xe]++; } }
 *   epilogue.
 * Case 6: if ((u16)1F50(s)==0) epilogue; else if ((u8)17474(ptr)>1 &&
 *   (u8)17474(ptr)<=5) { s[0x21]=6; D9EC(s,3); epilogue; }
 *   else if (q[7]!=2) s[0xe]++; else { D9EC(s,7); s[0xe]=9; } epilogue.
 * Case 7: if ((u16)1F50(s)!=0) { D9EC(s,0); s[0xe]++; } epilogue.
 * Case 8: if ((u8)17474(ptr)<=6) epilogue; else fall through to case 4.
 * Case 9: s[0x21]=0x3c; s[0x12]=0x28;
 *   1EE14(0,-4,s[0x23]&0xf,0xffffc400,0); s[0xe]++; epilogue.
 * Case 10: s[0x12]--; if (s[0x12]==0) { D9EC(s,2); 4A378(0x7f);
 *   s[0xe]++; } epilogue.
 * Case 11: if ((u8)17474(ptr)>6) { s[0xa]&=0xfe; 17478(ptr,8);
 *   17464(ptr); ptr=0; DD2C(s,0xffffc400,0); D9EC(s,0); q[4]=0;
 *   1F68(s,0); } epilogue.
 * TRUE extent 780 B (next fn 0x08016C94).
 * Plain C + .set stubs only (no pin, no inline asm in the body, no barrier).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_080174A4(u32 a, int b);
extern void Sub_0800DD2C(u8 *a, u32 b, int c);
extern void Sub_0800D9EC(u8 *a, int b);
extern u8 Sub_08017474(u32 a);
extern void Sub_08017478(u32 a, int b);
extern void Sub_08017464(u32 a);
extern u16 Sub_08011F50(u8 *a);
extern void Sub_08011F68(u8 *a, int b);
extern void Sub_0801EE14(int a, int b, int c, u32 d, int e);
extern void Sub_0800D9FC(u8 *a);
extern void Sub_0804A378(int a);
extern u8 G_02003670[];

__asm__(".set Sub_080174A4, 0x080174A4");
__asm__(".set Sub_0800DD2C, 0x0800DD2C");
__asm__(".set Sub_0800D9EC, 0x0800D9EC");
__asm__(".set Sub_08017474, 0x08017474");
__asm__(".set Sub_08017478, 0x08017478");
__asm__(".set Sub_08017464, 0x08017464");
__asm__(".set Sub_08011F50, 0x08011F50");
__asm__(".set Sub_08011F68, 0x08011F68");
__asm__(".set Sub_0801EE14, 0x0801EE14");

__attribute__((section(".text.w149c_08016988_v8_oldO2")))
void Sub_08016988(u8 *s)
{
    u8 *q = s + 0x7c;

    switch (s[0xe]) {
    case 0:
        if (q[7] == 0)
            Sub_080174A4(*(u32 *)(s + 0x2c), 0);
        Sub_0800DD2C(s, 0xffffc400, 0);
        Sub_0800D9EC(s, 0);
        s[0x12] = 0;
        if (q[7] == 0)
            s[0xe]++;
        else
            s[0xe] = 5;
        break;
    case 1:
        s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
        s[0x25] = 0;
        { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
        if (s[0x12] == 0xf) {
            int z = 0;
            s[0x13] = z;
            s[0xe]++;
        } else {
            s[0x12]++;
        }
        break;
    case 2:
        if ((u8)Sub_08017474(*(u32 *)(s + 0x2c)) > 6)
            s[0xe]++;
        else
            s[0x13]++;
        break;
    case 3:
        s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
        s[0x25] = 0;
        { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
        if (s[0x12] == 0)
            s[0xe]++;
        else
            s[0x12]--;
        break;
    case 5:
        if ((u8)Sub_08017474(*(u32 *)(s + 0x2c)) != 0) {
            { int t = s[0x24] | 1; { int m = ~0x1e; s[0x24] = t & m; } }
            s[0x25] = 0;
            { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
            if ((u8)Sub_08017474(*(u32 *)(s + 0x2c)) > 6) {
                s[0xe] = 5;
            } else {
                u8 *g = G_02003670;
                g += 0x11af;
                *g = (*g & 0xf) | 0x40;
                s[0x21] = 6;
                Sub_0800D9EC(s, 3);
                s[0xe]++;
            }
        } else {
            s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
            s[0x25] = 0;
            { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
            if (s[0x12] <= 0xe)
                s[0x12]++;
        }
        break;

    case 6:
        if ((u16)Sub_08011F50(s) == 0)
            break;
        if ((u8)Sub_08017474(*(u32 *)(s + 0x2c)) > 1) {
            if ((u8)Sub_08017474(*(u32 *)(s + 0x2c)) <= 5) {
                s[0x21] = 6;
                Sub_0800D9EC(s, 3);
                break;
            }
        }
        if (q[7] != 2) {
            s[0xe]++;
        } else {
            Sub_0800D9EC(s, 7);
            s[0xe] = 9;
        }
        break;
    case 7:
        if ((u16)Sub_08011F50(s) != 0) {
            Sub_0800D9EC(s, 0);
            s[0xe]++;
        }
        break;
    case 8:
        if ((u8)Sub_08017474(*(u32 *)(s + 0x2c)) <= 6)
            break;
    case 4:
        Sub_08017478(*(u32 *)(s + 0x2c), 8);
        Sub_08017464(*(u32 *)(s + 0x2c));
        *(u32 *)(s + 0x2c) = 0;
        Sub_0800DD2C(s, 0xffffc400, 0);
        Sub_0800D9EC(s, 0);
        q[4] = 0;
        Sub_08011F68(s, 0);
        break;
    case 9: {
        u8 *p = s + 0x21;
        int z = 0;
        *p = 0x3c;
        s[0x12] = 0x28;
        Sub_0801EE14(0, ~3, (int)(((unsigned)(s[0x23] << 28)) >> 28), 0xffffc400, z);
        s[0xe]++;
        break;
    }
    case 10:
        s[0x12]--;
        if (s[0x12] == 0) {
            Sub_0800D9EC(s, 2);
            Sub_0804A378(0x7f);
            s[0xe]++;
        }
        break;
    case 11:
        if ((u8)Sub_08017474(*(u32 *)(s + 0x2c)) > 6) {
            int t = s[0xa] & 0xfe;
            { int z = 0;
            s[0xa] = t;
            Sub_08017478(*(u32 *)(s + 0x2c), 8);
            Sub_08017464(*(u32 *)(s + 0x2c));
            *(u32 *)(s + 0x2c) = z;
            Sub_0800DD2C(s, 0xffffc400, 0);
            Sub_0800D9EC(s, 0);
            q[4] = z;
            Sub_08011F68(s, 0);
            }
        }
        break;
    default:
        break;
    }
    Sub_0800D9FC(s);
}
