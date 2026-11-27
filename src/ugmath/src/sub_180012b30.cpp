















#include <cmath>
#include <cstring>

struct BCDF_s;

int BCDF_return_num_of_points(struct BCDF_s*);
double* BCDF_return_param_array(struct BCDF_s*, int*);
void BCDF_copy_single_3d_point(struct BCDF_s*, int, double* const);
void BCDF_copy_single_3d_slope(struct BCDF_s*, int, double* const, int*);
int BCDF_slope_at_point(struct BCDF_s*, int, int*);
void BCDF_CALC_mirror_slope(double*, double*, double*, double*);
int SOLVE_solve_3equations(double (*const)[3], double* const, double* const);

extern "C" void sub_180012B30(struct BCDF_s* a1, int a2, double* a3)
{
    int cnt;
    int idx;
    int n = BCDF_return_num_of_points(a1);
    double* par = BCDF_return_param_array(a1, &cnt);
    int last = n - 1;
    int n3 = 3 * a2;
    int prev = n - 2;
    if (n3 > 0)
        memset(a3, 0, (size_t)(long long)n3 * 8);

    double p0[3];
    double p1[3];
    BCDF_copy_single_3d_point(a1, prev, p0);
    BCDF_copy_single_3d_point(a1, last, p1);

    if (n == 2)
    {
        double inv = 1.0 / (par[last] - par[prev]);
        a3[0] = (p1[0] - p0[0]) * inv;
        a3[1] = (p1[1] - p0[1]) * inv;
        a3[2] = (p1[2] - p0[2]) * inv;
    }
    else
    {


        double blk[9];
        double slope[3];
        int flag;
        if (BCDF_slope_at_point(a1, prev, &idx))
        {
            BCDF_copy_single_3d_slope(a1, idx, slope, &flag);
            if (((flag - 2) & 0xFFFFFFFC) != 0 || flag == 3)
            {

                double t0 = par[prev];
                double t1 = par[last];
                double m[3][3];
                m[0][0] = t0 * t0;
                m[0][1] = t0;
                m[0][2] = 1.0;
                m[1][0] = t0 + t0;
                m[1][1] = 1.0;
                m[1][2] = 0.0;
                m[2][0] = t1 * t1;
                m[2][1] = t1;
                m[2][2] = 1.0;

                double c2[3];
                double c1[3];
                double c0[3];
                double x[3];
                __int64 i = 0;
                while (1)
                {
                    double b[3];
                    b[0] = p0[i];
                    b[2] = p1[i];
                    b[1] = slope[i];
                    if ((unsigned int)SOLVE_solve_3equations((double (*const)[3])m, b, x))
                        break;
                    double xi1 = x[1];
                    c2[i] = x[0];
                    c0[i] = x[2];
                    c1[i] = xi1;
                    if (++i >= 3)
                    {
                        if (a2 >= 0)
                        {
                            blk[0] = (c2[0] * t1 + c1[0]) * t1 + c0[0];
                            blk[1] = (c2[1] * t1 + c1[1]) * t1 + c0[1];
                            blk[2] = (c2[2] * t1 + c1[2]) * t1 + c0[2];
                        }
                        if (a2 >= 1)
                        {
                            blk[3] = (c2[0] + c2[0]) * t1 + c1[0];
                            blk[4] = (c2[1] + c2[1]) * t1 + c1[1];
                            blk[5] = (c2[2] + c2[2]) * t1 + c1[2];
                        }
                        if (a2 >= 2)
                        {
                            blk[8] = c2[2] + c2[2];
                            blk[7] = c2[1] + c2[1];
                            blk[6] = c2[0] + c2[0];
                        }
                        break;
                    }
                }
            }
            else
            {



                BCDF_CALC_mirror_slope(slope, p0, p1, &blk[3]);
                double dx = p0[0] - p1[0];
                double dy = p0[1] - p1[1];
                double dz = p0[2] - p1[2];
                double nx = blk[5] * dy - blk[4] * dz;
                double ny = blk[3] * dz - blk[5] * dx;
                double nz = blk[4] * dx - blk[3] * dy;
                double len = std::sqrt(nx * nx + ny * ny + nz * nz);
                if (len >= 1.0e-10)
                {
                    double inv = 1.0 / len;
                    double ux = nx * inv;
                    double uy = ny * inv;
                    double uz = nz * inv;
                    blk[6] = blk[4] * uz - blk[5] * uy;
                    blk[7] = blk[5] * ux - blk[3] * uz;
                    blk[8] = blk[3] * uy - blk[4] * ux;
                }
            }
        }
        else
        {

            double q[3];
            BCDF_copy_single_3d_point(a1, n - 3, q);
            double t0 = par[n - 3];
            double t1 = par[n - 2];
            double t2 = par[last];
            blk[0] = t0 * t0;
            blk[1] = t0;
            blk[2] = 1.0;
            blk[3] = t1 * t1;
            blk[4] = t1;
            blk[5] = 1.0;
            blk[6] = t2 * t2;
            blk[7] = t2;
            blk[8] = 1.0;

            double c2[3];
            double c1[3];
            double c0[3];
            double x[3];
            __int64 i = 0;
            while (1)
            {
                double b[3];
                b[0] = q[i];
                b[2] = p1[i];
                b[1] = p0[i];
                if ((unsigned int)SOLVE_solve_3equations((double (*const)[3])blk, b, x))
                    break;
                double xi1 = x[1];
                c2[i] = x[0];
                c0[i] = x[2];
                c1[i] = xi1;
                if (++i >= 3)
                {
                    if (a2 >= 0)
                    {
                        blk[0] = (c2[0] * t2 + c1[0]) * t2 + c0[0];
                        blk[1] = (c2[1] * t2 + c1[1]) * t2 + c0[1];
                        blk[2] = (c2[2] * t2 + c1[2]) * t2 + c0[2];
                    }
                    if (a2 >= 1)
                    {
                        blk[3] = (c2[0] + c2[0]) * t2 + c1[0];
                        blk[4] = (c2[1] + c2[1]) * t2 + c1[1];
                        blk[5] = (c2[2] + c2[2]) * t2 + c1[2];
                    }
                    if (a2 >= 2)
                    {
                        blk[8] = c2[2] + c2[2];
                        blk[7] = c2[1] + c2[1];
                        blk[6] = c2[0] + c2[0];
                    }
                    break;
                }
            }
        }



        __int64 done = 0;
        __int64 n3_64 = n3;
        if (n3_64 >= 4)
        {
            double* dst = a3 + 2;
            unsigned long long iters = ((unsigned long long)(n3_64 - 4) >> 2) + 1;
            done = 4 * (__int64)iters;
            __int64 si = 0;
            do
            {
                dst[-2] = blk[3 + si];
                dst[-1] = blk[4 + si];
                dst[0] = blk[5 + si];
                dst[1] = blk[6 + si];
                dst += 4;
                si += 4;
            } while (--iters);
        }
        if (done < n3_64)
            memcpy(a3 + done, &blk[3] + done, (size_t)((n3_64 - done) * 8));
    }
}
