#ifndef __LIGHT_SOURCE_HPP__
#define __LIGHT_SOURCE_HPP__

#include <memory>
#include <vector>
#include "CommonDefinitions.hpp"
#include "GeometricObject.hpp"

namespace DBRT
{
    class LightSource
    {
        public:
            LightSource();
            virtual ~LightSource();

            virtual bool computeIllumination(const Coord3f &intersectionPoint, const Coord3f &localNormal, const std::vector<std::shared_ptr<DBRT::GeometricObject>> &objectList, const std::shared_ptr<DBRT::GeometricObject> &currentObject, Color3f &color, float &intensity) = 0;
        public:
            Coord3f lightPosition;
            Color3f lightColor;           
            float lightIntensity;            
    };
}

#endif