











struct PNTLST_s;



extern void PNTLST_free_structure(PNTLST_s *p);



__declspec(dllimport) void SM_free(void *p);


struct BCDF_s
{
    PNTLST_s *p0;
    PNTLST_s *p1;
    PNTLST_s *p2;
    PNTLST_s *p3;
    PNTLST_s *p4;
    PNTLST_s *p5;
    PNTLST_s *p6;
    PNTLST_s *p7;
    PNTLST_s *p8;
    void     *q0;
    void     *q1;
    void     *q2;
    char      pad[0x20];
    void     *r;
};

void BCDF_free_attributes(BCDF_s *a)
{
    if (!a)
        return;

    PNTLST_free_structure(a->p0);
    PNTLST_free_structure(a->p1);
    PNTLST_free_structure(a->p2);
    PNTLST_free_structure(a->p3);
    PNTLST_free_structure(a->p4);
    PNTLST_free_structure(a->p5);
    PNTLST_free_structure(a->p6);
    PNTLST_free_structure(a->p7);
    PNTLST_free_structure(a->p8);

    if (a->q0)
        SM_free(a->q0);
    if (a->q1)
        SM_free(a->q1);
    if (a->q2)
        SM_free(a->q2);
    if (a->r)
        SM_free(a->r);

    a->p0 = 0;
    a->p1 = 0;
    a->p2 = 0;
    a->p3 = 0;
    a->p4 = 0;
    a->p5 = 0;
    a->p6 = 0;
    a->p7 = 0;
    a->p8 = 0;
    a->q0 = 0;
    a->q1 = 0;
    a->q2 = 0;
    a->r = 0;
}
