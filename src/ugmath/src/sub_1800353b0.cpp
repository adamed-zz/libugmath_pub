







#include <cstdlib>
#include <cstring>

struct Blk16 { unsigned __int64 lo, hi; };
struct VecData16 { Blk16* begin; Blk16* end; Blk16* cap; };
struct Vec { char* begin; char* end; char* cap; };


Blk16* sub_180032C80(VecData16* self, Blk16* whereptr, const Blk16* val);
extern "C" void sub_1800329B0(void* vec, char* end, const int* val);
extern "C" __int64 sub_180033250(char* first, char* last, __int64 ideal,
                                 unsigned char (__fastcall* cmp)(const void*, const void*));
extern "C" bool sub_180033740(const void* a1, const void* a2);
extern "C" void _invalid_parameter_noinfo_noreturn(void);

extern "C" __int64 sub_1800353B0(int n, const unsigned __int64* keys, const unsigned int* ranks,
                                 Vec* out)
{
    VecData16 tmp = { 0, 0, 0 };
    if (n > 0)
    {
        for (int i = 0; i < n; ++i)
        {
            Blk16 e;
            e.lo = keys[i];
            e.hi = ((unsigned __int64)(unsigned)i << 32) | ranks[i];
            if (tmp.end == tmp.cap)
                sub_180032C80(&tmp, tmp.end, &e);
            else
            {
                *tmp.end = e;
                ++tmp.end;
            }
        }
    }
    char* tb = (char*)tmp.begin;
    char* te = (char*)tmp.end;
    __int64 result = sub_180033250(tb, te, (__int64)(te - tb) >> 4,
                  (unsigned char (__fastcall*)(const void*, const void*))sub_180033740);
    if (n > 0)
    {
        char* p = tb + 12;
        for (int k = 0; k < n; ++k)
        {
            int idx = *(int*)p;
            if (out->end == out->cap)
                sub_1800329B0(out, out->end, &idx);
            else
            {
                result = idx;
                *(int*)out->end = idx;
                out->end += 4;
            }
            p += 16;
        }
    }
    if (tmp.begin)
    {
        char* base = tb;
        if (((unsigned __int64)((char*)tmp.cap - tb) & ~15ull) >= 0x1000)
        {
            char* b2 = *(char**)(tb - 8);
            if ((unsigned __int64)(base - b2) - 8 > 0x1F)
                _invalid_parameter_noinfo_noreturn();
            base = b2;
        }

        typedef __int64 (__cdecl* FreeFn)(void*);
        return ((FreeFn)free)(base);
    }
    return result;
}
