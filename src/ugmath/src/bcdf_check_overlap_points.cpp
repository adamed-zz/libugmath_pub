














#include <cmath>

struct BCDF_s;

int BCDF_return_num_of_points(struct BCDF_s* a);
int BCDF_check_consecutive_dup_pts(struct BCDF_s* a);
void BCDF_copy_single_3d_point(struct BCDF_s* a, int index, double* const out);
double EQ_ask_length_tolerance();

int BCDF_check_overlap_points(struct BCDF_s* a1, int a2, int a3, double* const a4)
{
    int ret = 0;
    double p[3];
    double q[3];
    int n = BCDF_return_num_of_points(a1);
    switch (a2)
    {
    case 1:
        if (a3 > 0)
        {
            BCDF_copy_single_3d_point(a1, a3 - 1, p);
            if (sqrt((a4[0] - p[0]) * (a4[0] - p[0]) +
                     (a4[1] - p[1]) * (a4[1] - p[1]) +
                     (a4[2] - p[2]) * (a4[2] - p[2])) < EQ_ask_length_tolerance())
            {
                ret = 1;
                break;
            }
        }
        if (a3 < n - 1)
        {
            BCDF_copy_single_3d_point(a1, a3 + 1, q);
            if (sqrt((a4[0] - q[0]) * (a4[0] - q[0]) +
                     (a4[1] - q[1]) * (a4[1] - q[1]) +
                     (a4[2] - q[2]) * (a4[2] - q[2])) < EQ_ask_length_tolerance())
                ret = 1;
        }
        break;
    case 2:
        if (a3 > 0 && a3 < n - 1)
        {
            BCDF_copy_single_3d_point(a1, a3 - 1, p);
            BCDF_copy_single_3d_point(a1, a3 + 1, q);
            if (sqrt((p[0] - q[0]) * (p[0] - q[0]) +
                     (p[1] - q[1]) * (p[1] - q[1]) +
                     (p[2] - q[2]) * (p[2] - q[2])) < EQ_ask_length_tolerance())
            {
                ret = 1;
                break;
            }
        }
        break;
    case 3:
        ret = BCDF_check_consecutive_dup_pts(a1);
        break;
    }
    return ret;
}
