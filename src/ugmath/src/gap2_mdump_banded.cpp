







#include "b37_math.h"

#include <cstdio>

namespace {
FILE* B37Stdout() {
    return stdout;
}
}

void mdump_banded(double** a1, double* a2, int a3, int a4) {
    if (a3 <= 0)
        return;

    for (int r = 0; r < a3; ++r) {
        if (a1) {
            for (int j = 0; j < a3; ++j) {
                if (j < r - a4 || j > r + a4)
                    SYSS_fprintf(B37Stdout(), "     0      ");
                else
                    SYSS_fprintf(B37Stdout(), "%10.5f  ", a1[r][j]);
            }
        }
        if (a2)
            SYSS_fprintf(B37Stdout(), "%10.5f\n", a2[r]);
        else
            SYSS_fprintf(B37Stdout(), "\n");
    }
}
