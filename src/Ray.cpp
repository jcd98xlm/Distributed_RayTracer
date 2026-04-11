#include "Ray.hpp"

DBRT::Ray::Ray() : orig(Coord3f(0.0, 0.0, 0.0)), dest(Coord3f(0.0, 0.0, 0.0)), direction(Vec3f(dest-orig))
{
}

DBRT::Ray::Ray(const Coord3f &_orig, const Coord3f &_dest)
{
    this->orig = _orig;
    this->dest = _dest;
    this->direction = _dest - _orig;
}

Coord3f DBRT::Ray::getOrigPoint() const
{
    return this->orig;
}

Coord3f DBRT::Ray::getDestPoint() const
{
    return this->dest;
}

Vec3f DBRT::Ray::getDirection() const
{
    return this->direction;
}
