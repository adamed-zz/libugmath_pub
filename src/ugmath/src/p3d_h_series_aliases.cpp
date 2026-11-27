










void h0700(const double* a1, const double* a2, const double* a3, const double* a4,
           const double* a5, const double* a6, double* a7);
void h07313(const int* a1, const int* a2, const double* a3, const double* a4, double* a5);
void h07314(const int* a1, const int* a2, const double* a3, const double* a4, double* a5);
void h0732(const int* a1, const double* a2, const double* a3, const double* a4,
           int* a5, double* a6);
void h0735(const double* a1, const int* a2, double* a3, double* a4, int* a5);
void h805(const double* a1, const double* a2, const int* a3, int* a4);
void h806(const double* a1, const double* a2, const double* a3, int* a4);
void h807(const double* a1, const double* a2, const int* a3, const int* a4, int* a5);


typedef void (*H0700_REAL)(const double*, const double*, const double*, const double*,
                           const double*, const double*, double*);
typedef void (*H073_REAL)(const int*, const int*, const double*, const double*, double*);
typedef void (*H0732_REAL)(const int*, const double*, const double*, const double*,
                           int*, double*);
typedef void (*H0735_REAL)(const double*, const int*, double*, double*, int*);
typedef void (*H805_REAL)(const double*, const double*, const int*, int*);
typedef void (*H806_REAL)(const double*, const double*, const double*, int*);
typedef void (*H807_REAL)(const double*, const double*, const int*, const int*, int*);




void h0700(const double* a1, const double* a2, const double* a3, const double* a4,
           double* a5, double* a6, double* a7)
{
    static H0700_REAL const real = static_cast<H0700_REAL>(&h0700);
    real(a1, a2, a3, a4, a5, a6, a7);
}


void h07313(const int* a1, int* a2, const double* a3, double* a4, double* a5)
{
    static H073_REAL const real = static_cast<H073_REAL>(&h07313);
    real(a1, a2, a3, a4, a5);
}


void h07314(const int* a1, int* a2, const double* a3, double* a4, double* a5)
{
    static H073_REAL const real = static_cast<H073_REAL>(&h07314);
    real(a1, a2, a3, a4, a5);
}


void h0732(const int* a1, const double* a2, double* a3, const double* a4, int* a5, double* a6)
{
    static H0732_REAL const real = static_cast<H0732_REAL>(&h0732);
    real(a1, a2, a3, a4, a5, a6);
}


void h0735(const double* a1, int* a2, double* a3, double* a4, int* a5)
{
    static H0735_REAL const real = static_cast<H0735_REAL>(&h0735);
    real(a1, a2, a3, a4, a5);
}


void h805(double* a1, double* a2, int* a3, int* a4)
{
    static H805_REAL const real = static_cast<H805_REAL>(&h805);
    real(a1, a2, a3, a4);
}


void h806(const double* a1, const double* a2, double* a3, int* a4)
{
    static H806_REAL const real = static_cast<H806_REAL>(&h806);
    real(a1, a2, a3, a4);
}


void h807(double* a1, double* a2, const int* a3, const int* a4, int* a5)
{
    static H807_REAL const real = static_cast<H807_REAL>(&h807);
    real(a1, a2, a3, a4, a5);
}
