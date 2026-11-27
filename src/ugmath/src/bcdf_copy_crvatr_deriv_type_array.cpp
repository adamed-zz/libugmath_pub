








struct BCDF_s;

__declspec(dllimport) void* SM_alloc(size_t size);

namespace
{

struct BCDF_array_node
{
    void* first;
    int   count;
};
}


int* BCDF_copy_crvatr_deriv_type_array(struct BCDF_s* a)
{
    BCDF_array_node* node =
        *reinterpret_cast<BCDF_array_node**>(reinterpret_cast<char*>(a) + 0x38);
    int count = node ? node->count : 0;
    int* src = *reinterpret_cast<int**>(reinterpret_cast<char*>(a) + 0x58);
    int* result = static_cast<int*>(SM_alloc(4LL * count));
    for (__int64 j = 0; j < count; ++j)
    {
        result[j] = src[j];
    }
    return result;
}
