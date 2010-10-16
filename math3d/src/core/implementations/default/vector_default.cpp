
#include "math3d/core/math3d_plugin.h"
#include <cmath>
#include <iostream>

using namespace math3d;

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
