




#include <cstdlib>

extern "C" [[noreturn]] void sub_180093FC0();

extern "C" void* sub_180079AB0(unsigned long long n) {
    if (!n) return 0;
    if (n > 0x1FFFFFFFFFFFFFFFULL) sub_180093FC0();
    unsigned long long sz = 8 * n;
    void* r = std::malloc(sz);
    if (!r && sz) sub_180093FC0();
    return r;
}
