
#include <xmmintrin.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include "math3d/core/math3d_plugin_sse.h"
#include "math3d/core/sse_utils.h"

using namespace math3d;

float4 & sseImplementation::qinverse(float4 & q) {
    __m128 _q = _mm_load_ps(q);
    __m128 conjugate = _mm_mul_ps(_q, _conjugate);
    __m128 t = _mm_mul_ps(_q, _q);
    _q = _mm_div_ps(conjugate,_mm_add_ps(t,_mm_add_ps(_mm_shuffle_ps(t,t,0x4E),_mm_add_ps(_mm_shuffle_ps(t,t,0xB1), _mm_shuffle_ps(t,t,0x1B)))));
    _mm_store_ps(q,_q);
    return q;
}

float4 & sseImplementation::qmul(float4 & q1, const float4 & q2) {
    static const __m128 _mxz = _mm_set_ps(1, -1, 1, -1), _mxw = _mm_set_ps(-1, 1, 1, -1), _mxy = _mm_set_ps(1,1,-1,-1);
    __m128 xmm0, xmm1, xmm2, xmm3;
    xmm0 = _mm_mul_ps(_mm_shuffle_ps(_gv(q1), _gv(q1), 0), _gv(q2));
    xmm1 = _mm_mul_ps(_mm_mul_ps(_mxz, _mm_shuffle_ps(_gv(q1), _gv(q1), 0x55)), _mm_shuffle_ps(_gv(q2), _gv(q2), 0xB1));
    xmm2 = _mm_mul_ps(_mm_mul_ps(_mxw, _mm_shuffle_ps(_gv(q1), _gv(q1), 0xAA)), _mm_shuffle_ps(_gv(q2), _gv(q2), 0x4E));
    xmm3 = _mm_mul_ps(_mm_mul_ps(_mxy, _mm_shuffle_ps(_gv(q1), _gv(q1), 0xFF)), _mm_shuffle_ps(_gv(q2), _gv(q2), 0x1B));
    _gv(q1) = _mm_add_ps(_mm_add_ps(xmm0, xmm1), _mm_add_ps(xmm2, xmm3));
    return q1;
}

float4 & sseImplementation::qconjugate(float4 & q) {
    _mm_store_ps(q,_mm_mul_ps(_mm_load_ps(q), _conjugate));
    return q;
}

void sseImplementation::cvtqtom44(const float4 & q, float4 m[4]) {
    static const __m128 _mxy = _mm_set_ps(1,1,-1,-1);
    static const __m128 _myz = _mm_set_ps(1,-1,-1,1);
    static const __m128 _mxz = _mm_set_ps(1,-1,1,-1);
    __m128 xmm0,xmm1,xmm2,xmm3;
    __m128 aux = _mm_load_ps(q);
    __m128 t = _mm_mul_ps(aux, aux);
    aux = _mm_mul_ps(aux,_mm_rsqrt_ps(_mm_add_ps(t, _mm_add_ps(_mm_shuffle_ps(t,t,0x4E),_mm_add_ps(_mm_shuffle_ps(t,t,0xB1),_mm_shuffle_ps(t,t,0x1B))))));

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