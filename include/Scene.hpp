#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <memory>
#include <vector>
#include "ImageFile.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "PointLight.hpp"

namespace DBRT
{
    class Scene
    {
        public:
            Scene();
            ~Scene();

            //DBRT::Camera& getCamera(); para versao que permite modificacao
            DBRT::Camera& getCamera();
            std::vector<std::shared_ptr<DBRT::GeometricObject>>& getObjectList();
            std::vector<std::shared_ptr<DBRT::LightSource>>& getLightList();
            Color3f& getBackgroundColor();
            //bool render(ImageFile &outputImage);
            bool generateScene(const std::string &fileName);

        private:
            Camera sceneCamera;

            std::vector<std::shared_ptr<DBRT::GeometricObject>> sceneObjectList;
            std::vector<std::shared_ptr<DBRT::LightSource>> sceneLightList;

            Color3f backgroundColor;
    };
}

#endif