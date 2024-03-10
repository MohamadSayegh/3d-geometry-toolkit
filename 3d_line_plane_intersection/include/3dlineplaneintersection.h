#include <iostream>
#include <cmath>
#include <kdl/frames.hpp>
#include <limits>

// https://math.stackexchange.com/questions/83990/line-and-plane-intersection-in-3d 

namespace line_plane_intersection{

class Plane {
 private:
    KDL::Vector n; // normal
    float d; // distance from origin
 public:
    Plane(); // default constructor
    Plane(KDL::Vector a, KDL::Vector b, KDL::Vector c);
    float get_d();
    KDL::Vector get_n();
    bool intersectLine(KDL::Vector a0, KDL::Vector a1, KDL::Vector &res);
};

}
