











#define B24_CPPMEMORY_DLLIMPORT __declspec(dllimport)











#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace UGS {
namespace Memory {








#ifndef B24_CPPMEMORY_DLLIMPORT
#define B24_CPPMEMORY_DLLIMPORT
#endif
struct B24_CPPMEMORY_DLLIMPORT CppMemory {
    static void* __cdecl allocate(std::size_t n);
    static void __cdecl free(void* p);
};

template <class T>
struct SMAlloc {
    using value_type = T;

    SMAlloc() noexcept = default;
    template <class U>
    SMAlloc(const SMAlloc<U>&) noexcept {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(CppMemory::allocate(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t) noexcept { CppMemory::free(p); }

    template <class U>
    bool operator==(const SMAlloc<U>&) const noexcept {
        return true;
    }
    template <class U>
    bool operator!=(const SMAlloc<U>&) const noexcept {
        return false;
    }
};

}

namespace Math {

struct Point3 {
    double x;
    double y;
    double z;
};

class Graph;

typedef std::vector<int, Memory::SMAlloc<int>> IntVector;
typedef std::vector<double, Memory::SMAlloc<double>> DoubleVector;
typedef std::vector<Point3, Memory::SMAlloc<Point3>> Point3Vector;
typedef std::vector<std::pair<int, Point3>, Memory::SMAlloc<std::pair<int, Point3>>>
    IndexedPoint3Vector;
typedef std::pair<Point3, Point3> Point3Pair;
typedef std::vector<Point3Pair, Memory::SMAlloc<Point3Pair>> Point3PairVector;
typedef std::vector<IntVector, Memory::SMAlloc<IntVector>> IntVectorVector;
typedef std::pair<int, int> IndexPair;
typedef std::vector<IndexPair, Memory::SMAlloc<IndexPair>> IndexPairVector;
typedef std::pair<IndexPair, int> ClassifiedPair;
typedef std::vector<ClassifiedPair, Memory::SMAlloc<ClassifiedPair>>
    ClassifiedPairVector;

static_assert(sizeof(Point3) == 24, "Point3 ABI");
static_assert(sizeof(std::pair<int, Point3>) == 32, "pair<int,Point3> ABI");
static_assert(sizeof(Point3Pair) == 48, "pair<Point3,Point3> ABI");
static_assert(sizeof(IntVector) == 24, "vector ABI");
static_assert(sizeof(ClassifiedPair) == 12, "pair<pair<int,int>,int> ABI");



struct GraphLayout {
    int m_vertexCount;
    std::int32_t m_pad0;
    double* m_vertexArray;
    int m_edgeCount;
    std::int32_t m_pad1;
    int* m_edgeArray;
    DoubleVector m_vertices;
    IntVector m_edges;
};

static_assert(sizeof(GraphLayout) == 80, "Graph size ABI");
static_assert(offsetof(GraphLayout, m_vertexCount) == 0, "Graph +0");
static_assert(offsetof(GraphLayout, m_vertexArray) == 8, "Graph +8");
static_assert(offsetof(GraphLayout, m_edgeCount) == 16, "Graph +16");
static_assert(offsetof(GraphLayout, m_edgeArray) == 24, "Graph +24");
static_assert(offsetof(GraphLayout, m_vertices) == 32, "Graph +32");
static_assert(offsetof(GraphLayout, m_edges) == 56, "Graph +56");

}
}


#include <cstring>

#define NOINLINE __declspec(noinline)

extern "C" __declspec(dllimport) void* b24_alloc(unsigned long long n);
extern "C" __declspec(dllimport) void b24_free(void* p);
extern "C" __declspec(noreturn) void sub_180001530();

struct VInt {
    int* first;
    int* last;
    int* end;
};

extern "C" NOINLINE VInt* b24_assign_int(VInt* a1, const VInt* a2) {
    if (a1 != a2) {
        long long n = a2->last - a2->first;
        long long old = a1->last - a1->first;
        if (n <= old) {
            std::memmove(a1->first, a2->first, (size_t)(4 * n));
            a1->last = a1->first + n;
        } else {
            long long cap = a1->end - a1->first;
            if (n > cap) {
                const unsigned long long M = 0x3FFFFFFFFFFFFFFFULL;
                unsigned long long cn = (unsigned long long)cap;
                unsigned long long nc;
                if ((unsigned long long)n > M) sub_180001530();
                if (cn > M - (cn >> 1)) {
                    nc = M;
                } else {
                    nc = cn + (cn >> 1);
                    if ((unsigned long long)n > nc) nc = (unsigned long long)n;
                }
                int* p = a1->first;
                if (p) {
                    b24_free(p);
                    a1->first = nullptr;
                    a1->last = nullptr;
                    a1->end = nullptr;
                }
                int* nv = nc ? (int*)b24_alloc(4 * nc) : nullptr;
                a1->first = nv;
                a1->last = nv;
                a1->end = nv + nc;
                old = 0;
            }
            std::memmove(a1->first, a2->first, (size_t)(4 * old));
            int* d = a1->first + old;
            const int* s = a2->first + old;
            while (s != a2->last) *d++ = *s++;
            a1->last = d;
        }
    }
    return a1;
}
