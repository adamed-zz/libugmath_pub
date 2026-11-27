









extern "C" __declspec(dllimport) int MACH__checking_level;
extern "C" __declspec(dllimport) void ERROR_assertion_failed(char*, int, char*, ...);

struct NeighborRec {
    int num;
    int pad;
    int* list;
};

extern "C" __int64 sub_1800A8ED0(NeighborRec* a1, int a2, int a3, int a4) {
    NeighborRec* neighbor1_p = a1 + a3;
    NeighborRec* neighbor2_p = a1 + a4;
    const int num1 = neighbor1_p->num;
    const int num2 = neighbor2_p->num;
    int* list;
    int cnt;
    int tgt;
    __int64 result;
    if (num1 < num2) {
        list = neighbor1_p->list;
    } else {
        list = neighbor2_p->list;
    }
    cnt = (num1 >= num2) ? num2 : num1;
    tgt = (num1 >= num2) ? a3 : a4;
    result = 0;
    while (result < cnt) {
        if (list[result] == tgt) return result;
        ++result;
    }
LABEL_10:
    if (MACH__checking_level > 0) {
        if (num1 >= a2) {
            ERROR_assertion_failed(
                (char*)"o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ptf_poly_tri_fill.c",
                443, (char*)"%s", (char*)"neighbor1_p->num_neighbors < num_pts");
        }
        if (MACH__checking_level > 0 && neighbor2_p->num >= a2) {
            ERROR_assertion_failed(
                (char*)"o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ptf_poly_tri_fill.c",
                444, (char*)"%s", (char*)"neighbor2_p->num_neighbors < num_pts");
        }
    }
    neighbor1_p->list[neighbor1_p->num++] = a4;
    result = (__int64)neighbor2_p->list;
    neighbor2_p->list[neighbor2_p->num++] = a3;
    return result;
}
