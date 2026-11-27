












__declspec(dllimport) void *__cdecl SM_alloc(unsigned __int64 size);


struct PNTLST_s
{
    double *points;
    int num;
    int alloc;
    int stride;
};


double *__cdecl PNTLST_copy_points(PNTLST_s *p, int *num, int *stride);

PNTLST_s *__cdecl PNTLST_copy_structure(PNTLST_s *p)
{
    if (!p)
        return 0;
    PNTLST_s *n = static_cast<PNTLST_s *>(SM_alloc(0x18u));
    double *pts = PNTLST_copy_points(p, &n->num, &n->stride);
    int v5 = n->num;
    n->points = pts;
    n->alloc = v5;
    return n;
}
