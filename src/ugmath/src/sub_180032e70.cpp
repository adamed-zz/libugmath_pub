







#include <cstring>

typedef unsigned char (__fastcall* B6Cmp128)(const void*, const void*);

struct B6E128 { unsigned long long lo, hi; };

static inline B6E128 B6Load128(const void* p) {
    B6E128 v;
    std::memcpy(&v, p, 16);
    return v;
}

static inline void B6Store128(void* p, const B6E128& v) {
    std::memcpy(p, &v, 16);
}

extern "C" unsigned char sub_180032E70(void* a1, void* a2, void* a3, B6Cmp128 a4)
{
    if (a4(a2, a1))
    {
        B6E128 t = B6Load128(a2);
        B6Store128(a2, B6Load128(a1));
        B6Store128(a1, t);
    }
    unsigned char result = a4(a3, a2);
    if ((unsigned char)result)
    {
        B6E128 t = B6Load128(a3);
        B6Store128(a3, B6Load128(a2));
        B6Store128(a2, t);
        result = a4(a2, a1);
        if ((unsigned char)result)
        {
            B6E128 u = B6Load128(a2);
            B6Store128(a2, B6Load128(a1));
            B6Store128(a1, u);
        }
    }
    return (unsigned char)result;
}
