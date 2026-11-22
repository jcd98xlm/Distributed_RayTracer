#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <memory>
#include "CommonDefinitions.hpp"
#include "ImageFile.hpp"
#include "BinaryPPM.hpp"
#include "Scene.hpp"

namespace DBRT
{
    class Renderer
    {
        public:
            Renderer();
            Renderer(const std::string &fileName);
            ~Renderer();

            bool loadScene(const std::string &fileName);
            //void resetRenderer();
            //bool render(ImageFile &outputImage);
            bool render();

        private:
            void applyConfiguration(DBRT::RendererConfig &config);

        private:
            DBRT::Scene scene;
            DBRT::ImageFile *outputImage;
            unsigned int numSamplesPerPixel;
            DBRT::IRNG *rndGenerator;
    };
}

#endif