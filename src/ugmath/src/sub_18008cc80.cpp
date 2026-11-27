








#include <intrin.h>

extern "C" __declspec(noinline) long long sub_18008CC80(int* a1, int* a2, int* a3)
{
    *a3 = 0;
    *a2 = 0;
    *a1 = 0;
    int regs[4];
    __cpuidex(regs, 2, 0);
    unsigned char desc[16];
    for (int i = 0; i < 4; ++i) {
        desc[4 * i + 0] = (unsigned char)((unsigned int)regs[i]);
        desc[4 * i + 1] = (unsigned char)((unsigned int)regs[i] >> 8);
        desc[4 * i + 2] = (unsigned char)((unsigned int)regs[i] >> 16);
        desc[4 * i + 3] = (unsigned char)((unsigned int)regs[i] >> 24);
    }
    char split = 0;
    for (int i = 0; i < 14; ++i) {
        switch (desc[i + 2]) {
            case 0xA:
            case 0x66:
                *a1 = 8;
                break;
            case 0xC:
            case 0x10:
            case 0x15:
            case 0x60:
            case 0x67:
                *a1 = 16;
                break;
            case 0xE:
                *a1 = 24;
                break;
            case 0x1A:
                *a2 = 96;
                break;
            case 0x22:
                *a3 = 512;
                break;
            case 0x23:
                *a3 = 1024;
                break;
            case 0x25:
            case 0x88:
                *a3 = 2048;
                break;
            case 0x29:
            case 0x46:
            case 0x89:
                *a3 = 4096;
                break;
            case 0x2C:
            case 0x30:
            case 0x68:
                *a1 = 32;
                break;
            case 0x39:
            case 0x3B:
            case 0x41:
            case 0x79:
            case 0x81:
                *a2 = 128;
                break;
            case 0x3A:
                *a2 = 192;
                break;
            case 0x3C:
            case 0x42:
            case 0x7A:
            case 0x7E:
            case 0x82:
                *a2 = 256;
                break;
            case 0x3D:
                *a2 = 384;
                break;
            case 0x3E:
            case 0x43:
            case 0x7B:
            case 0x7F:
            case 0x80:
            case 0x83:
            case 0x86:
                *a2 = 512;
                break;
            case 0x40:
                *a2 = 0;
                break;
            case 0x44:
            case 0x78:
            case 0x7C:
            case 0x84:
            case 0x87:
                *a2 = 1024;
                break;
            case 0x45:
            case 0x7D:
            case 0x85:
                *a2 = 2048;
                break;
            case 0x47:
            case 0x4B:
            case 0x8A:
                *a3 = 0x2000;
                break;
            case 0x48:
                *a2 = 3072;
                break;
            case 0x49:
                if (!*a2) {
                    split = 1;
                    *a2 = 4096;
                }
                *a3 = 4096;
                break;
            case 0x4A:
                *a3 = 6144;
                break;
            case 0x4C:
                *a3 = 12288;
                break;
            case 0x4D:
                *a3 = 0x4000;
                break;
            case 0x4E:
                *a2 = 6144;
                break;
            case 0x8D:
                *a3 = 3072;
                break;
            default:
                break;
        }
    }
    if (split && *a2 == *a3)
        *a3 = 0;
    *a1 <<= 10;
    *a2 <<= 10;
    long long result = (unsigned int)(*a3 << 10);
    *a3 = (int)result;
    return result;
}
