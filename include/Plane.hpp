#ifndef __PLANE_HPP__
#define __PLANE_HPP__

#include "GeometricObject.hpp"

namespace DBRT
{
    class Plane : public GeometricObject
    {
        public:
            Plane();
            virtual ~Plane() override;

            virtual bool testIntersection(const Ray &castRay, Coord3f &intersectionPoint, Vec3f &localNormal, Color3f &localColor) override;
        private:
    };
}

#endif