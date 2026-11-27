







void NR_matrix_copy_2d_to_1d(double **src, int rows, int cols, double *dst)
{
    if (rows <= 0)
        return;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            dst[i * cols + j] = src[i][j];
    }
}
