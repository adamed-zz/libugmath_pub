


































struct BCDF_s;


int BCDF_return_num_of_slopes(BCDF_s* a1);
int BCDF_start_slope_exists(BCDF_s* a1);
int BCDF_end_slope_exists(BCDF_s* a1);

extern "C" void sub_18001A620(BCDF_s* a1, int a2);
int* BCDF_return_slope_type_array(BCDF_s* a1);
int BCDF_point_at_slope(BCDF_s* a1, int a2);
void BCDF_change_slope(BCDF_s* a1, int a2, double* a3, int a4);
void BCDF_copy_single_3d_slope(BCDF_s* a1, int a2, double* const a3,
                               int* a4);
void BCDF_CALC_auto_slope(BCDF_s* a1, int a2, double* a3);
void BCDF_CALC_normalized_slope(BCDF_s* a1, int a2, int a3,
                                double* a4);
void BCDF_replace_slope(BCDF_s* a1, double* a2, int a3, int a4);
void BCDF_update_end_slopes(BCDF_s* a1);

void BCDF_update_slopes(BCDF_s* a1)
{
    int num = BCDF_return_num_of_slopes(a1);
    int started = BCDF_start_slope_exists(a1);
    int ended = BCDF_end_slope_exists(a1);
    int end = ended ? num - 1 : num;
    int i = 0;
    int j = started != 0;
    for (; j < end; ++j)
        sub_18001A620(a1, j);
    if (started)
        sub_18001A620(a1, 0);
    if (ended)
        sub_18001A620(a1, num - 1);

    int byteoff = 0;
    for (; i < num; ++i, byteoff += 4)
    {
        int t = *(int*)((char*)BCDF_return_slope_type_array(a1) + byteoff);
        if ((t - 1) & 0xFFFFFFFD)
        {
            int pos = BCDF_point_at_slope(a1, i);
            if (!t)
            {
                BCDF_change_slope(a1, 0, 0, pos);
                continue;
            }
            if (((t - 2) & 0xFFFFFFFC) == 0 && t != 3)
            {
                double vec[3];
                double out[3];
                double* res;
                int rt;
                BCDF_copy_single_3d_slope(a1, i, vec, &t);
                switch (t)
                {
                case 0:
                    BCDF_CALC_auto_slope(a1, pos, out);
                    res = out;
                    rt = 0;
                    break;
                case 1:
                    res = vec;
                    rt = 1;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    BCDF_CALC_normalized_slope(a1, t, pos, vec);
                    res = vec;
                    rt = t;
                    break;
                default:
                    continue;
                }
                BCDF_replace_slope(a1, res, pos, rt);
            }
        }
    }

    BCDF_update_end_slopes(a1);
}
