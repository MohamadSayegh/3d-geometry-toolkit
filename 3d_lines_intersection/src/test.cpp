#include <gtest/gtest.h>
#include "3dlinesintersection.h"
#include <kdl/frames.hpp>

// Test for parallel lines with no intersection
TEST(Get3DLinesIntersectionTests, ParallelLinesNoIntersection) {
    KDL::Vector a0(0.0, 0.0, 0.0);
    KDL::Vector a1(1.0, 0.0, 0.0);
    KDL::Vector b0(0.0, 1.0, 0.0);
    KDL::Vector b1(1.0, 1.0, 0.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 4);  // Parallel lines, no intersection
}

// Test for collinear overlapping segments
TEST(Get3DLinesIntersectionTests, CollinearOverlappingSegments) {
    KDL::Vector a0(0.0, 0.0, 0.0);
    KDL::Vector a1(1.0, 0.0, 0.0);
    KDL::Vector b0(1.0, 0.0, 0.0);
    KDL::Vector b1(5.0, 0.0, 0.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 2);  // Collinear and overlapping segments
}

// Test for collinear disjoint segments
TEST(Get3DLinesIntersectionTests, CollinearDisjointSegments) {
    KDL::Vector a0(0.0, 0.0, 0.0);
    KDL::Vector a1(2.0, 0.0, 0.0);
    KDL::Vector b0(3.0, 0.0, 0.0);
    KDL::Vector b1(5.0, 0.0, 0.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 3);  // Collinear and disjoint segments
}

// Test for intersecting lines
TEST(Get3DLinesIntersectionTests, IntersectingLines) {
    KDL::Vector a0(0.0, 0.0, 0.0);
    KDL::Vector a1(2.0, 0.0, 0.0);
    KDL::Vector b0(1.0, 1.0, 0.0);
    KDL::Vector b1(1.0, -1.0, 0.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 5);  // Intersecting lines
}

// Test for non-parallel lines that do not intersect
TEST(Get3DLinesIntersectionTests, NonParallelNoIntersection) {
    KDL::Vector a0(0.0, 0.0, 0.0);
    KDL::Vector a1(2.0, 0.0, 0.0);
    KDL::Vector b0(3.0, 1.0, 0.0);
    KDL::Vector b1(3.0, -1.0, 0.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 6);  // Non-parallel lines that do not intersect
}


// Test for lines with a single point of intersection
TEST(Get3DLinesIntersectionTests, SinglePointOfIntersection) {
    KDL::Vector a0(0.0, 0.0, 0.0);
    KDL::Vector a1(2.0, 2.0, 2.0);
    KDL::Vector b0(0.0, 2.0, 0.0);
    KDL::Vector b1(2.0, 0.0, 2.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 5);  // Lines intersect at one point
}

// Test for lines with infinite intersections
TEST(Get3DLinesIntersectionTests, InfiniteIntersections) {
    KDL::Vector a0(0, 0, 0);
    KDL::Vector a1(1, 1, 1);
    KDL::Vector b0(0, 0, 0);
    KDL::Vector b1(1, 1, 1);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 1);  // Lines coincide, infinite intersections
}

// Test for lines with partial overlap
TEST(Get3DLinesIntersectionTests, PartialOverlap) {
    KDL::Vector a0(0.0, 0.0, 0.0);
    KDL::Vector a1(2.0, 2.0, 2.0);
    KDL::Vector b0(1.0, 1.0, 1.0);
    KDL::Vector b1(3.0, 3.0, 3.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 2);  // Lines partially overlap
}

// Test for diagonal lines
TEST(Get3DLinesIntersectionTests, DiagonalLines) {
    KDL::Vector a0(-7.0, 0.0, 5.0);
    KDL::Vector a1(-1.0, 10.0, 1.0);
    KDL::Vector b0(-7.0, 2.5, 4.01);
    KDL::Vector b1(-3.0001, -3.10, 5.0);

    KDL::Vector pA, pB;
    int result = lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);

    ASSERT_EQ(result, 6);  // no intersection
}

// Test for diagonal lines
TEST(Get3DLinesIntersectionTests, nan) {
    KDL::Vector a0(-7.0, 0.0, std::nan(""));
    KDL::Vector a1(-1.0, 10.0, 1.0);
    KDL::Vector b0(-7.0, 2.5, 4.01);
    KDL::Vector b1(-3.0001, -3.10, 5.0);

    KDL::Vector pA, pB;
    
    // Verify that the function throws an exception when NaN values are present
    ASSERT_THROW({
        lines_intersection::Get3DLinesIntersection(a0, a1, b0, b1, pA, pB);
    }, std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
