






















#include <math.h>

struct BCDF_s;


int BCDF_return_num_of_crvatrs(BCDF_s* a1);
int* BCDF_return_crvatr_type_array(BCDF_s* a1);
void BCDF_copy_single_3d_crvatr(BCDF_s* a1, int index, double* const out,
                                int* flag);
int BCDF_point_at_curvature(BCDF_s* a1, int a2);



void BCDF_change_curvature(BCDF_s* a1, int type, int a3, int pos, double curv);

void BCDF_update_curvatures(BCDF_s* a1)
{
    int num = BCDF_return_num_of_crvatrs(a1);
    int* types = BCDF_return_crvatr_type_array(a1);
    int i = 0;
    if (num > 0)
    {
        do
        {
            if (types[i] == 1)
            {
                double vec[3];
                int flag;
                BCDF_copy_single_3d_crvatr(a1, i, vec, &flag);
                double len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
                double curv = 1.0 / len;
                int pos = BCDF_point_at_curvature(a1, i);
                BCDF_change_curvature(a1, flag, 0, pos, curv);
            }
            ++i;
        } while (i < num);
    }
}
