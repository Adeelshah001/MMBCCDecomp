/* Wave 16 worker B: 0x080257FC (62 B).
 * If GetRomTableU16(TblLookup_25730(s,10)) and (s,11) both <= v,
 * store v to *(u16*)(s+16).
 */
typedef unsigned char u8;
typedef unsigned short u16;


extern u16 GetRomTableU16(u8 idx);
extern u8 TblLookup_25730(u8 *tbl, u8 idx);
u8 TblLookup_25730(u8 *tbl, u8 idx);
u16 GetRomTableU16(u8 idx);

void Sub_257FC(u8 *s, u16 v) __attribute__((section(".text.w16b_080257fc")));
void Sub_257FC(u8 *s, u16 v)
{
    if (GetRomTableU16(TblLookup_25730(s, 10)) > v)
        return;
    if (GetRomTableU16(TblLookup_25730(s, 11)) > v)
        return;
    *(u16 *)(s + 16) = v;
}



__attribute__((section(".text"))) static const u16 w16b_080257fc_pad = 0;