









#include <cstdlib>
#include <cstring>

struct Blk { unsigned long long a, b; };
typedef unsigned char (*Cmp)(const void*, const void*);
struct Pair16 { Blk* first; Blk* second; };

extern "C" Pair16* sub_180032EF0(Pair16* out, Blk* first, Blk* last, Cmp cmp);
extern "C" void sub_180033140(char* base, __int64 pos, __int64 n, Blk* tmp, Cmp cmp);

extern "C" void sub_180033250(char* first, char* last, __int64 ideal, Cmp pred)
{
    char* f = first;
    char* l = last;

    while (((l - f) & ~15ll) > 512)
    {
        if (ideal <= 0)
        {

            __int64 n = (l - f) >> 4;
            __int64 half = n >> 1;
            if (half > 0)
            {
                __int64 nm1 = n - 1;
                __int64 halfm1 = (n - 1) >> 1;
                char* it = f + 16 * half;
                do
                {
                    Blk tmp = *((Blk*)it - 1);
                    --half;
                    it -= 16;
                    __int64 pos = half;
                    __int64 child = half;
                    if (half < halfm1)
                    {
                        do
                        {
                            child = 2 * child + 2;
                            if (pred(f + 16 * child, f + 16 * child - 16))
                                --child;
                            *(Blk*)(f + 16 * pos) = *(Blk*)(f + 16 * child);
                            pos = child;
                        } while (child < halfm1);
                        nm1 = n - 1;
                    }
                    if (child == halfm1 && (n & 1) == 0)
                    {
                        *(Blk*)(f + 16 * pos) = *(Blk*)(f + 16 * n - 16);
                        pos = nm1;
                    }
                    if (half < pos)
                    {
                        __int64 parent;
                        do
                        {
                            parent = (pos - 1) >> 1;
                            if (!pred(f + 16 * parent, (char*)&tmp))
                                break;
                            *(Blk*)(f + 16 * pos) = *(Blk*)(f + 16 * parent);
                            pos = parent;
                        } while (half < parent);
                    }
                    *(Blk*)(f + 16 * pos) = tmp;
                } while (half > 0);
            }

            if (n >= 2)
            {
                char* end = l - 16;
                __int64 diff;
                do
                {
                    diff = end - f;
                    Blk tmp = *(Blk*)end;
                    *(Blk*)end = *(Blk*)f;
                    sub_180033140(f, 0, diff >> 4, &tmp, pred);
                    end -= 16;
                } while ((diff & ~15ll) >= 32);
            }
            return;
        }


        Pair16 mid;
        sub_180032EF0(&mid, (Blk*)f, (Blk*)l, pred);
        char* mfirst = (char*)mid.first;
        char* msecond = (char*)mid.second;
        ideal = (ideal >> 2) + (ideal >> 1);
        if (((mfirst - f) & ~15ll) < ((l - msecond) & ~15ll))
        {
            sub_180033250(f, mfirst, ideal, pred);
            f = msecond;
        }
        else
        {
            sub_180033250(msecond, l, ideal, pred);
            l = mfirst;
        }
    }


    if (f != l)
    {
        char* cur = f + 16;
        if (f + 16 != l)
        {
            char* prow = f;
            do
            {
                char* next = cur;
                Blk tmp = *(Blk*)cur;
                if (pred(&tmp, f))
                {
                    memmove(f + 16, f, cur - f);
                    *(Blk*)f = tmp;
                }
                else
                {
                    char* p = prow;
                    while (pred(&tmp, p))
                    {
                        *(Blk*)next = *(Blk*)p;
                        next = p;
                        p -= 16;
                    }
                    *(Blk*)next = tmp;
                }
                cur += 16;
                prow += 16;
            } while (cur != l);
        }
    }
}
