int sub_0803F920(u16 code)
{
    int result = 0;
    switch (code) {
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x805:
    case 0x821:
    case 0x1022:
    case 0x1030:
    case 0x2030:
    case 0x2800:
    case 0x3030:
    case 0x4030:
        result = 1;
        break;
    }
    return result;
}
