





#include <cstdint>

extern "C" std::int64_t* __fastcall sub_180072BE0(std::intptr_t  ,
                                                  std::int64_t* first,
                                                  std::int64_t* last,
                                                  std::int64_t* dst) {
    for (; first != last; ++dst)
        *dst = *first++;
    return dst;
}
