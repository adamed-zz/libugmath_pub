











struct BCDF_s;

extern void BCDF_CALC_auto_derivatives(struct BCDF_s* a, int pos, int order, double* out);

void BCDF_CALC_auto_slope(struct BCDF_s* a, int pos, double* out)
{
    BCDF_CALC_auto_derivatives(a, pos, 1, out);
}
