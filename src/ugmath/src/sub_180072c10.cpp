





#include <cstdint>

extern "C" std::int64_t* __fastcall sub_180072C10(std::intptr_t  ,
                                                  std::int64_t* first,
                                                  std::int64_t* last,
                                                  std::int64_t* dst) {
    for (; first != last; dst += 3, first += 3) {
        const std::int64_t a = first[0];
        const std::int64_t b = first[1];
        const std::int64_t c = first[2];
        first[0] = 0;
        first[1] = 0;
        first[2] = 0;
        dst[0] = a;
        dst[1] = b;
        dst[2] = c;
    }
    return dst;
}
