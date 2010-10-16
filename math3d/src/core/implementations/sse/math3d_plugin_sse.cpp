#include <xmmintrin.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include "math3d/core/math3d_plugin_sse.h"
#include "math3d/core/sse_utils.h"

using namespace math3d;

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
