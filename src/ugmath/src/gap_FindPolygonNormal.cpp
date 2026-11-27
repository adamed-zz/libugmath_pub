


























namespace UGS {
namespace Math {

void AddMatrices(bool add, const double* const a, const double* const b, int rows, int cols,
                 double* const out);
void ScaleMatrix(const double* const src, double scale, int rows, int cols,
                 double* const out);
bool NormalizeVector(const double* const v, int n, double* const out);

void FindPolygonNormal(int count, const double* const pts, double* const normal, bool& ok);

void FindPolygonNormal(int count, const double* const pts, double* const normal, bool& ok)
{
    ok = false;
    normal[0] = 0.0;
    normal[1] = 0.0;
    normal[2] = 1.0;
    if (count < 3) {
        ok = true;
        return;
    }
    const double* p = pts + 6;
    if (count == 3) {
        double u[3] = {0.0, 0.0, 0.0};
        AddMatrices(false, p, pts + 3, 3, 1, u);
        double m[3] = {0.0, 0.0, 0.0};
        AddMatrices(true, p, pts + 3, 3, 1, m);
        ScaleMatrix(m, 0.5, 3, 1, m);
        double v[3] = {0.0, 0.0, 0.0};
        AddMatrices(false, m, pts, 3, 1, v);
        normal[0] = u[2] * v[1] - u[1] * v[2];
        normal[1] = u[0] * v[2] - u[2] * v[0];
        normal[2] = u[1] * v[0] - u[0] * v[1];
    } else if (count == 4) {
        double u[3] = {0.0, 0.0, 0.0};
        AddMatrices(false, p, pts, 3, 1, u);
        double v[3] = {0.0, 0.0, 0.0};
        AddMatrices(false, pts + 9, pts + 3, count - 1, 1, v);

        normal[0] = v[2] * u[1] - u[2] * v[1];
        normal[1] = v[0] * u[2] - u[0] * v[2];
        normal[2] = v[1] * u[0] - v[0] * u[1];
    } else {
        normal[2] = 0.0;
        double d[3] = {0.0, 0.0, 0.0};
        AddMatrices(false, pts + 3, pts, 3, 1, d);
        int n = count - 2;
        do {
            double w[3] = {0.0, 0.0, 0.0};
            AddMatrices(false, p, pts, 3, 1, w);
            double c[3];
            c[0] = w[2] * d[1] - w[1] * d[2];
            c[1] = w[0] * d[2] - w[2] * d[0];
            c[2] = w[1] * d[0] - w[0] * d[1];
            AddMatrices(true, c, normal, 3, 1, normal);
            p += 3;
            d[0] = w[0];
            d[1] = w[1];
            d[2] = w[2];
            --n;
        } while (n);
    }
    ok = NormalizeVector(normal, 3, normal);
}

}
}
