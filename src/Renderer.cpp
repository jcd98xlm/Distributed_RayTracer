#include "Renderer.hpp"
#include <iostream>
#include <chrono>

DBRT::Renderer::Renderer(const std::string &fileName)
{
    std::clog << "------------------------------------------------\n";
    std::clog << "------------------- Renderer -------------------\n";

    std::clog << "---------------- Criando a cena ----------------\n";
    this->scene.generateScene(fileName);
    //this->scene = new DBRT::Scene();
    // TODO: permitir criacao da cena a partir da leitura de um arquivo de descricao

    std::clog << "--------------- Criando a imagem ---------------\n";
    //this->outputImage = new DBRT::BinaryPPM();
    std::clog << "------------------------------------------------\n";
}

DBRT::Renderer::~Renderer()
{
}

bool DBRT::Renderer::render(ImageFile &outputImage)
{
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
    //float minDist = 1e6;
    //float maxDist = 0.0;
    for(unsigned int y=0; y<ySize; y++)
    //for(unsigned int x=0; x<xSize; x++)
    {
        for(unsigned int x=0; x<xSize; x++)
        //for(unsigned int y=0; y<ySize; y++)
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
            double minDist = 1e6;
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
                Color3f color;
                float red = 0.0, green = 0.0, blue = 0.0;
                bool validIllum = false;
                bool illumFound = false;
                for(auto currentLight : this->scene.getLightList())
                {
                    validIllum = currentLight->computeIllumination(closestIntersectionPoint, closestLocalNormal, this->scene.getObjectList(), closestObject, color, intensity);
                    if(validIllum)
                    {
                        illumFound = true;
                        red += color[0]*intensity;
                        green += color[1]*intensity;
                        blue += color[2]*intensity;

                        if((ySize - y -1)*xSize + x == 115520)
                        {
                            std::clog << "Pos xy [" << x << "," << y << "] - Red green blue :" << red << "," << green << "," << blue << "\n";                            
                        }
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
                    //outputImage.pixelData.at((ySize - y - 1)*xSize + x) = Color3f{red, green, blue};
                    //outputImage.pixelData.at((ySize - y - 1)*xSize + x).setPixelRGB(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
                    //outputImage.pixelData.at((ySize - y -1)*xSize + x).setPixelRGB(static_cast<uint8_t>(localColor[0]*intensity), static_cast<uint8_t>(localColor[1]*intensity), static_cast<uint8_t>(localColor[2]*intensity));
                }
            }
        }
    }

    std::clog << "Cores da esfera do meio = " << this->scene.getObjectList().at(1)->baseColor << "\n";
    std::clog << "ImgBuffer[115520] na cena = " << imgBuffer.at(115520) << "\n";
    // Passar o buffer da imagem para o objeto responsavel
    outputImage.bufferToImageFormat(imgBuffer);
    outputImage.writeImageFile("rayTracingEsfera.ppm");

    //std::clog << "Minimun distance: " << minDist << "  Maximun distance: " << maxDist << "\n";
    duration = std::chrono::high_resolution_clock::now() - stamp;
    std::cout << "\tTempo gasto para renderizar a cena: " << duration.count() << " s\n";

    return true;
}
