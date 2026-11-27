











typedef unsigned long long u64;

struct Vec3 { double x, y, z; };


extern "C" double g_ugm_hlr_eye[3];
extern "C" double g_ugm_hlr_col[4][3];
extern "C" double g_ugm_hlr_mat[4][3];
extern "C" double g_ugm_hlr_axis[3][3];
extern "C" double g_ugm_hlr_E06A8;
extern "C" double g_ugm_hlr_E06B0;
extern "C" int    g_ugm_hlr_vloc_norm;


extern "C" void g_ugm_hlr_normalize(double *v);

void HLR_FACET_view(const double *const a1, const double *const a2,
                    double a3, double a4, int a5)
{

    *(Vec3 *)g_ugm_hlr_eye = *(const Vec3 *)a1;


    double ux = a2[0];
    double uy = a2[1];
    double uz = a2[2];
    double wx = a2[3];
    double wy = a2[4];
    double wz = a2[5];

    double *m = &g_ugm_hlr_axis[0][0];
    m[0] = ux;
    m[1] = uy;
    m[2] = uz;
    m[3] = wx;
    m[4] = wy;


    double bx = m[1] * wz - m[4] * m[2];
    double by = m[3] * m[2] - m[0] * wz;
    double bz = m[0] * m[4] - m[3] * m[1];
    m[6] = bx;
    m[7] = by;
    m[8] = bz;


    double vy = m[0] * m[8] - m[2] * m[6];
    double vx = m[7] * m[2] - m[8] * m[1];
    double vz = m[6] * m[1] - m[0] * m[7];
    m[4] = vy;
    m[3] = vx;
    m[5] = vz;


    double *row0 = &m[0];
    double *row1 = &m[3];
    double *row2 = &m[6];
    g_ugm_hlr_normalize(row0);
    g_ugm_hlr_normalize(row1);
    g_ugm_hlr_normalize(row2);


    g_ugm_hlr_vloc_norm = a5;
    g_ugm_hlr_E06A8 = a3;
    g_ugm_hlr_E06B0 = a4;


    double *d = &g_ugm_hlr_col[0][1];
    const double *s = row1;
    do
    {
        d[-1] = s[-3];
        d[0]  = s[0];
        d[1]  = s[3];
        ++s;
        d += 3;
    } while (d < &g_ugm_hlr_col[3][1]);


    double nx = -a1[0];
    double ny = -a1[1];
    double nz = -a1[2];
    g_ugm_hlr_col[3][0] = ny * m[1] + nx * m[0] + nz * m[2];
    g_ugm_hlr_col[3][1] = ny * m[4] + nx * m[3] + nz * m[5];
    g_ugm_hlr_col[3][2] = ny * m[7] + nx * m[6] + nz * m[8];
    if (a5)
        g_ugm_hlr_col[3][2] -= a4;


    double *out = &g_ugm_hlr_mat[0][0];
    const double *in = &g_ugm_hlr_col[0][0];
    for (int i = 0; i < 12; i += 3)
    {
        out[i]     = in[i];
        out[i + 1] = in[i + 1];
        out[i + 2] = in[i + 2];
    }
}
