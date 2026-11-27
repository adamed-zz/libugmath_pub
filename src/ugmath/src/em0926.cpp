









#include <cstring>

void em0914(int* a1, double* a2, double* a3, double* a4);
void wf256(const int* a1, const double* a2);
void wf266(const int* a1, double* a2);



#define B6_COPY_BLOCK(BUF, BLOCK, N)                                  \
    do {                                                              \
        unsigned long long off_ = 32ULL * (BLOCK);                    \
        const char* src_ = (const char*)(BUF) - off_;                 \
        double* dp_ = a4 + off_ / 8 + 2;                              \
        long long o1_ = src_ - (const char*)a4;                 \
        long long o2_ = (src_ + 8) - (const char*)a4;                       \
        __int64 cnt_ = (unsigned int)(N);                             \
        do {                                                          \
            *(dp_ - 2) = *(const double*)((const char*)dp_ + o1_ - 16); \
            *(dp_ - 1) = *(const double*)((const char*)dp_ + o2_ - 16); \
            *dp_ = *(const double*)((const char*)dp_ + o1_);          \
            dp_[1] = *(const double*)((const char*)dp_ + o2_);        \
            dp_ += 4;                                                 \
            --cnt_;                                                   \
        } while (cnt_);                                               \
    } while (0)

void em0926(int* a1, double* a2, int* a3, double* a4) {
    double v48[100];
    double v50[104];
    int v52;
    int v7 = -*a1;
    v52 = *a1 - 1;
    em0914(&v52, a2, v48, v50);

    int v8 = *a1;
    if (*a3 == 1) {
        int v9 = v8 + v7;
        if (v8 >= 1) {
            B6_COPY_BLOCK(v48, v9, v8);
        }
        if (*a1 >= 1) {
            B6_COPY_BLOCK(v50, v8 + v9, *a1);
        }
    } else {
        int v22, v23, v24, v35, v36, v37;
        v52 = 4 * v8;
        v22 = 1;
        wf256(&v52, v50);
        while (1) {
            v52 = *a1 - 1;
            em0914(&v52, v48, v48, v50);
            v23 = *a1;
            if (*a3 == 2) {
                v24 = v23 + v7;
                if (v23 >= 1) {
                    B6_COPY_BLOCK(v48, v24, v23);
                    v23 = *a1;
                }
                v7 = v23 + v24;
                if (v23 >= 1) {
                    B6_COPY_BLOCK(v50, v7, v23);
                }
            } else {
                ++v22;
                v52 = 4 * v23;
                wf256(&v52, v50);
                v35 = 1;
                while (1) {
                    v52 = *a1 - 1;
                    em0914(&v52, v48, v48, v50);
                    v36 = *a1;
                    v37 = *a1 + v7;
                    if (*a1 >= 1) {
                        B6_COPY_BLOCK(v48, v37, v36);
                        v36 = *a1;
                    }
                    v7 = v36 + v37;
                    if (v36 >= 1) {
                        B6_COPY_BLOCK(v50, v7, v36);
                    }
                    if (!v35)
                        break;
                    v35 = 0;
                    v52 = 4 * *a1;
                    --v22;
                    wf266(&v52, v48);
                }
            }
            if (v22 <= 0)
                break;
            --v22;
            v52 = 4 * *a1;
            wf266(&v52, v48);
        }
    }
}
