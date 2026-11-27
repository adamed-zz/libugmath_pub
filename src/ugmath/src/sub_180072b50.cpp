






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

struct VecHead {
    void* b;
    void* e;
    void* c;
};

extern "C" void __fastcall sub_180072B50(VecHead*  , VecHead* first,
                                         VecHead* last) {
    for (; first != last; ++first) {
        if (first->b) {
            b27_free(first->b);
            first->b = nullptr;
            first->e = nullptr;
            first->c = nullptr;
        }
    }
}
