











int  SOLVE_lu_solver(double** a, double** b, int n, int m);
void banbks(double** a, int n, int m1, int m2, double** al, int* indx, double* b);
void bandec(double** a, int n, int m1, int m2, double** al, int* indx, double* d);
void e0925(int* a1, double* a2, double* a3, double* a4);
int  em0928(const int* a1, const int* a2, const double* a3);
int  h0914(const int* a1, const double* a2, const double* a3, int* a4, double* a5);
void h0926(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, double* a6);
void h0926a(const int* a1, const double* a2, const double* a3, const double* a4,
            const double* a5, const int* a6, const double* a7, double** a8, double* a9);
void h0926a2(const int* a1, const double* a2, const double* a3, const double* a4,
             const double* a5, const int* a6, const double* a7, double** a8, double* a9);
void h0927(const int* a1, const double* a2, const double* a3, double* const a4);
double h128(double a, double b);
void h553(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, const double* a6, const int* a7, double* a8);
void h805(const double* a1, const double* a2, const int* a3, int* a4);
int  knot_seq_order_4(const int* a1, const double* a2, const double* a3, int* a4, double* a5);
void mdecompose_banded(double** a1, int a2, int a3);
void mdispose_banded(double*** a1, double** a2);
int  merrorflush();
int  merrorlevel();
void msetup_banded(int a1, int a2, double*** a3, double** a4);
void msolve_banded(double** a1, int a2, int a3, double* a4);



int ext_SOLVE_lu_solver(double** a, double** b, int n, int m)
{
    return SOLVE_lu_solver(a, b, n, m);
}

void ext_banbks(double** a, int n, int m1, int m2, double** al, int* indx, double* b)
{
    banbks(a, n, m1, m2, al, indx, b);
}

void ext_bandec(double** a, int n, int m1, int m2, double** al, int* indx, double* d)
{
    bandec(a, n, m1, m2, al, indx, d);
}

void ext_e0925(int* a1, double* a2, double* a3, double* a4)
{
    e0925(a1, a2, a3, a4);
}

int ext_em0928(const int* a1, const int* a2, const double* a3)
{
    return em0928(a1, a2, a3);
}

int ext_h0914(const int* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    return h0914(a1, a2, a3, a4, a5);
}

void ext_h0926(const int* a1, const double* a2, const double* a3, const double* a4,
               const int* a5, double* a6)
{
    h0926(a1, a2, a3, a4, a5, a6);
}

void ext_h0926a(const int* a1, const double* a2, const double* a3, const double* a4,
                const double* a5, const int* a6, const double* a7, double** a8, double* a9)
{
    h0926a(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

void ext_h0926a2(const int* a1, const double* a2, const double* a3, const double* a4,
                 const double* a5, const int* a6, const double* a7, double** a8, double* a9)
{
    h0926a2(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

void ext_h0927(const int* a1, const double* a2, const double* a3, double* a4)
{
    h0927(a1, a2, a3, a4);
}

double ext_h128(double a, double b)
{
    return h128(a, b);
}

int ext_h553(const double* a1, const double* a2, const double* a3,
             const double* a4, const double* a5, const double* a6,
             const int* a7, double* a8)
{
    h553(a1, a2, a3, a4, a5, a6, a7, a8);
    return 0;
}

void ext_h805(const double* a1, const double* a2, const int* a3, int* a4)
{
    h805(a1, a2, a3, a4);
}

int ext_knot_seq_order_4(const int* a1, const double* a3, const double* a4, int* a7, double* a8)
{
    return knot_seq_order_4(a1, a3, a4, a7, a8);
}

void ext_mdecompose_banded(double** a, int n, int m)
{
    mdecompose_banded(a, n, m);
}

void ext_mdispose_banded(double*** a, double** b)
{
    mdispose_banded(a, b);
}

void ext_merrorflush()
{
    (void)merrorflush();
}

int ext_merrorlevel()
{
    return merrorlevel();
}

void ext_msetup_banded(int n, int m, double*** a, double** b)
{
    msetup_banded(n, m, a, b);
}

void ext_msolve_banded(double** a, int n, int m, double* b)
{
    msolve_banded(a, n, m, b);
}
