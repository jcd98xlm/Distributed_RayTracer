#ifndef __POINT_LIGHT_HPP__
#define __POINT_LIGHT_HPP__

#include "LightSource.hpp"

namespace DBRT
{
    class PointLight : public LightSource
    {
        public:
            PointLight();
            virtual ~PointLight() override;

            virtual bool computeIllumination(const Coord3f &intersectionPoint, const Coord3f &localNormal, const std::vector<std::shared_ptr<DBRT::GeometricObject>> &objectList, const std::shared_ptr<DBRT::GeometricObject> &currentObject, Color3f &color, float &intensity) override;
    };
}

#endif