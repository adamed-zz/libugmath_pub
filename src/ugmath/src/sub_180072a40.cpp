






#include <cstddef>
#include <cstdint>

namespace UGS { namespace Memory {
class CppMemory {
public:
    static void* allocate(std::size_t);
    static void free(void*);
};
} }

extern "C" __declspec(dllimport) void b27_free(void*);

extern "C" void (*__imp_b27_free)(void*);

extern "C" std::int64_t* __fastcall sub_180072A40(std::int64_t** v,
                                                  std::int64_t* buf,
                                                  std::size_t size,
                                                  std::size_t cap) {
    if (void* p = *v)
        b27_free(p);
    v[0] = buf;
    v[1] = buf + size;
    v[2] = buf + cap;
    return v[2];
}
