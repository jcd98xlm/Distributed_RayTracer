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
            Renderer(const std::string &fileName);
            ~Renderer();

            bool render(ImageFile &outputImage);

        private:
            DBRT::Scene scene;
            DBRT::BinaryPPM outputImage;
    };
}

#endif