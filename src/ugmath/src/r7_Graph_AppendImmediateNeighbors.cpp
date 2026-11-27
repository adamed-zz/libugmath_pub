


















#define B24_CPPMEMORY_DLLIMPORT __declspec(dllimport)
#include "kits/b24_kit/b24_types.h"
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
