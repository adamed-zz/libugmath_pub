








namespace UGS {
namespace Math {



void ScaleMatrix(const double* const src, double scale, int rows, int cols,
                 double* const out)
{
    const int n = rows * cols;
    for (int i = 0; i < n; ++i) out[i] = scale * src[i];
}

}
}
