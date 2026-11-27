


#include <stdlib.h>

namespace UGS {
namespace Math {
struct Point2 {
    double x;
    double y;
};
}
}
struct PTF_tri_s {
    int a;
    int b;
    int c;
    int n0;
    int n1;
    int n2;
};
struct PTF_pt_neighbors_s {
    int num;
    int pad;
    int* list;
};
struct PTF_bnd_edge_neighbors_s {
    int a;
    int b;
};

extern "C" __declspec(dllimport) void* SM_alloc(size_t n);
extern "C" __declspec(dllimport) void SM_free(void* p);
extern "C" char sub_1800A89B0(int, const double*, int, int*, PTF_tri_s*, int*);
extern "C" __int64 sub_1800A8ED0(PTF_pt_neighbors_s*, int, int, int);

enum PTF_fill_status_e {
    PTF_FILL_OK = 0,
    PTF_FILL_FAIL = 1,
    PTF_FILL_DEGENERATE = 2,
};

PTF_fill_status_e PTF_poly_tri_fill(int a1, UGS::Math::Point2* a2, int* a3,
                                    PTF_tri_s** a4, PTF_bnd_edge_neighbors_s** a5,
                                    PTF_pt_neighbors_s** a6) {
    PTF_tri_s** v39 = a4;
    int* v38 = a3;
    int v6 = 0;
    const int v7 = a1;
    int v37 = 0;
    if (a3) *a3 = 0;
    if (a4) *a4 = nullptr;
    PTF_pt_neighbors_s** v9 = a6;
    if (a6) *a6 = nullptr;
    PTF_bnd_edge_neighbors_s** v10 = a5;
    if (a5) *a5 = nullptr;
    const int v11 = a1 - 2;
    if (v11 <= 0) return PTF_FILL_DEGENERATE;
    PTF_tri_s* v36 = (PTF_tri_s*)SM_alloc(24LL * v11);
    sub_1800A89B0(v7, (const double*)a2, v11, &v37, v36, nullptr);
    if (v37 != v11) return PTF_FILL_FAIL;
    if (v9) {
        *v9 = (PTF_pt_neighbors_s*)SM_alloc(16LL * v7);
        __int64 v14 = 0;
        int v15 = v7;
        do {

            (*(PTF_pt_neighbors_s*)((char*)*v9 + v14)).num = 0;
            (*(PTF_pt_neighbors_s*)((char*)*v9 + v14)).list =
                (int*)SM_alloc(4LL * v7);
            __int64 v16 = 0;
            do {
                (*(PTF_pt_neighbors_s*)((char*)*v9 + v14)).list[v16++] = -1;
            } while (v16 < v7);
            v14 += 16;
            --v15;
        } while (v15);
        int v17 = 0;
        v37 = 0;
        int v18 = 0;
        do {
            const int v19 = v36[v18].a;
            int v20 = v36[v18].b;
            const int v21 = v36[v18].c;
            const int v35 = v19;
            const int v34 = v20;
            const int v22 = abs(v19 - v20);
            const int v23 = abs(v20 - v21);
            const int v24 = abs(v19 - v21);
            int v21b = v21;
            if (v22 > 1) {
                if (v22 < v7 - 1) {
                    sub_1800A8ED0(*v9, v7, v19, v20);
                    v17 = v37;
                    v20 = v34;
                }
                v21b = v21;
            }
            if (v23 > 1 && v23 < v7 - 1) {
                sub_1800A8ED0(*v9, v7, v20, v21b);
                v17 = v37;
            }
            if (v24 > 1 && v24 < v7 - 1) {
                sub_1800A8ED0(*v9, v7, v35, v21b);
                v17 = v37;
            }
            v37 = ++v17;
            v18 = v17;
        } while (v17 < v11);
        v10 = a5;
        v36 = v36;
    }
    if (v10) {
        *v10 = (PTF_bnd_edge_neighbors_s*)SM_alloc(8LL * v7);
        __int64 v25 = 0;
        do {
            (*v10)[v25].a = -1;
            (*v10)[v25++].b = -1;
        } while (v25 < v7);
        int v26 = 0;
        v37 = 0;
        do {
            const int v27 = v36[v6].a;
            const int v28 = v36[v6].c;
            const int v29 = v36[v6].n1;
            const int v30 = v36[v6].n2;
            if (v36[v6].n0 == -1) {
                const int v31 = v36[v6].b;
                (*v10)[v31].a = v26;
                (*v10)[v31].b = 1;
                v26 = v37;
            }
            if (v29 == -1) {
                (*v10)[v28].a = v26;
                (*v10)[v28].b = 2;
                v26 = v37;
            }
            if (v30 == -1) {
                (*v10)[v27].a = v26;
                (*v10)[v27].b = 3;
                v26 = v37;
            }
            v37 = ++v26;
            v6 = v26;
        } while (v26 < v11);
    }
    if (v38) *v38 = v11;
    if (v39) *v39 = v36;
    else SM_free(v36);
    return PTF_FILL_OK;
}
