u32 sub_0803FDBC(u16 v) {
    int x = v;
    u32 r = 0;
    if (v == 0x1200) goto set;
    if (x > 0x1200) goto check_high;
    if (v == 0x226) goto set;
    if (v == 0x271) goto set;
    goto end;
check_high:
    if (v == 0x2201) goto set;
    if (v == 0x4201) goto set;
    goto end;
set:
    r = 1;
end:
    return r;
}
