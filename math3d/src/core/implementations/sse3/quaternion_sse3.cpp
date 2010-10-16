
#include <cmath>
#include <string>
#include <xmmintrin.h>
#include "math3d/core/math3d_plugin_sse3.h"
#include "math3d/core/sse_utils.h"

using namespace math3d;

#if _MSC_VER > 1400 || !defined(_MSC_VER)
#include <pmmintrin.h>


float4 & sse3Implementation::qinverse(float4 & q) {
    __m128 _q = _mm_load_ps(q);
    __m128 conjugate = _mm_mul_ps(_q, _conjugate);
    __m128 t = _mm_mul_ps(_q, _q);
    t = _mm_hadd_ps(t,t);
    t = _mm_hadd_ps(t,t);
    _mm_store_ps(q, _mm_div_ps(conjugate, t));
    return q;
}

float4 & sse3Implementation::qmul(float4 & q1, const float4 & q2) {
    __m128 a0, a1, a2, a3;
    __m128 xmm0, xmm1, xmm2;

    a3 = _mm_load_ps(q1);
    a0 = _mm_shuffle_ps(a3,a3, CHOOSE(0,0,0,0));
    a1 = _mm_shuffle_ps(a3,a3, CHOOSE(1,1,1,1));
    a2 = _mm_shuffle_ps(a3,a3, CHOOSE(2,2,2,2));
    a3 = _mm_shuffle_ps(a3,a3, CHOOSE(3,3,3,3));
    xmm2 = _mm_load_ps(q2);
    xmm0 = _mm_mul_ps(a0, xmm2);
    xmm0 = _mm_addsub_ps(xmm0, _mm_mul_ps(a1, _mm_shuffle_ps(xmm2, xmm2, 0xB1)));
    
    xmm1 = _mm_mul_ps(a2, _mm_shuffle_ps(xmm2,xmm2,CHOOSE(2,3,1,0)));
    xmm0 = _mm_shuffle_ps(xmm0,xmm0, CHOOSE(0,1,3,2));
    xmm0 = _mm_addsub_ps(xmm0, xmm1);

    xmm1 = _mm_mul_ps(a3, _mm_shuffle_ps(xmm2,xmm2,CHOOSE(3,1,2,0)));
    xmm0 = _mm_shuffle_ps(xmm0,xmm0, CHOOSE(0,3,1,2));
    xmm0 = _mm_addsub_ps(xmm0, xmm1);
    xmm0 = _mm_shuffle_ps(xmm0,xmm0,CHOOSE(0,2,1,3));

    _mm_store_ps(q1, xmm0);
    return q1;
}

void sse3Implementation::cvtqtom44(const float4 & q, float4 m[4]) {
    static const __m128 _mxy = _mm_set_ps(1,1,-1,-1);
    static const __m128 _myz = _mm_set_ps(1,-1,-1,1);
    static const __m128 _mxz = _mm_set_ps(1,-1,1,-1);
    __m128 xmm0,xmm1,xmm2,xmm3;
    __m128 aux = _mm_load_ps(q);
    __m128 t = _mm_mul_ps(aux, aux);
    t = _mm_hadd_ps(t,t);
     aux = _mm_mul_ps(_mm_rsqrt_ps(_mm_hadd_ps(t,t)), aux);

    xmm0 = _mm_mul_ps(_mm_shuffle_ps(aux,aux,0x15),_mm_shuffle_ps(aux,aux,0x39));
    xmm1 = _mm_mul_ps(_mm_shuffle_ps(aux,aux,0x14),_mm_shuffle_ps(aux,aux,0x38));
    xmm2 = _mm_mul_ps(_mm_mul_ps(_mxy,_mm_shuffle_ps(aux,aux,0x2)), _mm_shuffle_ps(aux,aux,0x2E));
    xmm3 = _mm_mul_ps(_mm_mul_ps(_mxy,_mm_shuffle_ps(aux,aux,0x3)), _mm_shuffle_ps(aux,aux,0x2F));

    _mm_store_ps(m[0], _mm_add_ps(_mm_add_ps(xmm0,xmm1),_mm_add_ps(xmm2,xmm3)));

    xmm0 = _mm_mul_ps(_mm_shuffle_ps(aux,aux,0x29),_mm_shuffle_ps(aux,aux,0x3A));
    xmm1 = _mm_mul_ps(_mm_shuffle_ps(aux,aux,0x21),_mm_shuffle_ps(aux,aux,0x32));
    xmm2 = _mm_mul_ps(_mm_mul_ps(_myz,_mm_shuffle_ps(aux,aux,0x4)),_mm_shuffle_ps(aux,aux,0x17));
    xmm3 = _mm_mul_ps(_mm_mul_ps(_myz,_mm_shuffle_ps(aux,aux,0xC)),_mm_shuffle_ps(aux,aux,0x1F));
    _mm_store_ps(m[1], _mm_add_ps(_mm_add_ps(xmm0,xmm1),_mm_add_ps(xmm2,xmm3)));

    xmm0 = _mm_mul_ps(_mm_shuffle_ps(aux,aux,0x9),_mm_shuffle_ps(aux,aux,0xF));
    xmm1 = _mm_mul_ps(_mm_shuffle_ps(aux,aux,0x39),_mm_shuffle_ps(aux,aux,0x3F));
    xmm2 = _mm_mul_ps(_mm_mul_ps(_mxz,_mm_shuffle_ps(aux,aux,0x10)),_mm_shuffle_ps(aux,aux,0x16));
    xmm3 = _mm_mul_ps(_mm_mul_ps(_mxz,_mm_shuffle_ps(aux,aux,0x20)),_mm_shuffle_ps(aux,aux,0x26));
    _mm_store_ps(m[2], _mm_add_ps(_mm_add_ps(xmm0,xmm1),_mm_add_ps(xmm2,xmm3)));

    vecset(m[3], 0.0f, 0.0f, 0.0f, 1.0f);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
}

#endif