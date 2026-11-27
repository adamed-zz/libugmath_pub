








struct BCDF_s;


double* BCDF_return_slope_array(struct BCDF_s* a, int* count1, int* count2);

void BCDF_scale_slopes(struct BCDF_s* a, double s)
{
    int c1, c2;
    double* arr = BCDF_return_slope_array(a, &c1, &c2);
    for (int i = 0; i < c1 * c2; ++i)
        arr[i] *= s;
}
