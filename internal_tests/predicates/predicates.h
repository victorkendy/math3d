

#ifndef MATH3D_INTERNAL_TESTING_PREDICATES_PREDICATES_H_
#define MATH3D_INTERNAL_TESTING_PREDICATES_PREDICATES_H_

#include <gtest/gtest.h>

::testing::AssertionResult NotNULL(void * p) {
    if(p == NULL)
        return ::testing::AssertionFailure() << p << "the pointer should not be null";
    else
        return ::testing::AssertionSuccess();
}

::testing::AssertionResult MemoryDontOverlap(void * p1, size_t size1, void * p2, size_t size2) {
    char * _p1 = static_cast<char*>(p1);
    char * _p2 = static_cast<char*>(p2);

    if((_p1 + size1 <= _p2 + size2) || (_p2 + size2 <= _p1 + size1))
        return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure() << "the pointers should not overlap";
}

::testing::AssertionResult HasAlignment(void * ptr, size_t align) {
    if(((size_t)ptr) % align == 0)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "the pointer should be aligned with " << align;
}

#endif