#include "3dlineplaneintersection.h"

// https://math.stackexchange.com/questions/83990/line-and-plane-intersection-in-3d 


line_plane_intersection::Plane::Plane() : n(0, 0, 0), d(0) {} // default constructor

line_plane_intersection::Plane::Plane(KDL::Vector a, KDL::Vector b, KDL::Vector c) { // Constructor to create a plane from 3 points
    // Calculate the normal vector using cross product
    KDL::Vector ab = b - a;
    KDL::Vector ac = c - a;
    n = ab * ac; // cross product 
    n.Normalize();

    // Calculate distance from origin
    // d = -(n.x()*a.x() + n.y()*a.y() + n.z()*a.z());
    d = -KDL::dot(n,a);
}

bool line_plane_intersection::Plane::intersectLine(KDL::Vector a0, KDL::Vector a1, KDL::Vector &res) {
    
    // Calculate the direction vector of the line
    KDL::Vector dir = a1 - a0;
    
    // Calculate the denominator of the formula
    float denominator = KDL::dot(n, dir);
    
    // Check if the denominator is close to zero
    if (fabs(denominator) < std::numeric_limits<float>::epsilon()) {
        // Handle division by zero or close to zero denominator
        // Return a default value or handle the special case as needed
        res =  KDL::Vector::Zero(); // Return a default vector
        return 0;
    }

    // Calculate the parameter t
    float t = (d - KDL::dot(n, a0)) / denominator;

    // Calculate the intersection point
    res =  a0 + (t * dir);
    return 1;
}

float line_plane_intersection::Plane::get_d(){
    return d;
}

KDL::Vector line_plane_intersection::Plane::get_n(){
    return n;
}
