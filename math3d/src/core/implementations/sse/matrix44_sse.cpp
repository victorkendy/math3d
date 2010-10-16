
#include <xmmintrin.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include "math3d/core/math3d_plugin_sse.h"
#include "math3d/core/sse_utils.h"

using namespace math3d;

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