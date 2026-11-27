

















#include <cstring>
#include <intrin.h>

struct PNTLST_s;


struct BCDF_s
{
    PNTLST_s* df_points;
    PNTLST_s* weights;
    PNTLST_s* params;
    PNTLST_s* slopes;
    PNTLST_s* slope_pos;
    PNTLST_s* crvatrs;
    PNTLST_s* crvatr_pars;
    PNTLST_s* crvatr_derivs;
    PNTLST_s* crvatr_deriv_pars;
    int*      slope_types;
    int*      crvatr_types;
    int*      crvatr_deriv_types;
    double    tolerance;
    int       pad_68;
    int       order;
    int       periodicity;
    char      pad_74[0x0C];
    int*      constraint_types;
};




__declspec(dllimport) unsigned __int64 SM_length_sz(const void* p);
__declspec(dllimport) void* SM_calloc_persistent(unsigned __int64 count, unsigned __int64 size);
__declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file, int line, const char* fmt, ...);
__declspec(dllimport) void SM_free(void* p);


void BCDF_free_attributes(BCDF_s* a);

#define BCDF_FILE_ "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c"
#define BCDF_ALLOC_FMT_ "Failed to allocate permanent memory for transient conversion of %lu bytes"



#define COPY_BLOCK(dstfield, srcfield)                                        \
    do {                                                                      \
        const void* src_ = (const void*)(srcfield);                           \
        void* dst_;                                                           \
        if (!src_)                                                            \
        {                                                                     \
            dst_ = 0;                                                         \
        }                                                                     \
        else                                                                  \
        {                                                                     \
            dst_ = SM_calloc_persistent(1, SM_length_sz(src_));               \
            if (!dst_)                                                        \
            {                                                                 \
                ERROR_internal(BCDF_FILE_, 3038, BCDF_ALLOC_FMT_,             \
                               SM_length_sz(src_));                           \
                __debugbreak();                                               \
            }                                                                 \
            memcpy(dst_, src_, SM_length_sz(src_));                           \
        }                                                                     \
        (dstfield) = (decltype(dstfield))dst_;                                \
    } while (0)


#define COPY_INNER(dstfield, srcfield)                                        \
    do {                                                                      \
        if (ret->dstfield)                                                    \
        {                                                                     \
            const void* src_ = *(const void**)(const void*)(a1->srcfield);    \
            void* dst_;                                                       \
            if (!src_)                                                        \
            {                                                                 \
                dst_ = 0;                                                     \
            }                                                                 \
            else                                                              \
            {                                                                 \
                dst_ = SM_calloc_persistent(1, SM_length_sz(src_));           \
                if (!dst_)                                                    \
                {                                                             \
                    ERROR_internal(BCDF_FILE_, 3038, BCDF_ALLOC_FMT_,         \
                                   SM_length_sz(src_));                       \
                    __debugbreak();                                           \
                }                                                             \
                memcpy(dst_, src_, SM_length_sz(src_));                       \
            }                                                                 \
            *(void**)(void*)(ret->dstfield) = dst_;                           \
        }                                                                     \
    } while (0)

BCDF_s* BCDF_make_bcdf_data_persistent(BCDF_s* a1)
{
    if (!a1)
        return 0;

    BCDF_s* ret = (BCDF_s*)SM_calloc_persistent(1, SM_length_sz(a1));
    if (!ret)
    {
        ERROR_internal(BCDF_FILE_, 3038, BCDF_ALLOC_FMT_, SM_length_sz(a1));
        __debugbreak();
    }
    memcpy(ret, a1, SM_length_sz(a1));

    COPY_BLOCK(ret->df_points, a1->df_points);
    COPY_BLOCK(ret->weights, a1->weights);
    COPY_BLOCK(ret->params, a1->params);
    COPY_BLOCK(ret->slopes, a1->slopes);
    COPY_BLOCK(ret->slope_pos, a1->slope_pos);
    COPY_BLOCK(ret->crvatrs, a1->crvatrs);
    COPY_BLOCK(ret->crvatr_derivs, a1->crvatr_derivs);
    COPY_BLOCK(ret->crvatr_pars, a1->crvatr_pars);
    COPY_BLOCK(ret->crvatr_deriv_pars, a1->crvatr_deriv_pars);
    COPY_BLOCK(ret->slope_types, a1->slope_types);
    COPY_BLOCK(ret->crvatr_types, a1->crvatr_types);
    COPY_BLOCK(ret->crvatr_deriv_types, a1->crvatr_deriv_types);
    COPY_BLOCK(ret->constraint_types, a1->constraint_types);

    COPY_INNER(df_points, df_points);
    COPY_INNER(weights, weights);
    COPY_INNER(params, params);
    COPY_INNER(slopes, slopes);
    COPY_INNER(slope_pos, slope_pos);
    COPY_INNER(crvatrs, crvatrs);
    COPY_INNER(crvatr_pars, crvatr_pars);
    COPY_INNER(crvatr_derivs, crvatr_derivs);
    COPY_INNER(crvatr_deriv_pars, crvatr_deriv_pars);

    BCDF_free_attributes(a1);
    SM_free(a1);
    return ret;
}
