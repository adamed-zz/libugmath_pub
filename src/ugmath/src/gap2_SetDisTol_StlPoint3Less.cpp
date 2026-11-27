






namespace UGS {

class StlPoint3Less {
public:
    static double GetDisTol();
    static void SetDisTol(double tol);
    static double m_disTol;
};

double StlPoint3Less::m_disTol = 1.0e-6;

double StlPoint3Less::GetDisTol()
{
    return m_disTol;
}

void StlPoint3Less::SetDisTol(double tol)
{
    m_disTol = tol;
}

}
