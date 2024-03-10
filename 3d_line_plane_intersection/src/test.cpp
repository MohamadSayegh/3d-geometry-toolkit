#include <iostream>
#include <gtest/gtest.h>
#include "3dlineplaneintersection.h" 

void PrintVector(KDL::Vector v) {
    std::cout<< "KDL Vector(" << v.x() << ", " << v.y() << ", " << v.z() << ")"<<std::endl;
}

TEST(LinePlaneIntersectionTests,testPlaneConstruction) {
    // Define three points to create a plane
    KDL::Vector a(1, 0, 0);
    KDL::Vector b(0, 1, 0);
    KDL::Vector c(0, 0, 0);

    // Create a plane using the constructor
    line_plane_intersection::Plane plane(a, b, c);

    // Verify that the normal vector of the plane is correct
    KDL::Vector v(0, 0, 1);
    v.Normalize();
    ASSERT_EQ(plane.get_n(),v);
    // Verify that the distance from the origin is correct
    ASSERT_EQ(plane.get_d(),0);
}

TEST(LinePlaneIntersectionTests,testLineIntersection) {
    // Define a plane
    KDL::Vector a(1, 0, 0);
    KDL::Vector b(0, 1, 0);
    KDL::Vector c(0, 0, 0);
    line_plane_intersection::Plane plane(a, b, c);

    // Define two points for the line
    KDL::Vector lineStart(1, 1, 0);
    KDL::Vector lineEnd(1, 1, 1);

    // Calculate the intersection point
    KDL::Vector intersectionPoint(0,0,0);
    bool intersects = plane.intersectLine(lineStart, lineEnd, intersectionPoint);

    PrintVector(intersectionPoint);

    // Verify that the line intersects the plane
    ASSERT_EQ(intersects,1);
    KDL::Vector v(1, 1, 0);
    // Verify that the intersection point is correct

    ASSERT_EQ(intersectionPoint,v);
}

TEST(LinePlaneIntersectionTests,testParallelLine) {
    // Define a plane
    KDL::Vector a(1, 0, 1);
    KDL::Vector b(0, 1, 1);
    KDL::Vector c(0, 0, 1);
    line_plane_intersection::Plane plane(a, b, c);

    // Define two parallel lines
    KDL::Vector lineStart(1, 1, 2);
    KDL::Vector lineEnd(2, 2, 2);

    // Calculate the intersection point
    KDL::Vector intersectionPoint;
    bool intersects = plane.intersectLine(lineStart, lineEnd, intersectionPoint);

    // Verify that the line and plane are parallel and thus do not intersect the plane
    ASSERT_EQ(intersects,0);
}


TEST(LinePlaneIntersectionTests,testCoincidentLine) {
    // Define a plane
    KDL::Vector a(1, 0, 0);
    KDL::Vector b(0, 1, 0);
    KDL::Vector c(0, 0, 1);
    line_plane_intersection::Plane plane(a, b, c);

    // Define a line coincident with the plane
    KDL::Vector lineStart(0, 0, 0);
    KDL::Vector lineEnd(1, 1, 1);

    // Calculate the intersection point
    KDL::Vector intersectionPoint;
    bool intersects = plane.intersectLine(lineStart, lineEnd, intersectionPoint);

    ASSERT_EQ(intersects,1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
