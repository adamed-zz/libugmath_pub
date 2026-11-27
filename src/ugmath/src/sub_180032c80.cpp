






typedef unsigned long long size_type;
typedef unsigned long long uptr;

struct Blk16 { unsigned long long lo, hi; };
struct VecData16 { Blk16* _Myfirst; Blk16* _Mylast; Blk16* _Myend; };


__declspec(noreturn) void sub_180001530();
__declspec(noreturn) void sub_180033720();
extern "C" __declspec(noreturn) void _invalid_parameter_noinfo_noreturn();

static const size_type kMax16 = 0xFFFFFFFFFFFFFFFULL;
static const size_type kBigThreshold = 0x1000;
static const size_type kNonUserSize = 0x27;
static const size_type kBigAlign = 0x20;
static const uptr kMaskAlign = ~(uptr)(kBigAlign - 1);

static inline size_type MaxSize16() { return kMax16; }

static inline size_type CalcGrowth16(size_type oldcap, size_type newsize)
{
    if (oldcap > MaxSize16() - oldcap / 2)
        sub_180033720();
    const size_type geom = oldcap + oldcap / 2;
    size_type cap = geom;
    if (cap < newsize)
        cap = newsize;
    if (cap > MaxSize16())
        sub_180033720();
    return cap;
}


static inline Blk16* Allocate16(size_type n)
{
    const size_type bytes = n * 16;
    if (bytes >= kBigThreshold)
    {
        const size_type blocksize = kNonUserSize + bytes;
        if (blocksize <= bytes)
            sub_180033720();
        void* const container = ::operator new(blocksize);
        if (container == nullptr)
            _invalid_parameter_noinfo_noreturn();
        Blk16* const p = (Blk16*)(((uptr)container + kNonUserSize) & kMaskAlign);
        ((void**)p)[-1] = container;
        return p;
    }
    if (bytes != 0)
        return (Blk16*)::operator new(bytes);
    return nullptr;
}


static inline void Deallocate16(Blk16* p, size_type cap)
{
    if (p == nullptr)
        return;
    size_type bytes = cap * 16;
    if (bytes >= kBigThreshold)
    {
        bytes += kNonUserSize;
        void* const container = ((void**)p)[-1];
        const uptr backshift = (uptr)p - (uptr)container;
        if (backshift - sizeof(void*) > kNonUserSize - sizeof(void*))
            _invalid_parameter_noinfo_noreturn();
        p = (Blk16*)container;
    }
    ::operator delete(p, bytes);
}


static inline Blk16* MoveRange(Blk16* first, Blk16* last, Blk16* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}

Blk16* sub_180032C80(VecData16* self, Blk16* whereptr, const Blk16* val)
{
    if ((size_type)(self->_Mylast - self->_Myfirst) == MaxSize16())
        sub_180001530();
    const size_type newsize = (size_type)(self->_Mylast - self->_Myfirst) + 1;
    const size_type oldcap = (size_type)(self->_Myend - self->_Myfirst);
    const size_type newcap = CalcGrowth16(oldcap, newsize);

    Blk16* const newvec = Allocate16(newcap);
    const size_type whereoff = (size_type)(whereptr - self->_Myfirst);
    Blk16* const newwhere = newvec + whereoff;
    Blk16* constructed_first = newwhere + 1;

    try
    {
        *newwhere = *val;
        constructed_first = newwhere;
        if (whereptr == self->_Mylast)
        {
            MoveRange(self->_Myfirst, self->_Mylast, newvec);
        }
        else
        {
            MoveRange(self->_Myfirst, whereptr, newvec);
            constructed_first = newvec;
            MoveRange(whereptr, self->_Mylast, newwhere + 1);
        }
    }
    catch (...)
    {
        (void)constructed_first;
        Deallocate16(newvec, newcap);
        throw;
    }

    Deallocate16(self->_Myfirst, oldcap);

    self->_Myfirst = newvec;
    self->_Mylast = newvec + newsize;
    self->_Myend = newvec + newcap;
    return newwhere;
}
