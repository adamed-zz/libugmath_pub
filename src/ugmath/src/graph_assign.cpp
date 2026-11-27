




















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


static void realloc_double(RVec* v, unsigned long long n) {
    const unsigned long long M = 0x1FFFFFFFFFFFFFFFULL;
    if (n > M) sub_180001530();
    double* first = (double*)v->first;
    unsigned long long oldsize = (unsigned long long)((double*)v->last - first);
    unsigned long long cap = (unsigned long long)((double*)v->end - first);
    unsigned long long newcap;
    if (cap > M - (cap >> 1)) {
        newcap = M;
    } else {
        newcap = cap + (cap >> 1);
        if (newcap < n) newcap = n;
    }
    double* nv = newcap ? (double*)b24_alloc(8 * newcap) : nullptr;
    if (n != oldsize) std::memset(nv + oldsize, 0, 8 * (n - oldsize));
    double* s = first;
    double* d = nv;
    unsigned long long cnt = oldsize;
    while (cnt--) *d++ = *s++;
    if (first) b24_free(first);
    v->first = nv;
    v->last = nv + n;
    v->end = nv + newcap;
}


static void realloc_int(RVec* v, unsigned long long n) {
    const unsigned long long M = 0x3FFFFFFFFFFFFFFFULL;
    if (n > M) sub_180001530();
    int* first = (int*)v->first;
    unsigned long long oldsize = (unsigned long long)((int*)v->last - first);
    unsigned long long cap = (unsigned long long)((int*)v->end - first);
    unsigned long long newcap;
    if (cap > M - (cap >> 1)) {
        newcap = M;
    } else {
        newcap = cap + (cap >> 1);
        if (newcap < n) newcap = n;
    }
    int* nv = newcap ? (int*)b24_alloc(4 * newcap) : nullptr;
    if (n != oldsize) std::memset(nv + oldsize, 0, 4 * (n - oldsize));
    int* s = first;
    int* d = nv;
    unsigned long long cnt = oldsize;
    while (cnt--) *d++ = *s++;
    if (first) b24_free(first);
    v->first = nv;
    v->last = nv + n;
    v->end = nv + newcap;
}


static void resize_double(RVec* v, unsigned long long n) {
    double* first = (double*)v->first;
    double* last = (double*)v->last;
    unsigned long long sz = (unsigned long long)(last - first);
    if (n >= sz) {
        if (n > sz) {
            unsigned long long cap = (unsigned long long)((double*)v->end - first);
            if (n > cap) {
                realloc_double(v, n);
                return;
            }
            double* p = last;
            unsigned long long fill = n - sz;
            if (fill) {
                std::memset(p, 0, 8 * fill);
                p += fill;
            }
            v->last = p;
        }
    } else {
        v->last = first + n;
    }
}


static void resize_int(RVec* v, unsigned long long n) {
    int* first = (int*)v->first;
    int* last = (int*)v->last;
    unsigned long long sz = (unsigned long long)(last - first);
    if (n >= sz) {
        if (n > sz) {
            unsigned long long cap = (unsigned long long)((int*)v->end - first);
            if (n > cap) {
                realloc_int(v, n);
                return;
            }
            int* p = last;
            unsigned long long fill = n - sz;
            if (fill) {
                std::memset(p, 0, 4 * fill);
                p += fill;
            }
            v->last = p;
        }
    } else {
        v->last = first + n;
    }
}


static void make_internal_copy(RGraph* g) {
    if (g->vertexArray) {
        long long nv = 3 * (long long)g->vertexCount;
        resize_double(&g->vertices, (unsigned long long)nv);
        std::memmove(g->vertices.first, g->vertexArray, (size_t)(nv * 8));
        long long ne = 2 * (long long)g->edgeCount;
        resize_int(&g->edges, (unsigned long long)ne);
        std::memmove(g->edges.first, g->edgeArray, (size_t)(ne * 4));
        g->vertexArray = nullptr;
        g->edgeArray = nullptr;
        g->vertexCount = 0;
        g->edgeCount = 0;
    }
}

extern "C" NOINLINE RGraph* b24_graph_assign(RGraph* a1, const RGraph* a2) {
    make_internal_copy(a1);

    long long nv;
    void* vsrc;
    if (a2->vertexArray) {
        nv = (long long)a2->vertexCount;
        vsrc = a2->vertexArray;
    } else {
        nv = ((long long)a2->vertices.last - (long long)a2->vertices.first) / 8 / 3;
        vsrc = a2->vertices.first;
    }
    resize_double(&a1->vertices, (unsigned long long)(3 * nv));
    if (nv == 0) vsrc = nullptr;
    std::memmove(a1->vertices.first, vsrc, (size_t)(3 * nv * 8));

    long long ne;
    void* esrc;
    if (a2->edgeArray) {
        ne = (long long)a2->edgeCount;
        esrc = a2->edgeArray;
    } else {
        ne = ((long long)a2->edges.last - (long long)a2->edges.first) / 4 / 2;
        esrc = a2->edges.first;
    }
    resize_int(&a1->edges, (unsigned long long)(2 * ne));
    if (ne == 0) esrc = nullptr;
    std::memmove(a1->edges.first, esrc, (size_t)(2 * ne * 4));
    return a1;
}
