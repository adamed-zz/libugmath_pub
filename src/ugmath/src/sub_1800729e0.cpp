






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

extern "C" int* __fastcall sub_1800729E0(int** v, int* buf,
                                         std::size_t size, std::size_t cap) {
    if (void* p = *v)
        b27_free(p);
    v[0] = buf;
    v[1] = buf + size;
    v[2] = buf + cap;
    return v[2];
}
