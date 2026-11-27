














int SOLVE_solve_2equations(double (* const A)[2], double* const b, double* const x)
{
    double det = (*A)[3] * (*A)[0] - (*A)[1] * (*A)[2];
    if (det == 0.0)
        return 1;
    x[0] = ((*A)[3] * *b - (*A)[1] * b[1]) / det;
    x[1] = -((*A)[2] * *b - b[1] * (*A)[0]) / det;
    return 0;
}
