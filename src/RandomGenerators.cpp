#include "RandomGenerators.hpp"

Vec3f DBRT::IRNG::random_in_unit_disk(IRNG &rng)
{
    while(true)
    {
        Vec3f p(rng.get_float()*2.0 - 1.0, rng.get_float()*2.0 - 1.0, 0.0);
        if(p.dotProduct(p) >= 1.0)
            continue;
        return p;
    }
}

Vec3f DBRT::IRNG::random_in_unit_sphere(IRNG &rng)
{
    while(true)
    {
        Vec3f p(rng.get_float()*2.0 - 1.0, rng.get_float()*2.0 - 1.0, rng.get_float()*2.0 - 1.0);
        if(p.dotProduct(p) >= 1.0)
            continue;
        return p;
    }
}

DBRT::MinStdGenerator::MinStdGenerator(uint32_t seed) : rng(seed)
{
}

float DBRT::MinStdGenerator::get_float()
{
    return dist(rng);
}

DBRT::MersenneTwisterGenerator::MersenneTwisterGenerator(uint32_t seed) : rng(seed)
{
}

float DBRT::MersenneTwisterGenerator::get_float()
{
    return dist(rng);
}

DBRT::RanluxGenerator::RanluxGenerator(uint32_t seed) : rng(seed)
{
}

float DBRT::RanluxGenerator::get_float()
{
    return dist(rng);
}
