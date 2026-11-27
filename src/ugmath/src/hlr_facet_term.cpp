













typedef unsigned long long QWORD;




extern "C" QWORD g_ugm_hlr_geom_desc;

extern "C" QWORD g_ugm_hlr_geom_list;

extern "C" QWORD g_ugm_hlr_scratch_ptr;
extern "C" int   g_ugm_hlr_scratch_len;

extern "C" QWORD g_ugm_hlr_bucket_ptr;
extern "C" int   g_ugm_hlr_bucket_count;


__declspec(dllimport) void SM_free(void* p);


struct UgmHlrGeomNode
{
    void*             payload;
    UgmHlrGeomNode*   next;
};


struct UgmHlrElemNode
{
    QWORD             f00;
    QWORD             f08;
    QWORD             f10;
    UgmHlrElemNode*   next;
};


struct UgmHlrFacetElem
{
    QWORD             f00;
    QWORD             f08;
    UgmHlrElemNode*   list;
    QWORD             f18;
};


struct UgmHlrDescNode
{
    UgmHlrFacetElem*  arr;
    QWORD             f08;
    UgmHlrDescNode*   next;
    QWORD             f18;
    QWORD             f20;
    int               count;
    int               f2c;
};

void HLR_FACET_term()
{
    UgmHlrGeomNode* node = reinterpret_cast<UgmHlrGeomNode*>(g_ugm_hlr_geom_list);
    UgmHlrDescNode* desc = reinterpret_cast<UgmHlrDescNode*>(g_ugm_hlr_geom_desc);

    while (node)
    {
        UgmHlrGeomNode* next = node->next;
        SM_free(node->payload);
        SM_free(node);
        node = next;
    }
    g_ugm_hlr_geom_list = 0;

    while (desc)
    {
        int count = desc->count;
        UgmHlrFacetElem* elem = desc->arr;
        UgmHlrDescNode* next = desc->next;
        if (count > 0)
        {
            do
            {
                UgmHlrElemNode* p = elem->list;
                if (p)
                {
                    UgmHlrElemNode* pn;
                    do
                    {
                        pn = p->next;
                        SM_free(p);
                        p = pn;
                    } while (pn);
                }
                ++elem;
            } while (--count > 0);
        }
        SM_free(desc->arr);
        SM_free(desc);
        desc = next;
    }
    g_ugm_hlr_geom_desc = 0;

    SM_free(reinterpret_cast<void*>(g_ugm_hlr_scratch_ptr));
    g_ugm_hlr_scratch_ptr = 0;
    g_ugm_hlr_scratch_len = 0;
    SM_free(reinterpret_cast<void*>(g_ugm_hlr_bucket_ptr));
    g_ugm_hlr_bucket_ptr = 0;
    g_ugm_hlr_bucket_count = 0;
}
