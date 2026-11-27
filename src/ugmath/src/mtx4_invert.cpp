













namespace UGS {
namespace Math {

struct TransformMatrix
{
    double m[4][4];
};

}
}


int ludcmp_a(double** a, int n, int* indx, double* d);
void lubksb_a(double** a, int n, int* indx, double* b);

int MTX4_invert(UGS::Math::TransformMatrix const* src,
                UGS::Math::TransformMatrix* dst)
{
    double lu[4][4];
    lu[0][0] = src->m[0][0];
    lu[1][0] = src->m[1][0];
    lu[2][0] = src->m[2][0];
    lu[3][0] = src->m[3][0];
    lu[0][1] = src->m[0][1];
    lu[1][1] = src->m[1][1];
    lu[2][1] = src->m[2][1];
    lu[3][1] = src->m[3][1];
    lu[0][2] = src->m[0][2];
    lu[1][2] = src->m[1][2];
    lu[2][2] = src->m[2][2];
    lu[3][2] = src->m[3][2];
    lu[0][3] = src->m[0][3];
    lu[1][3] = src->m[1][3];
    lu[2][3] = src->m[2][3];
    lu[3][3] = src->m[3][3];

    double* rows[4];
    rows[0] = lu[0];
    rows[1] = lu[1];
    rows[2] = lu[2];
    rows[3] = lu[3];

    int indx[4];
    double d;
    if (!ludcmp_a(rows, 4, indx, &d))
    {
        for (int j = 0; j < 4; ++j)
        {
            double b[4] = { 0.0, 0.0, 0.0, 0.0 };
            b[j] = 1.0;
            lubksb_a(rows, 4, indx, b);
            double* col = &dst->m[0][j];
            col[0] = b[0];
            col[4] = b[1];
            col[8] = b[2];
            col[12] = b[3];
        }
        return 0;
    }
    return 1;
}
