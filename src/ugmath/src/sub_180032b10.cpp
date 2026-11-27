






typedef unsigned long long size_type;
namespace UGS { namespace Memory {
struct CppMemory {
    static void* __cdecl allocate(unsigned __int64);
    static void  __cdecl free(void*);
};
}}
extern "C" __declspec(noreturn) void sub_180001530();

struct VecData8 { unsigned __int64* _Myfirst; unsigned __int64* _Mylast; unsigned __int64* _Myend; };
struct Vec8 { VecData8 _Myval2; };

static const size_type kMax8 = 0x1FFFFFFFFFFFFFFFULL;

static inline size_type MaxSize8() { return kMax8; }


static inline size_type CalcGrowth8(const VecData8& d, size_type newsize)
{
    const size_type oldcap = (size_type)(d._Myend - d._Myfirst);
    const size_type mx = MaxSize8();
    if (oldcap > mx - oldcap / 2)
        return mx;
    const size_type geom = oldcap + oldcap / 2;
    if (geom < newsize)
        return newsize;
    return geom;
}

static inline void ChangeArray8(VecData8& d, unsigned __int64* newvec, size_type newsize, size_type newcap)
{
    if (d._Myfirst)
        UGS::Memory::CppMemory::free(d._Myfirst);
    d._Myfirst = newvec;
    d._Mylast = newvec + newsize;
    d._Myend = newvec + newcap;
}

extern "C" unsigned __int64* sub_180032B10(Vec8* self, unsigned __int64* whereptr, const unsigned __int64* val)
{
    VecData8& d = self->_Myval2;
    const size_type whereoff = (size_type)(whereptr - d._Myfirst);
    const size_type oldsize = (size_type)(d._Mylast - d._Myfirst);
    if (oldsize == MaxSize8())
        sub_180001530();
    const size_type newsize = oldsize + 1;
    const size_type newcap = CalcGrowth8(d, newsize);
    unsigned __int64* const newvec = (unsigned __int64*)UGS::Memory::CppMemory::allocate(newcap * 8u);

    newvec[whereoff] = *val;

    if (whereptr == d._Mylast)
    {
        unsigned __int64* dest = newvec;
        for (unsigned __int64* src = d._Myfirst; src != d._Mylast; ++src)
            *dest++ = *src;
    }
    else
    {
        unsigned __int64* dest = newvec;
        for (unsigned __int64* src = d._Myfirst; src != whereptr; ++src)
            *dest++ = *src;
        dest = newvec + whereoff + 1;
        for (unsigned __int64* src = whereptr; src != d._Mylast; ++src)
            *dest++ = *src;
    }
    ChangeArray8(d, newvec, newsize, newcap);
    return newvec + whereoff;
}
