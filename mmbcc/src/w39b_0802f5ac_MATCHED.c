/* W39-B C: 0x0802f5ac, 896 B. Chip-ID dispatch, goto-structured to place the >199 body after the stubs. */
typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16; typedef signed int s32; typedef unsigned int u32;
extern void Sub_0802D7A0(u8 *s, u8 a, u8 b, int z, int e, int f, s16 g, s16 h, int code, u8 d);
__attribute__((section(".text.w39b_0802f5ac")))
void Sub_0802F5AC(u8 *s, u8 a, u8 b, u16 c, u8 idx, u8 d)
{
    int code = 0;
    if (idx <= 199) goto sw;
    goto big;
sw:
    switch (idx) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 33:
    case 34:
    case 35:
    case 40:
    case 41:
    case 42:
    case 51:
    case 52:
    case 53:
    case 54:
    case 59:
    case 60:
    case 61:
    case 63:
    case 64:
    case 65:
    case 116:
    case 155:
    case 174:
        code = 35; goto call;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 43:
    case 44:
    case 45:
    case 49:
    case 50:
    case 55:
    case 56:
    case 57:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 89:
    case 90:
    case 110:
    case 173:
        code = 36; goto call;
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 36:
    case 37:
    case 38:
    case 175:
    case 177:
    case 178:
    case 179:
        code = 37; goto call;
    case 46:
    case 47:
    case 84:
    case 85:
    case 86:
        code = 48; goto call;
    case 81:
    case 82:
        code = 49; goto call;
    case 39:
    case 58:
    case 66:
    case 67:
    case 68:
    case 78:
    case 79:
    case 80:
    case 87:
    case 88:
    case 91:
    case 92:
    case 93:
    case 94:
    case 95:
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 109:
    case 111:
    case 112:
    case 113:
    case 114:
    case 115:
    case 126:
    case 127:
    case 128:
    case 129:
    case 131:
    case 132:
    case 133:
    case 134:
    case 156:
    case 157:
    case 158:
    case 160:
    case 176:
        code = 50; goto call;
    case 48:
    case 62:
    case 69:
    case 70:
    case 71:
    case 83:
    case 117:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 130:
    case 135:
    case 136:
    case 137:
    case 138:
    case 139:
    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:
    case 147:
    case 148:
    case 149:
    case 150:
    case 151:
    case 152:
    case 153:
    case 154:
    case 159:
    case 161:
    case 162:
    case 163:
    case 164:
    case 165:
    case 166:
    case 167:
    case 168:
    case 169:
    case 170:
    case 171:
    case 172:
    case 180:
    case 181:
    case 182:
    case 183:
    case 184:
    case 185:
    case 186:
    case 187:
    case 188:
    case 189:
    case 190:
        code = 25; goto call;
    case 125:
        code = 66; goto call;
    default: goto check;
    }
big:
    code = 51;
check:
    if (code == 0) goto ret;
call:
    Sub_0802D7A0(s, a, b, 0, 2, 0, c, c, code, d);
ret:
    return;
}
__asm__(".set Sub_0802D7A0, 0x0802d7a0");
