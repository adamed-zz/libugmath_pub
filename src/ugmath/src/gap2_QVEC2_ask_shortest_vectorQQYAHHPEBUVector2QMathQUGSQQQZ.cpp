namespace UGS {
namespace Math {
struct Vector2 {
    double x, y;
};
}
}

namespace {
const int g_checking_level = 0;
}

void ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);

int VEC2_ask_shortest_vector(int a1, const UGS::Math::Vector2* a2)
{
    if (g_checking_level <= 0 || a1 > 0) {
        const double* v3 = reinterpret_cast<const double*>(a2);
        double v5 = v3[1];
        int v6 = 1;
        double v7 = v3[0];
        int v8 = 0;
        double v9 = v7 * v7 + v5 * v5;
        if (a1 > 1) {
            int v10 = 1;
            int v11;
            const double* v12;
            if (a1 <= 4)
                goto LABEL_25;
            v11 = a1 - 3;
            v12 = v3 + 5;
            do {
                double v13 = v12[-3] * v12[-3] + v12[-2] * v12[-2];
                bool v14 = !(v9 + 0.0 > v13);
                if (v9 + 0.0 > v13)
                    v9 = v12[-3] * v12[-3] + v12[-2] * v12[-2];
                double v15 = v9 + 0.0;
                int v16 = v6;
                if (v14)
                    v16 = v8;
                double v17 = v12[-1] * v12[-1] + v12[0] * v12[0];
                bool v18 = !(v15 > v17);
                if (v15 > v17)
                    v9 = v12[-1] * v12[-1] + v12[0] * v12[0];
                int v19 = v6 + 1;
                double v20 = v9 + 0.0;
                if (v18)
                    v19 = v16;
                double v21 = v12[1] * v12[1] + v12[2] * v12[2];
                bool v22 = !(v20 > v21);
                if (v20 > v21)
                    v9 = v12[1] * v12[1] + v12[2] * v12[2];
                int v23 = v6 + 2;
                double v24 = v9 + 0.0;
                if (v22)
                    v23 = v19;
                double v25 = v12[3] * v12[3] + v12[4] * v12[4];
                if (v24 > v25)
                    v9 = v12[3] * v12[3] + v12[4] * v12[4];
                v8 = v6 + 3;
                if (!(v24 > v25))
                    v8 = v23;
                v10 += 4;
                v12 += 8;
                v6 += 4;
            } while (v6 < v11);
            if (v6 < a1) {
            LABEL_25:
                const double* v26 = v3 + 2 * v10;
                do {
                    double v27 = v26[0] * v26[0] + v26[1] * v26[1];
                    bool v28 = !(v9 + 0.0 > v27);
                    if (v9 + 0.0 > v27)
                        v9 = v26[0] * v26[0] + v26[1] * v26[1];
                    int v29 = v6;
                    if (v28)
                        v29 = v8;
                    v26 += 2;
                    ++v6;
                    v8 = v29;
                } while (v6 < a1);
            }
        }
        return v8;
    } else {
        ERROR_assertion_failed("o:\nx2412\ip1700\src\ugmath\no\ind\vec2.c", 273, "%s",
                               "count > 0");
        return 0;
    }
}
