

#ifndef math3d_sse_utils_h
#define math3d_sse_utils_h 1

#ifndef _gv
#define _gv(v)  (*((__m128*)&v))
#endif

#ifndef CHOOSE

#define CHOOSE(fp0,fp1,fp2,fp3) (((fp3) << 6) | ((fp2) << 4) | \
                                     ((fp1) << 2) | ((fp0)))


static const __m128 _zero = _mm_set_ps(0.0f,0.0f,0.0f,0.0f);
static const __m128 _um   = _mm_set_ps(1.0f,1.0f,1.0f,1.0f);
static const __m128 _minus= _mm_set_ps(-1.0f,-1.0f,-1.0f,-1.0f);
static const __m128 _conjugate = _mm_set_ps(-1.0f, -1.0f, -1.0f, 1.0f);

#endif

#endif