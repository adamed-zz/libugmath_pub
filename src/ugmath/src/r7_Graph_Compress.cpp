

























#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <algorithm>

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


struct IP3 {
    int index;
    int pad;
    double x, y, z;
};
static_assert(sizeof(IP3) == 32, "pair<int,Point3> ABI");

static double g_tolerance;

static inline long long VertexCountRaw(const RGraph* g) {
    if (g->vertexArray) return (long long)g->vertexCount;
    unsigned long long bytes =
        (unsigned long long)((const char*)g->vertices.last - (const char*)g->vertices.first);
    return (long long)((bytes >> 3) / 3ULL);
}

static inline long long EdgeCountRaw(const RGraph* g) {
    if (g->edgeArray) return (long long)g->edgeCount;
    unsigned long long bytes =
        (unsigned long long)((const char*)g->edges.last - (const char*)g->edges.first);
    return (long long)((bytes >> 2) >> 1);
}

static inline unsigned long long GrowCap(unsigned long long cap, unsigned long long need,
                                         unsigned long long kMax) {
    if (cap > kMax - (cap >> 1)) return kMax;
    unsigned long long nc = cap + (cap >> 1);
    return nc < need ? need : nc;
}



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


static NOINLINE void MakeInternalCopyRaw(RGraph* g) {
    if (!g->vertexArray) return;
    const long long nv = g->vertexCount;
    const long long ne = g->edgeCount;
    ResizeVec(&g->vertices, (unsigned long long)(3 * nv), 8, 0x1FFFFFFFFFFFFFFFULL);
    std::memmove(g->vertices.first, g->vertexArray, (size_t)(3 * nv * 8));
    ResizeVec(&g->edges, (unsigned long long)(2 * ne), 4, 0x1FFFFFFFFFFFFFFFULL);
    std::memmove(g->edges.first, g->edgeArray, (size_t)(2 * ne * 4));
    g->vertexArray = nullptr;
    g->edgeArray = nullptr;
    g->vertexCount = 0;
    g->edgeCount = 0;
}


static bool VertexLessThanRaw(const IP3& a, const IP3& b) {
    const double t = g_tolerance;
    if (b.x - t > a.x) return true;
    if (t >= std::fabs(a.x - b.x)) {
        if (b.y - t > a.y) return true;
        if (t >= std::fabs(a.y - b.y)) return b.z - t > a.z;
    }
    return false;
}


static NOINLINE void GenerateSortedRaw(RGraph* g, RVec* out) {
    const int n = (int)VertexCountRaw(g);
    ResizeVec(out, (unsigned long long)n, 32, 0x07FFFFFFFFFFFFFFULL);
    MakeInternalCopyRaw(g);
    IP3* const p = (IP3*)out->first;
    const double* const v = (const double*)g->vertices.first;
    for (int i = 0; i < n; ++i) {
        p[i].index = i;
        p[i].pad = 0;
        p[i].x = v[3 * (long long)i];
        p[i].y = v[3 * (long long)i + 1];
        p[i].z = v[3 * (long long)i + 2];
    }
    std::sort(p, p + n, VertexLessThanRaw);
}


static NOINLINE int MapCompressedRaw(const RGraph* g, const RVec* sorted, RVec* repMap,
                                     RVec* compMap) {
    const IP3* const s = (const IP3*)sorted->first;
    int* const rep = (int*)repMap->first;
    int* const comp = (int*)compMap->first;
    const int n = (int)VertexCountRaw(g);
    const double tol = g_tolerance;

    int v8 = s[0].index;
    rep[v8] = v8;
    int processed = 0;
    long long next = 0;
    int prevEnd = 0;
    long long start = 0;
    int count = 0;
    for (;;) {
        long long j = start + 1;
        count = processed + 1;
        if (j < n) {
            for (;;) {
                const double dy = s[start].y - s[j].y;
                const double dx = s[start].x - s[j].x;
                const double dz = s[start].z - s[j].z;
                double d2 = dy * dy;
                d2 = d2 + dx * dx;
                d2 = d2 + dz * dz;
                const double d = std::sqrt(d2);

                if (!(tol >= std::fabs(d))) break;
                ++count;
                rep[s[j].index] = v8;
                ++j;
                if (j >= n) {
                    processed = prevEnd;
                    goto NEXT;
                }
            }
            processed = count;
            rep[s[j].index] = s[j].index;
            prevEnd = count;
            v8 = s[j].index;
            next = j;
        }
    NEXT:
        if (count == n) break;
        start = next;
        if (processed == n - 1) break;
    }

    int nr = 0;
    for (int i = 0; i < n; ++i) {
        if (rep[i] == i) comp[i] = nr++;
    }
    return nr;
}

extern "C" NOINLINE bool b24_compress(RGraph* self, double tol) {
    if ((int)VertexCountRaw(self) < 2) return false;

    MakeInternalCopyRaw(self);
    g_tolerance = tol;

    RVec sorted;
    sorted.first = sorted.last = sorted.end = nullptr;
    GenerateSortedRaw(self, &sorted);

    const int n = (int)VertexCountRaw(self);
    const unsigned long long nn = (unsigned long long)(long long)n;
    const unsigned long long kMapMax = 0x3FFFFFFFFFFFFFFFULL;

    RVec repMap, compMap;
    repMap.first = repMap.last = repMap.end = nullptr;
    compMap.first = compMap.last = compMap.end = nullptr;
    if (n) {
        if (nn > kMapMax) std::_Xlength_error("vector too long");
        int* const p = (int*)b24_alloc(4 * nn);
        repMap.first = p;
        repMap.last = (int*)p + nn;
        repMap.end = (int*)p + nn;
        std::memset(p, 0xFF, (size_t)(4 * nn));
    }
    if (n) {
        if (nn > kMapMax) std::_Xlength_error("vector too long");
        int* const p = (int*)b24_alloc(4 * nn);
        compMap.first = p;
        compMap.last = (int*)p + nn;
        compMap.end = (int*)p + nn;
        std::memset(p, 0xFF, (size_t)(4 * nn));
    }

    const int v9 = MapCompressedRaw(self, &sorted, &repMap, &compMap);
    int* const comp = (int*)compMap.first;
    bool compressed;
    if (v9 != n) {
        int* const rep = (int*)repMap.first;
        const long long total = 3LL * v9;
        RVec nb;
        nb.first = nb.last = nb.end = nullptr;
        if (total) {
            if ((unsigned long long)total > 0x1FFFFFFFFFFFFFFFULL)
                std::_Xlength_error("vector too long");
            double* const p = (double*)b24_alloc(8 * (unsigned long long)total);
            nb.first = p;
            nb.last = p + total;
            nb.end = p + total;
            std::memset(p, 0, (size_t)(8 * total));
        }
        if (self->vertexArray) MakeInternalCopyRaw(self);
        double* const nv = (double*)nb.first;

        long long v16 = 0;
        if (n < 4) {
            if (n > 0) {

            }
        } else {
            long long v17 = 0;
            int* v18 = comp + 2;
            unsigned long long v19 = ((unsigned long long)(n - 4) >> 2) + 1;
            v16 = (long long)(4 * v19);
            do {
                const int v20 = v18[-2];
                if (v20 != -1) {
                    const char* const v21 = (const char*)self->vertices.first;
                    unsigned long long v22 = 3ull * (unsigned)v20;
                    nv[v22] = *(const double*)(v17 + v21);
                    nv[v22 + 1] = *(const double*)(v17 + v21 + 8);
                    nv[v22 + 2] = *(const double*)(v17 + v21 + 16);
                }
                const int v23 = v18[-1];
                if (v23 != -1) {
                    const char* const v24 = (const char*)self->vertices.first;
                    unsigned long long v25 = 3ull * (unsigned)v23;
                    nv[v25] = *(const double*)(v17 + v24 + 24);
                    nv[v25 + 1] = *(const double*)(v17 + v24 + 32);
                    nv[v25 + 2] = *(const double*)(v17 + v24 + 40);
                }
                const int v26i = v18[0];
                if (v26i != -1) {
                    const char* const v26 = (const char*)self->vertices.first;
                    unsigned long long v27 = 3ull * (unsigned)v26i;
                    nv[v27] = *(const double*)(v17 + v26 + 48);
                    nv[v27 + 1] = *(const double*)(v17 + v26 + 56);
                    nv[v27 + 2] = *(const double*)(v17 + v26 + 64);
                }
                const int v28 = v18[1];
                if (v28 != -1) {
                    const char* const v29 = (const char*)self->vertices.first;
                    unsigned long long v30 = 3ull * (unsigned)v28;
                    nv[v30] = *(const double*)(v17 + v29 + 72);
                    nv[v30 + 1] = *(const double*)(v17 + v29 + 80);
                    nv[v30 + 2] = *(const double*)(v17 + v29 + 88);
                }
                v18 += 4;
                v17 += 96;
                --v19;
            } while (v19);
            if (v16 >= n) goto copy_done;
        }
        do {
            const int v32 = comp[v16];
            if (v32 != -1) {
                const char* const v33 = (const char*)self->vertices.first;
                unsigned long long v34 = 3ull * (unsigned)v32;
                const long long v31 = 24 * v16;
                nv[v34] = *(const double*)(v31 + v33);
                nv[v34 + 1] = *(const double*)(v31 + v33 + 8);
                nv[v34 + 2] = *(const double*)(v31 + v33 + 16);
            }
            ++v16;
        } while (v16 < n);
    copy_done:
        AssignDouble(&self->vertices, &nb);
        const long long m = EdgeCountRaw(self);
        for (long long j = 0; j < m; ++j) {
            int* const e0 = (int*)self->edges.first;
            e0[2 * j] = comp[rep[e0[2 * j]]];
            int* const e1 = (int*)self->edges.first;
            e1[2 * j + 1] = comp[rep[e1[2 * j + 1]]];
        }
        compressed = true;
        if (nb.first) b24_free(nb.first);
    } else {
        compressed = false;
    }

    if (compMap.first) b24_free(compMap.first);
    if (repMap.first) b24_free(repMap.first);
    if (sorted.first) b24_free(sorted.first);
    return compressed;
}
