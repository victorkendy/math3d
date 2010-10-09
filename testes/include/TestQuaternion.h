
#include <cmath>

#include "Tester.h"
#include "math3d/quaternion.h"
#include "math3d/matrix44.h"

using math3d::quaternion;

#ifndef M_PI
#define M_PI 3.141592
#endif

class TestQuaternion:public Tester<quaternion> {
public:
    void setUp() {
        std::cout << "Testing for quaternion" << std::endl;
        std::cout << "Test for: " << math3d::getCurrent()->getName() << std::endl;
        q1 = quaternion(1,-1,0,1);
        q2 = quaternion(1,1,1,1);
        i = quaternion(0,1,0,0);
        j = quaternion(0,0,1,0);
        k = quaternion(0,0,0,1);
        minus = quaternion(-1, 0,0,0);
    }

    void testFloatPart() {
        quaternion aux;
        assertEqual(2.0f, q2.size(), "sizeof q2");
        assertEqual(1.73205f, q1.size(), "sizeof q1");
        assertEqual(1, q1[0]);
        assertEqual(-1, q1[1]);
        assertEqual(0, q1[2]);
        assertEqual(1, q1[3]);
    }

    void testModifiers() {
        quaternion aux(q2);
        assertEqual(q2, aux, "should be equal");
        aux.normalize();
        assertEqual(1.0f, aux.size(), "size should be 1");
        assertEqual(quaternion(0.5, 0.5, 0.5, 0.5), aux, "should be equal");
        assertEqual(quaternion(1,1,1,1), q2, "should be equal");
        aux = q1;
        assertEqual(q1, aux);
        aux[0] = 10;
        aux[3] = 13;
        assertEqual(quaternion(10, -1,0, 13), aux);
        assertEqual(quaternion(1, -1, 0, 1), q1);
        aux = q1;
        aux += q2;
        assertEqual(q1 + q2, aux, "+=");
        aux = q1;
        aux -= q2;
        assertEqual(q1 - q2, aux, "-=");
        aux = q1;
        aux *= q2;
        assertEqual(q1 * q2, aux, "*=");
        aux = q1;
        aux *= 3.0;
        assertEqual(3.0 * q1, aux, "*=");
        aux = q1;
        aux /= 3.0;
        assertEqual(q1 / 3.0, aux, "/=");
    }
    
    void miscTest() {
        math3d::matrix44 identity;
        identity.loadIdentity();
        assertTrue(identity == quaternion(1,0,0,0).toMatrix(), "should be equal");
        
        assertTrue(math3d::matrix44(1, 0,           0,            0,
                                    0, cos(M_PI/6), -sin(M_PI/6), 0,
                                    0, sin(M_PI/6), cos(M_PI/6),  0,
                                    0, 0,           0,            1) == quaternion(cos(M_PI/12), sin(M_PI/12),0,0).toMatrix(), "rotation of pi/6 around x-axis");
        
        assertTrue(math3d::matrix44(cos(M_PI/6), 0, sin(M_PI/6), 0,
                                    0,           1, 0,           0,
                                    -sin(M_PI/6), 0, cos(M_PI/6),  0,
                                    0, 0,           0,            1) == quaternion(cos(M_PI/12), 0,sin(M_PI/12),0).toMatrix(), "rotation of pi/6 around y-axis");
        
        assertTrue(math3d::matrix44(cos(M_PI/6), -sin(M_PI/6), 0, 0,
                                    sin(M_PI/6), cos(M_PI/6),  0, 0,
                                    0,           0,            1, 0,
                                    0, 0,           0,            1) == quaternion(cos(M_PI/12), 0,0,sin(M_PI/12)).toMatrix(), "rotation of pi/6 around z-axis");
    }

    void test() {
        assertEqual(quaternion(2,0,1,2), q1+q2, "q1+q2");
        assertEqual(quaternion(2, -2, 0, 2), q1 * 2, "q1 * 2");
        assertEqual(quaternion(2, -2, 0, 2), 2 * q1, "2 * q1");
        assertEqual(quaternion(0, -2, -1, 0), q1 - q2, "q1 - q2");
        assertEqual(quaternion(0.5, -0.5, 0, 0.5), q1 / 2, "q1 / 2");
        assertEqual(quaternion(1, -1, 3, 1), q1 * q2, "q1 * q2");
        assertEqual(quaternion(-1,1,0,-1), -q1, "change signal");
        assertEqual(quaternion(1, -1, 0, 1), q1, "shouldnt modify");
        assertEqual(quaternion(1, 1, 1, 1), q2, "shouldnt modify");
        assertEqual(k, i*j, "i*j=k");
        assertEqual(-k, j*i, "j*i=-k");

        assertEqual(j, k*i, "k*i=j");
        assertEqual(-j, i*k, "i*k=-j");

        assertEqual(i, j*k, "j*k=i");
        assertEqual(-i, k*j, "k*j=-i");

        assertEqual(minus, i*i, "i*i=-1");
        assertEqual(minus, j*j, "j*j=-1");
        assertEqual(minus, k*k, "k*k=-1");
        assertEqual(minus, i*j*k, "i*j*k=-1");

        assertEqual(quaternion(1,1,0,-1), q1.conjugate(), "conjugate");
        assertEqual(quaternion(1,0,0,0), q1.conjugate() * q1 / 3.0f, "inverse1");
        assertEqual(quaternion(1,0,0,0), q1 * q1.conjugate() / 3.0f, "inverse1");

        assertEqual(quaternion(0.333, 0.333, 0, -0.333), q1.inverse());
        assertEqual(quaternion(1,0,0,0), q1 * q1.inverse());
        assertEqual(quaternion(1,0,0,0), q1.inverse() * q1);

        testFloatPart();
        testModifiers();
        miscTest();
    }
private:
    quaternion q1, q2;
    quaternion i, j, k, minus;
};
