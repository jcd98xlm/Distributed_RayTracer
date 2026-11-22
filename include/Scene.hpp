#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <memory>
#include <vector>
#include "ImageFile.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "PointLight.hpp"
#include "RendererConfig.hpp"

namespace DBRT
{
    class Scene
    {
        public:
            Scene();
            ~Scene();

            DBRT::Camera& getCamera();
            std::vector<std::shared_ptr<DBRT::GeometricObject>>& getObjectList();
            std::vector<std::shared_ptr<DBRT::LightSource>>& getLightList();
            Color3f& getBackgroundColor();
            DBRT::RendererConfig* loadSceneFromFile(const std::string &fileName);

        private:
            Camera sceneCamera;

            std::vector<std::shared_ptr<DBRT::GeometricObject>> sceneObjectList;
            std::vector<std::shared_ptr<DBRT::LightSource>> sceneLightList;

            Color3f backgroundColor;
    };
}

#endif