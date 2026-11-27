














struct BCDF_s;
struct PNTLST_s;

int BCDF_return_num_of_points(struct BCDF_s* a);
double PNTLST_calc_point_distance(struct PNTLST_s* pntlst, int i, int j);
double EQ_ask_length_tolerance();

int BCDF_check_consecutive_dup_pts(struct BCDF_s* a1)
{
    int n = BCDF_return_num_of_points(a1);
    struct PNTLST_s* lst = *reinterpret_cast<struct PNTLST_s**>(a1);
    int i = 1;
    if (n <= 1)
        return 0;
    do
    {
        double d = PNTLST_calc_point_distance(lst, i - 1, i);
        if (EQ_ask_length_tolerance() > d)
            return 1;
        ++i;
    } while (i < n);
    return 0;
}
