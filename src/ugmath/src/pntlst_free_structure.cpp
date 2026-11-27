











__declspec(dllimport) void SM_free(void *ptr);



struct PNTLST_s
{
    void *points;
    int   num;
    int   alloc;
    int   stride;
};

void PNTLST_free_structure(PNTLST_s *p)
{
    if (p)
    {
        if (p->alloc)
            SM_free(p->points);
        SM_free(p);
    }
}
