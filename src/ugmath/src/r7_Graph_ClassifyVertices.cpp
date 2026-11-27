















#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <stdexcept>

#include "kits/b24_kit/b24_types.h"

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
