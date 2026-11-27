












#include <cstddef>

void NR_matrix_copy_1d_to_2d(double* src, int rows, int cols, double** dst)
{
    if (rows > 0)
    {
        int off = 0;
        size_t n = (unsigned int)rows;
        do
        {
            for (int j = 0; j < cols; ++j)
                (*dst)[j] = src[off + j];
            off += cols;
            ++dst;
        } while (--n != 0);
    }
}
