











struct BCDF_s;

__declspec(dllimport) void* SM_alloc(size_t size);

int* BCDF_copy_constraint_type_array(struct BCDF_s* a1, int* a2)
{
    int i = 0;

    int count = (*reinterpret_cast<void**>(reinterpret_cast<char*>(a1) + 0x80) &&
                 *reinterpret_cast<void**>(a1))
                    ? *reinterpret_cast<int*>(*reinterpret_cast<char**>(a1) + 8)
                    : 0;
    *a2 = count;
    int* src = *reinterpret_cast<int**>(reinterpret_cast<char*>(a1) + 0x80);
    if (!src)
        return 0;
    int* result = static_cast<int*>(SM_alloc(4LL * count));
    for (i = 0; i < *a2; ++i)
        result[i] = src[i];
    return result;
}
