


struct PTF_tri_s;
struct PTF_pt_neighbors_s {
    int num_neighbors;
    int pad;
    void* list;
};
struct PTF_bnd_edge_neighbors_s;

extern "C" __declspec(dllimport) void SM_free(void* p);

void PTF_free_output(int a1, PTF_tri_s* a2, PTF_pt_neighbors_s* a3,
                     PTF_bnd_edge_neighbors_s* a4) {
    if (a3) {
        __int64 v7 = a1;
        if (a1 > 0) {
            PTF_pt_neighbors_s* v8 = a3;
            do {
                SM_free(v8->list);
                v8->list = nullptr;
                v8->num_neighbors = 0;
                ++v8;
                --v7;
            } while (v7);
        }
    }
    SM_free(a3);
    SM_free(a2);
    SM_free(a4);
}
