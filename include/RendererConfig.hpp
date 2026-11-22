#ifndef __RENDERER_CONFIG_HPP__
#define __RENDERER_CONFIG_HPP__

#include <string>

namespace DBRT
{
    struct RendererConfig
    {
        unsigned int width, height; 
        unsigned int nSamplesPP;
        unsigned int generatorSeed;
        std::string outputFileName;
        std::string rndGeneratorType;
    };
}

#endif