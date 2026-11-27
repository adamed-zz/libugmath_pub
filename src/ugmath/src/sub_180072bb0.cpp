





#include <cstdint>

extern "C" int* __fastcall sub_180072BB0(std::intptr_t  , int* first,
                                         int* last, int* dst) {
    for (; first != last; ++dst)
        *dst = *first++;
    return dst;
}
