




extern "C" long long sub_18007A050(const int* a1, double* a2) {
    a2[0] = 0.0;
    a2[1] = 0.0;
    a2[2] = 0.0;
    a2[3] = 0.0;
    a2[a1[0]] = 1.0;
    a2[a1[1] + 2] = 1.0;
    return a1[1];
}
