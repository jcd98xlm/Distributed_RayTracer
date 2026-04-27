#include "Renderer.hpp"
#include <iostream>
#include <chrono>

DBRT::Renderer::Renderer(const std::string &fileName)
{
    std::clog << "------------------------------------------------\n";
    std::clog << "------------------- Renderer -------------------\n";

    std::clog << "---------------- Criando a cena ----------------\n";
    this->scene.generateScene(fileName);
    std::clog << "------------------------------------------------\n";
}

DBRT::Renderer::~Renderer()
{
}

bool DBRT::Renderer::render(ImageFile &outputImage)
{
    std::clog << "--------------- Criando a imagem ---------------\n";
    auto stamp = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration;

    unsigned int xSize = outputImage.getWidth();
    unsigned int ySize = outputImage.getHeight();

    // Buffer local para a imagem
    std::vector<Color3f> imgBuffer(xSize*ySize, sizeof(Color3f));

    // Processa os pixels da imagem
    Ray cameraRay;
    Coord3f intPoint;
    Vec3f localNormal;
    Color3f localColor;

    // Pre-calcular fatores de escala para as coordenadas
    float xScaleFactor = 2.0/static_cast<float>(xSize);
    float yScaleFactor = 2.0/static_cast<float>(ySize);
    //float minDist = 1e6, maxDist = 0.0;
    for(unsigned int y=0; y<ySize; y++)
    {
        for(unsigned int x=0; x<xSize; x++)
        {
            // Normalizar as coordenadas x e y
            float normalizedX = (static_cast<float>(x)*xScaleFactor) - 1.0;
            float normalizedY = (static_cast<float>(y)*yScaleFactor) - 1.0;

            // Gerar o raio para este pixel
            this->scene.getCamera().generateRay(normalizedX, normalizedY, cameraRay);

            // TODO: posteriormente subtituir por um sistema de deteccao de colisoes
            // Testar interseccao com todos os objetos da cena
            std::shared_ptr<GeometricObject> closestObject;
            Vec3f closestIntersectionPoint, closestLocalNormal, closestLocalColor;
            double minDist = __DBL_MAX__;
            bool intersectionFound = false;
            for(auto currentObject : this->scene.getObjectList())
            {
                bool validIntersection = currentObject->testIntersection(cameraRay, intPoint, localNormal, localColor);
                if(validIntersection)
                {
                    // Setar flag para indicar que uma interseccao foi encontrada
                    intersectionFound = true;

                    // Calcular a distancia entre a camera e o ponto de interseccao
                    double dist = (intPoint - cameraRay.orig).norm();

                    // Se este objeto estiver mais proximo da camera do que os que verificamos antes, entao guardamos uma referencia a ele
                    if(dist < minDist)
                    {
                        minDist = dist;
                        closestObject = currentObject;
                        closestIntersectionPoint = intPoint;
                        closestLocalNormal = localNormal;
                        closestLocalColor = localColor;
                    }
                }
            }
            
            // Calcular a iluminacao para o objeto mais proximo, assumindo que exista uma interseccao valida
            if(intersectionFound)
            {
                // Calcular a intensidade da iluminacao
                float intensity;
                Color3f lcolor;
                float red = 0.0, green = 0.0, blue = 0.0;
                bool validIllum = false;
                bool illumFound = false;
                for(auto currentLight : this->scene.getLightList())
                {
                    validIllum = currentLight->computeIllumination(closestIntersectionPoint, closestLocalNormal, this->scene.getObjectList(), closestObject, lcolor, intensity);
                    if(validIllum)
                    {
                        illumFound = true;
                        red += (lcolor[0]*intensity);
                        green += (lcolor[1]*intensity);
                        blue += (lcolor[2]*intensity);
                    }
                    else
                    {
                        red += (lcolor[0]*intensity);
                        green += (lcolor[1]*intensity);
                        blue += (lcolor[2]*intensity);
                    }
                }
                
                if(illumFound)
                {
                    red *= closestLocalColor[0];
                    green *= closestLocalColor[1];
                    blue *= closestLocalColor[2];
                    imgBuffer.at((ySize - y - 1)*xSize + x)[0] = red;
                    imgBuffer.at((ySize - y - 1)*xSize + x)[1] = green;
                    imgBuffer.at((ySize - y - 1)*xSize + x)[2] = blue;
                }
                else
                {
                    red = closestLocalColor[0]*intensity;
                    green = closestLocalColor[1]*intensity;
                    blue = closestLocalColor[2]*intensity;
                    imgBuffer.at((ySize - y - 1)*xSize + x)[0] = red;
                    imgBuffer.at((ySize - y - 1)*xSize + x)[1] = green;
                    imgBuffer.at((ySize - y - 1)*xSize + x)[2] = blue;
                }
            }
            else
            {
                Color3f bckColor = this->scene.getBackgroundColor();
                imgBuffer.at((ySize - y - 1)*xSize + x)[0] = bckColor[0];
                imgBuffer.at((ySize - y - 1)*xSize + x)[1] = bckColor[1];
                imgBuffer.at((ySize - y - 1)*xSize + x)[2] = bckColor[2];
            }
        }
    }

    //std::clog << "Cores da esfera do meio = " << this->scene.getObjectList().at(1)->baseColor << "\n";
    //std::clog << "ImgBuffer[115520] na cena = " << imgBuffer.at(115520) << "\n";
    // Passar o buffer da imagem para o objeto responsavel
    outputImage.bufferToImageFormat(imgBuffer);
    outputImage.writeImageFile("rayTracingEsfera.ppm");

    duration = std::chrono::high_resolution_clock::now() - stamp;
    std::cout << "Tempo gasto para renderizar a cena: " << duration.count() << " s\n";
    std::clog << "------------------------------------------------\n";

    return true;
}
