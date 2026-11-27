












__declspec(dllimport) void *__cdecl SM_alloc(unsigned __int64 size);



extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned __int64 size);
#pragma intrinsic(memcpy)


struct PNTLST_s
{
    double *points;
    int num;
    int alloc;
    int dim;
};

double *__cdecl PNTLST_copy_points(PNTLST_s *p, int *a2, int *a3)
{
    int num = p->num;
    int dim = p->dim;
    double *src = p->points;
    double *copy = static_cast<double *>(SM_alloc(8 * (long long)dim * num));
    memcpy(copy, src, 8 * (long long)dim * num);
    *a2 = num;
    *a3 = dim;
    return copy;
}
