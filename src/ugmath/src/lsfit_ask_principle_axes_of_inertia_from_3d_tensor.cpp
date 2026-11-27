














#include <exception>

namespace UGS {
namespace Math {
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


double** NR_2d_matrix_allo(int rows, int cols, double** storage);
void NR_matrix_copy_1d_to_2d(double* src, int rows, int cols, double** dst);
void NR_ask_eigenvalues_jacobi(double** a, int n, int max_iter, double* const d,
                               double** v, int* status);



inline void MC_v_copy(const double* src, double* dst)
{
    *dst = *src;
    dst[1] = src[1];
    dst[2] = src[2];
}

void LSFIT_ask_principle_axes_of_inertia_from_3d_tensor(double* a1, double* const a2,
                                                        UGS::Math::Vector3* const a3)
{
    double* v19 = 0;
    double** v5 = NR_2d_matrix_allo(3, 3, &a1);
    double** v6 = NR_2d_matrix_allo(3, 3, &v19);
    try
    {
        NR_matrix_copy_1d_to_2d(a1, 3, 3, v5);
        double eig[3];
        int status;
        NR_ask_eigenvalues_jacobi(v5, 3, 60, eig, v6, &status);
        a2[1] = eig[1];
        a2[2] = eig[2];
        if (eig[2] > eig[1] && eig[2] > eig[0])
        {
            *a2 = eig[2];
            MC_v_copy(v6[2], (double*)&a3[0]);
            if (eig[1] > eig[0])
            {
                a2[1] = eig[1];
                a2[2] = eig[0];
                MC_v_copy(v6[1], (double*)&a3[1]);
                MC_v_copy(v6[0], (double*)&a3[2]);
            }
            else
            {
                a2[1] = eig[0];
                a2[2] = eig[1];
                MC_v_copy(v6[0], (double*)&a3[1]);
                MC_v_copy(v6[1], (double*)&a3[2]);
            }
        }
        else if (eig[1] > eig[0])
        {
            *a2 = eig[1];
            MC_v_copy(v6[1], (double*)&a3[0]);
            if (eig[2] > eig[0])
            {
                a2[1] = eig[2];
                a2[2] = eig[0];
                MC_v_copy(v6[2], (double*)&a3[1]);
                MC_v_copy(v6[0], (double*)&a3[2]);
            }
            else
            {
                a2[1] = eig[0];
                a2[2] = eig[2];
                MC_v_copy(v6[0], (double*)&a3[1]);
                MC_v_copy(v6[2], (double*)&a3[2]);
            }
        }
        else
        {
            *a2 = eig[0];
            MC_v_copy(v6[0], (double*)&a3[0]);
            if (eig[2] > eig[1])
            {
                a2[1] = eig[2];
                a2[2] = eig[1];
                MC_v_copy(v6[2], (double*)&a3[1]);
                MC_v_copy(v6[1], (double*)&a3[2]);
            }
            else
            {
                a2[1] = eig[1];
                a2[2] = eig[2];
                MC_v_copy(v6[1], (double*)&a3[1]);
                MC_v_copy(v6[2], (double*)&a3[2]);
            }
        }
    }
    catch (std::exception* e)
    {
        UGS::Error::Severe sev;
        UGS::Error::Exception* ue = dynamic_cast<UGS::Error::Exception*>(e);
        if (!ue)
            ue = const_cast<UGS::Error::Exception*>(&sev.Convert(*e));
        ue->doDefaultStartAction("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 5104, 0);
        if (v19)
        {
            SM_free(v19);
            v19 = 0;
        }
        if (v5)
            SM_free(v5);
        if (v6)
            SM_free(v6);
        ue->Rethrow();
    }
    if (v19)
    {
        SM_free(v19);
        v19 = 0;
    }
    if (v5)
        SM_free(v5);
    SM_free(v6);
}
