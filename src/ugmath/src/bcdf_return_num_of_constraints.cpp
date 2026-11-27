













struct BCDF_s;


struct BCDF_list
{
    double* points;
    int     num;
    int     alloc;
};

struct BCDF_s
{
    BCDF_list* list0;
    void*      f08;
    void*      f10;
    BCDF_list* list18;
    void*      f20;
    BCDF_list* list28;
    void*      f30;
    BCDF_list* list38;
    char       pad_40[0x30];
    int        periodicity;
};

int BCDF_return_num_of_constraints(struct BCDF_s* a1)
{
    int v4 = 0;
    if (a1->list0)
        v4 = a1->list0->num;
    int v6 = 0;
    if (a1->list18)
        v6 = a1->list18->num;
    int v8 = 0;
    if (a1->list28)
        v8 = a1->list28->num;
    int v1 = 0;
    if (a1->list38)
        v1 = a1->list38->num;
    int v10 = v4 + v6 + v8 + v1;
    return a1->periodicity == 1 ? v10 - 1 : v10;
}
