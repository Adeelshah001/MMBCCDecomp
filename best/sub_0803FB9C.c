u32 sub_0803FCC4(u16 v) {
    int x = v;
    u32 r = 0;
    if (x > 0x3B1) goto end;
    if (x < 0x3B0) goto end;
    r = 1;
end:
    return r;
}

u32 sub_0803FC8C(u16 v) {
    int x = v;
    u32 r = 0;
    if (v == 0x1021) goto set;
    if (x > 0x1021) goto check2;
    if (v == 0x50) goto set;
    goto end;
check2:
    if (v == 0x2021) goto set;
    if (v == 0x3021) goto set;
    goto end;
set:
    r = 1;
end:
    return r;
}

u32 sub_0803FB9C(u16 v) {
    int x = v;
    u32 r = 0;
    if (v == 0x2201) goto set;
    if (x > 0x2201) goto check2;
    if (v == 0x1200) goto set;
    goto end;
check2:
    if (v == 0x4201) goto set;
    goto end;
set:
    r = 1;
end:
    return r;
}
