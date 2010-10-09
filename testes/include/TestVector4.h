#include <string>
#include <iostream>

#include "Tester.h"
#include "math3d/vector4.h"
using math3d::vector4;

// Falta triple


class TestVector4 : public Tester<vector4> {
public:
    void setUp() {
        std::cout << "Testing vector4" << std::endl;
        std::cout << "Test for: " << math3d::getCurrent()->getName() << std::endl;
        v1 = vector4(1,2,3,4);
        v2 = vector4(8,7,6,5);
        absHell = vector4(-1, 0.56, -29, 4.6);
    }

    void testModifiers() {
        vector4 aux(v1);
        assertEqual(aux, v1);
        aux += v2;
        assertEqual(vector4(9,9,9,9), aux, "+=");
        assertEqual(vector4(1,2,3,4), v1, "shouldnt modify");

        aux = v2;
        assertEqual(v2, aux, "should be v2");
        aux -= v1;
        assertEqual(vector4(7, 5, 3, 1), aux, "-=");
        assertEqual(vector4(8,7,6,5), v2, "shouldnt modify");

        aux = v1;
        aux *= 3;
        assertEqual(vector4(3, 6, 9, 12), aux, "*=");
        assertEqual(vector4(1,2,3,4), v1, "shouldnt modify");

        aux = v2;
        aux /= 2;
        assertEqual(vector4(4, 3.5, 3, 2.5), aux, "/=");
        assertEqual(vector4(8,7,6,5), v2, "shouldnt modify");

        aux = v1;
        aux[0] = 12;
        assertEqual(vector4(9, 9, 9, 9), v1 + v2, "add");
        assertEqual(vector4(-7, -5, -3, -1), v1 - v2, "sub");
        assertEqual(vector4(2,4,6,8), 2*v1, "left mul");
        assertEqual(vector4(2,4,6,8), v1*2, "right mul");
        assertEqual(vector4(4, 3.5, 3, 2.5), v2 / 2, "div");
        assertEqual(vector4(-1, -2, -3, -4), -v1, "signal change");
        // teste de funcoes que retornam floats
        aux[1] = 10;
        assertEqual(vector4(12, 10, 3, 4), aux, "should modify v[0] and v[1]");

        aux = vector4(1,1,1,1);
        assertEqual(vector4(0.5, 0.5, 0.5, 0.5), aux.normalize(), "should normalize");
        assertEqual(1.0f, aux.size());
    }

    void testAuxiliaryFunctions() {
        vector4 zero(0,0,0,0), i(1,0,0,0), j(0,1,0,0), k(0,0,1,0);
        assertEqual(vector4(1, 0.56, 29, 4.6), math3d::Abs(absHell), "Abs");
        assertEqual(vector4(-1, 0.56, -29, 4), math3d::Min(v1, absHell), "Min");
        assertEqual(vector4(1, 2, 3, 4.6), math3d::Max(v1, absHell), "Min");

        assertEqual(k, math3d::cross(i, j), "i*j=k");
        assertEqual(-k, math3d::cross(j, i), "j*i=-k");

        assertEqual(i, math3d::cross(j, k), "j*k=i");
        assertEqual(-i, math3d::cross(k, j), "k*j=-i");

        assertEqual(-j, math3d::cross(i, k), "i*k=-j");
        assertEqual(j, math3d::cross(k, i), "k*i=j");

        assertEqual(zero, math3d::cross(i,i), "i*i = 0");
        assertEqual(zero, math3d::cross(j,j), "j*j = 0");
        assertEqual(zero, math3d::cross(k,k), "k*k = 0");
    }

    void testComplexCalculations() {
        assertEqual(vector4(19, 17.44, 47, 13.4), (v1 + v2) * 2 - absHell, "complex 1");
        assertEqual(vector4(1,1,0,0), vector4(1,-1,0,0) - vector4(0,1,0,0) * 2.0f * dot(vector4(0,1,0,0), vector4(1, -1, 0,0)));
    }

    void test() {
        assertEqual(v1, vector4(1,2,3,4));
        assertEqual(v2, vector4(8,7,6,5));
        // teste de operacoes basicas
        assertEqual(vector4(9, 9, 9, 9), v1 + v2, "add");
        assertEqual(vector4(-7, -5, -3, -1), v1 - v2, "sub");
        assertEqual(vector4(2,4,6,8), 2*v1, "left mul");
        assertEqual(vector4(2,4,6,8), v1*2, "right mul");
        assertEqual(vector4(4, 3.5, 3, 2.5), v2 / 2, "div");
        assertEqual(vector4(-1, -2, -3, -4), -v1, "signal change");
        // teste de funcoes que retornam floats
        assertEqual(60.0f, dot(v1, v2), "dot");
        assertEqual(5.477225575f, v1. size(), "size");

        assertEqual(-2, math3d::vector4(-2,-1,-1,0).minVal(), "minval");
        assertEqual(-2, math3d::vector4(1,-2,-1,0).minVal(), "minval");
        assertEqual(-2, math3d::vector4(-1,-1,-2,0).minVal(), "minval");
        assertEqual(-2, math3d::vector4(-1,-1,-1,-2).minVal(), "minval");
        assertEqual(-1, math3d::vector4(-1,-1,-1,-1).minVal(), "minval");
        assertEqual(1, v1.minVal(), "minval");
        
        assertEqual(0, math3d::vector4(-2,-1,-1,0).maxVal(), "maxval");
        assertEqual(1, math3d::vector4(1,-2,-1,0).maxVal(), "maxval");
        assertEqual(11, math3d::vector4(-1,11,-2,0).maxVal(), "maxval");
        assertEqual(0, math3d::vector4(-1,-1,0,-2).maxVal(), "maxval");
        assertEqual(-1, math3d::vector4(-1,-1,-1,-1).maxVal(), "maxval");
        assertEqual(4, v1.maxVal(), "maxval");

        assertEqual(1, v1[0], "accessor [0]");
        assertEqual(7, v2[1], "accessor [1]");
        // metodos que modificam o objeto
        testModifiers();

        testAuxiliaryFunctions();

        testComplexCalculations();

    }
private:
    vector4 v1, v2;
    vector4 absHell;
};


