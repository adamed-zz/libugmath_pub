












#define WIN32_LEAN_AND_MEAN
#include <intrin.h>

struct Pt3f
{
    float x, y, z;
};

struct Entry
{
    const Pt3f* key;
    const Pt3f* p1;
    const Pt3f* p2;
    Entry* next;
};

struct HullCtx
{
    Pt3f pt;
    int pad0c;
    Entry* head;
};

extern "C" __declspec(dllimport) void* SM_alloc(unsigned long long);
extern "C" __declspec(dllimport) void SM_free(void*);
extern "C" void (*d_E08D8)(int, int, const char*);
extern "C" const char d_BAD62[];
extern "C" int d_E07A4;
extern "C" double d_E0898;
extern "C" double d_E08A0;
extern "C" int d_E08A8;


static double Dot3(const Pt3f* n, const Pt3f* v)
{
    const double ny = n->y, nx = n->x, nz = n->z;
    const double vy = v->y, vx = v->x, vz = v->z;
    return (ny * vy + nx * vx) + nz * vz;
}

static void Unlink(HullCtx* ctx, Entry* prev, Entry* cur)
{
    Entry* nx = cur->next;
    if (!prev)
        ctx->head = nx;
    else
        prev->next = nx;
    SM_free(cur);
}

extern "C" void sub_18004A020(HullCtx* ctx, const Pt3f* p, const Pt3f* key, const Pt3f* p2,
                              char skip)
{

    Entry* prev = nullptr;
    if (!SM_alloc(0x20))
        d_E08D8(2, 3, d_BAD62);

    Entry* cur = ctx->head;
    while (cur)
    {
        if (cur->key == key)
            break;
        prev = cur;
        cur = cur->next;
    }

    if (cur)
    {
        if (skip)
            return;
        if (Dot3(cur->p1, p) > d_E0898 || Dot3(cur->p2, p2) > d_E0898)
        {
            Unlink(ctx, prev, cur);
        }
        return;
    }

    double dx, dy;
    if (d_E07A4)
    {
        const double cz = (double)ctx->pt.z;
        const double kz = (double)key->z;
        const double bx = (double)key->x / kz;
        const double ax = (double)ctx->pt.x / cz;
        dx = ax - bx;
        const double by = (double)key->y / kz;
        const double ay = (double)ctx->pt.y / cz;
        dy = ay - by;
    }
    else
    {
        dx = (double)(float)(ctx->pt.x - key->x);
        dy = (double)(float)(ctx->pt.y - key->y);
    }
    const double d = dy * dy + dx * dx;
    if (!(d > 0.0))
        return;

    ++d_E08A8;
    d_E08A0 += d;

    Entry* n = (Entry*)SM_alloc(0x20);
    if (!n)
        d_E08D8(2, 3, d_BAD62);
    n->next = ctx->head;
    ctx->head = n;
    n->key = key;
    n->p1 = p;
    n->p2 = p2;
}
