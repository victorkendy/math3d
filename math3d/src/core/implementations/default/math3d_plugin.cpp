
#include "math3d/core/math3d_plugin.h"
#include <cmath>
#include <iostream>

using namespace math3d;

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

