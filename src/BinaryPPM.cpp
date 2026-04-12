#include "BinaryPPM.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

DBRT::BinaryPPM::BinaryPPM()
{
}

DBRT::BinaryPPM::BinaryPPM(const unsigned int _width, const unsigned int _height) : ImageFile(_width, _height)
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
    // Calcula valor maximo presente no buffer
    float max = computeMaxValues(buffer);
    //std::clog << "Float maxValue = " << max << "  buffer[50] = " << buffer.at(50)[0] << "," << buffer.at(50)[1] << "," << buffer.at(50)[2] << "\n";
    for(unsigned int i=0; i < this->height*this->width; i++)
    {
        this->pixelData.at(i).r = static_cast<uint8_t>((buffer.at(i)[0] /max) * 255);
        this->pixelData.at(i).g = static_cast<uint8_t>((buffer.at(i)[1] /max) * 255);
        this->pixelData.at(i).b = static_cast<uint8_t>((buffer.at(i)[2] /max) * 255);
/*         this->pixelData.at(i).r = static_cast<uint8_t>((buffer.at(i)[0]) * 255);
        this->pixelData.at(i).g = static_cast<uint8_t>((buffer.at(i)[1]) * 255);
        this->pixelData.at(i).b = static_cast<uint8_t>((buffer.at(i)[2]) * 255); */
        //std::clog << "PixelData at " << i << " =>  r=" << static_cast<int>(this->pixelData.at(i).r) << " g=" << static_cast<int>(this->pixelData.at(i).g) << " b=" << static_cast<int>(this->pixelData.at(i).b) << "\n";
    }
    //std::clog << "PixelValue final buffer[115520] = " << pixelData.at(115520).r << "," << pixelData.at(115520).g << "," << pixelData.at(115520).b << "\n";
}

/*
void DBRT::BinaryPPM::denormalizeColorRange()
{
    // Calcular valor maximo presente na imagem
    float max = computeMaxValues();
    float vmax = {255.0/max};
    for(unsigned int y=0; y < this->height; y++)
    {
        for(unsigned int x=0; x < this->width; x++)
        {
            this->pixelData.at(y*this->width + x).operator*(vmax);
        }
    }
}
 */