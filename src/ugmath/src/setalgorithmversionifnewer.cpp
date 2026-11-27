


























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











#include <cstddef>
#include <new>


namespace UGS {
namespace Memory {

template <class T>
class SharedPtr {
public:
    T* m_payload;
    void* m_control;
};

static_assert(sizeof(SharedPtr<Math::AlgorithmVersionRestorer>) == 16,
              "SharedPtr ABI 16B");

}

namespace Math {

enum AlgorithmVersion : int {
};


UGS::Memory::SharedPtr<AlgorithmVersionRestorer> __cdecl SetAlgorithmVersion(
    AlgorithmVersion version, bool apply);
UGS::Memory::SharedPtr<AlgorithmVersionRestorer> __cdecl SetAlgorithmVersionIfNewer(
    AlgorithmVersion version, bool apply);
UGS::Memory::SharedPtr<AlgorithmVersionRestorer> __cdecl SetLatestAlgorithmVersion(
    bool apply);

}
}


extern "C" void* sub_180063420(void** out, void* payload);



namespace b20 {
inline void* MakeCountedBlock(void** out, void* payload) {
    typedef UGS::Memory::SharedPtrCountedBaseImpl_p<UGS::Math::AlgorithmVersionRestorer>
        Block;
    *out = nullptr;
    Block* block =
        static_cast<Block*>(UGS::Memory::SharedPtrCountedBase::Alloc(sizeof(Block)));
    if (block) {
        new (block) Block(static_cast<UGS::Math::AlgorithmVersionRestorer*>(payload));
    }
    *out = block;
    return out;
}
}


extern "C" __declspec(dllexport) void b20_aux_set(int v);
extern "C" __declspec(dllexport) int b20_aux_get();


namespace UGS {
namespace Math {

__declspec(dllimport) AlgorithmVersion __cdecl GetAlgorithmVersion();

UGS::Memory::SharedPtr<AlgorithmVersionRestorer> __cdecl SetAlgorithmVersionIfNewer(
    AlgorithmVersion version, bool apply) {
    if (apply && static_cast<int>(version) > static_cast<int>(GetAlgorithmVersion())) {
        return SetAlgorithmVersion(version, true);
    }
    return SetAlgorithmVersion(version, false);
}

}
}
