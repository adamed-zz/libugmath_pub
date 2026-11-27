








#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace {

struct Elem16 {
    double a;
    double b;
};

struct Vec16 {
    Elem16* begin;
    Elem16* end;
    Elem16* cap;
};

constexpr std::size_t kMaxElems = 0x0FFFFFFFFFFFFFFFull;

}

namespace UGS {
namespace Memory {
struct CppMemory {
    static void* __cdecl allocate(std::size_t);
    static void __cdecl free(void*);
};
}
}

extern "C" __declspec(dllimport) void* b27_alloc(std::size_t);
extern "C" __declspec(dllimport) void b27_free(void*);
extern "C" void* (*__imp_b27_alloc)(std::size_t) =
    &UGS::Memory::CppMemory::allocate;
extern "C" void (*__imp_b27_free)(void*) = &UGS::Memory::CppMemory::free;

extern "C" Elem16* __fastcall sub_1800737A0(Vec16* v, Elem16* pos,
                                            const Elem16* value) {
    const std::size_t size = static_cast<std::size_t>(v->end - v->begin);
    if (size == kMaxElems)
        std::_Xlength_error("vector<T> too long");
    const std::size_t newSize = size + 1;
    const std::size_t capacity = static_cast<std::size_t>(v->cap - v->begin);
    const std::size_t half = capacity / 2;
    std::size_t newCapacity;
    if (capacity > kMaxElems - half) {
        newCapacity = kMaxElems;
    } else {
        const std::size_t grown = capacity + half;
        newCapacity = grown < newSize ? newSize : grown;
    }
    Elem16* buf = newCapacity
                      ? static_cast<Elem16*>(b27_alloc(newCapacity *
                                                       sizeof(Elem16)))
                      : nullptr;
    Elem16* inserted = buf + (pos - v->begin);
    *inserted = *value;
    Elem16* dst = buf;
    Elem16* src = v->begin;
    if (pos == v->end) {
        while (src != v->end) {
            *dst = *src;
            ++dst;
            ++src;
        }
    } else {
        while (src != pos) {
            *dst = *src;
            ++dst;
            ++src;
        }
        ++dst;
        while (src != v->end) {
            *dst = *src;
            ++dst;
            ++src;
        }
    }
    if (v->begin)
        b27_free(v->begin);
    v->begin = buf;
    v->end = buf + newSize;
    v->cap = buf + newCapacity;
    return inserted;
}
