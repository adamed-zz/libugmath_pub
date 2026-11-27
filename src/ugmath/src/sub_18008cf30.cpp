








extern "C" void* malloc(unsigned long long);
extern "C" void free(void*);

static void* alloc_items(long long n)
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

extern "C" __declspec(noinline) long long sub_18008CF30(long long* a1, long long a2,
                                                        long long a3, long long a4)
{
    long long result = a1[2] * a1[1];
    if (a2 == result) {
        a1[1] = a3;
        a1[2] = a4;
    } else {
        free(reinterpret_cast<void*>(*a1));
        if (a2 <= 0) {
            *a1 = 0;
        } else {
            result = reinterpret_cast<long long>(alloc_items(a2));
            *a1 = result;
        }
        a1[1] = a3;
        a1[2] = a4;
    }
    return result;
}
