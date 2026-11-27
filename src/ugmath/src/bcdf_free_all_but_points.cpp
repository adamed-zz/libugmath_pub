
















#include <cstddef>

struct PNTLST_s;


void PNTLST_free_all_but_points(PNTLST_s *a1);
void PNTLST_free_structure(PNTLST_s *a1);


__declspec(dllimport) void SM_free(void *p);


struct BCDF_s
{
    PNTLST_s *points;
    PNTLST_s *weights;
    PNTLST_s *params;
    PNTLST_s *slopes;
    PNTLST_s *slope_pars;
    PNTLST_s *crvatrs;
    PNTLST_s *crvatr_pars;
    PNTLST_s *crvatr_derivs;
    PNTLST_s *crvatr_deriv_pars;
    int *slope_type_array;
    int *crvatr_type_array;
    int *crvatr_deriv_type_array;
    double ls_tolerance;
    int field68;
    int dimension;
    int periodicity;
    int field74;
    void *field78;
    void *unknown80;
    unsigned char field88;
    int field8C;
};

static_assert(offsetof(BCDF_s, points) == 0x00);
static_assert(offsetof(BCDF_s, weights) == 0x08);
static_assert(offsetof(BCDF_s, params) == 0x10);
static_assert(offsetof(BCDF_s, slopes) == 0x18);
static_assert(offsetof(BCDF_s, slope_pars) == 0x20);
static_assert(offsetof(BCDF_s, crvatrs) == 0x28);
static_assert(offsetof(BCDF_s, crvatr_pars) == 0x30);
static_assert(offsetof(BCDF_s, crvatr_derivs) == 0x38);
static_assert(offsetof(BCDF_s, crvatr_deriv_pars) == 0x40);
static_assert(offsetof(BCDF_s, slope_type_array) == 0x48);
static_assert(offsetof(BCDF_s, crvatr_type_array) == 0x50);
static_assert(offsetof(BCDF_s, crvatr_deriv_type_array) == 0x58);
static_assert(offsetof(BCDF_s, ls_tolerance) == 0x60);
static_assert(offsetof(BCDF_s, field68) == 0x68);
static_assert(offsetof(BCDF_s, dimension) == 0x6C);
static_assert(offsetof(BCDF_s, periodicity) == 0x70);
static_assert(offsetof(BCDF_s, field78) == 0x78);
static_assert(offsetof(BCDF_s, unknown80) == 0x80);
static_assert(offsetof(BCDF_s, field88) == 0x88);
static_assert(offsetof(BCDF_s, field8C) == 0x8C);

void BCDF_free_all_but_points(BCDF_s *a1)
{
    if (a1)
    {
        PNTLST_free_all_but_points(a1->points);
        PNTLST_free_structure(a1->weights);
        PNTLST_free_structure(a1->params);
        PNTLST_free_structure(a1->slopes);
        PNTLST_free_structure(a1->slope_pars);
        PNTLST_free_structure(a1->crvatrs);
        PNTLST_free_structure(a1->crvatr_pars);
        PNTLST_free_structure(a1->crvatr_derivs);
        PNTLST_free_structure(a1->crvatr_deriv_pars);
        if (a1->slope_type_array)
            SM_free(a1->slope_type_array);
        if (a1->crvatr_type_array)
            SM_free(a1->crvatr_type_array);
        if (a1->crvatr_deriv_type_array)
            SM_free(a1->crvatr_deriv_type_array);
        if (a1->unknown80)
            SM_free(a1->unknown80);
        SM_free(a1);
    }
}
