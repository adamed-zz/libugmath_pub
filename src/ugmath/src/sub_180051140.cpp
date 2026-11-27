



















#include <cstddef>
#include <cstdint>
#include <cstring>

namespace UGS {
namespace Math {
struct Vector3 {
  double x;
  double y;
  double z;
};
struct Point3 {
  double x;
  double y;
  double z;
};
}
}

using UGS::Math::Point3;
using UGS::Math::Vector3;


void* SM_alloc(std::size_t sz);
void SM_free(void* p);

double** NR_2d_matrix_allo(int rows, int cols, double*** base_out);
void NR_2d_matrix_init_zero(double** m, int rows, int cols);
void NR_matrix_2d_as_1d_identity(double* m, int n);

int SOLVE_lu_solver(double** a, double** b, int n, int nrhs);
void product_of_2(const double* a, const double* b, int n, int m, int p, double* out);
void copy_1d_to_2d(const double* src, int rows, int cols, double** dst);

void NR_ask_eigenvalues_jacobi(double** a, int n, int maxiter, double* vals, double** vecs,
                               int* status_out);
void NR_ask_max_eigen_val_vec(int n, double** a, int maxiter, double* work, double* val_out,
                              double* vec_out, int* status_out);

int VEC3_unitize(const Vector3* u, double tol, double* len_out, Vector3* out);

namespace {


constexpr int kDim = 6;
constexpr int kMatN = kDim * kDim;

inline std::uint64_t f64_bits(double d) {
  std::uint64_t b;
  static_assert(sizeof(b) == sizeof(d), "f64");
  std::memcpy(&b, &d, sizeof(b));
  return b;
}

inline double bits_f64(std::uint64_t b) {
  double d;
  std::memcpy(&d, &b, sizeof(d));
  return d;
}


inline double raw_abs(double d) { return bits_f64(f64_bits(d) & 0x7FFFFFFFFFFFFFFFULL); }


inline double raw_neg(double d) { return bits_f64(f64_bits(d) ^ 0x8000000000000000ULL); }

constexpr double kEps9 = 1.0e-9;
constexpr double kEps10 = 1.0e-10;
constexpr double kOne = 1.0;
constexpr double kInitScalar = 1.0e19;

}

void sub_180051140(int a1, __int64 a2, __int64 a3, __int64 a4, Point3* a5, int* a6,
                   Vector3* a7, __int64* a8, __int64* a9) {
  (void)a4;
  const int n = a1;
  const Point3* ptsA = reinterpret_cast<const Point3*>(a2);
  const Point3* ptsB = reinterpret_cast<const Point3*>(a3);
  double* out_pt = reinterpret_cast<double*>(a8);
  double* out_scalar = reinterpret_cast<double*>(a9);

  int lu_status = 0;
  *a6 = 0;
  a7->x = 0.0;
  a7->y = 0.0;
  a7->z = 0.0;
  out_pt[0] = 0.0;
  out_pt[1] = 0.0;
  out_pt[2] = 0.0;
  *out_scalar = kInitScalar;

  double** base1 = nullptr;
  double** m1 = NR_2d_matrix_allo(kDim, kDim, &base1);
  double** base2 = nullptr;
  double** m2 = NR_2d_matrix_allo(kDim, kDim, &base2);
  double** base3 = nullptr;
  double** m3 = NR_2d_matrix_allo(kDim, kDim, &base3);
  double** base4 = nullptr;
  double** m4 = NR_2d_matrix_allo(kDim, kDim, &base4);
  double** base5 = nullptr;
  double** m5 = NR_2d_matrix_allo(kDim, kDim, &base5);
  NR_2d_matrix_init_zero(m1, kDim, kDim);


  const std::size_t cbuf_sz = static_cast<std::size_t>(n) * 24u;
  double* cbuf = reinterpret_cast<double*>(SM_alloc(cbuf_sz));


  {
    int i = 0;
    if (n >= 4) {
      int blocks = ((n - 4) >> 2) + 1;
      for (int k = 0; k < blocks; ++k, i += 4) {
        cbuf[3 * i + 0] = ptsA[i].x - a5->x;
        cbuf[3 * i + 1] = ptsA[i].y - a5->y;
        cbuf[3 * i + 2] = ptsA[i].z - a5->z;
        cbuf[3 * i + 3] = ptsA[i + 1].x - a5->x;
        cbuf[3 * i + 4] = ptsA[i + 1].y - a5->y;
        cbuf[3 * i + 5] = ptsA[i + 1].z - a5->z;
        cbuf[3 * i + 6] = ptsA[i + 2].x - a5->x;
        cbuf[3 * i + 7] = ptsA[i + 2].y - a5->y;
        cbuf[3 * i + 8] = ptsA[i + 2].z - a5->z;
        cbuf[3 * i + 9] = ptsA[i + 3].x - a5->x;
        cbuf[3 * i + 10] = ptsA[i + 3].y - a5->y;
        cbuf[3 * i + 11] = ptsA[i + 3].z - a5->z;
      }
    }
    for (; i < n; ++i) {
      cbuf[3 * i + 0] = ptsA[i].x - a5->x;
      cbuf[3 * i + 1] = ptsA[i].y - a5->y;
      cbuf[3 * i + 2] = ptsA[i].z - a5->z;
    }
  }


  if (n > 0) {
    for (int i = 0; i < n; ++i) {
      const double c0 = cbuf[3 * i + 0];
      const double c1 = cbuf[3 * i + 1];
      const double c2 = cbuf[3 * i + 2];
      const double b0 = ptsB[i].x;
      const double b1 = ptsB[i].y;
      const double b2 = ptsB[i].z;

      const double x0 = b2 * c1 - c2 * b1;
      const double x1 = c2 * b0 - b2 * c0;
      const double x2 = c0 * b1 - c1 * b0;

      m1[0][0] += x0 * x0;
      m1[0][1] += x1 * x0;
      m1[0][2] += x2 * x0;
      m1[1][1] += x1 * x1;
      m1[1][2] += x2 * x1;
      m1[2][2] += x2 * x2;
      m1[0][3] += x0 * b0;
      m1[0][4] += x0 * b1;
      m1[0][5] += x0 * b2;
      m1[1][3] += x1 * b0;
      m1[1][4] += x1 * b1;
      m1[1][5] += x1 * b2;
      m1[2][3] += x2 * b0;
      m1[2][4] += x2 * b1;
      m1[2][5] += x2 * b2;
      m1[3][3] += b0 * b0;
      m1[3][4] += b1 * b0;
      m1[3][5] += b2 * b0;
      m1[4][4] += b1 * b1;
      m1[4][5] += b2 * b1;
      m1[5][5] += b2 * b2;
    }
  }


  {
    const double* r0 = m1[0];
    const double* r1 = m1[1];
    const double* r2 = m1[2];
    const double* r3 = m1[3];
    const double* r4 = m1[4];
    const double* r5 = m1[5];
    m1[1][0] = r0[1];
    m1[2][0] = r0[2];
    m1[3][0] = r0[3];
    m1[4][0] = r0[4];
    m1[5][0] = r0[5];
    m1[2][1] = r1[2];
    m1[3][1] = r1[3];
    m1[4][1] = r1[4];
    m1[5][1] = r1[5];
    m1[3][2] = r2[3];
    m1[4][2] = r2[4];
    m1[5][2] = r2[5];
    m1[4][3] = r3[4];
    m1[5][3] = r3[5];
    m1[5][4] = r4[5];
  }

  double proj[kMatN];
  NR_matrix_2d_as_1d_identity(proj, kDim);
  proj[3 * kDim + 3] = 0.0;
  proj[4 * kDim + 4] = 0.0;
  proj[5 * kDim + 5] = 0.0;


  NR_matrix_2d_as_1d_identity(reinterpret_cast<double*>(base2), kDim);


  lu_status = SOLVE_lu_solver(m1, m2, kDim, kDim);
  if (lu_status != 0) {
    *a6 = 1;
    goto cleanup;
  }

  {

    product_of_2(reinterpret_cast<const double*>(base2), proj, kDim, kDim, kDim,
                 reinterpret_cast<double*>(base3));
    copy_1d_to_2d(reinterpret_cast<const double*>(base3), kDim, kDim, m4);

    double eig[kDim] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    int jac_status = 0;
    NR_ask_eigenvalues_jacobi(m4, kDim, 60, eig, m5, &jac_status);


    double best = 0.0;
    int sel = -1;
    double vec6[kDim] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    for (int k = 0; k < kDim; ++k) {
      const double e = eig[k];
      const double ab = raw_abs(e - 0.0);
      if (kEps9 >= ab) {

        eig[k] = 0.0;
        continue;
      }

      if (e > 0.0 && e > best) {
        best = e;
        *out_scalar = kOne / e;
        sel = k;
        for (int j = 0; j < kDim; ++j) vec6[j] = m5[j][k];
      }
    }

    if (sel < 0) {


      double work[kDim];
      for (int i = 0; i < kDim; ++i) work[i] = 1.0;
      for (int j = 0; j < kDim; ++j) vec6[j] = 0.0;
      int fb_status = 0;
      NR_ask_max_eigen_val_vec(kDim, m3, 100, work, &best, vec6, &fb_status);
      if (fb_status != 0) {
        *a6 = 1;
        goto cleanup;
      }
      if (kEps10 > best) {
        *a6 = 1;
        goto cleanup;
      }
      *out_scalar = kOne / best;
    }

    if (*a6 != 0) goto cleanup;


    {
      Vector3 axis_in;
      axis_in.x = vec6[0];
      axis_in.y = vec6[1];
      axis_in.z = vec6[2];
      double len = 0.0;
      VEC3_unitize(&axis_in, kEps10, &len, a7);

      const double v3 = vec6[3];
      const double v4 = vec6[4];
      const double v5 = vec6[5];
      const double len2 = len * len;
      const double dot = v3 * vec6[0] + v4 * vec6[1] + v5 * vec6[2];
      const double s = raw_neg(dot / len2);
      const double inv = kOne / len;
      const double qx = (vec6[0] * s + v3) * inv;
      const double qy = (vec6[1] * s + v4) * inv;
      const double qz = (vec6[2] * s + v5) * inv;

      const double ax = a7->x;
      const double ay = a7->y;
      const double az = a7->z;
      const double px = ay * qz - az * qy + a5->x;
      const double py = az * qx - ax * qz + a5->y;
      const double pz = ax * qy - ay * qx + a5->z;

      out_pt[0] = py * az - pz * ay;
      out_pt[1] = pz * ax - px * az;
      out_pt[2] = px * ay - py * ax;
    }
  }

cleanup:
  SM_free(m1);
  if (base1) SM_free(base1);
  if (m2) SM_free(m2);
  if (base2) SM_free(base2);
  if (m3) SM_free(m3);
  if (base3) SM_free(base3);
  if (m4) SM_free(m4);
  if (base4) SM_free(base4);
  if (cbuf) SM_free(cbuf);

}
