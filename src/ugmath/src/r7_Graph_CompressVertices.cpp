

















#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>

#include "kits/b24_kit/b24_types.h"

#define NOINLINE __declspec(noinline)

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
static_assert(sizeof(RGraph) == 80, "Graph ABI");

static inline unsigned long long GrowCap(unsigned long long cap, unsigned long long need,
                                         unsigned long long kMax) {
    if (cap > kMax - (cap >> 1)) return kMax;
    unsigned long long nc = cap + (cap >> 1);
    return nc < need ? need : nc;
}


static NOINLINE void ResizeDoubleVec(RVec* v, unsigned long long n);



static NOINLINE void ResizeVec(RVec* v, unsigned long long n, unsigned long long esize,
                               unsigned long long kMax) {
    unsigned char* const b = (unsigned char*)v->first;
    const unsigned long long size = (unsigned long long)((unsigned char*)v->last - b) / esize;
    const unsigned long long cap = (unsigned long long)((unsigned char*)v->end - b) / esize;
    if (n <= size) {
        v->last = b + esize * n;
        return;
    }
    if (n <= cap) {
        std::memset(b + esize * size, 0, (size_t)(esize * (n - size)));
        v->last = b + esize * n;
        return;
    }
    if (n > kMax) std::_Xlength_error("vector too long");
    const unsigned long long nc = GrowCap(cap, n, kMax);
    unsigned char* const buf = (unsigned char*)b24_alloc(esize * nc);
    if (size) std::memcpy(buf, b, (size_t)(esize * size));
    std::memset(buf + esize * size, 0, (size_t)(esize * (n - size)));
    if (b) b24_free(b);
    v->first = buf;
    v->last = buf + esize * n;
    v->end = buf + esize * nc;
}

static NOINLINE void ResizeDoubleVec(RVec* v, unsigned long long n) {
    ResizeVec(v, n, 8, 0x1FFFFFFFFFFFFFFFULL);
}


static NOINLINE void AssignDouble(RVec* dst, const RVec* src) {
    if (dst == src) return;
    const long long n = (long long)(((double*)src->last) - ((double*)src->first));
    long long old = (long long)(((double*)dst->last) - ((double*)dst->first));
    if (n <= old) {
        std::memmove(dst->first, src->first, (size_t)(8 * n));
        dst->last = (double*)dst->first + n;
        return;
    }
    const long long cap = (long long)(((double*)dst->end) - ((double*)dst->first));
    if (n > cap) {
        const unsigned long long kMax = 0x1FFFFFFFFFFFFFFFULL;
        if ((unsigned long long)n > kMax) std::_Xlength_error("vector too long");
        const unsigned long long nc = GrowCap((unsigned long long)cap, (unsigned long long)n, kMax);
        if (dst->first) b24_free(dst->first);
        dst->first = nullptr;
        dst->last = nullptr;
        dst->end = nullptr;
        double* const buf = (double*)b24_alloc(8 * nc);
        dst->first = buf;
        dst->last = buf;
        dst->end = buf + nc;
        old = 0;
    }
    std::memmove(dst->first, src->first, (size_t)(8 * old));
    double* d = (double*)dst->first + old;
    const double* s = (const double*)src->first + old;
    while (s != (const double*)src->last) *d++ = *s++;
    dst->last = d;
}

extern "C" NOINLINE void b24_compress_vertices(RGraph* self, const RVec* src) {
    const long long v4 = (long long)(((const char*)src->last - (const char*)src->first)) >> 2;
    const int v4i = (int)v4;
    const int v5i = 3 * v4i;
    const long long v5 = v5i;

    RVec nb;
    nb.first = nb.last = nb.end = nullptr;
    if (v5i) {
        if ((unsigned long long)v5 > 0x1FFFFFFFFFFFFFFFULL) std::_Xlength_error("vector too long");
        double* const p = (double*)b24_alloc((unsigned long long)(8 * v5));
        nb.first = p;
        nb.last = p + v5;
        nb.end = p + v5;
        std::memset(p, 0, (size_t)(8 * v5));
    }

    double* const v7 = (double*)nb.first;
    int v6 = 0;
    long long v8 = 0;
    const int* v9 = nullptr;
    if ((long long)v4i < 4LL) {
        if (v4i <= 0) goto LABEL_24;
        v9 = (const int*)src->first;
        goto LABEL_20;
    }
    {
        v9 = (const int*)src->first;
        long long v10 = 0;
        const int* v11 = v9 + 2;
        unsigned long long v12 = ((unsigned long long)(v4i - 4) >> 2) + 1;
        v8 = (long long)(4 * v12);
        do {
            const int v13 = v11[-2];
            if (v13 != -1) {
                const double* const v14 = (const double*)self->vertices.first;
                const long long v15 = 3 * (long long)v13;
                v7[v15] = *(const double*)(v10 + (const char*)v14);
                v7[v15 + 1] = *(const double*)(v10 + (const char*)v14 + 8);
                v7[v15 + 2] = *(const double*)(v10 + (const char*)v14 + 16);
                ++v6;
            }
            const int v16 = v11[-1];
            if (v16 != -1) {
                const double* const v17 = (const double*)self->vertices.first;
                const long long v18 = 3 * (long long)v16;
                v7[v18] = *(const double*)(v10 + (const char*)v17 + 24);
                v7[v18 + 1] = *(const double*)(v10 + (const char*)v17 + 32);
                v7[v18 + 2] = *(const double*)(v10 + (const char*)v17 + 40);
                ++v6;
            }
            if (v11[0] != -1) {
                const double* const v19 = (const double*)self->vertices.first;
                const long long v20 = 3 * (long long)v11[0];
                v7[v20] = *(const double*)(v10 + (const char*)v19 + 48);
                v7[v20 + 1] = *(const double*)(v10 + (const char*)v19 + 56);
                v7[v20 + 2] = *(const double*)(v10 + (const char*)v19 + 64);
                ++v6;
            }
            const int v21 = v11[1];
            if (v21 != -1) {
                const double* const v22 = (const double*)self->vertices.first;
                const long long v23 = 3 * (long long)v21;
                v7[v23] = *(const double*)(v10 + (const char*)v22 + 72);
                v7[v23 + 1] = *(const double*)(v10 + (const char*)v22 + 80);
                v7[v23 + 2] = *(const double*)(v10 + (const char*)v22 + 88);
                ++v6;
            }
            v11 += 4;
            v10 += 96;
            --v12;
        } while (v12);
        if (v8 >= v4i) goto LABEL_24;
    }
LABEL_20:
    {
        long long v24 = 24 * v8;
        do {
            const int v25 = v9[v8];
            if (v25 != -1) {
                const double* const v26 = (const double*)self->vertices.first;
                const long long v27 = 3 * (long long)v25;
                v7[v27] = *(const double*)(v24 + (const char*)v26);
                v7[v27 + 1] = *(const double*)(v24 + (const char*)v26 + 8);
                v7[v27 + 2] = *(const double*)(v24 + (const char*)v26 + 16);
                ++v6;
            }
            ++v8;
            v24 += 24;
        } while (v8 < v4i);
    }
LABEL_24:
    AssignDouble(&self->vertices, &nb);
    ResizeDoubleVec(&self->vertices, (unsigned long long)(long long)(3 * v6));
    if (nb.first) b24_free(nb.first);
}
