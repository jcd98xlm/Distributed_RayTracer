#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "Ray.hpp"
#include "RandomGenerators.hpp"

namespace DBRT
{
    class Camera
    {
        public:
            Camera();
            ~Camera() = default;

            void setPosition(const Coord3f &newPosition);
            void setLookAt(const Coord3f &newLookAt);
            void setUpDirection(const Vec3f &updirection);
            void setFocalLength(float newLength);
            void setAperture(float newAperture);
            void setHorizontalSize(float newHorizontalSize);
            void setAspectRatio(float newAspectRatio);
            
            Coord3f getPosition() const;
            Coord3f getLookAt() const;
            Vec3f getUpDirection() const;
            Vec3f getUVec() const;
            Vec3f getVVec() const;
            Coord3f getScreenCenter() const;
            float getFocalLength() const;
            float getAperture() const;
            float getHorizontalSize() const;
            float getAspectRatio() const;
            
            bool generateRay(float projScreenX, float projScreenY, Ray &cameraRay);
            bool generateRay(float projScreenX, float projScreenY, Ray &cameraRay, IRNG &sampler);
            void updateCameraGeometry();
        
        private:
            Coord3f cameraPosition;            
            Coord3f cameraLookAt;
            Vec3f cameraUpDirection;
            float cameraFocalLength;
            float cameraAperture;
            float cameraHorizontalSize;
            float cameraAspectRatio;

            Vec3f alignmentVector;
            Vec3f projectionScreenU;
            Vec3f projectionScreenV;
            Coord3f projectionScreenCenter;            
    };
}

#endif