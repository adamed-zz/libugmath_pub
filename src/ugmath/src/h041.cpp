





int eqz(const double* a1, const double* a2, const int* a3);

int h041(const double* a1) {
    static const double kZero = 0.0;
    static const int kSel = 0;
    return eqz(a1, &kZero, &kSel) && eqz(a1 + 1, &kZero, &kSel) && eqz(a1 + 2, &kZero, &kSel);
}
