






extern "C" long long sub_18007BD10(double* dst, long long n, const double* val);

extern "C" long long sub_18007ADA0(const long long* a1, const long long* a2) {
    double zero = 0.0;
    long long result = sub_18007BD10((double*)a2[0], a2[1] * a2[2], &zero);
    for (long long i = 0; i < a1[1]; ++i) {
        result = a1[0];
        long long row = i * a2[1];
        long long col = ((const int*)result)[i];
        ((double*)a2[0])[row + col] = 1.0;
    }
    return result;
}
