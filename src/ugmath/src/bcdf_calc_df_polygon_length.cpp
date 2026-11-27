

















struct BCDF_s;
struct PNTLST_s;

int BCDF_return_num_of_points(BCDF_s* a);
double PNTLST_calc_point_distance(PNTLST_s* pntlst, int i, int j);

double BCDF_calc_df_polygon_length(BCDF_s* a1)
{
    PNTLST_s* lst = *reinterpret_cast<PNTLST_s**>(a1);
    double sum = 0.0;
    int n = BCDF_return_num_of_points(a1) - 1;
    int i = 0;
    if (n > 0)
    {
        do
        {
            sum += PNTLST_calc_point_distance(lst, i, i + 1);
            ++i;
        } while (i < n);
        return sum;
    }
    return 0.0;
}
