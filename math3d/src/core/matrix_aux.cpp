
#include "math3d/core/math3d_plugin.h"

namespace math3d {
    void math3dImplementation::createm44ortho(float4 m[4], const float & left, const float & right, 
                                                     const float & bottom, const float & top, 
                                                     const float & near, const float & far) {
        float right_left = right - left,
              top_bottom = top - bottom,
              far_near = far - near;
        m44identity(m);

        m[0][0] = 2 / right_left;
        m[1][1] = 2 / top_bottom;
        m[2][2] = -2.0f / far_near;

        m[0][3] = -(right + left) / right_left;
        m[1][3] = -(top + bottom) / top_bottom;
        m[2][3] = -(far + near) / far_near;
    }
}