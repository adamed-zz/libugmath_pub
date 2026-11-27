


















#include <cmath>
#include <cstring>

#include "kits/b24_kit/b24_types.h"

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
    double* vertexArray;
    int edgeCount;
    int pad1;
    int* edgeArray;
    RVec vertices;
    RVec edges;
};
static_assert(sizeof(RGraph) == 80, "Graph ABI");

struct Box3DRaw {
    unsigned char raw[336];
};
static_assert(sizeof(Box3DRaw) == 336, "Box3D ABI");

using UGS::Math::Point3;


static inline const double* VertexPtr(const RGraph* g, int v) {
    const double* p = g->vertexArray;
    long long n;
    if (p) {
        n = g->vertexCount;
    } else {
        n = ((const double*)g->vertices.last - (const double*)g->vertices.first) / 3;
    }
    if (n) {
        if (!p) p = (const double*)g->vertices.first;
    } else {
        p = nullptr;
    }
    return p ? p + 3 * (long long)v : nullptr;
}


static NOINLINE Point3 BoxOrigin(const Box3DRaw* box) {
    Point3 p;
    std::memcpy(&p, box->raw + 80, 24);
    return p;
}

static inline unsigned long long GrowCap(unsigned long long cap, unsigned long long need,
                                         unsigned long long kMax) {
    if (cap > kMax - (cap >> 1)) return kMax;
    unsigned long long nc = cap + (cap >> 1);
    return nc < need ? need : nc;
}


static NOINLINE void PushPair(RVec* v, int a, int b) {
    unsigned long long value = (unsigned long long)(unsigned)a |
                               ((unsigned long long)(unsigned)b << 32);
    unsigned char* base = (unsigned char*)v->first;
    unsigned long long size = (unsigned long long)((unsigned char*)v->last - base) / 8;
    unsigned long long cap = (unsigned long long)((unsigned char*)v->end - base) / 8;
    if (size < cap) {

        std::memcpy((unsigned char*)v->last, &value, 8);
        v->last = (unsigned char*)v->last + 8;
        return;
    }
    unsigned long long nc = GrowCap(cap, size + 1, 0x1FFFFFFFFFFFFFFFull);
    unsigned char* buf = (unsigned char*)b24_alloc(8 * nc);
    if (base) {
        std::memcpy(buf, base, (size_t)(size * 8));
        b24_free(base);
    }
    std::memcpy(buf + 8 * size, &value, 8);
    v->first = buf;
    v->last = buf + 8 * (size + 1);
    v->end = buf + 8 * nc;
}


static NOINLINE void PushPoint(RVec* v, const Point3& p) {
    unsigned char* base = (unsigned char*)v->first;
    unsigned long long size = (unsigned long long)((unsigned char*)v->last - base) / 24;
    unsigned long long cap = (unsigned long long)((unsigned char*)v->end - base) / 24;
    if (size < cap) {
        std::memcpy((unsigned char*)v->last, &p, 24);
        v->last = (unsigned char*)v->last + 24;
        return;
    }
    unsigned long long nc = GrowCap(cap, size + 1, 0xAAAAAAAAAAAAAAAull);
    unsigned char* buf = (unsigned char*)b24_alloc(24 * nc);
    if (base) {
        std::memcpy(buf, base, (size_t)(size * 24));
        b24_free(base);
    }
    std::memcpy(buf + 24 * size, &p, 24);
    v->first = buf;
    v->last = buf + 24 * (size + 1);
    v->end = buf + 24 * nc;
}

extern "C" NOINLINE void b24_complement_vertices(const RGraph* self, const Box3DRaw* box,
                                                 int axis, double tol, RVec* v1, RVec* v2,
                                                 RVec* pairs, RVec* points) {
    double pa[3] = {0, 0, 0};
    double pb[3] = {0, 0, 0};
    double q[3] = {0, 0, 0};

    for (int pass = 0; pass < 2; ++pass) {
        RVec* L = pass ? v2 : v1;
        RVec* R = pass ? v1 : v2;
        pa[0] = pa[1] = pa[2] = 0;
        pb[0] = pb[1] = pb[2] = 0;
        q[0] = q[1] = q[2] = 0;
        long long n = ((int*)L->last - (int*)L->first);
        for (long long k = 0; k < n; ++k) {
            int a = ((int*)L->first)[k];
            if (a == -1) continue;
            const double* vp = VertexPtr(self, a);
            if (vp) {
                pa[0] = vp[0];
                pa[1] = vp[1];
                pa[2] = vp[2];
                q[0] = pa[0];
                q[1] = pa[1];
                q[2] = pa[2];
            }
            long long nR = ((int*)R->last - (int*)R->first);
            bool matched = false;
            for (long long j = 0; j < nR; ++j) {
                int b = ((int*)R->first)[j];
                if (b == -1) continue;
                const double* wp = VertexPtr(self, b);
                if (wp) {
                    pb[0] = wp[0];
                    pb[1] = wp[1];
                    pb[2] = wp[2];
                }
                double d1, d2;
                if (axis == 0) {
                    d1 = pa[1] - pb[1];
                    d2 = pa[2] - pb[2];
                } else if (axis == 1) {
                    d1 = pa[0] - pb[0];
                    d2 = pa[2] - pb[2];
                } else if (axis == 2) {
                    d1 = pa[0] - pb[0];
                    d2 = pa[1] - pb[1];
                } else {
                    continue;
                }


                if (!(tol >= std::fabs(d1))) continue;
                if (!(tol >= std::fabs(d2))) continue;
                PushPair(pairs, a, b);
                ((int*)L->first)[k] = -1;
                ((int*)R->first)[j] = -1;
                matched = true;
                break;
            }
            if (matched) continue;
            const double* lengths = (const double*)(box->raw + 104);
            Point3 op = BoxOrigin(box);
            double origin[3] = {op.x, op.y, op.z};
            double coord = origin[axis];
            if (pass == 0) coord = coord + lengths[axis];
            q[axis] = coord;
            Point3 out;
            out.x = q[0];
            out.y = q[1];
            out.z = q[2];
            PushPoint(points, out);
            pa[0] = q[0];
            pa[1] = q[1];
            pa[2] = q[2];
        }
    }
}
