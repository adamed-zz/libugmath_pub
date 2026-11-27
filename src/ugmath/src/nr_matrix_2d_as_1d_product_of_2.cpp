









void NR_matrix_2d_as_1d_product_of_2(double* a1, double* a2, int a3, int a4, int a5, double* a6)
{
    for (int i = 0; i < a3; ++i)
    {
        for (int j = 0; j < a5; ++j)
        {
            double sum = 0.0;
            for (int k = 0; k < a4; ++k)
                sum += a1[i * a4 + k] * a2[k * a5 + j];
            a6[i * a5 + j] = sum;
        }
    }
}
