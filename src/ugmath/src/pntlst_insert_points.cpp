










#include <string.h>


__declspec(dllimport) void* SM_realloc(void* ptr, unsigned __int64 size);


struct PNTLST_s {
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

void PNTLST_insert_points(PNTLST_s* pntlst, int n, int at, double* pts)
{
    int alloc = pntlst->alloc;
    int num   = pntlst->num;
    int newnum = num + n;
    if (alloc < newnum)
    {
        int newalloc = num + 2 * alloc + n;

        pntlst->points = (double*)SM_realloc(pntlst->points,
                                             pntlst->dim * (__int64)newalloc * 8);
        pntlst->alloc = newalloc;
    }
    double* points = pntlst->points;
    int dim = pntlst->dim;
    int dst = at * dim;

    memmove(&points[(at + 1) * dim], &points[dst],
            (num - at) * (__int64)dim * 8);
    if (n > 0)
    {
        __int64 src = 0;
        do
        {
            for (int j = 0; j < dim; ++j)
                points[dst + j] = pts[src + j];
            dst += dim;
            src += dim;
        } while (--n);
    }
    pntlst->num = newnum;
}
