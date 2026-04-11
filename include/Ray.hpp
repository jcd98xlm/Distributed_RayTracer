#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "CommonDefinitions.hpp"

namespace DBRT
{
    class Ray : public Vec3f
    {
        public:
            Ray();
            Ray(const Coord3f &_orig, const Coord3f &_dest);
            ~Ray() = default;
            Coord3f getOrigPoint() const;
            Coord3f getDestPoint() const;
            Vec3f getDirection() const;
        
        public:
            Coord3f orig, dest;
            Vec3f direction;
    };
}

#endif