









#include <string.h>


__declspec(dllimport) void* SM_realloc(void* ptr, unsigned __int64 size);


struct PNTLST_s {
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

void PNTLST_concat_one_point(PNTLST_s* a1, double* a2)
{
    double* points = a1->points;
    int alloc = a1->alloc;
    int num   = a1->num;
    __int64 dim = a1->dim;
    if (alloc == num)
    {
        int newAlloc = alloc + 1;

        points = (double*)SM_realloc(points, dim * (__int64)newAlloc * 8);
        a1->points = points;
        a1->alloc  = newAlloc;
    }
    a1->num = num + 1;

    memcpy(&points[num * (int)dim], a2, 8 * dim);
}
