




#include <cstddef>
#include <new>

namespace UGS {
namespace Memory {
class CppMemory {
public:
    __declspec(dllimport) static void *allocate(unsigned __int64);
    __declspec(dllimport) static void *allocate(unsigned __int64, int);
    __declspec(dllimport) static void *allocate(unsigned __int64, std::align_val_t);
    __declspec(dllimport) static void *allocate(unsigned __int64, std::align_val_t, int);
    __declspec(dllimport) static void free(void *);
    __declspec(dllimport) static void free(void *, int);
    __declspec(dllimport) static void free(void *, std::align_val_t);
    __declspec(dllimport) static void free(void *, std::align_val_t, int);
};
}
}

namespace UGS {

struct StlPoint3Less {
    static void *operator new[](size_t n);
    static void *operator new[](size_t n, int z);
    static void *operator new(size_t n, void *p);
    static void *operator new[](size_t n, std::align_val_t a);
    static void *operator new[](size_t n, std::align_val_t a, int z);
    static void operator delete[](void *p);
    static void operator delete[](void *p, int z);
    static void operator delete[](void *p, std::align_val_t a);
    static void operator delete[](void *p, std::align_val_t a, int z);
};

void *StlPoint3Less::operator new[](size_t n) { return Memory::CppMemory::allocate(n); }
void *StlPoint3Less::operator new[](size_t n, int z) { return Memory::CppMemory::allocate(n, z); }
void *StlPoint3Less::operator new(size_t, void *p) { return p; }
void *StlPoint3Less::operator new[](size_t n, std::align_val_t a) { return Memory::CppMemory::allocate(n, a); }
void *StlPoint3Less::operator new[](size_t n, std::align_val_t a, int z) { return Memory::CppMemory::allocate(n, a, z); }
void StlPoint3Less::operator delete[](void *p) { Memory::CppMemory::free(p); }
void StlPoint3Less::operator delete[](void *p, int z) { Memory::CppMemory::free(p, z); }
void StlPoint3Less::operator delete[](void *p, std::align_val_t a) { Memory::CppMemory::free(p, a); }
void StlPoint3Less::operator delete[](void *p, std::align_val_t a, int z) { Memory::CppMemory::free(p, a, z); }

}
