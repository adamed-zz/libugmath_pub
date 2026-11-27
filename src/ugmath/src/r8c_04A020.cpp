


#include <emmintrin.h>

extern "C" void* g_b15_raw_base;

static void* Slot(unsigned rva) { return *(void**)((char*)g_b15_raw_base + rva); }

struct Node
{
    const void* key;
    const void* n1;
    const void* n2;
    Node* next;
};

typedef void* (*Fn_alloc)(unsigned long long);
typedef void (*Fn_free)(void*);
typedef void (*Fn_err)(int, int, const char*);



static double dot3(const float* n, const float* v)
{
    double ny = n[1], nx = n[0], nz = n[2];
    double vy = v[1], vx = v[0], vz = v[2];
    __m128d acc = _mm_mul_sd(_mm_load_sd(&ny), _mm_load_sd(&vy));
    acc = _mm_add_sd(acc, _mm_mul_sd(_mm_load_sd(&nx), _mm_load_sd(&vx)));
    acc = _mm_add_sd(acc, _mm_mul_sd(_mm_load_sd(&nz), _mm_load_sd(&vz)));
    double r;
    _mm_store_sd(&r, acc);
    return r;
}

extern "C" void sub_18004A020(void* a1, float* a2, float* a3, float* a4, char a5)
{


    if (!((Fn_alloc)Slot(0xB9448))(0x20))
        ((Fn_err)Slot(0xE08D8))(2, 3, (const char*)((char*)g_b15_raw_base + 0xBAD62));

    Node* cur = *(Node**)((char*)a1 + 0x10);
    Node* prev = nullptr;
    while (cur && cur->key != a3)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur)
    {
        if (a5)
            return;
        const double thr = *(double*)((char*)g_b15_raw_base + 0xE0898);
        const float* n1 = (const float*)cur->n1;
        const float* n2 = (const float*)cur->n2;
        if (dot3(n1, a2) > thr)
        {
            Node* nx = cur->next;
            if (prev)
                prev->next = nx;
            else
                *(Node**)((char*)a1 + 0x10) = nx;
            ((Fn_free)Slot(0xB9440))(cur);
            return;
        }
        if (dot3(n2, a4) > thr)
        {
            Node* nx = cur->next;
            if (prev)
                prev->next = nx;
            else
                *(Node**)((char*)a1 + 0x10) = nx;
            ((Fn_free)Slot(0xB9440))(cur);
        }
        return;
    }

    const float* ctx = (const float*)a1;
    double dx, dy;
    if (*(int*)((char*)g_b15_raw_base + 0xE07A4))
    {
        dx = (double)ctx[0] / (double)ctx[2] - (double)a3[0] / (double)a3[2];
        dy = (double)ctx[1] / (double)ctx[2] - (double)a3[1] / (double)a3[2];
    }
    else
    {
        dx = (double)(float)(ctx[0] - a3[0]);
        dy = (double)(float)(ctx[1] - a3[1]);
    }
    double d = dy * dy + dx * dx;
    if (!(d > 0.0))
        return;

    ++*(int*)((char*)g_b15_raw_base + 0xE08A8);
    *(double*)((char*)g_b15_raw_base + 0xE08A0) += d;

    Node* n = (Node*)((Fn_alloc)Slot(0xB9448))(0x20);
    if (!n)
        ((Fn_err)Slot(0xE08D8))(2, 3, (const char*)((char*)g_b15_raw_base + 0xBAD62));
    n->next = *(Node**)((char*)a1 + 0x10);
    *(Node**)((char*)a1 + 0x10) = n;
    n->key = a3;
    n->n1 = a2;
    n->n2 = a4;
}
