













struct BCDF_s;

int BCDF_return_num_of_slopes(struct BCDF_s* a);
int BCDF_start_slope_exists(struct BCDF_s* a);
int BCDF_end_slope_exists(struct BCDF_s* a);
void BCDF_remove_slopes(struct BCDF_s* a, int start, int count);

void BCDF_remove_interior_slopes(struct BCDF_s* a)
{
    int n = BCDF_return_num_of_slopes(a);
    if (!n)
        return;
    int last = n - 1;


    int first = 0;
    if (BCDF_start_slope_exists(a))
        first = 1;
    if (BCDF_end_slope_exists(a))
        --last;
    if (first <= last)
        BCDF_remove_slopes(a, first, last - first + 1);
}
