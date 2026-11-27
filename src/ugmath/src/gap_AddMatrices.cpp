











namespace UGS {
namespace Math {

void AddMatrices(bool add, const double* const a, const double* const b, int rows,
                 int cols, double* const out)

{
    const int n = rows * cols;
    double s = 1.0;
    if (!add) s = -1.0;
    for (int i = 0; i < n; ++i) out[i] = a[i] + s * b[i];
}

}
}
