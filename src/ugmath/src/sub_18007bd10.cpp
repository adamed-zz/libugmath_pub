









#include <cstring>

extern "C" __declspec(noinline) unsigned long long* sub_18007BD10(
    unsigned long long* dst, long long n, const unsigned long long* val) {
    if (n > 0) {
        unsigned long long first = *val;
        volatile double zero = 0.0;
        if (first == *(const volatile unsigned long long*)&zero) {
            memset(dst, 0, 8 * (unsigned long long)n);
            return dst + n;
        }
        if (n >= 4) {
            unsigned long long blocks = ((unsigned long long)(n - 4) >> 2) + 1;
            n -= (long long)(4 * blocks);
            do {
                dst[0] = *val;
                dst[1] = *val;
                dst[2] = *val;
                dst[3] = *val;
                dst += 4;
                --blocks;
            } while (blocks);
        }
        while (n > 0) {
            --n;
            *dst++ = *val;
        }
    }
    return dst;
}
