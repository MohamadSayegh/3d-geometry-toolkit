#ifndef LINESINESINTERSECTION
#define LINESINESINTERSECTION
#include <iostream>
#include <cmath>
#include <kdl/frames.hpp>

namespace lines_intersection{

double Determinant(KDL::Vector v1, KDL::Vector v2, KDL::Vector v3);

double AngleBetweenTwoVectors(KDL::Vector v1, KDL::Vector v2);

int Get3DLinesIntersection(KDL::Vector a0, KDL::Vector a1, KDL::Vector b0, KDL::Vector b1, KDL::Vector &resA, KDL::Vector &resB, double tol=1e-5);

void PrintVector(KDL::Vector v);

}

#endif /* LINESINESINTERSECTION */
