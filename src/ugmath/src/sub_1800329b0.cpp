






typedef unsigned long long size_type;
namespace UGS { namespace Memory {
struct CppMemory {
    static void* __cdecl allocate(unsigned __int64);
    static void  __cdecl free(void*);
};
}}
extern "C" __declspec(noreturn) void sub_180001530();

struct VecData4 { int* _Myfirst; int* _Mylast; int* _Myend; };
struct Vec4 { VecData4 _Myval2; };

static const size_type kMax4 = 0x3FFFFFFFFFFFFFFFULL;

static inline size_type MaxSize4() { return kMax4; }


static inline size_type CalcGrowth4(const VecData4& d, size_type newsize)
{
    const size_type oldcap = (size_type)(d._Myend - d._Myfirst);
    const size_type mx = MaxSize4();
    if (oldcap > mx - oldcap / 2)
        return mx;
    const size_type geom = oldcap + oldcap / 2;
    if (geom < newsize)
        return newsize;
    return geom;
}

static inline void ChangeArray4(VecData4& d, int* newvec, size_type newsize, size_type newcap)
{
    if (d._Myfirst)
        UGS::Memory::CppMemory::free(d._Myfirst);
    d._Myfirst = newvec;
    d._Mylast = newvec + newsize;
    d._Myend = newvec + newcap;
}

extern "C" int* sub_1800329B0(Vec4* self, int* whereptr, const int* val)
{
    VecData4& d = self->_Myval2;
    const size_type whereoff = (size_type)(whereptr - d._Myfirst);
    const size_type oldsize = (size_type)(d._Mylast - d._Myfirst);
    if (oldsize == MaxSize4())
        sub_180001530();
    const size_type newsize = oldsize + 1;
    const size_type newcap = CalcGrowth4(d, newsize);
    int* const newvec = (int*)UGS::Memory::CppMemory::allocate(newcap * sizeof(int));

    newvec[whereoff] = *val;

    if (whereptr == d._Mylast)
    {
        int* dest = newvec;
        for (int* src = d._Myfirst; src != d._Mylast; ++src)
            *dest++ = *src;
    }
    else
    {
        int* dest = newvec;
        for (int* src = d._Myfirst; src != whereptr; ++src)
            *dest++ = *src;
        dest = newvec + whereoff + 1;
        for (int* src = whereptr; src != d._Mylast; ++src)
            *dest++ = *src;
    }
    ChangeArray4(d, newvec, newsize, newcap);
    return newvec + whereoff;
}
