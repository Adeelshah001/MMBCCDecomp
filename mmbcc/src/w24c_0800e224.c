/* Wave 24 Worker C @0x0800e224 (168 B incl pools). MATCHED with main agbcc.
 * ChipList_Setup_0800E224: S[24:25]=1; if S[21]==0 { S[21]++; n1=
 * Node_PopAndInit_11E20(1,0,1); n2=Node_PopAndInit_11E20(1,1,1);
 * Sub_16E0C(n1,S[4]); Sub_16E0C(n2,S[5]); } ListIterate_D568 over
 * 0x02005270/0x020053C0; load a=*(u32*)0x02005020, b=*(u32*)0x02005024;
 * if ((u16)Byte128_IsZero(a)) S[22]|=1; if ((u16)Byte128_IsZero(b)) S[22]|=2;
 * if (S[22]==3 && (u8)Cmp_08004E0C(0)) { S[24:25]=0; SetByte20(0); }.
 * Idioms: `v=1; v|=S[22]; S[22]=v` for the movs-first orr; zero variable
 * reused for strh+bl to avoid the second movs r0,#0.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 *Node_PopAndInit_11E20(u8 a, u8 b, u8 c);
extern void Sub_16E0C(u8 *s, u32 v);
extern void ListIterate_D568(u8 *s);
extern u32 Byte128_IsZero(u8 *s);
extern int Cmp_08004E0C(u8 x);
extern void SetByte20_Clear21to23_02005130(u8 v);

__attribute__((section(".text.w24c_0800e224")))
void ChipList_Setup_0800E224(void)
{
    u8 *S = (u8 *)0x02005130;
    u32 *n1, *n2;
    u32 *p;
    u8 v;

    *(u16 *)(S + 24) = 1;
    if (S[21] == 0) {
        S[21]++;
        n1 = Node_PopAndInit_11E20(1, 0, 1);
        n2 = Node_PopAndInit_11E20(1, 1, 1);
        Sub_16E0C((u8 *)n1, S[4]);
        Sub_16E0C((u8 *)n2, S[5]);
    }
    ListIterate_D568(*(u8 **)0x02005270);
    ListIterate_D568(*(u8 **)0x020053C0);
    p = (u32 *)0x02005020;
    n1 = (u32 *)p[0];
    n2 = (u32 *)p[1];
    if ((u16)Byte128_IsZero((u8 *)n1) != 0) {
        u8 v1 = 1;
        v1 |= S[22];
        S[22] = v1;
    }
    if ((u16)Byte128_IsZero((u8 *)n2) != 0) {
        u8 v2 = 2;
        v2 |= S[22];
        S[22] = v2;
    }
    if (S[22] == 3) {
        u8 z = 0;
        v = Cmp_08004E0C(0);
        if ((u8)v != 0) {
            *(u16 *)(S + 24) = z;
            SetByte20_Clear21to23_02005130(z);
        }
    }
}
