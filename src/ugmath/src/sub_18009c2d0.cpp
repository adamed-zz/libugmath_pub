









#include <math.h>

extern "C" unsigned char __fastcall sub_18009C2D0(__int64 a1)
{
  unsigned __int8 v1;
  __int64 v2;
  double *v3;
  bool v4;
  int v5;
  __int64 v6;
  double v7;
  double v8;
  double v9;
  volatile __int64 v11[4];

  v1 = 0;
  v11[1] = a1 + 24;
  v2 = 0;
  v11[2] = a1 + 48;
  v11[0] = a1;
  do
  {
    v3 = (double *)v11[v2];
    v4 = 0;
    v5 = 0;
    v6 = 0;
    do
    {
      if ( v4 )
        break;
      v7 = v3[v6];
      if ( v7 != 0.0 )
      {
        v8 = fabs(v7);
        if ( v8 != 1.0 )
        {
          if ( v8 <= 1.0e-10 )
          {
            v7 = 0.0;
            v3[v6] = 0;
            v1 = 1;
          }
          if ( fabs(fabs(v7) - 1.0) <= 1.0e-10 )
          {
            v4 = v1 = 1;
            if ( v7 > 0.0 )
              v9 = 1.0;
            else
              v9 = -1.0;
            v3[v6] = v9;
            if ( v6 )
              *v3 = 0;
            if ( v5 == 1 || (v3[1] = 0, v5 != 2) )
              v3[2] = 0;
          }
        }
      }
      ++v5;
      ++v6;
    }
    while ( v5 < 3 );
    ++v2;
  }
  while ( v2 < 3 );
  return v1;
}
