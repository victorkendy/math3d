/*
 * Tester.cpp
 *
 *  Created on: Jun 10, 2010
 *      Author: Victor Kendy Harada
 */


#include <xmmintrin.h>

#include "TestVector4.h"
#include "TestQuaternion.h"
#include "TestMatrix44.h"
#include "math3d/math3d.h"

#include <iostream>
#include <cstdio>
#include <ctime>


#pragma warning(disable: 4305)
#pragma warning(disable: 4244)

void runImplementationTests(math3d::math3dImplementation * implementation) {
    TestVector4 test;
    TestQuaternion testq;
    TestMatrix44 testm44;
    test.runTests();
    testq.runTests();
    testm44.runTests();
    std::cout << std::endl;
}

#define num_iterations 1000

inline float random() {
    return (float)(rand())/(float)(RAND_MAX);
}

void teste(math3d::math3dImplementation * implementation, char * which) {
    clock_t t0,t1;
    math3d::matrix44 m = math3d::identity44;
    math3d::vector4 v(1,1,1,0);
    math3d::vector4 w(0,1,1,0);
    math3d::quaternion q(1,1,0,0);
    math3d::quaternion q1(1,-1,1,1);
	t0 = clock();
    
	for(int i = 0; i < num_iterations; i++) {
		//m.inverse();
        //math3d::identity44.inverse();
		//math3d::Abs(v);
		//math3d::Max(v, w);
        //q = math3d::quaternion(random(), random(), random(), random());
        m = m.inverse();
        //q.toMatrix();
		//v.normalize();
		//q.conjugate();
		//q.toMatrix();
	}
	t1 = clock();
    printf("%s: %f\n", which, (float)(t1 - t0)/(float)(CLOCKS_PER_SEC));
}

int main() {
    runImplementationTests(math3d::getImplementation(math3d::DEFAULT_IMPLEMENTATION));
    runImplementationTests(math3d::getImplementation(math3d::SSE_IMPLEMENTATION));
    runImplementationTests(math3d::getImplementation(math3d::SSE3_IMPLEMENTATION));

    teste(math3d::getImplementation(math3d::DEFAULT_IMPLEMENTATION), "normal");
    teste(math3d::getImplementation(math3d::SSE_IMPLEMENTATION), "SSE");
    teste(math3d::getImplementation(math3d::SSE3_IMPLEMENTATION), "SSE3");
    math3d::printCPUInfo();
    return 0;
}

