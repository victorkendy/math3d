
#include <cmath>
#include <string>
#include <xmmintrin.h>
#include "math3d/core/math3d_plugin_sse3.h"
#include "math3d/core/sse_utils.h"

using namespace math3d;

#if _MSC_VER > 1400 || !defined(_MSC_VER)
#include <pmmintrin.h>



float4 & sse3Implementation::vecnormalize(float4 & v) {
    __m128 vector = _mm_load_ps(v);
    __m128 t = _mm_mul_ps(vector, vector);
    t = _mm_hadd_ps(t,t);
     _mm_store_ps(v,_mm_mul_ps(_mm_rsqrt_ps(_mm_hadd_ps(t,t)), vector));
    return v;
}

const float sse3Implementation::vecdot(const float4 & v1, const float4 & v2) {
    float resp;
    __m128 t = _mm_mul_ps(_mm_load_ps(v1), _mm_load_ps(v2));
    t = _mm_hadd_ps(t,t);
    t = _mm_hadd_ps(t,t);
    _mm_store_ss(&resp,t);
    return resp;
}

#endif