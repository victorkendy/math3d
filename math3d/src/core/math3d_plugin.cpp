
#include "math3d/core/math3d_plugin.h"
#include <cmath>
#include <iostream>

using namespace math3d;

// Standard implementation
float4 & math3dImplementation::vecset(float4 & v, const float v0, const float v1, const float v2, const float v3) {
    v[0] = v0; v[1] = v1; v[2] = v2; v[3] = v3;
    return v;
}

float4 & math3dImplementation::vecset(float4 & dest, const float4 & source) {
    dest[0] = source[0];
    dest[1] = source[1];
    dest[2] = source[2];
    dest[3] = source[3];
    return dest;
}

float4 & math3dImplementation::vecadd(float4 & v1, const float4 & v2) {
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
    v1[3] += v2[3];
    return v1;
}

float4 & math3dImplementation::vecsub(float4 & v1, const float4 & v2) {
    v1[0] -= v2[0];
    v1[1] -= v2[1];
    v1[2] -= v2[2];
    v1[3] -= v2[3];
    return v1;
}

float4 & math3dImplementation::vecdiv(float4 & v, const float & a) {
    v[0] /= a;
    v[1] /= a;
    v[2] /= a;
    v[3] /= a;
    return v;
}

float4 & math3dImplementation::vecmul(float4 & v, const float & a) {
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
    v[3] *= a;
    return v;
}

float4 & math3dImplementation::veccross(float4 & v1, const float4 & v2) {
    float4 r;
    r[0] = v1[1] * v2[2] - v1[2] * v2[1];
    r[1] = v1[2] * v2[0] - v1[0] * v2[2];
    r[2] = v1[0] * v2[1] - v1[1] * v2[0];
    r[3] = 0.0f;
    return vecset(v1, r);
}

float4 & math3dImplementation::vecnormalize(float4 & v) {
    float size = vecsize(v);
    return vecdiv(v, size);
}

float4 & math3dImplementation::vecabs(float4 & v) {
    v[0] = v[0] < 0 ? -v[0] : v[0];
    v[1] = v[1] < 0 ? -v[1] : v[1];
    v[2] = v[2] < 0 ? -v[2] : v[2];
    v[3] = v[3] < 0 ? -v[3] : v[3];
    return v;
}

float4 & math3dImplementation::vecmax(float4 & v1, const float4 & v2) {
    v1[0] = v1[0] > v2[0] ? v1[0] : v2[0];
    v1[1] = v1[1] > v2[1] ? v1[1] : v2[1];
    v1[2] = v1[2] > v2[2] ? v1[2] : v2[2];
    v1[3] = v1[3] > v2[3] ? v1[3] : v2[3];
    return v1;
}

float4 & math3dImplementation::vecmin(float4 & v1, const float4 & v2) {
    v1[0] = v1[0] < v2[0] ? v1[0] : v2[0];
    v1[1] = v1[1] < v2[1] ? v1[1] : v2[1];
    v1[2] = v1[2] < v2[2] ? v1[2] : v2[2];
    v1[3] = v1[3] < v2[3] ? v1[3] : v2[3];
    return v1;
}

float4 & math3dImplementation::vecreflect(float4 & v, const float4 & n) {
    float4 nn;
    vecset(nn, n[0], n[1], n[2], n[3]);
    vecnormalize(nn);
    return vecsub(v, vecmul(nn, 2.0f*vecdot(nn,v)));
}

const float math3dImplementation::vecsize(const float4 & v) {
    float size = v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3];
    return sqrt(size);
}

const float math3dImplementation::vecdot(const float4 & v1, const float4 & v2) {
    float r = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] + v1[3]*v2[3];
    return r;
}

const float math3dImplementation::vecminval(const float4 & v) {
    float min = v[0];
    for(register int i = 1; i < 4; i++)
        if(v[i] < min) min = v[i];
    return min;
}

const float math3dImplementation::vecmaxval(const float4 & v) {
    float max = v[0];
    for(register int i = 1; i < 4; i++)
        if(v[i] > max) max = v[i];
    return max;
}

const float math3dImplementation::vectripleproduct(const float4 & v1, const float4 & v2, const float4 & v3) {
    return v3[0]*(v1[1]*v2[2] - v1[2]*v2[1]) +
           v3[1]*(v1[2]*v2[0] - v1[0]*v2[2]) +
           v3[2]*(v1[0]*v2[1] - v1[1]*v2[0]);
}

const bool  math3dImplementation::vecequal(const float4 & v1, const float4 & v2) {
    static const float eps = 0.01f;
    return ((fabs(v1[0]-v2[0]) <= eps) && (fabs(v1[1]-v2[1]) <= eps) && (fabs(v1[2]-v2[2]) <= eps) && (fabs(v1[3]-v2[3]) <= eps));
}

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


void math3dImplementation::batchm44mul(float4 m[], const float4 base[4], const int numMatrices) {
    for(int i = 0; i < numMatrices; i++) {
        float4 * x = m + 4*i;
        float4 r[4];
        vecset(r[0], x[0]); vecset(r[1], x[1]); vecset(r[2], x[2]); vecset(r[3], x[3]);
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++) {
                x[i][j] = 0.0f;
                for(int k = 0; k < 4; k++)
                    x[i][j] += base[i][k] * r[k][j];
            }
    }
}

const std::string math3dImplementation::getName() const { return "DEFAULT"; }

