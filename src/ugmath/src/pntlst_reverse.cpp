




#include <cstdint>

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

void PNTLST_reverse(PNTLST_s* a1)
{
    if (!a1)
        return;
    double* points = a1->points;
    int num = a1->num;
    int dim = a1->dim;
    for (int i = 0; i < num; ++i)
    {
        int j = num - 1 - i;
        if (j <= i)
            break;
        double* front = points + i * dim;
        double* back = points + j * dim;
        for (int k = 0; k < dim; ++k)
        {
            double t = front[k];
            front[k] = back[k];
            back[k] = t;
        }
    }
}
