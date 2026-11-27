






extern "C" void* malloc(unsigned long long);
extern "C" void free(void*);

static void* alloc_items_1d(long long n)
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

extern "C" __declspec(noinline) void sub_18008CFB0(long long* a1, long long a2)
{
    if (a2 == a1[1]) {
        a1[1] = a2;
    } else {
        free(reinterpret_cast<void*>(*a1));
        if (a2 <= 0)
            *a1 = 0;
        else
            *a1 = reinterpret_cast<long long>(alloc_items_1d(a2));
        a1[1] = a2;
    }
}
