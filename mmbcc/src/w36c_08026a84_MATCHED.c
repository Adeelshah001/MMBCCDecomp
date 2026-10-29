/* Wave 36-C MATCHED: 0x08026a84, 124 B, true extent 0x08026a84-0x08026b00 (next fn 0x08026b00).
   Compiler: main agbcc (old_agbcc also 0 diffs). Variants: 8. Key idioms: goto-structured switch (beq/beq/b);
   ++s[6] value reuse; bits base pin r1 + mask pin r0 with mask=mask&bits assignment forcing ands r0,r1;
   draw call 5 args (stack 0); s8 return test for Sub_0804DEE8. Pools LE-verified: 0x082350d0, 0x02002f50, 0x020070f0.
   Verification: clean-room harness 124/124 B, 0 diffs.
   Landing note: Sub_08004E44 .set must be stripped at landing (already defined); other callee .sets kept (unmatched). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
extern void Sub_08004E44(void);
__asm__(".set Sub_08004E44, 0x08004e44");
extern void Sub_08004F18(void);
__asm__(".set Sub_08004F18, 0x08004f18");
extern s8 Sub_0804DEE8(u8 a, int b);
__asm__(".set Sub_0804DEE8, 0x0804dee8");
extern void Sub_08006A54(u32 *p, int a, int b, int c, int d);
__asm__(".set Sub_08006A54, 0x08006a54");
extern void Sub_080267B4(u8 *p, int a);
__asm__(".set Sub_080267B4, 0x080267b4");
extern void Sub_08004F80(void);
__asm__(".set Sub_08004F80, 0x08004f80");
__attribute__((section(".text.w36c_08026a84")))
void Sub_08026A84(u8 *s)
{
    u8 t = s[1];
    if (t == 0) goto case0;
    if (t == 1) goto aa2;
    goto end;
case0:
    s[6] = 0;
    Sub_08004E44();
    s[1]++;
aa2:
    Sub_08004F18();
    if (Sub_0804DEE8(s[6], 20) != 0) {
        u32 *p = (u32 *)0x082350d0;
        Sub_08006A54(*p, 1, 1, 8, 0);
    }
    if (++s[6] > 60) goto docall;
    {
        register u8 *base __asm__("r1") = (u8 *)0x02002f50;
        register u32 mask __asm__("r0") = 1;
        mask = mask & *(u16 *)(base + 4);
        if (mask == 0) goto skipcall;
    }
docall:
    Sub_080267B4((u8 *)0x020070f0, 3);
skipcall:
    Sub_08004F80();
end:;
}
