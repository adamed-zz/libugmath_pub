
















struct BCDF_s;




void BCDF_CALC_auto_slope(struct BCDF_s* a, int pos, double* out);
void BCDF_replace_slope(struct BCDF_s* a, double* slope, int idx, int type);

extern "C" void sub_180015F00(struct BCDF_s* a1, int a2)
{
    double v4[3];
    BCDF_CALC_auto_slope(a1, a2, v4);
    BCDF_replace_slope(a1, v4, a2, 0);
}
