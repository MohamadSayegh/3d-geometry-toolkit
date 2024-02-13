#include "3dlinesintersection.h"
#include <kdl/frames.hpp>

// Resources:
// - https://theswissbay.ch/pdf/Gentoomen%20Library/Game%20Development/Programming/Graphics%20Gems%203.pdf 
// - https://stackoverflow.com/questions/2824478/shortest-distance-between-two-line-segments
// - https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect 

namespace lines_intersection{

int Get3DLinesIntersection(KDL::Vector a0, KDL::Vector a1, KDL::Vector b0, KDL::Vector b1, KDL::Vector &pA, KDL::Vector &pB, double tol /*=1e-5*/){
    
    // Check for NaN values
    if (std::isnan(a0.x()) || std::isnan(a0.y()) || std::isnan(a0.z()) ||
        std::isnan(a1.x()) || std::isnan(a1.y()) || std::isnan(a1.z()) || 
        std::isnan(b0.x()) || std::isnan(b0.y()) || std::isnan(b0.z()) ||
        std::isnan(b1.x()) || std::isnan(b1.y()) || std::isnan(b1.z())) {
        throw std::invalid_argument("Invalid input vectors");
    }

    KDL::Vector Va = a1 - a0;
    KDL::Vector Vb = b1 - b0;

    double angle = AngleBetweenTwoVectors(Va,Vb);

    if ( -tol<=angle && angle<=tol){ 

        KDL::Vector normalized_Va = Va;
        KDL::Vector normalized_Vb = Vb;

        normalized_Va.Normalize();
        normalized_Vb.Normalize();


        // calculate distance between two parallel line segments 
        KDL::Vector d0 = normalized_Va*KDL::dot(normalized_Vb,(b0-a0));
        double dist = (d0+a0-b0).Norm();

        if (-tol<=dist && dist<=tol){
            // collinear, in this case, express the endpoints of the second segment (b0 and b0 + Vb) 
            // in terms of the equation of the first line segment (a0 + Va*s):
            
            double s0 = KDL::dot(b0-a0,Va)/KDL::dot(Va,Va);
            double s1 = KDL::dot(b0+Vb-Va,Va)/KDL::dot(Vb,Vb);

            if ( (0<=s0 && s0<=1) || (0<=s1 && s1<=1)){ // the interval [s0,s1] intersects [0,1]
                    
                if ( -tol<=(a0-b0).Norm() && (a0-b0).Norm()<=tol &&
                     -tol<=(a1-b1).Norm() && (a1-b1).Norm()<=tol ){
                        // std::cout<<(a0-b0).Norm()<<std::endl;
                        // std::cout<<(a1-b1).Norm()<<std::endl;
                        std::cout<<"The two lines are identical within the spcefied tolerance"<<std::endl;
                        pA = a0;
                        pB = b0;
                        return 1;
                } 
                else{
                        std::cout<<"The two line segments are collinear and overlapping within the specified tolerance"<<std::endl;
                        return 2;
                    }
            }
            else {
                std::cout<<"The two line segments are collinear and disjoint"<<std::endl;
                return 3;
            }
        }
        else{
            std::cout<<"The two line segments are parallel, no intersection"<<std::endl;
            pA = a0;
            pB = b0;
            return 4;
        }
    }
    else{

        KDL::Vector Vc = Va*Vb;
        double denom = Vc.Norm()*Vc.Norm();
        double det1 = Determinant(b0-a0,Vb,Vc);
        double det2 = Determinant(b0-a0,Va,Vc);

        double t = det1/denom;
        double s = det2/denom;

        //the closest points
        pA = a0 + Va*t;
        pB = b0 + Vb*s;

        // std::cout<<"s = "<<s<<std::endl;
        // std::cout<<"t = "<<t<<std::endl;
        // std::cout<<(a0-b0).Norm()<<std::endl;
        // std::cout<<(a1-b1).Norm()<<std::endl;
        // std::cout<<(0<=t && t<=1 && 0<=s && s<=1 && -tol<=(a0-b0).Norm() && (a1-b1).Norm()<=tol)<<std::endl;

        if (0<=t && t<=1 && 0<=s && s<=1
            && -tol<=(pA-pB).Norm() 
            && (pA-pB).Norm()<=tol){

            std::cout<<"The two line segments intersect"<<std::endl;
            return 5;

        } else{

            if((a0-b0).Norm() < (a1-b1).Norm()){
                pA=a0;
                pB=b0;
            }else{
                pA=a1;
                pB=b1;                
            }
            
            std::cout<<"The two line segments are not parallel and do not intersect within the spcefied tolerance"<<std::endl;
            return 6;
        }

    }

    return false;
    
}

double AngleBetweenTwoVectors(KDL::Vector v1, KDL::Vector v2){

    if (v1 == v2){

        return 0;

    } else {

        double dotp = KDL::dot(v1,v2);

        return std::acos(dotp/(v1.Norm() * v2.Norm()));
    }

}

//should also be const &
double Determinant(KDL::Vector v1,KDL::Vector v2,KDL::Vector v3) {
    double det = v1.x() * (v2.y() * v3.z() - v2.z() * v3.y())
               - v1.y() * (v2.x() * v3.z() - v2.z() * v3.x())
               + v1.z() * (v2.x() * v3.y() - v2.y() * v3.x());
    return det;
}

void PrintVector(KDL::Vector v) {
    std::cout<< "KDL Vector(" << v.x() << ", " << v.y() << ", " << v.z() << ")"<<std::endl;
}


}