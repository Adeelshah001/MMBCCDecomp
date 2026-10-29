/* Wave 22-C: 0x08011A78 (80 B, main agbcc + explicit .short 0x0000 pad).
 * State-init with TableWalk_080113F4 call. Key shapes:
 * - q pinned r1 but later uses go through p->f0, so ROM's `ldrb r1,[r1,#10]`
 *   (kill q) + `ldr r1,[r4,#0]` reload fall out naturally.
 * - eight (r6) initialized AFTER `*r2 = z` for ROM's movs r5/movs r6 order.
 * - 78 B code + 2 B zero pad: trailing nop replaced via explicit
 *   `.short 0x0000` (linker-padding pad idiom).
 * Evidence: docs/match_notes_wave22_C.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

extern u8 *TableWalk_080113F4(u16 cur);

typedef struct {
    u8 *f0;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 pad[28];
    u8 b35;
} Obj;

__attribute__((section(".text.w22c_08011A78")))
s32 F_08011A78(Obj *p)
{
    register u8 *q __asm__("r1") = p->f0;
    register u8 *r2 __asm__("r2") = (u8 *)p + 35;
    u8 z = 0;
    u8 e;
    u8 t;
    *r2 = z;
    {
        register u8 eight __asm__("r6") = 8;
        e = eight;
        t = q[10];
        if ((e & t) != 0) {
            *r2 = 1;
        }
        if (*(s16 *)(p->f0 + 30) > 0) {
            u16 v = *(u16 *)(p->f0 + 30);
            u8 *w = TableWalk_080113F4(v);
            if (w != 0) {
                p->f0 = w;
                p->b4++;
                goto done;
            }
        }
        p->b4 = eight;
    done:
        p->b5 = z;
        p->b6 = z;
        p->b7 = z;
        return -1;
    }
}
