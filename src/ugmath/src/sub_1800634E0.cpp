













#include <cstddef>
#include <new>













#include <cstddef>

namespace UGS {
namespace Math {
class AlgorithmVersionRestorer {
public:
    int* m_versionToRestore;
};
}

namespace Memory {

class SharedPtrCountedBase {
public:


    virtual ~SharedPtrCountedBase();
    virtual int release() { return 0; }



    static void* __cdecl Alloc(std::size_t n) { return allocate(n); }
    static void Release(void* p) { free(p); }

private:
    static __declspec(dllimport) void* __cdecl allocate(std::size_t n);
    static __declspec(dllimport) void __cdecl free(void* p);
};


template <class T>
class SharedPtrCountedBaseImpl_p : public SharedPtrCountedBase {
public:
    explicit SharedPtrCountedBaseImpl_p(T* payload) : m_payload(payload) {}

    ~SharedPtrCountedBaseImpl_p() override;

    int m_strong = 1;
    int m_weak = 1;
    T* m_payload;
};

class CppMemory {
public:
    static __declspec(dllimport) void* __cdecl allocate(std::size_t n);
    static __declspec(dllimport) void __cdecl free(void* p);
};

}
}

static_assert(sizeof(UGS::Memory::SharedPtrCountedBaseImpl_p<UGS::Math::AlgorithmVersionRestorer>) ==
                  0x18,
              "counted block ABI 0x18");


extern "C" void* sub_1800634E0(void* self, char flags) {
    new (self) UGS::Memory::SharedPtrCountedBase();
    if ((flags & 1) != 0) {
        if ((flags & 4) == 0) {
            UGS::Memory::SharedPtrCountedBase::Release(self);
            return self;
        }
        ::operator delete(self, 0x18);
    }
    return self;
}
