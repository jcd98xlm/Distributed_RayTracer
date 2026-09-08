#ifndef __IMAGE_FILE_HPP__
#define __IMAGE_FILE_HPP__

#include <string>
#include <vector>
#include <cstdint>
#include "CommonDefinitions.hpp"
#include "Pixel.hpp"

namespace DBRT
{
    class ImageFile
    {
        public:
            ImageFile();
            ImageFile(const unsigned int _width, const unsigned int _height);
            ImageFile(const unsigned int _width, const unsigned int _height, const std::string &_fileName);
            ImageFile(const unsigned int _width, const unsigned int _height, std::vector<PixelRGB> &_pixels);
            ImageFile(const unsigned int _width, const unsigned int _height, const std::string &_fileName, std::vector<PixelRGB> &_pixels);
            virtual ~ImageFile();

            const unsigned int getWidth() const;
            const unsigned int getHeight() const;
        
            virtual bool readImageFile(const std::string &fileName) = 0;
            virtual void writeImageFile() const = 0;
            virtual void writeImageFile(const std::string &fileName) const = 0;
            virtual void bufferToImageFormat(const std::vector<Color3f> &buffer) = 0;
            //static void writeImageFile(const unsigned int width, const unsigned int height, std::vector<PixelRGB>& pixels, const std::string &fileName);
            //virtual void denormalizeColorRange() = 0;
        
        protected:
            float computeMaxValues(const std::vector<Color3f> &buffer) const;

        public:
            unsigned int width, height;
            std::string fileName;
            std::vector<PixelRGB> pixelData;
    };
}

#endif