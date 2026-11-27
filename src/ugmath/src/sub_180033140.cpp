





struct Blk { unsigned long long a, b; };
typedef unsigned char (*Cmp)(const void*, const void*);

extern "C" void sub_180033140(char* a1, __int64 a2, __int64 a3, Blk* a4, Cmp cmp)
{
    __int64 n = a3;
    __int64 half = (n - 1) >> 1;
    __int64 cur = a2;
    __int64 child = a2;
    __int64 last = n - 1;
    if (a2 < half)
    {
        do
        {
            child = 2 * child + 2;
            if (cmp(a1 + 16 * child, a1 + 16 * child - 16))
                --child;
            *(Blk*)(a1 + 16 * cur) = *(Blk*)(a1 + 16 * child);
            cur = child;
        }
        while (child < half);
    }
    if (child == half && (n & 1) == 0)
    {
        *(Blk*)(a1 + 16 * cur) = *(Blk*)(a1 + 16 * n - 16);
        cur = last;
    }
    if (a2 < cur)
    {
        __int64 parent;
        do
        {
            parent = (cur - 1) >> 1;
            if (!cmp(a1 + 16 * parent, a4))
                break;
            *(Blk*)(a1 + 16 * cur) = *(Blk*)(a1 + 16 * parent);
            cur = parent;
        }
        while (a2 < parent);
    }
    *(Blk*)(a1 + 16 * cur) = *a4;
}
