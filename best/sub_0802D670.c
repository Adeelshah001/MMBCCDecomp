/* Sub_0802D670 @ 0x0802D670 (110 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0802d670_MATCHED.c (registry: mmbcc/src/w36b_0802d670_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Obj { u8 f0; u8 f1; u8 pad2[2]; u16 f4; u16 f6; u16 f8; u16 f10; };

struct S { struct Obj *arr[6]; u32 f24; };

extern u16 sub_0802458C(u8 x);

extern u16 sub_08024570(u8 x);

extern u8 sub_080245FC(u8 x);

extern u8 sub_0803FB9C(u16 x);

void sub_0802D670(struct S *s)
{
    u8 counter;
    s->arr[0] = 0;
    s->arr[1] = 0;
    s->f24 = 0;
    for (counter = 2; counter <= 5; counter++) {
        if (s->arr[counter] != 0) {
            s->arr[counter]->f4 = sub_0802458C(s->arr[counter]->f0);
            s->arr[counter]->f6 = sub_08024570(s->arr[counter]->f0);
            s->arr[counter]->f1 = sub_080245FC(s->arr[counter]->f0);
            if (counter == 2) {
                s->arr[2]->f10 &= 128;
            } else {
                if (sub_0803FB9C(s->arr[counter]->f8) == 0) {
                    s->arr[counter]->f10 = 0;
                }
            }
        }
    }
}
