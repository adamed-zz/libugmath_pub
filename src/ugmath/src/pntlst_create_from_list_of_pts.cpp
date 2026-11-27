











__declspec(dllimport) void *__cdecl SM_alloc(unsigned __int64 size);


struct PNTLST_s
{
    double *points;
    int num;
    int alloc;
    int stride;
};

PNTLST_s *__cdecl PNTLST_create_from_list_of_pts(double *pts, int num, int stride)
{
    PNTLST_s *p = static_cast<PNTLST_s *>(SM_alloc(0x18));
    p->points = pts;
    p->stride = stride;
    p->num = num;
    p->alloc = num;
    return p;
}
