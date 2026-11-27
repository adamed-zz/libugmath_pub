










struct PNTLST_s
{
    double *points;
    int num;
    int capacity;
    int dim;
};



PNTLST_s *PNTLST_allocate_struct(int a, int b);

PNTLST_s *PNTLST_get_from_func(int a1, int a2, void (*a3)(int, double *))
{
    PNTLST_s *p = PNTLST_allocate_struct(a2, a1);
    double *pts = p->points;
    p->num = a1;
    a3(a1, pts);
    return p;
}
