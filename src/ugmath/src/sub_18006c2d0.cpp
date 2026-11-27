



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
using namespace UGS::Math;
extern "C" void* b24_alloc(unsigned long long n);
extern "C" void b24_free(void* p);
extern "C" __declspec(noreturn) void sub_180001530();

typedef std::pair<Point3, Point3> P3P3;

extern "C" NOINLINE void* b24_resize_p3p3(P3P3* v[3], unsigned long long n) {
    const unsigned long long M = 0x555555555555555ULL;
    if (n > M) sub_180001530();
    P3P3* first = v[0];
    P3P3* last = v[1];
    P3P3* end = v[2];
    unsigned long long oldsize = (unsigned long long)((char*)last - (char*)first) / 48;
    unsigned long long cap = (unsigned long long)((char*)end - (char*)first) / 48;
    unsigned long long newcap;
    if (cap > M - (cap >> 1)) {
        newcap = M;
    } else {
        newcap = cap + (cap >> 1);
        if (newcap < n) newcap = n;
    }
    char* nv = newcap ? (char*)b24_alloc(48 * newcap) : nullptr;
    if (n != oldsize) {
        unsigned long long fill = n - oldsize;
        char* d = nv + 48 * oldsize;
        do {
            for (int k = 0; k < 6; k++) *(unsigned long long*)(d + 8 * k) = 0;
            d += 48;
        } while (--fill);
    }
    char* s = (char*)first;
    char* e = (char*)last;
    char* d = nv;
    while (s != e) {
        for (int k = 0; k < 6; k++) *(unsigned long long*)(d + 8 * k) = *(unsigned long long*)(s + 8 * k);
        d += 48;
        s += 48;
    }
    if (first) b24_free(first);
    v[0] = (P3P3*)nv;
    v[1] = (P3P3*)(nv + 48 * n);
    v[2] = (P3P3*)(nv + 48 * newcap);
    return v[2];
}
