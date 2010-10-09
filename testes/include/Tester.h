
#include <iostream>
#include <cmath>
#include <string>

#ifndef math3d_tester_base_h
#define math3d_tester_base_h 1

template <class T>
class Tester {
public:
    virtual void setUp() = 0;
    virtual void test() = 0;

    void assertEqual(const T & expected, const T & actual, std::string error_message = "test failed") {
        if(!(expected == actual)) {
            std::cout << error_message << std::endl;
            std::cout << "expected: " << expected.asString() << std::endl;
            std::cout << "got: " << actual.asString() << std::endl;
            std::cout << std::endl;
            testFailed = true;
        }
    }

    void assertEqual(float expected, float actual, std::string error_message = "test failed") {
        if(!(fabs(expected - actual) <= 0.01)) {
            std::cout << error_message << std::endl;
            std::cout << "expected: " << expected << std::endl;
            std::cout << "got: " << actual << std::endl;
            std::cout << std::endl;
            testFailed = true;
        }

    }

    void assertTrue(bool assertion, std::string error_message = "test failed") {
        if(!assertion) {
            std::cout << error_message << std::endl << std::endl;
            testFailed = true;
        }
    }

    void runTests() {
        testFailed = false;
        setUp();
        test();
        if(testFailed) {
            std::cout << "some of your tests failed" << std::endl;
        } else {
            std::cout << "your tests passed" << std::endl;
        }
    }
protected:
    bool testFailed;
};


#endif
