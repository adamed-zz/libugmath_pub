










#include <cstddef>

struct BCDF_s;



extern "C" void sub_180011DB0(struct BCDF_s* src, long long dst);


__declspec(dllimport) void* SM_alloc(std::size_t);

struct BCDF_s* BCDF_copy_structure(struct BCDF_s* src)
{
    if (!src)
        return 0;
    struct BCDF_s* dst = (struct BCDF_s*)SM_alloc(0x90);
    sub_180011DB0(src, (long long)dst);
    return dst;
}
