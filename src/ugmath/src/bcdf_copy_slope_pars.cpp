












struct BCDF_s;
struct PNTLST_s;



extern double* PNTLST_copy_points(PNTLST_s* p, int* a2, int* a3);

double* BCDF_copy_slope_pars(BCDF_s* a, int* count)
{
    *count = 0;
    PNTLST_s* node = *reinterpret_cast<PNTLST_s**>(reinterpret_cast<char*>(a) + 0x20);
    if (!node)
        return 0;
    int tmp;
    return PNTLST_copy_points(node, count, &tmp);
}
