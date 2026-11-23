int sub_0803F998(u16 arg0) {
    int val = (u16)arg0;
    int val_copy = val;
    int result = 0;

    if (val == 0x1022) goto match;
    if (val <= 0x1022) {
        if (val <= 0x34) {
            if (val >= 0x31) goto match;
            if (val == 0x11) goto match;
            goto nomatch;
        }
        if (val == 0x805) goto match;
        if (val <= 0x805) {
            if (val == 0x40) goto match;
            goto nomatch;
        }
        if (val == 0x821) goto match;
        goto nomatch;
    }
    if (val == 0x2030) goto match;
    if (val <= 0x2030) {
        if (val == 0x1030) goto match;
        if (val == 0x1040) goto match;
        goto nomatch;
    }
    if (val == 0x3030) goto match;
    if (val <= 0x3030) {
        if (val == 0x2800) goto match;
        goto nomatch;
    }
    if (val_copy == 0x4030) goto match;
    goto nomatch;

match:
    result = 1;
nomatch:
    return result;
}
