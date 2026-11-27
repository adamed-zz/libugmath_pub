




































struct BCDF_s;


int BCDF_return_periodicity(BCDF_s* a1);
int BCDF_return_num_of_points(BCDF_s* a1);
int* BCDF_return_slope_type_array(BCDF_s* a1);
int BCDF_slope_at_point(BCDF_s* a1, int a2, int* a3);
void BCDF_copy_single_3d_slope(BCDF_s* a1, int a2, double* const a3,
                               int* a4);
void BCDF_change_slope(BCDF_s* a1, int a2, double* a3, int a4);

static __forceinline void update_one_end(BCDF_s* a1, int point)
{
    int pos = 0;
    if (BCDF_slope_at_point(a1, point, &pos))
    {
        int t = BCDF_return_slope_type_array(a1)[pos];
        if ((t - 1) & 0xFFFFFFFD)
        {
            if (t == 0)
            {
                BCDF_change_slope(a1, t, 0, point);
            }
            else if (((t - 2) & 0xFFFFFFFC) == 0 && t != 3)
            {
                double vec[3];
                BCDF_copy_single_3d_slope(a1, pos, vec, &t);
                BCDF_change_slope(a1, t, vec, point);
            }
        }
    }
}

void BCDF_update_end_slopes(BCDF_s* a1)
{
    if (BCDF_return_periodicity(a1) == 1)
        return;

    update_one_end(a1, 0);
    update_one_end(a1, BCDF_return_num_of_points(a1) - 1);
}
