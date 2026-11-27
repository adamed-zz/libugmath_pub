




#include <cstdlib>

extern "C" [[noreturn]] void sub_180093FC0();

extern "C" void* sub_180079B00(void* p, unsigned long long n, unsigned long long cap) {
    if (n > 0x1FFFFFFFFFFFFFFFULL || cap > 0x1FFFFFFFFFFFFFFFULL) sub_180093FC0();
    unsigned long long sz = 8 * n;
    void* r = std::realloc(p, sz);
    if (!r && sz) sub_180093FC0();
    return r;
}
