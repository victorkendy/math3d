/*
 * TestMatrix44.h
 *
 *  Created on: Jun 29, 2010
 *      Author: kendy
 */

#ifndef TESTMATRIX44_H_
#define TESTMATRIX44_H_

#include "Tester.h"
#include "math3d/matrix44.h"

using math3d::matrix44;


class TestMatrix44 : public Tester<matrix44> {
public:
    void setUp() {
        std::cout << "Testing for matrix44" << std::endl;
        std::cout << "Test for: " << math3d::getCurrent()->getName() << std::endl;
        m1 = matrix44(1, 1.1, 1.2, 1.3,
                      2, 2.1, 2.2, 2.3,
                      3, 3.1, 3.2, 3.3,
                      4, 4.1, 4.2, 4.3);
        m2 = matrix44(5.55, 6.3, 4.44, 0,
                      9, 10, 11, 12,
                      1,2,3,4,
                      1,1,1,1);

    }

    void misc() {
        matrix44 m = m1;
        assertEqual(m1, m);
        m.loadIdentity();
        assertEqual(matrix44(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1), m);
        m = m2;
        assertEqual(matrix44(5.55, 9.00, 1.00, 1.00,
                             6.30, 10.0, 2.00, 1.00,
                             4.44, 11.0, 3.00, 1.00,
                             0.00, 12.0, 4.00, 1.00), m2.transpose());
        assertEqual(m, m2);

        m.set(0.360, 0.480, -0.800, 0.000,
              -0.800, 0.600, 0.000, 0.000,
              0.480, 0.640, 0.600, 0.000,
              0.000, 0.000, 0.000, 1.000);

        assertEqual(matrix44(0.360, -0.800,  0.480,  0.000,
                             0.480,  0.600,  0.640,  0.000,
                             -0.800,  0.000,  0.600,  0.000,
                             0.000,  0.000,  0.000,  1.000), m.inverse());

        m.set( 0.360, -1.600,  0.480,  2.000,
               0.480,  1.200,  0.640,  3.000,
               -0.800,  0.000,  0.600, -1.000,
                0.000,  0.000,  0.000,  1.000);

        assertEqual(matrix44(0.360, 0.480, -0.800, -2.960,
                             -0.400,  0.300,  0.000, -0.100,
                             0.480,  0.640,  0.600, -2.280,
                             0.000, 0.000, 0.000, 1.000), m.inverse());

        m.set(1,3,3,0,
              1,4,3,0,
              1,3,4,0,
              0,0,0,1);

        assertEqual(matrix44(7,-3,-3,0,
                             -1,1,0,0,
                             -1,0,1,0,
                             0,0,0,1), m.inverse());
        m.set(1,2,3,0,
              0,4,5,0,
              1,0,6,0,
              0,0,0,1);
        assertEqual(matrix44(1.0909f,-0.5454f,-0.0909f,0,
                             0.2272f,0.1363f,-0.2272f,0,
                             -0.1818f,0.0909f,0.1818f,0,
                              0,0,0,1), m.inverse());
    }

    void constructorAndAssignment() {
        matrix44 m;
        assertEqual(m1, matrix44(m1));
        assertEqual(m2, matrix44(m2));
        m = m1;
        assertEqual(m1, m);
        m = m2;
        assertEqual(m2, m);
        m.set(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
        assertEqual(matrix44(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1), m);
        m[0][0] = 5.0f; m[1][0] = -2.3; m[2][3] = 6.0f; m[3][0] = 1.0f;
        assertEqual(matrix44(5,0,0,0, -2.3,1,0,0, 0,0,1,6, 1,0,0,1), m);
    }

    void basicArithmetic() {
        assertEqual(matrix44(6.55, 7.4,  5.64, 1.3,
                             11,   12.1, 13.2, 14.3,
                             4,    5.1,   6.2, 7.3,
                             5,    5.1,   5.2, 5.3), m1 + m2);

        assertEqual(matrix44(4.55, 5.20, 3.24, -1.3,
                             7.00, 7.90, 8.80, 9.70,
                             -2.0, -1.1, -0.2, 0.70,
                             -3.0, -3.1, -3.2, -3.3), m2 - m1);

        assertEqual(matrix44(2, 2.2, 2.4, 2.6,
                             4, 4.2, 4.4, 4.6,
                             6, 6.2, 6.4, 6.6,
                             8, 8.2, 8.4, 8.6), 2 * m1);

        assertEqual(matrix44(2, 2.2, 2.4, 2.6,
                             4, 4.2, 4.4, 4.6,
                             6, 6.2, 6.4, 6.6,
                             8, 8.2, 8.4, 8.6), m1 * 2);

        assertEqual(matrix44(0.50, 0.55, 0.60, 0.65,
                             1.00, 1.05, 1.10, 1.15,
                             1.50, 1.55, 1.60, 1.65,
                             2.00, 2.05, 2.10, 2.15), m1 / 2.0);

        assertEqual(matrix44(-1, -1.1, -1.2, -1.3,
                             -2, -2.1, -2.2, -2.3,
                             -3, -3.1, -3.2, -3.3,
                             -4, -4.1, -4.2, -4.3), -m1);
        assertEqual(matrix44(17.95, 21.00, 21.44, 19.30,
                             34.50, 40.30, 40.88, 36.30,
                             51.05, 59.60, 60.32, 53.30,
                             67.60, 78.90, 79.76, 70.30), m1 * m2);
        assertTrue(vector4(33.69, 58, 10, 6) == m2 * vector4(3,2,1,0));

    }

    void shortArithmetic() {
        matrix44 m = m2;
        m += m1;
        assertEqual(matrix44(6.55, 7.4,  5.64, 1.3,
                             11,   12.1, 13.2, 14.3,
                             4,    5.1,   6.2, 7.3,
                             5,    5.1,   5.2, 5.3), m);
        m = m2;
        m -= m1;
        assertEqual(matrix44(4.55, 5.20, 3.24, -1.3,
                             7.00, 7.90, 8.80, 9.70,
                             -2.0, -1.1, -0.2, 0.70,
                             -3.0, -3.1, -3.2, -3.3), m);
        m = m1;
        m *= 2;
        assertEqual(matrix44(2, 2.2, 2.4, 2.6,
                             4, 4.2, 4.4, 4.6,
                             6, 6.2, 6.4, 6.6,
                             8, 8.2, 8.4, 8.6), m);
        m = m1;
        m /= 2;
        assertEqual(matrix44(0.50, 0.55, 0.60, 0.65,
                             1.00, 1.05, 1.10, 1.15,
                             1.50, 1.55, 1.60, 1.65,
                             2.00, 2.05, 2.10, 2.15), m);
        m = m1;
        m *= m2;
        assertEqual(matrix44(17.95, 21.00, 21.44, 19.30,
                             34.50, 40.30, 40.88, 36.30,
                             51.05, 59.60, 60.32, 53.30,
                             67.60, 78.90, 79.76, 70.30), m);
    }

    void test() {
        constructorAndAssignment();
        basicArithmetic();
        shortArithmetic();
        misc();
    }

private:
    matrix44 m1, m2, m3;
};

#endif /* TESTMATRIX44_H_ */
