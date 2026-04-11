#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "GeometricObject.hpp"

namespace DBRT
{
    class Sphere : public GeometricObject
    {
        public:
            Sphere();
            virtual ~Sphere();

            virtual bool testIntersection(const Ray &castRay, Coord3f &intersectionPoint, Vec3f &localNormal, Color3f &localColor) override;
    };
}

#endif