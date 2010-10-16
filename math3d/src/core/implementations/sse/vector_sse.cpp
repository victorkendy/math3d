
#include <xmmintrin.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include "math3d/core/math3d_plugin_sse.h"
#include "math3d/core/sse_utils.h"

using namespace math3d;

float4 & sseImplementation::vecset(float4 & v, const float v0, const float v1, const float v2, const float v3) {
    _gv(v) = _mm_set_ps(v3, v2, v1, v0);
    return v;
}

float4 & sseImplementation::vecset(float4 & dest, const float4 & source) {
    _gv(dest) = _gv(source);
    return dest;
}

float4 & sseImplementation::vecadd(float4 & v1, const float4 & v2) {
    _mm_store_ps(v1, _mm_add_ps(_mm_load_ps(v1), _mm_load_ps(v2)));
    return v1;
}

float4 & sseImplementation::vecsub(float4 & v1, const float4 & v2) {
    _mm_store_ps(v1, _mm_sub_ps(_mm_load_ps(v1), _mm_load_ps(v2)));
    return v1;
}

float4 & sseImplementation::vecdiv(float4 & v, const float & a) {
    _mm_store_ps(v, _mm_div_ps(_mm_load_ps(v), _mm_set1_ps(a)));
    return v;
}

float4 & sseImplementation::vecmul(float4 & v, const float & a) {
    _mm_store_ps(v,_mm_mul_ps(_mm_load_ps(v),_mm_set_ps1(a)));
    return v;
}

float4 & sseImplementation::veccross(float4 & v1, const float4 & v2) {
    __m128 vec1 = _mm_load_ps(v1), vec2 = _mm_load_ps(v2), r;
    r = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(vec1, vec1, CHOOSE(1,2,0,3)), _mm_shuffle_ps(vec2, vec2, CHOOSE(2,0,1,3))),
                   _mm_mul_ps(_mm_shuffle_ps(vec1, vec1, CHOOSE(2,0,1,3)), _mm_shuffle_ps(vec2, vec2, CHOOSE(1,2,0,3))));
    _mm_store_ps(v1, r);
    return v1;
}

float4 & sseImplementation::vecnormalize(float4 & v) {
    __m128 vector = _mm_load_ps(v);
    __m128 t = _mm_mul_ps(vector, vector);
    _mm_store_ps(v,_mm_mul_ps(vector,_mm_rsqrt_ps(_mm_add_ps(t, _mm_add_ps(_mm_shuffle_ps(t,t,0x4E),_mm_add_ps(_mm_shuffle_ps(t,t,0xB1),_mm_shuffle_ps(t,t,0x1B)))))));
    return v;
}

float4 & sseImplementation::vecabs(float4 & v) {
    __m128 _v = _mm_load_ps(v);
    _v = _mm_add_ps(_mm_mul_ps(_mm_and_ps(_mm_cmpgt_ps(_v,_zero),_um),_v),_mm_mul_ps(_mm_andnot_ps(_mm_cmpgt_ps(_v,_zero),_minus),_v));
    _mm_store_ps(v,_v);
    return v;
}

float4 & sseImplementation::vecmax(float4 & v1, const float4 & v2) {
    _mm_store_ps(v1,_mm_max_ps(_mm_load_ps(v1), _mm_load_ps(v2)));
    return v1;
}

float4 & sseImplementation::vecmin(float4 & v1, const float4 & v2) {
    _mm_store_ps(v1,_mm_min_ps(_mm_load_ps(v1), _mm_load_ps(v2)));
    return v1;
}

const float sseImplementation::vecsize(const float4 & v) {
    __m128 vector = _mm_load_ps(v);
    __m128 t = _mm_mul_ps(vector, vector);
    float r;
    _mm_store_ss(&r,_mm_sqrt_ss(_mm_add_ss(t,_mm_add_ss(_mm_shuffle_ps(t,t,1),_mm_add_ss(_mm_shuffle_ps(t,t,2),_mm_shuffle_ps(t,t,3))))));
    return r;
}

const float sseImplementation::vecdot(const float4 & v1, const float4 & v2) {
    float resp;
    __m128 t = _mm_mul_ps(_mm_load_ps(v1), _mm_load_ps(v2));
    t = _mm_add_ps(t, _mm_shuffle_ps(t,t, CHOOSE(2,3,2,3)));
    t = _mm_add_ss(t, _mm_shuffle_ps(t,t, CHOOSE(1,1,1,1)));
    _mm_store_ss(&resp,t);
    return resp;
}

const float sseImplementation::vecminval(const float4 & v) {
    __m128 _v = _mm_load_ps(v);
    float r;
    _v = _mm_min_ps(_v, _mm_shuffle_ps(_v,_v,CHOOSE(1,2,3,0)));
    _v = _mm_min_ss(_v, _mm_shuffle_ps(_v,_v,CHOOSE(2,0,0,0)));
    _mm_store_ss(&r, _v);
    return r;
}

const float sseImplementation::vecmaxval(const float4 & v) {
    float r;
    __m128 xmm0 = _mm_load_ps(v);
    _mm_store_ss(&r,
                    _mm_max_ss(
                               _mm_max_ss(xmm0,_mm_shuffle_ps(xmm0,xmm0,1)),
                               _mm_max_ss(_mm_shuffle_ps(xmm0,xmm0,2),_mm_shuffle_ps(xmm0,xmm0,3))
                              )
                );
    return r;
}
