


















#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <stdexcept>












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



#define NOINLINE __declspec(noinline)
#define FORCEINLINE __forceinline

extern "C" __declspec(dllimport) void* b24_alloc(unsigned long long n);
extern "C" __declspec(dllimport) void b24_free(void* p);

struct RVec {
    void* first;
    void* last;
    void* end;
};

struct RGraph {
    int vertexCount;
    int pad0;
    double* vertexArray;
    int edgeCount;
    int pad1;
    int* edgeArray;
    RVec vertices;
    RVec edges;
};

struct PairII {
    int a;
    int b;
};

struct PairTriple {
    int a;
    int b;
    int c;
};

static FORCEINLINE int EdgeCountRaw(const RGraph* g) {
    if (g->edgeArray) return g->edgeCount;
    long long bytes = (long long)((const char*)g->edges.last - (const char*)g->edges.first);
    return (int)((unsigned long long)(bytes >> 2) >> 1);
}

static FORCEINLINE const int* EdgeDataRaw(const RGraph* g) {
    const int* p = g->edgeArray;
    long long bytes = (long long)((const char*)g->edges.last - (const char*)g->edges.first);
    const int n = p ? g->edgeCount : (int)((unsigned long long)(bytes >> 2) >> 1);
    if (n) {
        if (!p) p = (const int*)g->edges.first;
    } else {
        p = nullptr;
    }
    return p;
}

static inline unsigned long long GrowCap(unsigned long long cap, unsigned long long need,
                                         unsigned long long kMax) {
    if (cap > kMax - (cap >> 1)) return kMax;
    unsigned long long nc = cap + (cap >> 1);
    return nc < need ? need : nc;
}

static NOINLINE void ReallocInsert8(RVec* v, void* pos, const void* value) {
    unsigned char* const b = (unsigned char*)v->first;
    const unsigned long long idx = (unsigned long long)((unsigned char*)pos - b) / 8;
    const unsigned long long size = (unsigned long long)((unsigned char*)v->last - b) / 8;
    const unsigned long long kMax = 0x1FFFFFFFFFFFFFFFull;
    if (size == kMax) std::_Xlength_error("vector too long");
    const unsigned long long newsize = size + 1;
    const unsigned long long cap = (unsigned long long)((unsigned char*)v->end - b) / 8;
    const unsigned long long nc = GrowCap(cap, newsize, kMax);
    unsigned char* const buf = nc ? (unsigned char*)b24_alloc(8 * nc) : nullptr;
    unsigned char* const at = buf + 8 * idx;
    std::memcpy(at, value, 8);
    unsigned char* const e = (unsigned char*)v->last;
    std::memcpy(buf, b, (size_t)((unsigned char*)pos - b));
    std::memcpy(at + 8, pos, (size_t)(e - (unsigned char*)pos));
    if (v->first) b24_free(v->first);
    v->first = buf;
    v->last = buf + 8 * newsize;
    v->end = buf + 8 * nc;
}

static NOINLINE void ReallocInsert12(RVec* v, void* pos, const void* value) {
    unsigned char* const b = (unsigned char*)v->first;
    const unsigned long long idx = (unsigned long long)((unsigned char*)pos - b) / 12;
    const unsigned long long size = (unsigned long long)((unsigned char*)v->last - b) / 12;
    const unsigned long long kMax = 0x1555555555555555ull;
    if (size == kMax) std::_Xlength_error("vector too long");
    const unsigned long long newsize = size + 1;
    const unsigned long long cap = (unsigned long long)((unsigned char*)v->end - b) / 12;
    const unsigned long long nc = GrowCap(cap, newsize, kMax);
    unsigned char* const buf = nc ? (unsigned char*)b24_alloc(12 * nc) : nullptr;
    unsigned char* const at = buf + 12 * idx;
    std::memcpy(at, value, 12);
    unsigned char* const e = (unsigned char*)v->last;
    std::memcpy(buf, b, (size_t)((unsigned char*)pos - b));
    std::memcpy(at + 12, pos, (size_t)(e - (unsigned char*)pos));
    if (v->first) b24_free(v->first);
    v->first = buf;
    v->last = buf + 12 * newsize;
    v->end = buf + 12 * nc;
}


static FORCEINLINE void PushBack8(RVec* v, const void* value) {
    unsigned char* const last = (unsigned char*)v->last;
    if (last == (unsigned char*)v->end) {
        ReallocInsert8(v, last, value);
        return;
    }
    std::memcpy(last, value, 8);
    v->last = last + 8;
}

static FORCEINLINE void PushBack12(RVec* v, const void* value) {
    unsigned char* const last = (unsigned char*)v->last;
    if (last == (unsigned char*)v->end) {
        ReallocInsert12(v, last, value);
        return;
    }
    std::memcpy(last, value, 12);
    v->last = last + 12;
}

static inline const int* LowerBound(const int* first, const int* last, int key) {
    long long n = last - first;
    while (n > 0) {
        const int* const mid = first + (n >> 1);
        if (*mid >= key) {
            n >>= 1;
        } else {
            first = mid + 1;
            n += -1 - (n >> 1);
        }
    }
    return first;
}

extern "C" NOINLINE void b24_classify_vertices(const RGraph* self, const RVec* src,
                                               RVec* pairs, RVec* trips) {
    pairs->last = pairs->first;
    trips->last = trips->first;

    int* const sfirst = (int*)src->first;
    int* const slast = (int*)src->last;
    if (sfirst == slast) return;

    const long long n = slast - sfirst;
    int* const buf = (int*)b24_alloc((unsigned long long)(4 * n));
    int* p = buf;
    for (const int* q = sfirst; q != slast; ++q) *p++ = *q;
    std::sort(buf, p);

    const int ec = EdgeCountRaw(self);
    int edgeIndex = 0;
    for (int i = 0; i < ec; ++i, ++edgeIndex) {
        const int* const eb = EdgeDataRaw(self);
        const int v0 = eb[2 * i];
        const int v1 = eb[2 * i + 1];
        const int* const f0 = LowerBound(buf, p, v0);
        const bool m0 = f0 != p && v0 >= *f0;
        const int* const f1 = LowerBound(buf, p, v1);
        const bool m1 = f1 != p && v1 >= *f1;
        if (m0) {
            if (m1) {
                PairTriple t;
                t.a = v0;
                t.b = v1;
                t.c = edgeIndex;
                PushBack12(trips, &t);
            } else {
                PairII p0;
                p0.a = v0;
                p0.b = edgeIndex;
                PushBack8(pairs, &p0);
            }
        } else if (m1) {
            PairII p1;
            p1.a = v1;
            p1.b = edgeIndex;
            PushBack8(pairs, &p1);
        }
    }
    if (buf) b24_free(buf);
}
