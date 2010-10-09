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

void sseImplementation::m44mul(float4 a[4], const float4 b[4]) {
    __m128 b0 = _mm_load_ps(b[0]), b1 = _mm_load_ps(b[1]),
           b2 = _mm_load_ps(b[2]), b3 = _mm_load_ps(b[3]);
    __m128 xmm0, xmm1, lineA;
    __m128 a0, a1, a2, a3;

    lineA = _mm_load_ps(a[0]);
    a0 = _mm_shuffle_ps(lineA,lineA,CHOOSE(0,0,0,0));
    a1 = _mm_shuffle_ps(lineA,lineA,CHOOSE(1,1,1,1));
    a2 = _mm_shuffle_ps(lineA,lineA,CHOOSE(2,2,2,2));
    a3 = _mm_shuffle_ps(lineA,lineA,CHOOSE(3,3,3,3));
    xmm0 = _mm_add_ps(_mm_mul_ps(a0,b0),_mm_mul_ps(a1,b1));
    xmm1 = _mm_add_ps(_mm_mul_ps(a2,b2),_mm_mul_ps(a3,b3));
    _mm_store_ps(a[0], _mm_add_ps(xmm0,xmm1));

    lineA = _mm_load_ps(a[1]);
    a0 = _mm_shuffle_ps(lineA,lineA,CHOOSE(0,0,0,0));
    a1 = _mm_shuffle_ps(lineA,lineA,CHOOSE(1,1,1,1));
    a2 = _mm_shuffle_ps(lineA,lineA,CHOOSE(2,2,2,2));
    a3 = _mm_shuffle_ps(lineA,lineA,CHOOSE(3,3,3,3));
    xmm0 = _mm_add_ps(_mm_mul_ps(a0,b0),_mm_mul_ps(a1,b1));
    xmm1 = _mm_add_ps(_mm_mul_ps(a2,b2),_mm_mul_ps(a3,b3));
    _mm_store_ps(a[1], _mm_add_ps(xmm0,xmm1));

    lineA = _mm_load_ps(a[2]);
    a0 = _mm_shuffle_ps(lineA,lineA,CHOOSE(0,0,0,0));
    a1 = _mm_shuffle_ps(lineA,lineA,CHOOSE(1,1,1,1));
    a2 = _mm_shuffle_ps(lineA,lineA,CHOOSE(2,2,2,2));
    a3 = _mm_shuffle_ps(lineA,lineA,CHOOSE(3,3,3,3));
    xmm0 = _mm_add_ps(_mm_mul_ps(a0,b0),_mm_mul_ps(a1,b1));
    xmm1 = _mm_add_ps(_mm_mul_ps(a2,b2),_mm_mul_ps(a3,b3));
    _mm_store_ps(a[2], _mm_add_ps(xmm0,xmm1));

    lineA = _mm_load_ps(a[3]);
    a0 = _mm_shuffle_ps(lineA,lineA,CHOOSE(0,0,0,0));
    a1 = _mm_shuffle_ps(lineA,lineA,CHOOSE(1,1,1,1));
    a2 = _mm_shuffle_ps(lineA,lineA,CHOOSE(2,2,2,2));
    a3 = _mm_shuffle_ps(lineA,lineA,CHOOSE(3,3,3,3));
    xmm0 = _mm_add_ps(_mm_mul_ps(a0,b0),_mm_mul_ps(a1,b1));
    xmm1 = _mm_add_ps(_mm_mul_ps(a2,b2),_mm_mul_ps(a3,b3));
    _mm_store_ps(a[3], _mm_add_ps(xmm0,xmm1));
}

float4& sseImplementation::m44mulvec(float4 & a, const float4 m[4]) {
    __m128 v = _mm_load_ps(a), xmm0, xmm1, xmm2, xmm3;

    xmm0 = _mm_mul_ps(_mm_load_ps(m[0]), v);
    xmm1 = _mm_mul_ps(_mm_load_ps(m[1]), v);
    xmm2 = _mm_mul_ps(_mm_load_ps(m[2]), v);
    xmm3 = _mm_mul_ps(_mm_load_ps(m[3]), v);
    xmm0 = _mm_add_ps(_mm_movehl_ps(xmm1, xmm0), _mm_movelh_ps(xmm0, xmm1));
    xmm1 = _mm_add_ps(_mm_movehl_ps(xmm3, xmm2), _mm_movelh_ps(xmm2, xmm3));
    xmm2 = _mm_shuffle_ps(xmm0, xmm1, 0x88);
    xmm3 = _mm_shuffle_ps(xmm0, xmm1, 0xDD);
    _mm_store_ps(a, _mm_add_ps(xmm3, xmm2));
    return a;
}

void sseImplementation::m44inv(float4 a[4]) {
    const __m128 m0 = _mm_load_ps(a[0]),m1 = _mm_load_ps(a[1]),m2 = _mm_load_ps(a[2]),m3 = _mm_load_ps(a[3]);
    __m128 a0,a1,a2,a3;
    static const __m128 signal = _mm_set_ps(1,1,-1,-1); // [-1,-1,1,1]
    __m128 det;
    {
        __m128 k0,k1;
        /* Calculo das constantes para as duas primeiras linhas */
        __m128 aux1,aux2,aux3,aux4;
        aux1 = _mm_shuffle_ps(m2,m0,CHOOSE(2,3,2,3));
        aux2 = _mm_shuffle_ps(m3,m2,CHOOSE(3,2,2,3));
        aux3 = _mm_shuffle_ps(m3,m1,CHOOSE(3,3,2,3));
        aux4 = _mm_shuffle_ps(aux1, aux2, CHOOSE(0,2,0,2));
        k0 = _mm_mul_ps(aux4, aux3);
        aux3 = _mm_shuffle_ps(m3,m1,CHOOSE(2,2,3,2));
        aux4 = _mm_shuffle_ps(aux1, aux2, CHOOSE(1,3,1,3));
        aux3 = _mm_mul_ps(aux3, aux4);
        k0 = _mm_sub_ps(k0, aux3);
        aux1 = _mm_shuffle_ps(m1,m0,CHOOSE(3,2,2,3));
        aux2 = _mm_shuffle_ps(m3,m1,CHOOSE(3,2,3,2));
        aux3 = _mm_shuffle_ps(m2,m0,CHOOSE(2,3,2,2));
        aux4 = _mm_shuffle_ps(aux1,aux2, CHOOSE(0,2,0,2));
        k1 = _mm_mul_ps(aux3,aux4);
        aux3 = _mm_shuffle_ps(m2,m0,CHOOSE(3,2,3,3));
        aux4 = _mm_shuffle_ps(aux1,aux2,CHOOSE(1,3,1,3));
        aux3 = _mm_mul_ps(aux3, aux4);
        k1 = _mm_sub_ps(k1, aux3);
        /* Calculo da primeira linha da adjunta */
        aux1 = _mm_shuffle_ps(m1,m2,CHOOSE(0,1,0,1));
        aux3 = _mm_shuffle_ps(aux1, m0, CHOOSE(1,3,1,1));
        a0 = _mm_mul_ps(aux3, k0);
        aux3 = _mm_shuffle_ps(m3,aux1,CHOOSE(1,1,1,3));
        aux4 = _mm_mul_ps(aux3, k1);
        a0 = _mm_sub_ps(a0, aux4);
        aux1 = _mm_shuffle_ps(m2,m0,CHOOSE(0,1,0,1));
        aux2 = _mm_shuffle_ps(m3,m1,CHOOSE(0,1,0,1));
        aux3 = _mm_shuffle_ps(aux1,aux2,CHOOSE(1,3,1,3));
        aux4 = _mm_mul_ps(aux3, signal);
        aux3 = _mm_shuffle_ps(k0,k1,CHOOSE(2,0,3,1));
        aux4 = _mm_mul_ps(aux4, aux3);
        a0 = _mm_add_ps(a0, aux4);
        aux3 = _mm_shuffle_ps(aux1, aux2, CHOOSE(0,2,0,2)); // 20 00 30 10 
        aux3 = _mm_shuffle_ps(aux3, aux3, CHOOSE(1,3,0,2));
        aux3 = _mm_mul_ps(a0, aux3);
        /* det eh um vetor no qual os quatro componentes tem o valor do determinante de a */
        det = _mm_add_ps(_mm_add_ps(aux3, _mm_shuffle_ps(aux3, aux3, CHOOSE(1,2,3,0))),
                         _mm_add_ps(_mm_shuffle_ps(aux3,aux3,CHOOSE(2,3,0,1)),_mm_shuffle_ps(aux3, aux3,CHOOSE(3,0,1,2))));
        /* Calculo da segunda linha da adjunta */
        aux1 = _mm_shuffle_ps(m3,m0,CHOOSE(0,0,0,0));
        aux2 = _mm_shuffle_ps(m1,m2,CHOOSE(0,0,0,0));
        aux3 = _mm_shuffle_ps(aux1, aux2, CHOOSE(0,0,0,2));
        aux4 = _mm_shuffle_ps(aux2, aux1, CHOOSE(0,2,2,2));
        aux1 = _mm_shuffle_ps(aux4,aux3, CHOOSE(1,2,0,2));
        a1 = _mm_mul_ps(k1, aux3);
        aux3 = _mm_mul_ps(k0,aux4);
        a1 = _mm_sub_ps(a1, aux3);
        aux2 = _mm_shuffle_ps(signal, signal,CHOOSE(2,2,0,0));
        aux2 = _mm_mul_ps(aux1, aux2);
        aux1 = _mm_shuffle_ps(k0,k1,CHOOSE(2,0,3,1));
        aux2 = _mm_mul_ps(aux1,aux2);
        a1 = _mm_add_ps(a1, aux2);
    }
    {
        __m128 k0,k1;
        __m128 aux1,aux2,aux3,aux4;
        aux1 = _mm_shuffle_ps(m3, m2, CHOOSE(0,1,0,1));// [30,31,20,21]
        aux2 = _mm_shuffle_ps(m0, m1, CHOOSE(0,1,0,1));// [00,01,10,11]
        aux3 = _mm_shuffle_ps(aux1,aux2,CHOOSE(1,0,0,3));//[31,30,00,11]
        aux4 = _mm_shuffle_ps(aux1,aux2,CHOOSE(0,1,1,2));//[30,31,01,10]
        aux2 = _mm_shuffle_ps(m1,m2,CHOOSE(0,1,0,1));//[10,11,20,21]
        k0 = _mm_shuffle_ps(aux2,aux1,CHOOSE(0,3,1,2));//[10,21,31,20]
        k0 = _mm_mul_ps(k0, aux3); // [3110,3021,0031,1120]
        aux3 = _mm_shuffle_ps(aux2,aux1,CHOOSE(1,2,0,3));// [11,20,30,21]
        aux3 = _mm_mul_ps(aux4,aux3);// [3011,3120,0130,1021]
        k0 = _mm_sub_ps(k0,aux3); // [c10,c1,c11,c8]
        aux3 = _mm_shuffle_ps(aux1,aux4,CHOOSE(2,2,1,2)); // [20,20,31,01]
        k1 = _mm_shuffle_ps(m1,m0,CHOOSE(0,1,0,1)); // [10,11,00,01]
        k1 = _mm_shuffle_ps(k1,aux2,CHOOSE(1,3,0,0)); // [11,01,10,10]
        k1 = _mm_mul_ps(k1, aux3); // [2011,2001,3110,0110]
        aux2 = _mm_shuffle_ps(aux2,aux2,CHOOSE(3,3,1,1)); // [21,21,11,11]
        aux3 = _mm_shuffle_ps(m0, aux1, CHOOSE(0,0,0,0)); // [00,00,30,30]
        aux3 = _mm_shuffle_ps(aux3,aux4,CHOOSE(0,2,0,3)); // [00,30,30,10]
        aux3 = _mm_shuffle_ps(aux3,aux3,CHOOSE(3,0,1,0)); // [10,00,30,00]
        aux3 = _mm_mul_ps(aux3,aux2); // [2110,2100,1130,1100]
        k1 = _mm_sub_ps(k1, aux3); // [c8,c9,c10,c2]

        aux1 = _mm_shuffle_ps(m0,m1,CHOOSE(3,3,3,3)); // [03,03,13,13]
        aux2 = _mm_shuffle_ps(m2,m3,CHOOSE(3,3,3,3)); // [23,23,33,33]
        aux1 = _mm_shuffle_ps(aux1,aux2,CHOOSE(0,2,0,2)); // [03,13,23,33]
        aux2 = _mm_shuffle_ps(aux1,aux1,CHOOSE(2,0,1,0)); // [23,03,13,03]
        aux3 = _mm_shuffle_ps(signal,signal,CHOOSE(0,2,0,2));
        aux3 = _mm_mul_ps(aux2, aux3);
        a2 = _mm_mul_ps(k0,aux3);
        aux2 = _mm_shuffle_ps(aux1,aux1,CHOOSE(3,3,0,2));
        aux3 = _mm_shuffle_ps(signal,signal,CHOOSE(0,2,2,2));
        aux3 = _mm_mul_ps(aux2,aux3);
        aux3 = _mm_mul_ps(aux3,k1);
        a2 = _mm_add_ps(a2,aux3);
        aux2 = _mm_shuffle_ps(aux1,aux1,CHOOSE(1,2,3,1));
        aux3 = _mm_shuffle_ps(signal,signal,CHOOSE(0,2,0,0));
        aux3 = _mm_mul_ps(aux3,aux2);
        aux2 = _mm_shuffle_ps(k0,k1,CHOOSE(1,2,3,1));
        aux3 = _mm_mul_ps(aux3,aux2);
        a2 = _mm_add_ps(a2, aux3);
        
        aux1 = _mm_shuffle_ps(m0,m1,CHOOSE(2,2,2,2)); // [02,02,12,12]
        aux2 = _mm_shuffle_ps(m2,m3,CHOOSE(2,2,2,2)); // [22,22,32,32]
        aux1 = _mm_shuffle_ps(aux1,aux2,CHOOSE(0,2,0,2)); // [02,12,22,32]
        aux2 = _mm_shuffle_ps(aux1,aux1,CHOOSE(2,0,1,0));
        aux3 = _mm_shuffle_ps(signal,signal,CHOOSE(2,0,2,0));
        aux3 = _mm_mul_ps(aux2,aux3);
        a3 = _mm_mul_ps(aux3, k0);
        aux2 = _mm_shuffle_ps(aux1,aux1,CHOOSE(3,3,0,2));
        aux3 = _mm_shuffle_ps(signal,signal,CHOOSE(2,0,0,0));
        aux3 = _mm_mul_ps(aux2,aux3);
        aux3 = _mm_mul_ps(aux3,k1);
        a3 = _mm_add_ps(a3, aux3);
        aux2 = _mm_shuffle_ps(aux1,aux1,CHOOSE(1,0,3,1));
        aux3 = _mm_shuffle_ps(signal,signal,CHOOSE(2,0,2,2));
        aux4 = _mm_shuffle_ps(k0,k1,CHOOSE(1,2,3,1));
        aux3 = _mm_mul_ps(aux2,aux3);
        aux3 = _mm_mul_ps(aux3,aux4);
        a3 =_mm_add_ps(a3, aux3);
        
    }
    /* Transforma a adjunta em inversa inv(a) = adj(a) / det(a) */
    a0 = _mm_div_ps(a0, det);
    a1 = _mm_div_ps(a1, det);
    a2 = _mm_div_ps(a2, det);
    a3 = _mm_div_ps(a3, det);
    _mm_store_ps(a[0],a0);
    _mm_store_ps(a[1],a1);
    _mm_store_ps(a[2],a2);
    _mm_store_ps(a[3],a3);
}

void sseImplementation::m44identity(float4 a[4]) {
    static const __m128 e0 = _mm_set_ps(0,0,0,1),
                        e1 = _mm_set_ps(0,0,1,0),
                        e2 = _mm_set_ps(0,1,0,0),
                        e3 = _mm_set_ps(1,0,0,0);
    _gv(a[0]) = e0;
    _gv(a[1]) = e1;
    _gv(a[2]) = e2;
    _gv(a[3]) = e3;
}

// TODO: redo this mess
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

void sseImplementation::batchm44mul(float4 m[], const float4 base[4], const int numMatrices) {
    _mm_prefetch((char*)m, _MM_HINT_T1);
    int i;
    __m128 xmm0, xmm1;
    for(int j = 0; j < numMatrices; j++) {
        float4 * b = m + 4*j;
        for(i = 0; i < 4; i++){
            xmm0 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(_gv(base[i]),_gv(base[i]),0),_gv(b[0])),_mm_mul_ps(_mm_shuffle_ps(_gv(base[i]),_gv(base[i]),0x55),_gv(b[1])));
            xmm1 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(_gv(base[i]),_gv(base[i]),0xAA),_gv(b[2])),_mm_mul_ps(_mm_shuffle_ps(_gv(base[i]),_gv(base[i]),0xFF),_gv(b[3])));
            _gv(b[i]) = _mm_add_ps(xmm0,xmm1);
        }
    }
}

const std::string sseImplementation::getName() const { return "SSE"; }
