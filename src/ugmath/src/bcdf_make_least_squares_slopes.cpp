










struct BCDF_s;

int BCDF_return_num_of_slopes(BCDF_s* a);
int BCDF_return_num_of_points(BCDF_s* a);
int BCDF_start_slope_exists(BCDF_s* a);
int BCDF_end_slope_exists(BCDF_s* a);
void BCDF_CALC_auto_slope(BCDF_s* a, int pos, double* out);
void BCDF_replace_slope(BCDF_s* a, double* slope, int idx, int type);
void BCDF_remove_slopes(BCDF_s* a, int start, int count);
void BCDF_unitize_slopes(BCDF_s* a);

void BCDF_make_least_squares_slopes(BCDF_s* a)
{
    int n = BCDF_return_num_of_slopes(a);
    if (n == 0)
        return;
    int np = BCDF_return_num_of_points(a);
    int started = BCDF_start_slope_exists(a);
    int ended = BCDF_end_slope_exists(a);
    double slope[4];
    if (!started)
    {
        if (!ended)
        {
            BCDF_remove_slopes(a, 0, n);
            return;
        }
        BCDF_CALC_auto_slope(a, 0, slope);
        BCDF_replace_slope(a, slope, 0, 0);
    }
    else
    {
        if (ended)
            goto L9;
        BCDF_CALC_auto_slope(a, np - 1, slope);
        BCDF_replace_slope(a, slope, np - 1, 0);
    }
L9:
    BCDF_remove_slopes(a, 1, n - 2);
    BCDF_unitize_slopes(a);
}
