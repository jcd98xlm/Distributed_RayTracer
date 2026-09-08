#include "BinaryPPM.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

DBRT::BinaryPPM::BinaryPPM()
{
}

DBRT::BinaryPPM::BinaryPPM(const unsigned int _width, const unsigned int _height, const std::string &_fileName) : ImageFile(_width, _height, _fileName)
{
}

bool DBRT::BinaryPPM::readImageFile(const std::string &fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if(!file)
    {
        // Erro        
    }

    std::string line;
    std::getline(file,line);
    if(line != "P6")
    {
        // Erro
    }

    do
    {        
        std::getline(file,line);
        if(line[0] == '#')
        {            
            continue;
        }
        else
        {
            break;
        }
            
    } while(!file.eof());

    std::stringstream ss(line);
    ss >> this->width >> this->height;

    unsigned int maxColorValue;
    file >> maxColorValue;
    file.get();

    this->pixelData.resize(this->width*this->height);
    file.read(reinterpret_cast<char *>(this->pixelData.data()), this->pixelData.size()*sizeof(PixelRGB));

    if(!file)
    {
        // Erro
    }

    return true;
}

void DBRT::BinaryPPM::writeImageFile() const
{
    std::ofstream file(this->fileName, std::ios::binary);
    if(!file)
    {
        // Erro
    }

    file << "P6\n" << this->width << " " << this->height << "\n255\n";
    file.write(reinterpret_cast<const char *>(pixelData.data()), this->pixelData.size()*sizeof(PixelRGB));
    //file.write(reinterpret_cast<const char *>(pixelData.data()), pixelData.size()*sizeof(Color3f));

    if(!file)
    {
        // Erro
    }
}

void DBRT::BinaryPPM::writeImageFile(const std::string &fileName) const
{
    std::ofstream file(fileName, std::ios::binary);
    if(!file)
    {
        // Erro
    }

    file << "P6\n" << this->width << " " << this->height << "\n255\n";
    file.write(reinterpret_cast<const char *>(pixelData.data()), this->pixelData.size()*sizeof(PixelRGB));
    //file.write(reinterpret_cast<const char *>(pixelData.data()), pixelData.size()*sizeof(Color3f));

    if(!file)
    {
        // Erro
    }
}

void DBRT::BinaryPPM::bufferToImageFormat(const std::vector<Color3f> &buffer)
{
    for(unsigned int i=0; i < this->height*this->width; i++)
    {
        this->pixelData.at(i) = PixelRGB::floatToRGB(buffer.at(i));
    }
}
