
#include <cmath>
#include <string>
#include <xmmintrin.h>
#include "math3d/core/math3d_plugin_sse3.h"
#include "math3d/core/sse_utils.h"

using namespace math3d;

#if _MSC_VER > 1400 || !defined(_MSC_VER)
#include <pmmintrin.h>



float4& sse3Implementation::m44mulvec(float4 & a, const float4 m[4]) {
	__m128 vec = _mm_load_ps(a);
    __m128 m0 = _mm_load_ps(m[0]), m1 = _mm_load_ps(m[1]), m2 = _mm_load_ps(m[2]), m3 = _mm_load_ps(m[3]);
	m0 = _mm_hadd_ps(_mm_mul_ps(m0,vec), _mm_mul_ps(m1,vec));
	m1 = _mm_hadd_ps(_mm_mul_ps(m2,vec), _mm_mul_ps(m3,vec));
    _mm_store_ps(a, _mm_hadd_ps(m0,m1));
	return a;
}

#endif