















#include <cmath>

namespace UGS {
namespace Math {

struct Point3
{
    double x, y, z;
};

}
}

using UGS::Math::Point3;


__declspec(dllimport) void* SM_alloc(size_t size);
__declspec(dllimport) void SM_free(void* p);


double** NR_2d_matrix_allo(int rows, int cols, double** storage);
void NR_2d_matrix_init_zero(double** m, int rows, int cols);
void NR_matrix_2d_as_1d_identity(double* m, int n);
void NR_matrix_copy_2d_to_1d(double** src, int rows, int cols, double* dst);
void NR_generalized_eigenvalues_symm(double* a, double* b, int n, int maxiter,
                                     double* const eval, double* evec, int* iter,
                                     int* ifail);
void LSFIT_cre_tetrahedron_from_pts(int n, Point3* pts, double tol, int* status,
                                    int* which, Point3* p1, Point3* p2, Point3* p3,
                                    Point3* p4);
void LSFIT_cre_circumsphere_of_tetrahedron(Point3* p1, Point3* p2, Point3* p3,
                                           Point3* p4, Point3* center, double* radius);


double* sub_1800548F0(int n, const Point3* pts, double* center, double radius,
                      double* max_dev, double* mean_dev);

void LSFIT_sphere_to_points_3d(Point3* pts, int n, Point3* center, double* radius,
                               int* flag, double* extra)
{
    double* w0 = 0;
    double* w1 = 0;
    double* w2 = 0;
    double** A = NR_2d_matrix_allo(5, 5, &w0);
    double** B = NR_2d_matrix_allo(5, 5, &w1);
    double** C = NR_2d_matrix_allo(5, 5, &w2);

    int* fl = flag;
    center->x = 0.0;
    center->y = 0.0;
    center->z = 0.0;
    *radius = 1.0e19;
    *fl = 0;
    NR_2d_matrix_init_zero(A, 5, 5);

    Point3* buf = (Point3*)SM_alloc(sizeof(Point3) * n);

    double best;
    double inv;
    double c0;
    double c1;
    double c2;
    double c3;
    double c4;
    int ib;
    Point3 p1;
    Point3 p2;
    Point3 p3;
    Point3 p4;
    int dummy;

    double sx = 0.0;
    double sy = 0.0;
    double sz = 0.0;
    for (int i = 0; i < n; i++)
    {
        sx += pts[i].x;
        sy += pts[i].y;
        sz += pts[i].z;
    }
    double dn = (double)n;
    double mx = sx / dn;
    double my = sy / dn;
    double mz = sz / dn;

    for (int i = 0; i < n; i++)
    {
        buf[i].x = pts[i].x - mx;
        buf[i].y = pts[i].y - my;
        buf[i].z = pts[i].z - mz;
    }

    A[0][0] = dn;
    A[0][1] = 0.0;
    A[0][2] = 0.0;
    A[0][3] = 0.0;
    for (int i = 0; i < n; i++)
    {
        double x = buf[i].x;
        double y = buf[i].y;
        double z = buf[i].z;
        double r2 = x * x + y * y + z * z;
        A[0][4] += r2;
        A[1][1] += x * x;
        A[1][2] += y * x;
        A[1][3] += z * x;
        A[1][4] += r2 * x;
        A[2][2] += y * y;
        A[2][3] += z * y;
        A[2][4] += r2 * y;
        A[3][3] += z * z;
        A[3][4] += r2 * z;
        A[4][4] += r2 * r2;
    }
    A[1][0] = A[0][1];
    A[2][0] = A[0][2];
    A[2][1] = A[1][2];
    A[3][0] = A[0][3];
    A[3][1] = A[1][3];
    A[3][2] = A[2][3];
    A[4][0] = A[0][4];
    A[4][1] = A[1][4];
    A[4][2] = A[2][4];
    A[4][3] = A[3][4];

    double id1[25];
    NR_matrix_2d_as_1d_identity(id1, 5);
    id1[4] = -2.0;
    id1[20] = -2.0;
    id1[0] = 0.0;
    id1[24] = 0.0;
    double* w3 = 0;
    double id2[25];
    NR_matrix_2d_as_1d_identity(id2, 5);
    id2[0] = 0.0;
    id2[24] = 0.0;
    id2[4] = -2.0;
    id2[20] = -2.0;

    double** D = NR_2d_matrix_allo(5, 5, &w3);
    NR_matrix_copy_2d_to_1d(A, 5, 5, w3);

    double eval[5];
    double evec[25];
    int iter;
    int ifail;
    NR_generalized_eigenvalues_symm(id2, w3, 5, 60, eval, evec, &iter, &ifail);
    if (D)
        SM_free(D);
    if (w3)
        SM_free(w3);
    if (ifail == 1)
        goto FALLBACK;

    best = 0.0;
    ib = 0;
    if (eval[0] > 1.0e-19 && eval[0] > best)
        best = eval[0];
    if (eval[1] > 1.0e-19 && eval[1] > best)
    {
        best = eval[1];
        ib = 1;
    }
    if (eval[2] > 1.0e-19 && eval[2] > best)
    {
        best = eval[2];
        ib = 2;
    }
    if (eval[3] > 1.0e-19 && eval[3] > best)
    {
        best = eval[3];
        ib = 3;
    }
    if (eval[4] > 1.0e-19 && eval[4] > best)
    {
        best = eval[4];
        ib = 4;
    }
    if (1.0e-10 > best)
        goto FALLBACK;

    inv = 1.0 / best;
    c0 = evec[ib];
    c1 = evec[ib + 5];
    c2 = evec[ib + 10];
    c3 = evec[ib + 15];
    c4 = evec[ib + 20];
    if (*fl == 0)
    {
        if (fabs(c4 - 0.0) > 1.0e-19)
        {
            center->y = -0.5 * (c2 / c4);
            center->x = -0.5 * (c1 / c4);
            center->z = -0.5 * (c3 / c4);
            *radius = sqrt(fabs(center->y * center->y + center->x * center->x +
                                center->z * center->z - c0 / c4));
            center->x += mx;
            center->y += my;
            center->z += mz;
            sub_1800548F0(n, pts, (double*)center, *radius, extra, extra + 2);
            extra[1] = sqrt(dn * inv);
        }
        else
        {
            *fl = 1;
        }
    }
    SM_free(A);
    SM_free(B);
    SM_free(C);
    if (w0)
        SM_free(w0);
    if (w1)
        SM_free(w1);
    if (w2)
        SM_free(w2);
    if (buf)
        SM_free(buf);
    return;

FALLBACK:
    p1 = Point3{0.0, 0.0, 0.0};
    p2 = Point3{0.0, 0.0, 0.0};
    p3 = Point3{0.0, 0.0, 0.0};
    p4 = Point3{0.0, 0.0, 0.0};
    dummy = 0;
    LSFIT_cre_tetrahedron_from_pts(n, pts, 0.001, fl, &dummy, &p1, &p2, &p3, &p4);
    if (*fl == 1)
        *radius = 1.0e19;
    else
        LSFIT_cre_circumsphere_of_tetrahedron(&p1, &p2, &p3, &p4, center, radius);
}
