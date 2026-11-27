









void NR_2d_matrix_product_of_2(double **a1, double **a2, int a3, int a4, int a5, double **a6)
{
    for (int i = 0; i < a3; ++i)
    {
        for (int j = 0; j < a5; ++j)
        {
            double sum = 0.0;
            for (int k = 0; k < a4; ++k)
                sum += a1[i][k] * a2[k][j];
            a6[i][j] = sum;
        }
    }
}
