










struct BCDF_s;
struct PNTLST_s;



double *__cdecl PNTLST_copy_points(struct PNTLST_s *p, int *c1, int *c2);

double *__cdecl BCDF_copy_slopes(struct BCDF_s *a, int *c1, int *c2)
{
    double *result = 0;
    *c1 = 0;
    *c2 = 0;
    PNTLST_s *node = *(PNTLST_s **)((char *)a + 0x18);
    if (node)
        return PNTLST_copy_points(node, c1, c2);
    return result;
}
