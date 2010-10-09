/*
 * projection.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kendy
 */
#define _EXPORT

#include <cmath>
#include <iostream>

#include "math3d/utils/matrix_utils.h"
#include "math3d/core/core.h"
#include "math3d/constants.h"

namespace math3d {
    const matrix44 frustumMatrix(const float & left, const float & right, const float & bottom, const float & top, const float & near, const float & far) {
        matrix44 projectionMatrix;
        float A = (right + left) / (right - left),
              B = (top + bottom) / (top - bottom),
              C = -(far + near) / (far - near),
              D = -(2*far*near) / (far - near);
        projectionMatrix.loadIdentity ();
        projectionMatrix[0][0] = 2 * near / (right - left);
        projectionMatrix[1][1] = 2 * near / (top - bottom);
        
        projectionMatrix[0][2] = A;
        projectionMatrix[1][2] = B;
        projectionMatrix[2][2] = C;
        projectionMatrix[3][2] = -1;
        projectionMatrix[2][3] = D;
        projectionMatrix[3][3] = 0;

        return projectionMatrix;
    }
/*
    const matrix44 perspectiveMatrix(const float & fovy, const float & aspect, const float & near, const float & far){
        matrix44 projectionMatrix;
        float cotan = 1.0f / static_cast<float>(tan (fovy/2.0f));
        float near_far = near - far;
        projectionMatrix = zeroMatrix44;
        projectionMatrix[0][0] = cotan / aspect;
        projectionMatrix[1][1] = cotan;
        projectionMatrix[2][2] = (near + far) / near_far;
        projectionMatrix[3][2] = -1.0f;
        projectionMatrix[2][3] = 2 * near * far / near_far;

        return projectionMatrix;
    }
*/
    const matrix44 orthographicMatrix(const float & left, const float & right, const float & bottom, const float & top, const float & near, const float & far){
        matrix44 projectionMatrix;
        float right_left = right - left,
              top_bottom = top - bottom,
              far_near = far - near;
        projectionMatrix.loadIdentity();
        projectionMatrix[0][0] = 2 / right_left;
        projectionMatrix[1][1] = 2 / top_bottom;
        projectionMatrix[2][2] = -2.0f / far_near;

        projectionMatrix[0][3] = -(right + left) / right_left;
        projectionMatrix[1][3] = -(top + bottom) / top_bottom;
        projectionMatrix[2][3] = -(far + near) / far_near;

        return projectionMatrix;
    }
}
