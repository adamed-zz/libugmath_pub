





extern "C" __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char*, int,
                                                             const char*, ...);

struct NeighborRec {
    int num;
    int pad;
    int* list;
};

extern "C" __int64 sub_1800A8ED0(NeighborRec* a1, int a2, int a3, int a4) {
    NeighborRec* v8 = a1 + a3;
    NeighborRec* v7 = a1 + a4;
    const int v9 = v8->num;
    int* v10 = (v8->num >= v7->num) ? v7->list : v8->list;
    int v11 = v8->num;
    int v12 = a4;
    if (v9 >= v7->num) {
        v11 = v7->num;
        v12 = a3;
    }
    __int64 result;
    for (result = 0; result < v11; ++result) {
        if (v10[result] == v12) return result;
    }
LABEL_10:
    if (MACH__checking_level > 0) {
        if (v9 >= a2) {
            ERROR_assertion_failed(
                (char*)"o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ptf_poly_tri_fill.c",
                443, (char*)"%s", (char*)"neighbor1_p->num_neighbors < num_pts");
        }
        if (MACH__checking_level > 0 && v7->num >= a2) {
            ERROR_assertion_failed(
                (char*)"o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ptf_poly_tri_fill.c",
                444, (char*)"%s", (char*)"neighbor2_p->num_neighbors < num_pts");
        }
    }
    v8->list[v8->num++] = a4;
    result = (__int64)v7->list;
    v7->list[v7->num++] = a3;
    return result;
}
