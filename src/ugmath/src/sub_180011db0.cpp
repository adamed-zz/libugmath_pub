






#include <cstddef>

struct BCDF_s;
struct PNTLST_s;


PNTLST_s* PNTLST_copy_structure(PNTLST_s* a);
int* BCDF_copy_slope_type_array(BCDF_s* a);
int* BCDF_copy_crvatr_type_array(BCDF_s* a);
int* BCDF_copy_crvatr_deriv_type_array(BCDF_s* a);


__declspec(dllimport) void* SM_alloc(size_t size);




extern "C" void sub_180011DB0(struct BCDF_s** a1, long long a2)
{
    if (!a1)
        return;
    if (!a2)
        return;

    PNTLST_s** src = (PNTLST_s**)a1;
    char* dst = (char*)a2;

    *(PNTLST_s**)dst = PNTLST_copy_structure(src[0]);
    *(PNTLST_s**)(dst + 16) = PNTLST_copy_structure(src[2]);
    *(PNTLST_s**)(dst + 8) = PNTLST_copy_structure(src[1]);
    *(PNTLST_s**)(dst + 24) = PNTLST_copy_structure(src[3]);
    *(PNTLST_s**)(dst + 32) = PNTLST_copy_structure(src[4]);
    *(int**)(dst + 72) = BCDF_copy_slope_type_array((BCDF_s*)a1);
    *(PNTLST_s**)(dst + 40) = PNTLST_copy_structure(src[5]);
    *(PNTLST_s**)(dst + 48) = PNTLST_copy_structure(src[6]);
    *(int**)(dst + 80) = BCDF_copy_crvatr_type_array((BCDF_s*)a1);
    *(PNTLST_s**)(dst + 56) = PNTLST_copy_structure(src[7]);
    *(PNTLST_s**)(dst + 64) = PNTLST_copy_structure(src[8]);
    *(int**)(dst + 88) = BCDF_copy_crvatr_deriv_type_array((BCDF_s*)a1);

    int* constraints = 0;
    PNTLST_s* node = src[16];
    if (node)
    {
        int count = 0;
        if (src[0])
            count = *(int*)((char*)src[0] + 8);
        long long n = count;
        constraints = (int*)SM_alloc(4 * n);
        if (n > 0)
        {
            int* d = constraints;
            long long delta = (char*)node - (char*)d;
            do
            {
                *d = *(int*)((char*)d + delta);
                ++d;
                --n;
            } while (n);
        }
    }
    *(long long*)(dst + 128) = (long long)constraints;

    *(long long*)(dst + 96) = ((long long*)a1)[12];
    *(int*)(dst + 104) = ((int*)a1)[26];
    *(int*)(dst + 108) = ((int*)a1)[27];
    *(int*)(dst + 112) = ((int*)a1)[28];
    *(int*)(dst + 140) = ((int*)a1)[35];
    *(char*)(dst + 136) = ((char*)a1)[136];
}
