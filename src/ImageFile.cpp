#include "ImageFile.hpp"

DBRT::ImageFile::ImageFile()
{
}

DBRT::ImageFile::ImageFile(const unsigned int _width, const unsigned int _height) : width(_width), height(_height)
{
    this->pixelData.resize(_width*_height);
}

DBRT::ImageFile::ImageFile(const unsigned int _width, const unsigned int _height, std::vector<PixelRGB> &_pixels) : width(_width), height(_height), pixelData(_pixels)
{
}

DBRT::ImageFile::~ImageFile()
{
}

const unsigned int DBRT::ImageFile::getWidth() const
{
    return width;
}

const unsigned int DBRT::ImageFile::getHeight() const
{
    return height;
}

float DBRT::ImageFile::computeMaxValues(const std::vector<Color3f> &buffer) const
{
    float maxRed = 0, maxGreen = 0, maxBlue = 0, maxValue;
    for(unsigned int y=0; y<this->height; y++)
    {
        for(unsigned int x=0; x<this->width; x++)
        {
            if(buffer.at(y*this->width + x)[0] > maxRed)
                maxRed = buffer.at(y*this->width + x)[0];
            if(buffer.at(y*this->width + x)[1] > maxGreen)
                maxGreen = buffer.at(y*this->width + x)[1];
            if(buffer.at(y*this->width + x)[2] > maxBlue)
                maxBlue = buffer.at(y*this->width + x)[2];
        }
    }
    maxValue = maxRed;
    if(maxGreen > maxValue)
        maxValue = maxGreen;
    if(maxBlue > maxValue)
        maxValue = maxBlue;    
    return maxValue;
}
