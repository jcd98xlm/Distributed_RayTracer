#ifndef __BINARY_PPM_HPP__
#define __BINARY_PPM_HPP__

#include "ImageFile.hpp"

namespace DBRT
{
    class BinaryPPM : public ImageFile
    {
        public:
            BinaryPPM();
            BinaryPPM(const unsigned int _width, const unsigned int _height);
            virtual bool readImageFile(const std::string &fileName) override;
            virtual void writeImageFile() const override;
            virtual void writeImageFile(const std::string &fileName) const override;
            virtual void bufferToImageFormat(const std::vector<Color3f> &buffer) override;
            //virtual void denormalizeColorRange() override;            
    };
}

#endif
