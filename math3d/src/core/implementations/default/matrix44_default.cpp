
#include "math3d/core/math3d_plugin.h"
#include <cmath>
#include <iostream>

using namespace math3d;

void math3dImplementation::m44mul(float4 a[4], const float4 b[4]) {
    float4 r[4];
    vecset(r[0], a[0]); vecset(r[1], a[1]); vecset(r[2], a[2]); vecset(r[3], a[3]);
    // unrolling this reduced the speed of the algorithm
    for(register int i = 0; i < 4; i++) {
        a[i][0] = r[i][0]*b[0][0] + r[i][1]*b[1][0] + r[i][2]*b[2][0] + r[i][3]*b[3][0];
        a[i][1] = r[i][0]*b[0][1] + r[i][1]*b[1][1] + r[i][2]*b[2][1] + r[i][3]*b[3][1];
        a[i][2] = r[i][0]*b[0][2] + r[i][1]*b[1][2] + r[i][2]*b[2][2] + r[i][3]*b[3][2];
        a[i][3] = r[i][0]*b[0][3] + r[i][1]*b[1][3] + r[i][2]*b[2][3] + r[i][3]*b[3][3];
    }
}

float4& math3dImplementation::m44mulvec(float4 & a, const float4 m[4]) {
    float4 r;
    for(register int i = 0; i < 4; i++) {
        r[i] = m[i][0]*a[0] + m[i][1]*a[1] + m[i][2]*a[2] + m[i][3]*a[3];
    }
    return vecset(a, r);
}

void math3dImplementation::m44inv(float4 a[4]){
    float4 m[4];
    vecset(m[0], a[0]);vecset(m[1], a[1]);vecset(m[2], a[2]);vecset(m[3], a[3]);
    float det = 1.0;
    float c0 = m[2][2]*m[3][3] - m[3][2]*m[2][3];
    float c1 = m[2][1]*m[3][0] - m[3][1]*m[2][0];
    float c2 = m[0][1]*m[1][0] - m[0][0]*m[1][1];
    float c3 = m[0][2]*m[1][3] - m[1][2]*m[0][3];
    float c4 = m[1][3]*m[2][2] - m[1][2]*m[2][3];
    float c5 = m[0][2]*m[3][3] - m[0][3]*m[3][2];
    float c6 = m[1][2]*m[3][3] - m[1][3]*m[3][2];
    float c7 = m[0][2]*m[2][3] - m[2][2]*m[0][3];
    float c8 = m[1][1]*m[2][0] - m[1][0]*m[2][1];
    float c9 = m[0][1]*m[2][0] - m[0][0]*m[2][1];
    float c10 = m[3][1]*m[1][0] - m[1][1]*m[3][0];
    float c11 = m[0][0]*m[3][1] - m[0][1]*m[3][0];

    a[0][0] = m[1][1]*c0 - m[3][1]*c4 - (m[2][1]*c6);
    a[0][1] = m[2][1]*c5 - (m[3][1]*c7 + m[0][1]*c0);
    a[0][2] = m[0][1]*c6 + m[3][1]*c3 - m[1][1]*c5;
    a[0][3] = m[1][1]*c7 + m[0][1]*c4 - m[2][1]*c3;
    det = a[0][0]*m[0][0]+a[0][1]*m[1][0]+a[0][2]*m[2][0]+a[0][3]*m[3][0];

    a[1][0] = m[3][0]*c4 + m[2][0]*c6 - m[1][0]*c0;
    a[1][1] = m[0][0]*c0 + m[3][0]*c7 - m[2][0]*c5;
    a[1][2] = m[1][0]*c5 - (m[0][0]*c6 + m[3][0]*c3);
    a[1][3] = -m[0][0]*c4 + m[2][0]*c3 - (m[1][0]*c7);

    a[2][0] = -(m[3][3]*c8 + m[1][3]*c1 + m[2][3]*c10);
    a[2][1] = m[0][3]*c1 + m[3][3]*c9 + m[2][3]*c11;
    a[2][2] = -m[1][3]*c11 + m[0][3]*c10 - m[3][3]*c2;
    a[2][3] = m[0][3]*c8 + m[2][3]*c2 - m[1][3]*c9;

    a[3][0] = m[1][2]*c1 + m[3][2]*c8 + m[2][2]*c10;
    a[3][1] = -m[2][2]*c11 - (m[0][2]*c1 + m[3][2]*c9);
    a[3][2] = m[3][2]*c2 + m[1][2]*c11 - (m[0][2]*c10);
    a[3][3] = m[1][2]*c9 - (m[0][2]*c8 + m[2][2]*c2);
    
    a[0][0]/=det; a[0][1]/=det; a[0][2]/=det; a[0][3]/=det;
    a[1][0]/=det; a[1][1]/=det; a[1][2]/=det; a[1][3]/=det;
    a[2][0]/=det; a[2][1]/=det; a[2][2]/=det; a[2][3]/=det;
    a[3][0]/=det; a[3][1]/=det; a[3][2]/=det; a[3][3]/=det;
}

void math3dImplementation::m44identity(float4 a[4]) {
    vecset(a[0], 1.0f, 0.0f, 0.0f, 0.0f);
    vecset(a[1], 0.0f, 1.0f, 0.0f, 0.0f);
    vecset(a[2], 0.0f, 0.0f, 1.0f, 0.0f);
    vecset(a[3], 0.0f, 0.0f, 0.0f, 1.0f);
}

void math3dImplementation::m44transpose(float4 a[4]) {
    float aux;
    for(register int i = 0; i < 4; i++) {
        for(register int j = i + 1; j < 4; j++) {
            aux = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = aux;
        }
    }
}
