





#include "b37_math.h"

void mdispose_banded(double*** a1, double** a2) {
    double** rows = *a1;
    if (rows) {
        SM_free(*(void**)(rows - 1));
        SM_free((void*)(rows - 1));
        *a1 = 0;
    }
    if (*a2) {
        SM_free(*a2);
        *a2 = 0;
    }
}
