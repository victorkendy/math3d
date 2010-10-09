/*
 * constants.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kendy
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "math3d/matrix44.h"
#include "math3d/vector4.h"
#include "math3d/quaternion.h"

namespace math3d {
    const matrix44 zeroMatrix44(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
    const matrix44 identity44(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

    const vector4  zeroVector4(0,0,0,0);
    const vector4  e1(1,0,0);
    const vector4  e2(0,1,0);
    const vector4  e3(0,0,1);

    const quaternion unitQuaternion(1,0,0,0);
}



#endif /* CONSTANTS_H_ */
