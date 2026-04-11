#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "Ray.hpp"

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
            void setLength(float newLength);
            void setHorizontalSize(float newHorizontalSize);
            void setAspectRatio(float newAspectRatio);
            
            Coord3f getPosition() const;
            Coord3f getLookAt() const;
            Vec3f getUpDirection() const;
            Vec3f getUVec() const;
            Vec3f getVVec() const;
            Coord3f getScreenCenter() const;
            float getLength() const;
            float getHorizontalSize() const;
            float getAspectRatio() const;
            
            bool generateRay(float projScreenX, float projScreenY, Ray &cameraRay);
            void updateCameraGeometry();
        
        private:
            Coord3f cameraPosition;            
            Coord3f cameraLookAt;
            Vec3f cameraUpDirection;
            float cameraLength;
            float cameraHorizontalSize;
            float cameraAspectRatio;

            Vec3f alignmentVector;
            Vec3f projectionScreenU;
            Vec3f projectionScreenV;
            Coord3f projectionScreenCenter;            
    };
}

#endif