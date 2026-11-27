












#include "b37_math.h"

void msetup_banded(int a1, int a2, double*** a3, double** a4) {
    const int n = a1;
    const int m = a2;

    if (n < 1 || m < 0) {
        merrorpush((char* const) "", 280, 4);
    } else {
        *a3 = 0;
        int total = 0;
        int lo = -m;
        for (int r = 0; r < n; ++r) {
            int hi = (n - 1 >= 2 * m + lo) ? 2 * m + lo : n - 1;
            int low = (lo >= 0) ? lo : 0;
            ++lo;
            total += hi - low + 1;
        }
        if (total > 0) {
            char* buf = (char*)SM_calloc((unsigned __int64)total, 8u);
            unsigned long long* hdr =
                (unsigned long long*)SM_calloc((unsigned __int64)(n + 1), 8u);
            int cum = 0;
            hdr[0] = (unsigned long long)(unsigned long long)(void*)buf;
            *a3 = (double**)(hdr + 1);
            int low = -m;
            for (int r = 0; r < n; ++r) {
                int l = (low >= 0) ? low : 0;
                int hi = (n - 1 >= low + 2 * m) ? low + 2 * m : n - 1;
                (*a3)[r] = (double*)&buf[8 * (cum - (long long)l)];
                ++low;
                cum += hi - l + 1;
            }
            if (*a3) {
                *a4 = (double*)SM_alloc(8u * (unsigned __int64)n);
                goto cleanup;
            }
        }
        merrorpush((char* const) "", 950, 4);
    }

cleanup:
    if (merrorlevel()) {
        double** rows = *a3;
        if (rows) {
            SM_free(*(void**)(rows - 1));
            SM_free((void*)(rows - 1));
            *a3 = 0;
        }
        if (*a4) {
            SM_free(*a4);
            *a4 = 0;
        }
    }
}
