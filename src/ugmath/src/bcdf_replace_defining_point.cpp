
















struct BCDF_s;
struct PNTLST_s;

extern int BCDF_return_num_of_points(struct BCDF_s*);
extern int BCDF_return_periodicity(struct BCDF_s*);
extern void PNTLST_replace_points(struct PNTLST_s*, int, int, double*);

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

void BCDF_replace_defining_point(struct BCDF_s* a, double* pt, int pos, int dim)
{
    struct PNTLST_s* list = *(struct PNTLST_s**)((char*)a + 0);
    int mirror = -1;
    int num = BCDF_return_num_of_points(a);
    if (BCDF_return_periodicity(a) == 1)
    {
        if (pos == 0)
            mirror = num - 1;
        else if (pos == num - 1)
            mirror = 0;
    }
    if (dim == 3 && list->dim == 4)
    {
        double w = list->points[pos * 4 + 3];
        double buf[4];
        buf[3] = w;
        buf[0] = pt[0] * w;
        buf[1] = pt[1] * w;
        buf[2] = pt[2] * w;
        PNTLST_replace_points(list, dim - 2, pos, buf);
        if (mirror != -1)
            PNTLST_replace_points(list, 1, mirror, buf);
        return;
    }
    if (dim == 4 && list->dim == 3)
    {
        double w = pt[3];
        double buf[3];
        buf[0] = pt[0] / w;
        buf[1] = pt[1] / w;
        buf[2] = pt[2] / w;
        PNTLST_replace_points(list, dim - 3, pos, buf);
        if (mirror != -1)
            PNTLST_replace_points(list, 1, mirror, buf);
        return;
    }
    PNTLST_replace_points(list, 1, pos, pt);
    if (mirror != -1)
        PNTLST_replace_points(list, 1, mirror, pt);
}
