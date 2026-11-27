









#include <cstring>
#include <xmmintrin.h>

void em0911(int* a1, double* a2, double* a3, double* a4, double* a5) {
    int v5 = *a1;
    double v7 = *a3;
    int v8 = *a1 + 1;
    int v36 = *a1;
    double v9 = 1.0 - *a3;
    double v35[2500];
    memcpy(v35, a2, 32LL * v8);
    int v10 = 1;
    __int64 v11 = v8;
    unsigned int v20;
    __int64 v21;
    __int64 v24;
    if (v8 <= 1) {
        if (v8 <= 0)
            return;
    } else {
        int v12 = 0;
        __int64 v13 = 104;
        __int64 v14 = v8 - 1;
        __int64 v37 = v14;
        int v15 = v5;
        do {
            __int64 v16 = v13;
            int v17 = v10;
            if (v10 < v8) {
                __int64 v18 = v12;
                __int64 v19 = v12 + 4;
                if (v15 < 4)
                    goto LABEL_8;
                v20 = ((unsigned int)(v8 - v10 - 4) >> 2) + 1;
                v21 = v20;
                v17 = v10 + 4 * v20;
                do {
                    v35[v16]      = v7 * v35[v19]      + v9 * v35[v18];
                    v35[v16 + 1]  = v7 * v35[v19 + 1]  + v9 * v35[v18 + 1];
                    v35[v16 + 2]  = v7 * v35[v19 + 2]  + v9 * v35[v18 + 2];
                    v35[v16 + 3]  = v7 * v35[v19 + 3]  + v9 * v35[v18 + 3];
                    v35[v16 + 4]  = v7 * v35[v19 + 4]  + v9 * v35[v18 + 4];
                    v35[v16 + 5]  = v7 * v35[v19 + 5]  + v9 * v35[v18 + 5];
                    v35[v16 + 6]  = v7 * v35[v19 + 6]  + v9 * v35[v18 + 6];
                    v35[v16 + 7]  = v7 * v35[v19 + 7]  + v9 * v35[v18 + 7];
                    v35[v16 + 8]  = v7 * v35[v19 + 8]  + v9 * v35[v18 + 8];
                    v35[v16 + 9]  = v7 * v35[v19 + 9]  + v9 * v35[v18 + 9];
                    v35[v16 + 10] = v7 * v35[v19 + 10] + v9 * v35[v18 + 10];
                    v35[v16 + 11] = v7 * v35[v19 + 11] + v9 * v35[v18 + 11];
                    v35[v16 + 12] = v7 * v35[v19 + 12] + v9 * v35[v18 + 12];
                    v19 += 16;
                    v18 += 16;
                    v35[v16 + 13] = v7 * v35[v19 - 3] + v9 * v35[v18 - 3];
                    v35[v16 + 14] = v7 * v35[v19 - 2] + v9 * v35[v18 - 2];
                    v35[v16 + 15] = v7 * v35[v19 - 1] + v9 * v35[v18 - 1];
                    v16 += 16;
                    --v21;
                } while (v21);
                v14 = v37;
                if (v17 < v8) {
LABEL_8:
                    v24 = v8 - v17;
                    do {
                        v35[v16] = v7 * v35[v19] + v9 * v35[v18];
                        v35[v16 + 1] = v7 * v35[v19 + 1] + v9 * v35[v18 + 1];
                        v35[v16 + 2] = v7 * v35[v19 + 2] + v9 * v35[v18 + 2];
                        double v25 = v7 * v35[v19 + 3];
                        v19 += 4;
                        double v26 = v9 * v35[v18 + 3];
                        v18 += 4;
                        v35[v16 + 3] = v25 + v26;
                        v16 += 4;
                        --v24;
                    } while (v24);
                }
            }
            ++v10;
            v12 += 104;
            --v15;
            v13 += 104;
            v37 = --v14;
        } while (v14);
        v5 = v36;
    }

    double* v27 = a5;
    const char* v28 = (const char*)v35;
    __int64* v29 = (__int64*)v35 + 104 * v5;
    __int64 v30 = (char*)a4 - (char*)a5;
    do {
        v27 += 4;
        __m128 v31 = _mm_loadu_ps((const float*)v28);
        v29 -= 100;
        __m128 v32 = _mm_loadu_ps((const float*)(v28 + 16));
        v28 += 832;
        _mm_storeu_ps((float*)((char*)v27 + v30 - 32), v31);
        __m128 v33 = _mm_loadu_ps((const float*)(v29 + 100));
        _mm_storeu_ps((float*)((char*)v27 + v30 - 16), v32);
        __m128 v34 = _mm_loadu_ps((const float*)(v29 + 102));
        _mm_storeu_ps((float*)(v27 - 4), v33);
        _mm_storeu_ps((float*)(v27 - 2), v34);
        --v11;
    } while (v11);
}
