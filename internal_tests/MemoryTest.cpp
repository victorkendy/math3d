
#include <gtest/gtest.h>
#include "math3d/core/core.h"
#include "predicates/predicates.h"

TEST(MemoryTest, internalMallocMustReturnAPointerThatIsNotNULL) {
    void * p = math3d::internal_malloc(16,16);
    EXPECT_TRUE(NotNULL(p));
    math3d::internal_free(p);
}

TEST(MemoryTest, internalMallocReturnsPoitersThatDontOverlap) {
    void * p1, *p2, *p3;
    size_t size1 = 16;
    size_t size2 = 32;
    size_t size3 = 64;
    p1 = math3d::internal_malloc(size1, 16);
    p2 = math3d::internal_malloc(size2, 16);
    p3 = math3d::internal_malloc(size3, 16);

    EXPECT_TRUE(MemoryDontOverlap(p1, size1, p2, size2));
    EXPECT_TRUE(MemoryDontOverlap(p1, size1, p3, size3));
    EXPECT_TRUE(MemoryDontOverlap(p2, size2, p3, size3));

    math3d::internal_free(p1);
    math3d::internal_free(p2);
    math3d::internal_free(p3);
}

TEST(MemoryTest, internalMallocReturnsPoitersThatDontOverlapEvenIfSizesAreBig) {
    void * p1, *p2, *p3;
    size_t size1 = 16 * 1024;
    size_t size2 = 32 * 1024;
    size_t size3 = 64 * 1024;
    p1 = math3d::internal_malloc(size1, 16);
    p2 = math3d::internal_malloc(size2, 16);
    p3 = math3d::internal_malloc(size3, 16);

    EXPECT_TRUE(MemoryDontOverlap(p1, size1, p2, size2));
    EXPECT_TRUE(MemoryDontOverlap(p1, size1, p3, size3));
    EXPECT_TRUE(MemoryDontOverlap(p2, size2, p3, size3));

    math3d::internal_free(p1);
    math3d::internal_free(p2);
    math3d::internal_free(p3);
}

TEST(MemoryTest, internalMallocReturnsAlignedPointers) {
    void * ptrs[100];
    for(int i = 0; i < 100; i++) {
        ptrs[i] = math3d::internal_malloc(i+1, 4);
        EXPECT_TRUE(HasAlignment(ptrs[i], 4));
    }
    math3d::print_internal_memory_page_info();

    for(int i = 0; i < 100; i++) {
        math3d::internal_free(ptrs[i]);
    }
}
