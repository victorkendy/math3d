
#include "math3d/core/math3d_plugin.h"
#include <cmath>
#include <iostream>

using namespace math3d;

float4 & math3dImplementation::qinverse(float4 & q) {
    float sSize = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
    q[0] /= sSize; sSize = -sSize;
    q[1] /= sSize;
    q[2] /= sSize;
    q[3] /= sSize;
    return q;
}

float4 & math3dImplementation::qmul(float4 & q1, const float4 & q2) {
    float4 r;
    r[0] = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
    r[1] = q1[0]*q2[1] + q1[1]*q2[0] + q1[2]*q2[3] - q1[3]*q2[2];
    r[2] = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
    r[3] = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
    q1[0] = r[0];
    q1[1] = r[1];
    q1[2] = r[2];
    q1[3] = r[3];
    return q1;
}

float4 & math3dImplementation::qconjugate(float4 & q) {
    q[1] = -q[1]; q[2] = -q[2]; q[3] = -q[3];
    return q;
}

void math3dImplementation::cvtqtom44(const float4 & q, float4 m[4]) {
    float4 aux;
    // Sets aux as the normalized(q). q is unchanged
    vecnormalize(vecset(aux, q));
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    vecset(m[3], 0.0f, 0.0f, 0.0f, 1.0f);

    float a12 = 2.0f*aux[1]*aux[2], a03 = 2.0f*aux[0]*aux[3], a13 = 2.0f*aux[1]*aux[3];
    float a02 = 2.0f*aux[0]*aux[2], a23 = 2.0f*aux[2]*aux[3], a01 = 2.0f*aux[0]*aux[1];
    float a11 = 2.0f*aux[1]*aux[1], a22 = 2.0f*aux[2]*aux[2], a33 = 2.0f*aux[3]*aux[3];

    m[0][0] = 1.0f - (a22 + a33);
    m[0][1] = a12 - a03;
    m[0][2] = a13 + a02;

    m[1][0] = a12 + a03;
    m[1][1] = 1.0f - (a11 + a33);
    m[1][2] = a23 - a01;

    m[2][0] = a13 - a02;
    m[2][1] = a23 + a01;
    m[2][2] = 1.0f - (a11 + a22);
}