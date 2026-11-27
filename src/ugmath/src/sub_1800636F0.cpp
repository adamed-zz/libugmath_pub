












#include <cstddef>













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


__declspec(dllimport) void __cdecl ERROR_assertion_failed(const char* file,
                                                          int line,
                                                          const char* message, ...);


namespace UGS { namespace Math { extern int g_algorithmVersion; } }
using UGS::Math::g_algorithmVersion;

extern "C" __declspec(dllexport) void b20_aux_set(int v) {
    g_algorithmVersion = v;
}

extern "C" __declspec(dllexport) int b20_aux_get() {
    return g_algorithmVersion;
}

extern "C" void sub_1800636F0(void* self) {

    UGS::Math::AlgorithmVersionRestorer* payload =
        static_cast<UGS::Memory::SharedPtrCountedBaseImpl_p<
            UGS::Math::AlgorithmVersionRestorer>*>(self)
            ->m_payload;
    int* p = reinterpret_cast<int*>(payload);
    if (!p) return;
    if (*p == -1) {
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_AlgorithmVersion.cxx",
            64, "Never condition true: %s",
            "m_versionToRestore == AlgorithmVersion::VERSION_UNDEFINED");
    } else {
        g_algorithmVersion = *p;
        *p = -1;
    }
    UGS::Memory::CppMemory::free(p);
}
