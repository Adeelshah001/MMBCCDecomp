/* W58-C v5 (sub2 test reads s[13] fresh) (a r2 + b r3 pins on v2) (sub2-advance reads s[13] fresh): 0x08021FDC, TRUE extent 496 B (code 494 B thru bx @0x221c8 +
 * 2 B pad @0x221ca; next fn @0x221cc). Mode machine on s[13] with
 * sub-states on s[14]; every path ends with Sub_0800D9FC(s).
 * Prologue loads: a = *(u8*)*(s+40), b = *(u8*)*(s+44), s18 = s[18],
 * mode = s[13]. Mode 0: a==255 -> end else s[13]=1, s[14]=mode, s[18]=a.
 * Mode 1 sub0: s[14]=mode, s[100]=1536, s[92]=2048, s[84]=20480 then
 * s[84] = s[17]==0 ? -20480 : 61440; shared: f17=s[17]; if f17: s[84]-=s[92],
 * s[92]+=s[100], advance if s[84]<=20480||b==2 (s[14]++, f17=0, s[19]=8,
 * call 0303c(114) unless b==2, s[84]=20480, s[92] via (s+88)[1]=f17,
 * s[100]=f17); else: s[84]+=s[92], s[92]+=s[100], advance if s[84]>20479||
 * b==2 (s[14]++, s[19]=8, call unless b==2, s[84]=20480, s[92]=f17,
 * s[100]=f17). Mode 1 sub2: wobble s[84] by (F_052a0()&3)<<8 (+ if
 * s[19]&mode else -), s[19]--, on (u8)wrap-to-0: s[84]=20480, goto tail
 * (s[13]=mode+1, s[14]=0). Mode 2: a==s18 -> end else tail (3, 0).
 * Mode 3 sub0: s[14]=1, s[100]=1024, s[92]=1536, fall into sub1: f17=s[17];
 * if f17: s[84]-=s[92], s[92]+=s[100], end unless s[84]<=-20480 then
 * (s[14]++, s[84]=-20480, (s+88)[1]=0, s[100]=0); else: s[84]+=s[92],
 * s[92]+=s[100], end unless s[84]>61439 then (s[14]++, s[84]=61440,
 * s[92]=f17, s[100]=f17). Mode 3 sub2: s[13]=s[14]=sub (2).
 * Pools (raw LE): 0x2204c/0x221b4 = 0xffffb000 (-20480), 0x22098 = 0x4fff
 * (20479), 0x22188 = 0xefff (61439).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Sub_0800303C(int a);
__asm__(".set Sub_0800303C, 0x0800303c");
extern int Sub_080052A0(void);
__asm__(".set Sub_080052A0, 0x080052a0");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w59c_08021fdc")))
void Sub_08021FDC(u8 *s)
{
    register int a __asm__("r2") = *(u8 *)(*(u32 *)(s + 40));
    register int b __asm__("r3") = *(u8 *)(*(u32 *)(s + 44));
    u8 s18 = s[18];
    int nm, ns;

    switch (s[13]) {
    case 0: {
        u8 old;
        if (a == 255)
            break;
        old = s[13];
        s[13] = 1;
        s[14] = old;
        s[18] = a;
        break;
    }
    case 1: {
        u8 sub = s[14];
        switch (sub) {
        case 0:
            s[14] = s[13];
            *(u32 *)(s + 100) = 192 << 3;
            *(u32 *)(s + 92) = 128 << 4;
            *(u32 *)(s + 84) = 160 << 7;
            if (s[17] == 0)
                *(u32 *)(s + 84) = -20480;
            else
                *(u32 *)(s + 84) = 240 << 8;
            /* fallthrough to shared block */
        case 1: {
            u8 f17 = s[17];
            if (f17 == 0) {
                int v84 = *(u32 *)(s + 84) + *(u32 *)(s + 92);
                int v92;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                if (v84 > 20479 || b == 2) {
                    s[14]++;
                    s[19] = 8;
                    if (b != 2)
                        Sub_0800303C(114);
                    *(u32 *)(s + 84) = 160 << 7;
                    *(u32 *)(s + 92) = f17;
                    *(u32 *)(s + 100) = f17;
                }
            } else {
                int v84 = *(u32 *)(s + 84) - *(u32 *)(s + 92);
                int v92;
                int c;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                c = 160 << 7;
                if (v84 <= c || b == 2) {
                    u8 ns14;
                    ns14 = s[14] + 1;
                    f17 = 0;
                    s[14] = ns14;
                    s[19] = 8;
                    if (b != 2)
                        Sub_0800303C(114);
                    *(u32 *)(s + 84) = c;
                    __asm__ volatile ("add r0, r4, #0\n\tadd r0, #88\n\tstr %0, [r0, #4]" :: "r" (f17) : "r0", "memory");
                    *(u32 *)(s + 100) = f17;
                }
            }
            break;
        }
        case 2: {
            u32 x;
            if (s[19] & s[13]) {
                *(u32 *)(s + 84) = 160 << 7;
                x = *(u32 *)(s + 84) + ((Sub_080052A0() & 3) << 8);
            } else {
                *(u32 *)(s + 84) = 160 << 7;
                x = *(u32 *)(s + 84) - ((Sub_080052A0() & 3) << 8);
            }
            *(u32 *)(s + 84) = x;
            ns = --s[19];
            if (ns != 0)
                break;
            *(u32 *)(s + 84) = 160 << 7;
            nm = s[13] + 1;
            goto tail;
        }
        }
        break;
    }
    case 2:
        if (a == s18)
            break;
        nm = 3;
        ns = 0;
        /* fallthrough to shared tail */
    tail:
        s[13] = nm;
        s[14] = ns;
        break;
    case 3: {
        u8 sub = s[14];
        switch (sub) {
        case 0:
            s[14] = 1;
            *(u32 *)(s + 100) = 128 << 3;
            *(u32 *)(s + 92) = 192 << 3;
            /* fallthrough to shared block */
        case 1: {
            u8 f17 = s[17];
            if (f17 == 0) {
                int v84 = *(u32 *)(s + 84) + *(u32 *)(s + 92);
                int v92;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                if (v84 > 61439) {
                    s[14]++;
                    *(u32 *)(s + 84) = 240 << 8;
                    *(u32 *)(s + 92) = f17;
                    *(u32 *)(s + 100) = f17;
                }
            } else {
                int v84 = *(u32 *)(s + 84) - *(u32 *)(s + 92);
                int v92;
                *(u32 *)(s + 84) = v84;
                v92 = *(u32 *)(s + 92) + *(u32 *)(s + 100);
                *(u32 *)(s + 92) = v92;
                if (v84 <= -20480) {
                    u32 *p;
                    u32 z;
                    u8 ns14 = s[14] + 1;
                    z = 0;
                    s[14] = ns14;
                    *(u32 *)(s + 84) = -20480;
                    p = (u32 *)(s + 88);
                    p[1] = z;
                    *(u32 *)(s + 100) = z;
                }
            }
            break;
        }
        case 2:
            s[13] = 0;
            s[14] = 0;
            break;
        }
        break;
    }
    }
    Sub_0800D9FC(s);
}

/* Trailing pad: code size is 2 mod 4; the next function is 4-aligned. */
__asm__(".balign 4, 0");
