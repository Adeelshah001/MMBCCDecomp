/* Wave 16-D: F_0802FD68 @ 0x0802fd68 (56 B).
 * Coordinator-landed, 0-diff verified vs ROM (bl immediates are
 * R_ARM_THM_CALL relocs). Compiler: main agbcc.
 * Behavior: state machine on p[3]: 0 -> Clr8_08004B94(1), p[3]++,
 * fallthrough; 1 -> r=Dispatch_081705A4_0(), if r==1 { p[3]=0; return 1 }
 * else return 0.
 * Idioms: goto branch layout reproduces cmp/beq/cmp/beq/b with
 * fallthrough. */
typedef unsigned char u8; typedef signed char s8;
void Clr8_08004B94(int x);
s8 Dispatch_081705A4_0(void);
int F_0802FD68(u8 *p) __attribute__((section(".text.w16d_0802fd68")));
int F_0802FD68(u8 *p)
{
    int ret = 0;
    u8 v = p[3];
    if (v == 0)
        goto L1;
    if (v == 1)
        goto L2;
    goto End;
L1:
    Clr8_08004B94(1);
    p[3]++;
L2:
    {
        s8 r = Dispatch_081705A4_0();
        if (r != 1)
            goto End;
        p[3] = 0;
        ret = 1;
    }
End:
    return ret;
}
