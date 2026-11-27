






struct BCDF_s;

void BCDF_copy_single_3d_slope(BCDF_s *a1, int a2, double *const a3, int *a4);
int  BCDF_point_at_slope(BCDF_s *a1, int a2);
void BCDF_CALC_auto_slope(BCDF_s *a1, int a2, double *a3);
void BCDF_replace_slope(BCDF_s *a1, double *a2, int a3, int a4);

extern "C" void __fastcall sub_18001A620(BCDF_s *a1, int a2)
{
    double v5[3];
    double v8[3];
    int v9;

    BCDF_copy_single_3d_slope(a1, a2, v5, &v9);
    if (v9 == 4)
    {
        int v4 = BCDF_point_at_slope(a1, a2);
        BCDF_CALC_auto_slope(a1, v4, v8);
        if (0.0 > v8[0] * v5[0] + v8[1] * v5[1] + v8[2] * v5[2])
        {
            v5[0] = v5[0] * -1.0;
            v5[1] = v5[1] * -1.0;
            v5[2] = v5[2] * -1.0;
            BCDF_replace_slope(a1, v5, v4, v9);
        }
    }
}
