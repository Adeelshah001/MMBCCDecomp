/* Wave 20-D @0x08005F44 (110 B code + 14 B pad/pool = 124 B section). MATCHED with main agbcc.
 * Table-entry setup at gEwram_02004830: clears base[10]&1 flag + base[2..3] if set,
 * writes (b,c) into 32-byte record at base+0x470+(a<<5), sets p[28]=1, and if
 * (gEwram_02003670[0x11ae]&248)!=16 and p[31]&16==0, sets p[31]|=16 and calls
 * NodeInit_08022F88(p).
 *
 * Idioms: pinned `register u8 t __asm__("r6")=1` + opaque divided-syntax
 * "add %0,%1,#0" forces `adds r0,r6,#0` before `ands` (compiler swaps operands);
 * u32 runtime mask negation (`nm=2; nm=-nm;` — u8 folds, u32 does not) for
 * `movs r0,#2; negs r0,r0`; explicit `int a32=a<<5` temp forces (a<<5) before
 * 142*8; divided-syntax "add %0,%1,%2" forces `adds r3,r0,r1` order; pinned
 * `register u32 m __asm__("r0")` + opaque "and %0,%0,%1" forces `ands r0,r1`.
 * Pool (12 B) lives in the inter-function gap at 0x8005FB4 (section = 124 B).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 *NodeInit_08022F88(u32 x);

__asm__(
    ".globl gEwram_02004830\n.set gEwram_02004830, 0x02004830\n"
);
extern u8 gEwram_02004830[];
extern u8 gEwram_02003670[];

__attribute__((section(".text.w20d_08005F44")))
void Setup_08005F44(u8 a, u8 b, u8 c)
{
    u8 *base2 = gEwram_02003670;
    register u8 *base __asm__("r1") = gEwram_02004830;
    u8 b10 = base[10];
    register u8 t __asm__("r6") = 1;
    u8 tc;
    u32 nm;
    register u32 m __asm__("r0");
    u8 *addr;
    /* opaque copy forces adds r0,r6,#0 before the ands (compiler swaps operands otherwise).
       Divided-syntax "add" (no s) assembles to 1c30; "adds" is rejected by GAS 2.42. */
    __asm__ ("add %0, %1, #0" : "=r" (tc) : "r" (t));
    if ((tc & b10) != 0) {
        nm = 2;
        nm = -nm;
        nm &= b10;
        base[10] = (u8)nm;
        *(u16 *)(base + 2) = 0;
    }
    {
        int a32 = a << 5;
        u8 *p;
        base += 142 * 8;
        /* divided-syntax forces adds r3,r0,r1 operand order (compiler swaps otherwise) */
        __asm__ ("add %0, %1, %2" : "=r" (p) : "r" (a32), "r" (base));
        p[0] = b;
        p[1] = c;
        if (p[28] == 0) {
            p[2] = b;
            p[3] = c;
        }
        p[28] = t;
        addr = base2 + 0x11ae;
        m = 248;
        /* opaque AND forces ands r0,r1 (compiler swaps operands otherwise).
           Divided-syntax "and" (no s) assembles to the flag-setting encoding. */
        __asm__ ("and %0, %0, %1" : "+r" (m) : "r" (*addr));
        if (m != 16) {
            if ((p[31] & 16) == 0) {
                p[31] |= 16;
                NodeInit_08022F88((u32)p);
            }
        }
    }
}
