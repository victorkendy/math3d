/*
 * projection.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kendy
 */

#ifndef PROJECTION_H_
#define PROJECTION_H_

#include "math3d/core/core.h"
#include "math3d/core/math3d_plugin.h"
#include "math3d/matrix44.h"
#include "math3d/core/export.h"

namespace math3d {

    EXPORT const matrix44 orthographicMatrix(const float & left, const float & right,
                                             const float & bottom, const float & top, 
                                             const float & near, const float & far);

    EXPORT const matrix44 frustumMatrix(const float & left, const float & right, const float & bottom, const float & top, const float & near, const float & far);
}
#endif /* PROJECTION_H_ */
