#ifndef __GEOMETRIC_TRANSFORM_HPP__
#define __GEOMETRIC_TRANSFORM_HPP__

#include "CommonDefinitions.hpp"
#include "Ray.hpp"

namespace DBRT
{
    // Flags auxiliares para indicar o sentido da operacao que deve ser realizada
    constexpr bool LOCAL_TO_WORLD = true;
    constexpr bool WORLD_TO_LOCAL = !LOCAL_TO_WORLD;

    class GeometricTransform
    {
        public:
            GeometricTransform();
            GeometricTransform(const Mat44f &localToWorld, const Mat44f &worldToLocal);
            ~GeometricTransform();

            void setTransform(const Vec3f &translation, const Vec3f &rotation, const Vec3f &scale);
            Mat44f getLocalToWorldMatrix() const;
            Mat44f getWorldToLocalMatrix() const;

            Ray applyTransform(const Ray &inputRay, bool directionFlag);
            Coord3f applyTransform(const Coord3f &inputVector, bool directionFlag);

            GeometricTransform operator * (const GeometricTransform &rhs);
            GeometricTransform operator = (const GeometricTransform &rhs);

            static void printMat(const Mat44f &matrix);

        public:
            Mat44f localToWorldTransform;
            Mat44f worldToLocalTransform;
    };
}

#endif