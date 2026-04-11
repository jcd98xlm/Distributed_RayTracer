#ifndef __GEOMETRIC_OBJECT_HPP__
#define __GEOMETRIC_OBJECT_HPP__

#include "CommonDefinitions.hpp"
#include "Ray.hpp"
#include "GeometricTransform.hpp"

namespace DBRT
{
    class GeometricObject
    {
        public:
            GeometricObject();
            virtual ~GeometricObject();

            virtual bool testIntersection(const Ray &castRay, Coord3f &intersectionPoint, Vec3f &localNormal, Color3f &localColor) = 0;
            void setTransformMatrix(const GeometricTransform &newTransformMatrix);

        public:
            Color3f baseColor;
            GeometricTransform transformMatrix;
    };
}

#endif