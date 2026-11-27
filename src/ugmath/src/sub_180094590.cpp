



















#include <intrin.h>

extern "C" void* sub_180094590(void*, unsigned int);

namespace UGS {
namespace Memory {

class CppMemory {
public:
    __declspec(dllimport) static void free(void* p);
};

}
}

namespace {

void dev_tol_slot0(void*) {}

void* const dev_itolerances_vftable[4] = {
    (void*)&dev_tol_slot0,
    (void*)&dev_tol_slot0,
    (void*)&dev_tol_slot0,
    (void*)&dev_tol_slot0,
};

}

extern "C" void* sub_180094590(void* self, unsigned int flags) {
    void* const keep = self;
    void* const vt = (void*)dev_itolerances_vftable;
    *(void* volatile*)keep = vt;
    if ((flags & 1u) == 0) return keep;
    if ((flags & 4u) == 0) {
        UGS::Memory::CppMemory::free(keep);
        __nop();
        return keep;
    }
    ::operator delete(keep, (size_t)0x20);
    return keep;
}
