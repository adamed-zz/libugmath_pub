










extern "C" void* malloc(unsigned long long);
extern "C" void* realloc(void*, unsigned long long);
extern "C" void free(void*);

static void* alloc_2d(long long n)
{
    if (!n)
        return nullptr;
    if ((unsigned long long)n > 0x1FFFFFFFFFFFFFFFULL)
        throw "bad_alloc";
    void* p = malloc(8 * (unsigned long long)n);
    if (!p)
        throw "bad_alloc";
    return p;
}

static void* realloc_2d(void* old, long long n)
{
    if ((unsigned long long)n > 0x1FFFFFFFFFFFFFFFULL)
        throw "bad_alloc";
    void* p = realloc(old, 8 * (unsigned long long)n);
    if (!p && n)
        throw "bad_alloc";
    return p;
}

extern "C" void sub_18008CF30(long long* d, long long n, long long w, long long h);

extern "C" __declspec(noinline) void sub_18008D1B0(long long* d, long long nw, long long nh)
{
    if (d[1] == nw) {

        if (d[2] != nh) {
            if (nw && nh && nw > 0x7FFFFFFFFFFFFFFFLL / nh)
                throw "bad_alloc";
            d[0] = reinterpret_cast<long long>(realloc_2d(reinterpret_cast<void*>(d[0]),
                                                          nh * nw));
            d[1] = nw;
            d[2] = nh;
        }
    } else {
        long long tmp[3] = {0, 0, 0};
        if (nw && nh && nw > 0x7FFFFFFFFFFFFFFFLL / nh)
            throw "bad_alloc";
        sub_18008CF30(tmp, nh * nw, nw, nh);
        long long cw = d[1] < nw ? d[1] : nw;
        long long ch = d[2] < nh ? d[2] : nh;
        const double* src = reinterpret_cast<const double*>(d[0]);
        double* dst = reinterpret_cast<double*>(tmp[0]);
        for (long long r = 0; r < ch; ++r)
            for (long long c = 0; c < cw; ++c)
                dst[r * nw + c] = src[r * d[1] + c];
        long long old_data = d[0];
        d[0] = tmp[0];
        d[1] = tmp[1];
        d[2] = tmp[2];
        free(reinterpret_cast<void*>(old_data));
    }
}
