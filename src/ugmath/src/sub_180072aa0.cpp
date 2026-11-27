






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

extern "C" void __fastcall sub_180072AA0(VecHead* v, VecHead* buf,
                                         std::size_t size,
                                         std::size_t cap) {
    if (v->b) {
        VecHead* p = static_cast<VecHead*>(v->b);
        VecHead* last = static_cast<VecHead*>(v->e);
        if (p != last) {
            do {
                if (p->b) {
                    b27_free(p->b);
                    p->b = nullptr;
                    p->e = nullptr;
                    p->c = nullptr;
                }
                ++p;
            } while (p != last);
        }
        b27_free(v->b);
    }
    v->b = buf;
    v->e = buf + size;
    v->c = buf + cap;
}
