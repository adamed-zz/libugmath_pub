





















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


#include <cstdint>

#define NOINLINE __declspec(noinline)

extern "C" __declspec(dllimport) void* b24_alloc(unsigned long long n);
extern "C" __declspec(dllimport) void b24_free(void* p);
extern "C" __declspec(noreturn) void sub_180001530();

struct RVec {
    void* first;
    void* last;
    void* end;
};

struct RGraph {
    int vertexCount;
    int pad0;
    void* vertexArray;
    int edgeCount;
    int pad1;
    void* edgeArray;
    RVec vertices;
    RVec edges;
};
static_assert(sizeof(RGraph) == 80, "Graph ABI");

struct VBit {
    void* first;
    void* last;
    void* end;
};


static int EdgeCountOf(const RGraph* g) {
    if (!g->edgeArray) return (int)(((int*)g->edges.last - (int*)g->edges.first) / 2);
    return g->edgeCount;
}

static const int* EdgeData(const RGraph* g) {
    const int* e = (const int*)g->edgeArray;
    int n = EdgeCountOf(g);
    if (!n) e = nullptr;
    else if (!e) e = (const int*)g->edges.first;
    return e;
}

static int EdgeStart(const RGraph* g, int edge) { return EdgeData(g)[edge * 2]; }
static int EdgeEnd(const RGraph* g, int edge) { return EdgeData(g)[edge * 2 + 1]; }


static void GrowInt(RVec* v, int value) {
    int* first = (int*)v->first;
    int* last = (int*)v->last;
    int* end = (int*)v->end;
    uint64_t oldsize = (uint64_t)(last - first);
    uint64_t oldcap = (uint64_t)(end - first);
    const uint64_t kMax = 0x1FFFFFFFFFFFFFFFull;
    uint64_t newsize = oldsize + 1;
    uint64_t newcap;
    if (oldcap > kMax - oldcap / 2) {
        newcap = kMax;
    } else {
        newcap = oldcap + oldcap / 2;
        if (newcap < newsize) newcap = newsize;
    }
    int* p = (int*)b24_alloc(newcap * 4);
    for (uint64_t i = 0; i < oldsize; i++) p[i] = first[i];
    p[oldsize] = value;
    if (first) b24_free(first);
    v->first = p;
    v->last = p + oldsize + 1;
    v->end = p + newcap;
}

static void PushInt(RVec* v, int value) {
    int* last = (int*)v->last;
    if (last != (int*)v->end) {
        *last = value;
        v->last = last + 1;
        return;
    }
    GrowInt(v, value);
}

extern "C" NOINLINE int b24_append_immediate(const RGraph* self, int edge,
                                             const RVec* adjacency, VBit* visited,
                                             RVec* out) {
    int result = edge;
    for (int i = 0; i < 2; i++) {
        int v = i ? EdgeEnd(self, edge) : EdgeStart(self, edge);
        const RVec* outer = (const RVec*)adjacency->first;
        const RVec* inner = outer + v;
        int idx = 0;
        int count = (int)((int*)inner->last - (int*)inner->first);
        if (count) {
            const int* p = (const int*)inner->first;
            do {
                int w = p[idx];
                unsigned* words = (unsigned*)visited->first;
                if ((words[(unsigned)w >> 5] & (1u << (w & 31))) == 0) {
                    PushInt(out, w);
                    words = (unsigned*)visited->first;
                    words[(unsigned)w >> 5] |= 1u << (w & 31);
                    b24_append_immediate(self, w, adjacency, visited, out);
                    outer = (const RVec*)adjacency->first;
                    inner = outer + v;
                    p = (const int*)inner->first;
                }
                idx++;
            } while (idx < (int)((int*)inner->last - (int*)inner->first));
        }
    }
    return result;
}
