#ifndef __RANDOM_GENERATORS_HPP__
#define __RANDOM_GENERATORS_HPP__

#include <random>
#include "Vectors.hpp"

namespace DBRT
{
    class IRNG
    {
        public:
            virtual ~IRNG() = default;
            virtual float get_float() = 0;

            Vec3f random_in_unit_disk(IRNG &rng);
            Vec3f random_in_unit_sphere(IRNG &rng);
    };    

    class MinStdGenerator : public IRNG
    {
        public:
            MinStdGenerator(uint32_t seed = std::random_device{}());
            float get_float() override;
        
        private:
            std::minstd_rand rng;
            std::uniform_real_distribution<float> dist{0.0, 1.0};

    };

    class MersenneTwisterGenerator: public IRNG
    {
        public:
            MersenneTwisterGenerator(uint32_t seed = std::random_device{}());
            float get_float() override;

        private:
            std::mt19937 rng;
            std::uniform_real_distribution<float> dist{0.0, 1.0};
    };

    class RanluxGenerator: public IRNG
    {
        public:
            RanluxGenerator(uint32_t seed = std::random_device{}());
            float get_float() override;

        private:
            std::ranlux48 rng;
            std::uniform_real_distribution<float> dist{0.0, 1.0};
    };
}

#endif