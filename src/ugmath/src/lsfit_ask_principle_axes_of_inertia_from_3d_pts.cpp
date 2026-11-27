














#include <cmath>
#include <exception>

namespace UGS {
namespace Math {

struct Point3
{
    double x, y, z;
};

struct Vector3
{
    double x, y, z;
};

}

namespace Error {




class Exception : public std::exception
{
public:
    virtual void doDefaultStartAction(const char* file, int line, int recover_type) const;

    [[noreturn]] void Rethrow() const;

protected:
    unsigned char m_reserved[0x78];
};

class Severe : public Exception
{
public:
    Severe();
    const Exception& Convert(const std::exception& ex);
};

}
}


__declspec(dllimport) void SM_free(void* p);

__declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file, int line,
                                                               const char* msg, ...);


double** NR_2d_matrix_allo(int rows, int cols, double** storage);
void NR_matrix_copy_1d_to_2d(double* src, int rows, int cols, double** dst);
void NR_ask_eigenvalues_jacobi(double** a, int n, int max_iter, double* const d,
                               double** v, int* status);



static inline void MC_v_copy(const double* src, double* dst)
{
    *dst = *src;
    dst[1] = src[1];
    dst[2] = src[2];
}

void LSFIT_ask_principle_axes_of_inertia_from_3d_pts(int a1, UGS::Math::Point3* a2,
                                                     UGS::Math::Point3* a3, double* const a4,
                                                     UGS::Math::Vector3* const a5)
{
    double* cov = 0;
    double* evec = 0;
    double** m = NR_2d_matrix_allo(3, 3, &cov);
    double** v = NR_2d_matrix_allo(3, 3, &evec);

    *a4 = 0.0;
    a5[0].x = a5[0].y = a5[0].z = 0.0;
    a4[1] = 0.0;
    a5[1].x = a5[1].y = a5[1].z = 0.0;
    a4[2] = 0.0;
    a5[2].x = a5[2].y = a5[2].z = 0.0;
    double inv[3] = {0.0, 0.0, 0.0};

    try
    {
        double sx = 0.0, sy = 0.0, sz = 0.0;
        if (a1 > 0)
        {
            const UGS::Math::Point3* p = a2;
            for (__int64 k = a1; k != 0; --k)
            {
                sx += p->x;
                sy += p->y;
                sz += p->z;
                ++p;
            }
        }
        double np = (double)a1;
        a3->x = sx / np;
        a3->y = sy / np;
        a3->z = sz / np;

        for (int j = 0; j < 9; j++)
        {
            cov[j] = 0.0;
            evec[j] = 0.0;
        }

        for (__int64 i = 0; i < a1; i++)
        {
            UGS::Math::Point3 p = a2[i];
            cov[0] += (p.x - a3->x) * (p.x - a3->x);
            cov[3] += (p.y - a3->y) * (p.x - a3->x);
            cov[6] += (p.z - a3->z) * (p.x - a3->x);
            cov[4] += (p.y - a3->y) * (p.y - a3->y);
            cov[7] += (p.z - a3->z) * (p.y - a3->y);
            cov[8] += (p.z - a3->z) * (p.z - a3->z);
        }

        cov[0] /= np;
        cov[3] /= np;
        cov[6] /= np;
        cov[1] = cov[3];
        cov[4] /= np;
        cov[7] /= np;
        cov[2] = cov[6];
        cov[5] = cov[7];
        cov[8] /= np;

        NR_matrix_copy_1d_to_2d(cov, 3, 3, m);

        double eig[3];
        int status;
        NR_ask_eigenvalues_jacobi(m, 3, 60, eig, v, &status);

        for (__int64 i = 0; i < 3; i++)
        {
            if (!(eig[i] >= 1.0e-10))
                ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 4845,
                               "The inertia matrix is not positive definite as expected.");
            inv[i] = 1.0 / sqrt(eig[i]);
        }

        if (inv[2] > inv[1] && inv[2] > inv[0])
        {
            *a4 = inv[2];
            MC_v_copy(v[2], (double*)&a5[0]);
            if (inv[1] > inv[0])
            {
                a4[1] = inv[1];
                a4[2] = inv[0];
                MC_v_copy(v[1], (double*)&a5[1]);
                MC_v_copy(v[0], (double*)&a5[2]);
            }
            else
            {
                a4[1] = inv[0];
                a4[2] = inv[1];
                MC_v_copy(v[0], (double*)&a5[1]);
                MC_v_copy(v[1], (double*)&a5[2]);
            }
        }
        else if (inv[1] > inv[0])
        {
            *a4 = inv[1];
            MC_v_copy(v[1], (double*)&a5[0]);
            if (inv[2] > inv[0])
            {
                a4[1] = inv[2];
                a4[2] = inv[0];
                MC_v_copy(v[2], (double*)&a5[1]);
                MC_v_copy(v[0], (double*)&a5[2]);
            }
            else
            {
                a4[1] = inv[0];
                a4[2] = inv[2];
                MC_v_copy(v[0], (double*)&a5[1]);
                MC_v_copy(v[2], (double*)&a5[2]);
            }
        }
        else
        {
            *a4 = inv[0];
            MC_v_copy(v[0], (double*)&a5[0]);
            if (inv[2] > inv[1])
            {
                a4[1] = inv[2];
                a4[2] = inv[1];
                MC_v_copy(v[2], (double*)&a5[1]);
                MC_v_copy(v[1], (double*)&a5[2]);
            }
            else
            {
                a4[1] = inv[1];
                a4[2] = inv[2];
                MC_v_copy(v[1], (double*)&a5[1]);
                MC_v_copy(v[2], (double*)&a5[2]);
            }
        }
    }
    catch (std::exception& e)
    {
        UGS::Error::Severe sev;
        UGS::Error::Exception* ue = dynamic_cast<UGS::Error::Exception*>(&e);
        if (!ue)
            ue = const_cast<UGS::Error::Exception*>(&sev.Convert(e));
        ue->doDefaultStartAction("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 4917, 0);
        if (cov)
        {
            SM_free(cov);
            cov = 0;
        }
        if (evec)
        {
            SM_free(evec);
            evec = 0;
        }
        if (m)
            SM_free(m);
        if (v)
            SM_free(v);
        ue->Rethrow();
    }

    if (cov)
    {
        SM_free(cov);
        cov = 0;
    }
    if (evec)
    {
        SM_free(evec);
        evec = 0;
    }
    if (m)
        SM_free(m);
    SM_free(v);
}
